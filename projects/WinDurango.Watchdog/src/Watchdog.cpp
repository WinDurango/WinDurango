#include "Watchdog.h"

namespace WinDurango {
    Watchdog::Watchdog() {
        spdlog::set_pattern("[WD::Watchdog] - %^%l%$: %v");
    }

    std::jthread Watchdog::ObserveProcess(int pid) {
        if (m_observingProc) {
            spdlog::error("Failed to observer process {} another process is already being observed", pid);
            return std::jthread();
        }
        m_observingProc = true;
        std::jthread thread([this, pid](std::stop_token stop) {
            bool d_proc = DebugActiveProcess(pid);

            DebugSetProcessKillOnExit(FALSE);

            DEBUG_EVENT event{};
            HANDLE proc = nullptr;

            while (!stop.stop_requested()) {
                if (!WaitForDebugEvent(&event, INFINITE)) {
                    break;
                }

                if (event.dwDebugEventCode == OUTPUT_DEBUG_STRING_EVENT) {
                    spdlog::info("{}", event.u.DebugString.nDebugStringLength);
                } else if (event.dwDebugEventCode == EXCEPTION_DEBUG_EVENT) {
                    EXCEPTION_RECORD e_info = event.u.Exception.ExceptionRecord;
                    std::string e_type = GetExceptionType(e_info.ExceptionCode);
                    std::string dllName = GetDllPath((uint64_t)e_info.ExceptionAddress);

                    spdlog::warn("{}: {} - 0x{}", e_type, dllName, e_info.ExceptionAddress);

                    ShowCallstack(proc, m_loadedThreads[(uint64_t)event.dwThreadId]);
                } else if (event.dwDebugEventCode == LOAD_DLL_DEBUG_EVENT) {
                    LOAD_DLL_DEBUG_INFO e_info = event.u.LoadDll;
                    HANDLE dllName = e_info.hFile;
                    uint64_t dllAddr = (uint64_t)e_info.lpBaseOfDll;

                    char m_path[MAX_PATH] = "";
                    if (dllName) {
                        GetFinalPathNameByHandleA(dllName, m_path, MAX_PATH, 0);
                        CloseHandle(dllName);
                    }

                    m_loadedDLLs[dllAddr] = m_path;
                    spdlog::info("Loaded: {} - 0x{}", std::filesystem::path(m_path).filename().string(), dllAddr);
                } else if (event.dwDebugEventCode == UNLOAD_DLL_DEBUG_EVENT) {
                    UNLOAD_DLL_DEBUG_INFO e_info = event.u.UnloadDll;

                    uint64_t dllAddr = (uint64_t)e_info.lpBaseOfDll;
                    std::string dllName = GetDllPath(dllAddr);
                    m_loadedDLLs.erase(dllAddr);

                    spdlog::info("Loaded: {} - 0x{}", dllName, dllAddr);
                } else if (event.dwDebugEventCode == CREATE_PROCESS_DEBUG_EVENT) {
                    CREATE_PROCESS_DEBUG_INFO e_info = event.u.CreateProcessInfo;

                    uint64_t p_threadid = (uint64_t)event.dwThreadId;

                    proc = e_info.hProcess;
                    m_loadedThreads[p_threadid] = e_info.hThread;

                    SymInitialize(proc, nullptr, TRUE);
                    spdlog::info("Process Created: {}", p_threadid);
                } else if (event.dwDebugEventCode == CREATE_THREAD_DEBUG_EVENT) {
                    CREATE_THREAD_DEBUG_INFO e_info = event.u.CreateThread;

                    uint64_t p_threadid = (uint64_t)event.dwThreadId;

                    m_loadedThreads[p_threadid] = e_info.hThread;

                    std::string threadName = "Unknown";

                    PWSTR data;
                    HRESULT hr = GetThreadDescription(e_info.hThread, &data);
                    if (SUCCEEDED(hr)) {
                        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                        threadName = converter.to_bytes(data);
                        LocalFree(data);
                    }

                    spdlog::info("Thread Created: {} - {}", p_threadid, threadName);
                } else if (event.dwDebugEventCode == EXIT_THREAD_DEBUG_EVENT) {
                    uint64_t p_threadid = (uint64_t)event.dwThreadId;

                    std::string threadName = "Unknown";

                    PWSTR data;
                    HRESULT hr = GetThreadDescription(m_loadedThreads[p_threadid], &data);
                    if (SUCCEEDED(hr)) {
                        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                        threadName = converter.to_bytes(data);
                        LocalFree(data);
                    }

                    m_loadedThreads.erase(p_threadid);
                    spdlog::info("Thread Exit: {} - {}", p_threadid, threadName);
                }

                DWORD continueStatus = DBG_CONTINUE;
                if (event.dwDebugEventCode == EXCEPTION_DEBUG_EVENT) {
                    continueStatus = DBG_EXCEPTION_NOT_HANDLED;
                }

                if (event.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) {
                    break;
                }

                ContinueDebugEvent(event.dwProcessId, event.dwThreadId, continueStatus);
            }
        });

        return thread;
    }

    std::string Watchdog::GetExceptionType(DWORD e_code) {
        std::string e_type = "UNKNOWN";
        
        switch (e_code) {
            case EXCEPTION_ACCESS_VIOLATION:
                e_type = "Access Violation";
                break;
            case EXCEPTION_BREAKPOINT:
                e_type = "Breakpoint";
                break;
            case 0xE06D7363:
                e_type = "C++ Exception";
                break;
            default:
                e_type = "Unknown Exception";
                break;
        }

        return e_type;
    }
    
    std::string Watchdog::GetDllPath(uint64_t addr) {
        std::string dllName = "UNKNOWN";

        auto it = m_loadedDLLs.upper_bound(addr);
        if (it == m_loadedDLLs.begin()) {
            dllName = "UNKNOWN";
        } else {
            --it;
            dllName = it->second;
        }

        return std::filesystem::path(dllName).filename().string();
    }

    void Watchdog::ShowCallstack(HANDLE proc, HANDLE thread) {
        CONTEXT ctx{};
        ctx.ContextFlags = CONTEXT_FULL;
        GetThreadContext(thread, &ctx);

        STACKFRAME64 frame{};
        frame.AddrPC.Offset = ctx.Rip;
        frame.AddrPC.Mode = AddrModeFlat;
        frame.AddrFrame.Offset = ctx.Rbp;
        frame.AddrFrame.Mode = AddrModeFlat;
        frame.AddrStack.Offset = ctx.Rsp;
        frame.AddrStack.Mode = AddrModeFlat;

        for (int i = 0; i < 32; i++) {
            bool sw = StackWalk64(IMAGE_FILE_MACHINE_AMD64, proc, thread, &frame, &ctx, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr);
            
            if (!sw || frame.AddrPC.Offset == 0) {
                break;
            }

            char b_symbol[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
            SYMBOL_INFO* symbol = reinterpret_cast<SYMBOL_INFO*>(b_symbol);
            symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
            symbol->MaxNameLen = MAX_SYM_NAME;

            DWORD64 disp = 0;
            std::string symName = "unknown";
            if (SymFromAddr(proc, frame.AddrPC.Offset, &disp, symbol)) {
                symName = std::string(symbol->Name) + " + 0x" + std::to_string(disp);
            }

            std::string mod = GetDllPath((uint64_t)frame.AddrPC.Offset);

            spdlog::warn(" - 0x{:x} {} [{}]", frame.AddrPC.Offset, symName, mod);
        }
    }
}
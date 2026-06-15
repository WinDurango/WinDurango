#pragma once
#include <string>
#include <locale>
#include <codecvt>
#include <map>
#include <thread>
#include <filesystem>
#include <spdlog/spdlog.h>

/*
 * TODO: Make a ver for other systems
*/
#include <Windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "DbgHelp.lib")

namespace WinDurango {
    class Watchdog {
    public:
        Watchdog();

        std::jthread ObserveProcess(int pid);
    private:
        std::string GetExceptionType(DWORD e_code);
        std::string GetDllPath(uint64_t addr);
        void ShowCallstack(HANDLE proc, HANDLE thread);

        std::map<uint64_t, std::string> m_loadedDLLs;
        std::map<uint64_t, HANDLE> m_loadedThreads;
        bool m_observingProc = false;
    };
}
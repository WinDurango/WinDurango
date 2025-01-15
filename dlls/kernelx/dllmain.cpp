#include "pch.h"
#include "hooks.h"
#include "ForzaThreadHook_X.h"
#include "kernelx.h"
#include <Windows.h>

// note from unixian: i used this since using appxlauncher requires me attaching to the game after it launches
#define WINDURANGO_WAIT_FOR_DEBUGGER 0

//Rodrigo Todescatto: For debbuging Forza.
#define RETURN_IF_FAILED(hr) if (FAILED(hr)) return hr
#define FORZADEBUG

#define RETURN_HR(hr) return hr
#define RETURN_LAST_ERROR_IF(cond) if (cond) return HRESULT_FROM_WIN32(GetLastError())

inline HRESULT WINAPI GetActivationFactoryRedirect(PCWSTR str, REFIID riid, void** ppFactory)
{
	HRESULT hr;
	HSTRING className;
	HSTRING_HEADER classNameHeader;

	if (FAILED(hr = WindowsCreateStringReference(str, wcslen(str), &classNameHeader, &className)))
		return hr;

	//printf("GetActivationFactoryRedirect: %S\n", str);

	hr = RoGetActivationFactory_Hook(className, riid, ppFactory);
	WindowsDeleteString(className);
	return hr;
}

HRESULT XWineGetImport(_In_opt_ HMODULE Module, _In_ HMODULE ImportModule, _In_ LPCSTR Import, _Out_ PIMAGE_THUNK_DATA * pThunk)
{
	if (ImportModule == nullptr)
		RETURN_HR(E_INVALIDARG);

	if (pThunk == nullptr)
		RETURN_HR(E_POINTER);

	if (Module == nullptr)
		Module = GetModuleHandleW(nullptr);

	auto dosHeader = (PIMAGE_DOS_HEADER)Module;
	auto ntHeaders = (PIMAGE_NT_HEADERS)((PBYTE)Module + dosHeader->e_lfanew);
	auto directory = &ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	auto peImports = (PIMAGE_IMPORT_DESCRIPTOR)((PBYTE)Module + directory->VirtualAddress);

	for (size_t i = 0; peImports[i].Name; i++)
	{
		if (GetModuleHandleA((LPCSTR)((PBYTE)Module + peImports[i].Name)) != ImportModule)
			continue;

		auto iatThunks = (PIMAGE_THUNK_DATA)((PBYTE)Module + peImports[i].FirstThunk);
		auto intThunks = (PIMAGE_THUNK_DATA)((PBYTE)Module + peImports[i].OriginalFirstThunk);

		for (size_t j = 0; intThunks[j].u1.AddressOfData; j++)
		{
			if ((intThunks[j].u1.AddressOfData & IMAGE_ORDINAL_FLAG) != 0)
			{
				if (!IS_INTRESOURCE(Import))
					continue;

				if (((intThunks[j].u1.Ordinal & ~IMAGE_ORDINAL_FLAG) == (ULONG_PTR)Import))
				{
					*pThunk = &iatThunks[j];
					return S_OK;
				}

				continue;
			}

			if (strcmp(((PIMAGE_IMPORT_BY_NAME)((PBYTE)Module + intThunks[j].u1.AddressOfData))->Name, Import))
				continue;

			*pThunk = &iatThunks[j];
			return S_OK;
		}
	}

	*pThunk = nullptr;
	return (E_FAIL);
}

HRESULT XWinePatchImport(_In_opt_ HMODULE Module, _In_ HMODULE ImportModule, _In_ PCSTR Import, _In_ PVOID Function)
{
	DWORD protect;
	PIMAGE_THUNK_DATA pThunk;
	RETURN_IF_FAILED(XWineGetImport(Module, ImportModule, Import, &pThunk));
	RETURN_LAST_ERROR_IF(!VirtualProtect(&pThunk->u1.Function, sizeof(ULONG_PTR), PAGE_READWRITE, &protect));
	pThunk->u1.Function = (ULONG_PTR)Function;
	RETURN_LAST_ERROR_IF(!VirtualProtect(&pThunk->u1.Function, sizeof(ULONG_PTR), protect, &protect));
	return S_OK;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID reserved)
{
	winrt::hstring GamePackage = winrt::Windows::ApplicationModel::Package::Current().Id().FamilyName();

	InitializeCriticalSection(&XMemSetAllocationHooksLock_X);

	if (DetourIsHelperProcess()) return TRUE;

	if (dwReason == DLL_PROCESS_ATTACH)
	{
#ifdef _DEBUG
		// note from unixian: some games do not create a console window, so if one isn't already created, we create one.
		if (!GetConsoleWindow())
		{
			AllocConsole();
			FILE* stream;
			freopen_s(&stream, "CONOUT$", "w", stdout);
			SetConsoleTitleA("WinDurango Debug Console");
		}
		
#ifdef FORZADEBUG
		//Rodrigo Todescatto: Forza Horizon 2 Demo.
		if (GamePackage == L"265E1020-Anthem_8wekyb3d8bbwe")
		{
			printf("Forza Horizon 2 Demo\n");
    			*(void**)&P_StartForzaThread_X = (char*)GetModuleHandleW(nullptr) + 0xFE6920;
    			RETURN_IF_FAILED(HRESULT_FROM_WIN32(DetourTransactionBegin()));
    			RETURN_IF_FAILED(HRESULT_FROM_WIN32(DetourAttach((void**)&P_StartForzaThread_X, &D_StartForzaThread_X)));
    			RETURN_IF_FAILED(HRESULT_FROM_WIN32(DetourTransactionCommit()));
		}
		//Rodrigo Todescatto: Forza Horizon 2.
		if (GamePackage == L"Anthem_8wekyb3d8bbwe")
		{
			printf("Forza Horizon 2\n");
    			*(void**)&P_StartForzaThread_X = (char*)GetModuleHandleW(nullptr) + 0x1081A90;
    			RETURN_IF_FAILED(HRESULT_FROM_WIN32(DetourTransactionBegin()));
    			RETURN_IF_FAILED(HRESULT_FROM_WIN32(DetourAttach((void**)&P_StartForzaThread_X, &D_StartForzaThread_X)));
    			RETURN_IF_FAILED(HRESULT_FROM_WIN32(DetourTransactionCommit()));
    			*(void**)&P_FmodThreadProc_X = (char*)GetModuleHandleW(nullptr) + 0x19D3F80;
    			RETURN_IF_FAILED(HRESULT_FROM_WIN32(DetourTransactionBegin()));
    			RETURN_IF_FAILED(HRESULT_FROM_WIN32(DetourAttach((void**)&P_FmodThreadProc_X, &D_FmodThreadProc_X)));
    			RETURN_IF_FAILED(HRESULT_FROM_WIN32(DetourTransactionCommit()));
		}
		//Rodrigo Todescatto: Forza Motorsport 5.
		if (GamePackage == L"Forza_8wekyb3d8bbwe")
		{
			printf("Forza Motorsport 5");
		}
		//Rodrigo Todescatto: Forza Horizon 2 Presents Fast & Furious.
		if (GamePackage == L"Spire_8wekyb3d8bbwe")
		{
			printf("Forza Horizon 2 Presents Fast & Furious");
		}
#endif

#if WINDURANGO_WAIT_FOR_DEBUGGER
		printf("Waiting for debugger...\n");
		while (!IsDebuggerPresent())
			Sleep(1);
#endif

#endif

		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		//DetourAttach(&reinterpret_cast<PVOID&>(TrueRoGetActivationFactory), RoGetActivationFactory_Hook);
		
		// games uses different vccorlib versions so just HardCoding vccorlib140 won't work
		// so we can just check if any of corlib modules are loaded and use that
		// (add more of them as we find in games)
		std::array<const wchar_t*, 3> modules = { L"vccorlib140.dll", L"vccorlib110.dll", L"vccorlib120.dll" };
		HMODULE hModule = nullptr;
		for (auto& module : modules)
		{
			hModule = GetModuleHandleW(module);
			if (hModule != nullptr)
			{
				break;
			}
		}

		XWinePatchImport(GetModuleHandleW(nullptr), hModule, "?GetActivationFactoryByPCWSTR@@YAJPEAXAEAVGuid@Platform@@PEAPEAX@Z", GetActivationFactoryRedirect);

		DetourAttach(&reinterpret_cast<PVOID&>(TrueOpenFile), OpenFile_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueCreateFileW), CreateFileW_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesW), GetFileAttributesW_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesExW), GetFileAttributesExW_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueFindFirstFileW), FindFirstFileW_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueDeleteFileW), DeleteFileW_Hook);
		//DetourAttach(&reinterpret_cast<PVOID&>(TrueLoadLibraryExW), LoadLibraryExW_Hook);

		DetourTransactionCommit();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&reinterpret_cast<PVOID&>(TrueRoGetActivationFactory), RoGetActivationFactory_Hook);
		
		DetourDetach(&reinterpret_cast<PVOID&>(TrueOpenFile), OpenFile_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueCreateFileW), CreateFileW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesW), GetFileAttributesW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesExW), GetFileAttributesExW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueFindFirstFileW), FindFirstFileW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueDeleteFileW), DeleteFileW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueLoadLibraryExW), LoadLibraryExW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueLoadLibraryW), LoadLibraryW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueLoadLibraryExA), LoadLibraryExA_Hook);

		DetourTransactionCommit();
	}

	return TRUE;
}

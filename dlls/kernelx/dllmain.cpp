#include "pch.h"
#include "hooks.h"
#include "ForzaThreadHook_X.h"
#include "kernelx.h"
#include <Windows.h>
#include "Shlwapi.h"
#include <audioclient.h>
#include "Allocation.h"
// note from unixian: i used this since using appxlauncher requires me attaching to the game after it launches
// #define WINDURANGO_WAIT_FOR_DEBUGGER 1
#define WINDURANGO_WAIT_FOR_DEBUGGER 0

//Rodrigo Todescatto: For debbuging Forza.
#define RETURN_IF_FAILED(hr) if (FAILED(hr)) return hr
#define FORZADEBUG

std::vector<HMODULE> loadedMods;

inline void LoadMods()
{
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(GetModuleHandleW(nullptr), path, MAX_PATH);
	PathRemoveFileSpecW(path);
	PathAppendW(path, L"Mods");
	
	/*if (!PathFileExistsW(path))
	{
		BOOL ret = CreateDirectoryW(path, nullptr);
		
		if (!ret)
		{
			DWORD error = GetLastError();
			printf("Error creating Mods directory: %d\n", error);
		}
		
	}*/
	if (!PathFileExistsW(path))
	{
		return;
	}
	WCHAR searchPath[MAX_PATH];
	wcscpy_s(searchPath, path);
	PathAppendW(searchPath, L"\\*.dll");
	WIN32_FIND_DATAW findData;
	HANDLE hFind = FindFirstFileW(searchPath, &findData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				WCHAR modPath[MAX_PATH];
				wcscpy_s(modPath, path);
				PathAppendW(modPath, findData.cFileName);
				HMODULE loadedModule = LoadLibraryW(modPath);
				if (loadedModule != nullptr)
				{
					loadedMods.push_back(loadedModule);
					printf("Loaded mod: %S\n", modPath);
				}
			}
		} while (FindNextFileW(hFind, &findData));
		FindClose(hFind);
	}
}	

inline void UnLoadMods()
{
	for (auto mod : loadedMods)
	{
		FreeLibrary(mod);
	}

}
#include <winrt/Windows.Services.Store.h>
#include <winrt/Windows.Foundation.h>

winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> GetProductIdAsync()
{
	auto storeContext = winrt::Windows::Services::Store::StoreContext::GetDefault();
	auto appLicense = co_await storeContext.GetAppLicenseAsync();
	winrt::hstring productId = appLicense.SkuStoreId();

	co_return productId;
}
std::string GetPackageName() {
	winrt::hstring GamePackage = winrt::Windows::ApplicationModel::Package::Current().Id().FamilyName();
	std::string packageName = winrt::to_string(GamePackage);

	size_t underscorePos = packageName.find('_');
	if (underscorePos != std::string::npos) {
		packageName = packageName.substr(0, underscorePos);
	}

	return packageName;
}
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID reserved)
{
	winrt::hstring GamePackage = winrt::Windows::ApplicationModel::Package::Current().Id().FamilyName();
	std::string packageName = GetPackageName();
	InitializeCriticalSection(&XmpAllocationHookLock);

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
		if (packageName == "HappyDungeons")
		{
		}
		if (packageName == "HappyWars")
		{
			printf("Happy Wars Detected!");
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

		XPatchImport(GetModuleHandleW(nullptr), GetRuntimeModule(), "?GetActivationFactoryByPCWSTR@@YAJPEAXAEAVGuid@Platform@@PEAPEAX@Z", GetActivationFactoryRedirect);

		DetourAttach(&reinterpret_cast<PVOID&>(TrueOpenFile), OpenFile_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueCreateDirectoryA), CreateDirectoryA_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueCreateFileW), CreateFileW_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueCreateFile2), CreateFile2_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesW), GetFileAttributesW_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesExW), GetFileAttributesExW_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueFindFirstFileW), FindFirstFileW_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueDeleteFileW), DeleteFileW_Hook);
		//DetourAttach(&reinterpret_cast<PVOID&>(TrueLoadLibraryExW), LoadLibraryExW_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueLoadLibraryW), LoadLibraryW_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueLoadLibraryExA), LoadLibraryExA_Hook);
		DetourAttach(&reinterpret_cast<PVOID&>(TrueCoCreateInstance), CoCreateInstance_hook);

		DetourTransactionCommit();


		LoadMods();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&reinterpret_cast<PVOID&>(TrueRoGetActivationFactory), RoGetActivationFactory_Hook);
		
		DetourDetach(&reinterpret_cast<PVOID&>(TrueOpenFile), OpenFile_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueCreateDirectoryA), CreateDirectoryA_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueCreateFileW), CreateFileW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueCreateFile2), CreateFile2_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesW), GetFileAttributesW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueGetFileAttributesExW), GetFileAttributesExW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueFindFirstFileW), FindFirstFileW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueDeleteFileW), DeleteFileW_Hook);
		//DetourDetach(&reinterpret_cast<PVOID&>(TrueLoadLibraryExW), LoadLibraryExW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueLoadLibraryW), LoadLibraryW_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueLoadLibraryExA), LoadLibraryExA_Hook);
		DetourDetach(&reinterpret_cast<PVOID&>(TrueCoCreateInstance), CoCreateInstance_hook);

		DetourTransactionCommit();

		UnLoadMods();
	}

	return TRUE;
}

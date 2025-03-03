#include "d3d11_x.h"
#include <cstdio>
#include <mutex>
#include "overlay/overlay.h"
#include <d3d11.h>
#include "device_context_x.h"
#include "device_x.h"
#include "../common/debug.h"

HRESULT CreateDevice(UINT Flags, wdi::ID3D11Device** ppDevice, wdi::ID3D11DeviceContext** ppImmediateContext)
{
    D3D_FEATURE_LEVEL featurelevels[] = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };

    ID3D11Device2* device2{};
    ID3D11DeviceContext2* device_context2{};

    auto flags = Flags & CREATE_DEVICE_FLAG_MASK;

#ifdef _DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags, featurelevels, _ARRAYSIZE(featurelevels), D3D11_SDK_VERSION, reinterpret_cast<ID3D11Device**>(ppDevice), NULL, reinterpret_cast<ID3D11DeviceContext**>(ppImmediateContext));
    if (SUCCEEDED(hr))
    {
        // get dx11.2 feature level, since that's what dx11.x inherits from
        if (ppDevice != nullptr)
        {
            (*ppDevice)->QueryInterface(IID_PPV_ARGS(&device2));
            *ppDevice = reinterpret_cast<wdi::ID3D11Device*>(new wd::device_x(device2));
        }

        if (ppImmediateContext != nullptr)
        {
            (*ppImmediateContext)->QueryInterface(IID_PPV_ARGS(&device_context2));
            *ppImmediateContext = reinterpret_cast<wdi::ID3D11DeviceContext*>(new wd::device_context_x(device_context2));
        }
    }
    else
    {
        printf("failed to assign wrapped device, result code 0x%X, error code 0x%X\n", hr, GetLastError( ));
    }

    return hr;
}
HRESULT __stdcall D3DMapEsramMemory_X(UINT Flags, VOID* pVirtualAddress, UINT NumPages, const UINT* pPageList)
{
    DEBUGPRINT( );
    HANDLE hDevice = INVALID_HANDLE_VALUE;
    HRESULT result = 0;
    DWORD accessFlags = 0;
    HANDLE deviceHandle = INVALID_HANDLE_VALUE;

    // Open a handle to the VdKmd device
    hDevice = CreateFileW(L"\\\\.\\VdKmd", GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hDevice == INVALID_HANDLE_VALUE)
    {
        DWORD lastError = GetLastError( );
        result = HRESULT_FROM_WIN32(lastError);
    }
    else
    {
        // Call DeviceIoControlHelper to check access
        result = DeviceIoControlHelper(hDevice);
        if (SUCCEEDED(result))
        {
            deviceHandle = hDevice;
            result = S_OK;
        }
        else
        {
            CloseHandle(hDevice);
        }
    }

    if (SUCCEEDED(result))
    {
        // Set access flags based on Flags parameter
        if (Flags & 1)
        {
            accessFlags = 0x20000000;
        }
        else if (Flags & 2)
        {
            accessFlags = 0x80000000;
        }

        // Map the address to ESRAM
        result = VdMapAddressToEsram(deviceHandle, accessFlags, (uintptr_t) pVirtualAddress, NumPages, pPageList);

        // Close device handle after operation
        CloseHandle(deviceHandle);
    }

    return result;
}

HRESULT __stdcall VdMapAddressToEsram(
    HANDLE hDevice,
    DWORD flags,
    uintptr_t virtualAddress,
    UINT numPages,
    const UINT* pageList)
{
    // Early validation checks
    if (hDevice == INVALID_HANDLE_VALUE || numPages == 0 || !virtualAddress || (flags & 0x5FFFFFFF) != 0)
        return HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER); // 2147942487 (0x80070057)

    unsigned int pageLimit = (flags & 0x20000000) ? 511 : 7;

    if (((flags & 0x20000000) && (virtualAddress == 0)) ||
        (!(flags & 0x20000000) && (virtualAddress & 0x3FFFFF) != 0) ||
        (numPages > pageLimit + 1))
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);
    }

    // Initialize input buffer
    struct
    {
        DWORD flags;
        uintptr_t virtualAddress;
        UINT numPages;
        UINT pageData[ 512 ]; // Maximum possible pages
    } inBuffer = { 0 };

    memset(&inBuffer, 0, sizeof(inBuffer));
    inBuffer.flags = flags;
    inBuffer.virtualAddress = virtualAddress;
    inBuffer.numPages = numPages;

    // Copy page list if provided
    if (pageList)
    {
        for (unsigned int i = 0; i < numPages; ++i)
        {
            if (pageList[ i ] > pageLimit)
                return HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER); // Invalid page number
            inBuffer.pageData[ i ] = pageList[ i ];
        }
    }
    else
    {
        inBuffer.flags |= 1; // If page list is null, modify flags
    }

    DWORD bytesReturned = 0;

    // Send IOCTL request to device
    if (DeviceIoControl(hDevice, 0x7900C1ACu, &inBuffer, sizeof(inBuffer), nullptr, 0, &bytesReturned, nullptr))
    {
        return S_OK;
    }

    // If DeviceIoControl fails, retrieve and return the error code
    DWORD lastError = GetLastError( );
    return HRESULT_FROM_WIN32(lastError);
}
HRESULT __stdcall DeviceIoControlHelper(HANDLE hDevice)
{
    DWORD bytesReturned = 0;

    // Check if the handle is invalid
    if (hDevice == INVALID_HANDLE_VALUE)
        return HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE); // 2147942487 (0x80070006)

    // Perform the DeviceIoControl operation
    if (DeviceIoControl(hDevice, 0x7900C190u, nullptr, 0, nullptr, 0, &bytesReturned, nullptr))
    {
        return (bytesReturned != 0) ? E_FAIL : S_OK; // 0x80004005 (Generic failure) if bytesReturned is not zero
    }

    // Get last error if DeviceIoControl fails
    DWORD lastError = GetLastError( );
    if (lastError > 0)
    {
        return HRESULT_FROM_WIN32(lastError);
    }

    return lastError;
}
HRESULT _stdcall D3DQuerySEQCounters_X(D3D_SEQ_COUNTER_DATA* pData)
{
    return E_NOTIMPL;
}

HRESULT _stdcall D3DUploadCustomMicrocode_X(
    _In_ UINT32 MicrocodeVersion,
    _In_ SIZE_T CeMicrocodeSizeBytes,
    _In_reads_bytes_(CeMicrocodeSizeBytes) const void* pCeMicrocode,
    _In_ SIZE_T PfpMicrocodeSizeBytes,
    _In_reads_bytes_(PfpMicrocodeSizeBytes) const void* pPfpMicrocode,
    _In_ SIZE_T MeMicrocodeSizeBytes,
    _In_reads_bytes_(MeMicrocodeSizeBytes) const void* pMeMicrocode)
{
    return E_NOTIMPL;
}

HRESULT __stdcall D3D11XCreateDeviceXAndSwapChain1_X(const D3D11X_CREATE_DEVICE_PARAMETERS* pParameters,
    const DXGI_SWAP_CHAIN_DESC1* pSwapChainDesc, IDXGISwapChain1** ppSwapChain,
    // ID3D11DeviceX** ppDevice, ID3D11DeviceContextX** ppImmediateContext
    ID3D11Device** ppDevice, ID3D11DeviceContext** ppImmediateContext)
{
    // D3D11_CREATE_DEVICE_VIDEO_EXCLUSIVE
    if ((pParameters->Flags & 0x10000) != 0 || !ppSwapChain)
    {
        return E_INVALIDARG;
    }

    printf("!!! Game is trying to initialize D3D11 through D3D11X !!!");
    printf("SDK Version: %d\n", pParameters->Version);
    return D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, 0, pParameters->Flags & CREATE_DEVICE_FLAG_MASK, NULL, NULL, D3D11_SDK_VERSION, ppDevice, NULL, ppImmediateContext);
}

HRESULT __stdcall D3DAllocateGraphicsMemory_X(SIZE_T SizeBytes, SIZE_T AlignmentBytes, UINT64 DesiredGpuVirtualAddress, UINT Flags, void** ppAddress)
{
    DWORD Protect = 0;

    if (!ppAddress || AlignmentBytes > 0x20000)
        return E_INVALIDARG;

    // @Patoke todo: these 2 types in the XBOX also use the MEM_GRAPHICS flag
    //  meaning it's allocating GPU memory, fix
    DWORD AllocType = MEM_4MB_PAGES | MEM_COMMIT | MEM_RESERVE;
    if (AlignmentBytes <= 0x10000)
        AllocType = MEM_LARGE_PAGES | MEM_COMMIT | MEM_RESERVE;

    switch(Flags) {
    case D3D11_GRAPHICS_MEMORY_ACCESS_CPU_CACHE_COHERENT:
        // @Patoke note: this also includes the PAGE_GPU_COHERENT flag in the XBOX
        Protect = PAGE_READWRITE;
        break;
    case D3D11_GRAPHICS_MEMORY_ACCESS_CPU_WRITECOMBINE_NONCOHERENT:
        Protect = PAGE_READWRITE | PAGE_WRITECOMBINE;
        break;
    case D3D11_GRAPHICS_MEMORY_ACCESS_CPU_CACHE_NONCOHERENT_GPU_READONLY:
        return E_INVALIDARG;
    default:
        // @Patoke note: this also includes the PAGE_GPU_READONLY flag in the XBOX
        Protect = PAGE_READWRITE;
    }

    *ppAddress = VirtualAlloc((LPVOID) DesiredGpuVirtualAddress, SizeBytes, AllocType, Protect);

    return !*ppAddress ? E_OUTOFMEMORY : S_OK;
}

HRESULT __stdcall D3DConfigureVirtualMemory_X(_Inout_ D3D11X_VIRTUAL_MEMORY_CONFIGURATION* pVMConfiguration)
{
    return E_NOTIMPL;
}

void __stdcall D3DFlushEntireCpuCache_X()
{
    FlushInstructionCache(GetCurrentProcess( ), NULL, NULL);
}

HRESULT __stdcall D3DFreeGraphicsMemory_X(void* pAddress)
{
    // @Patoke todo: this should be freeing GPU memory
    VirtualFree(pAddress, NULL, MEM_RELEASE);
    return S_OK;
}


HRESULT __stdcall DXGIXGetFrameStatistics_X(
    _In_ UINT NumberFramesRequested,
    _Out_writes_(NumberFramesRequested) DXGIX_FRAME_STATISTICS* pStats)
{
    return E_NOTIMPL;
}

HRESULT _stdcall DXGIXPresentArray_X(
    _In_ UINT SyncInterval,
    _In_ UINT PresentImmediateThreshold,
    _In_ UINT Flags,
    _In_ UINT NumSwapChains,
    _In_ IDXGISwapChain1* const* ppSwapChain,
    _In_ const DXGIX_PRESENTARRAY_PARAMETERS* pPresentParameters)
{
    printf("[d3d11_x] !!! STUBBED: DXGIXPresentArray !!!");
    return E_NOTIMPL;
}

HRESULT __stdcall DXGIXSetFrameNotification_X(
    _In_ DXGIX_FRAME_NOTIFICATION NotificationType,
    _In_ HANDLE hEvent)
{
    return E_NOTIMPL;
}

HRESULT __stdcall DXGIXSetVLineNotification_X(
    _In_ DXGIX_VLINECOUNTER VLineCounter,
    _In_ UINT32 VLineNumber,
    _In_opt_ HANDLE hEvent)
{
    return E_NOTIMPL;
}

HRESULT __stdcall D3D11CreateDevice_X(
    _In_opt_ IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _Out_opt_ wdi::ID3D11Device** ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    _Out_opt_ wdi::ID3D11DeviceContext** ppImmediateContext)
{
    printf("!!! Game is trying to initialize D3D11 through NORMAL D3D11 !!!\n");
    printf("SDK Version: %d\n", SDKVersion);

    if (SDKVersion != D3D11_SDK_VERSION)
    {
        printf("SDK Version mismatch: %d, correcting to %d\n", SDKVersion, D3D11_SDK_VERSION);
        SDKVersion = D3D11_SDK_VERSION;
    }

    D3D_FEATURE_LEVEL featurelevels[] = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };

    ID3D11Device2* device2{};
    ID3D11DeviceContext2* device_context2{};
    auto flags = Flags & CREATE_DEVICE_FLAG_MASK;
#ifdef _DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    HRESULT hr = D3D11CreateDevice(pAdapter, DriverType, Software, flags, featurelevels, _ARRAYSIZE(featurelevels), SDKVersion, (ID3D11Device**) ppDevice, pFeatureLevel, (ID3D11DeviceContext**) ppImmediateContext);


    if (SUCCEEDED(hr))
    {
        // get dx11.2 feature level, since that's what dx11.x inherits from
        if (ppDevice != nullptr)
        {
            (*ppDevice)->QueryInterface(IID_PPV_ARGS(&device2));
            *ppDevice = reinterpret_cast<wdi::ID3D11Device*>(new wd::device_x(device2));
        }

        if (ppImmediateContext != nullptr)
        {
            (*ppImmediateContext)->QueryInterface(IID_PPV_ARGS(&device_context2));
            *ppImmediateContext = reinterpret_cast<wdi::ID3D11DeviceContext*>(new wd::device_context_x(device_context2));
        }
    }
    else
    {
        printf("failed to assign wrapped device, result code 0x%X, error code 0x%X\n", hr, GetLastError( ));
    }

    return hr;
}

HRESULT __stdcall D3D11XCreateDeviceX_X(
    _In_ const D3D11X_CREATE_DEVICE_PARAMETERS* pParameters,
    _Out_opt_ wdi::ID3D11Device** ppDevice,
    _Out_opt_ wdi::ID3D11DeviceContext** ppImmediateContext)
{
    printf("!!! Game is trying to initialize D3D11 through D3D11X !!!");
    printf("SDK Version: %d\n", pParameters->Version);

	return CreateDevice(pParameters->Flags, ppDevice, ppImmediateContext);
}

HRESULT __stdcall D3D11CreateDeviceAndSwapChain_X(
    _In_opt_ IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _In_opt_ CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    _Out_opt_ IDXGISwapChain** ppSwapChain,
    _Out_opt_ ID3D11Device** ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    _Out_opt_ ID3D11DeviceContext** ppImmediateContext)
{
    printf("!!! Game is trying to initialize D3D11 through NORMAL D3D11 !!!");
    printf("SDK Version: %d\n", SDKVersion);
    return D3D11CreateDeviceAndSwapChain(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
}



std::mutex g_NotifyMutex;

// this function exists for other WinDurango dlls to notify the graphics component of an action
// for right now, this is used for signaling when a keyboard is requested by a game and rendering it using ImGUI
void WD11XNotify_X(WDEVENT_TYPE event)
{
    const std::lock_guard lock(g_NotifyMutex);
	printf("[d3d11_x] received notification\n");

    switch (event)
    {
	case WDEVENT_TYPE_INVALID:
		throw std::exception("this shouldn't happen, check code that sends events.");
	case WDEVENT_TYPE_KEYBOARD_ENGAGE:
		printf("[d3d11_x] keyboard engage\n");
		wd::g_Overlay->EnableKeyboard( );
		break;
    }
}

void WDWaitForKeyboard(const char** outText)
{
	printf("[d3d11_x] waiting for keyboard\n");

    WaitForSingleObject(wd::g_KeyboardFinished, INFINITE);

	*outText = wd::g_KeyboardText;
}
#include "MMDeviceEnumerator.h"

// MMDeviceEnumerator
HRESULT __stdcall MMDeviceEnumeratorWrapper::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == __uuidof(IMMXboxDeviceEnumerator))
    {
        *ppvObject = new MMXboxDeviceEnumerator(this);
        AddRef();
        return S_OK;
    }

    return m_realEnumerator->QueryInterface(riid, ppvObject);
}

ULONG __stdcall MMDeviceEnumeratorWrapper::AddRef(void)
{
    m_realEnumerator->AddRef();
    return InterlockedIncrement(&m_RefCount);
}

ULONG __stdcall MMDeviceEnumeratorWrapper::Release(void)
{
    m_realEnumerator->Release();
    ULONG RefCount = InterlockedDecrement(&m_RefCount);
    if (!RefCount)
        delete this;
    return RefCount;
}

HRESULT __stdcall MMDeviceEnumeratorWrapper::EnumAudioEndpoints(EDataFlow dataFlow, DWORD dwStateMask,
                                                                IMMDeviceCollection **ppDevices)
{
    if (dwStateMask == 31)
        dwStateMask = DEVICE_STATE_ACTIVE;

    return m_realEnumerator->EnumAudioEndpoints(dataFlow, dwStateMask, ppDevices);
}

HRESULT __stdcall MMDeviceEnumeratorWrapper::GetDefaultAudioEndpoint(EDataFlow dataFlow, ERole role,
                                                                     IMMDevice **ppEndpoint)
{
    return m_realEnumerator->GetDefaultAudioEndpoint(dataFlow, role, ppEndpoint);
}

HRESULT __stdcall MMDeviceEnumeratorWrapper::GetDevice(LPCWSTR pwstrId, IMMDevice **ppDevice)
{
    return m_realEnumerator->GetDevice(pwstrId, ppDevice);
}

HRESULT __stdcall MMDeviceEnumeratorWrapper::RegisterEndpointNotificationCallback(IMMNotificationClient *pClient)
{
    return m_realEnumerator->RegisterEndpointNotificationCallback(pClient);
}

HRESULT __stdcall MMDeviceEnumeratorWrapper::UnregisterEndpointNotificationCallback(IMMNotificationClient *pClient)
{
    return m_realEnumerator->UnregisterEndpointNotificationCallback(pClient);
}


// MMXboxDeviceEnumerator
HRESULT __stdcall MMXboxDeviceEnumerator::QueryInterface(REFIID riid, void **ppvObject)
{
    return m_realEnumerator->QueryInterface(riid, ppvObject);
}

ULONG __stdcall MMXboxDeviceEnumerator::AddRef(void)
{
    m_realEnumerator->AddRef();
    return InterlockedIncrement(&m_RefCount);
}

ULONG __stdcall MMXboxDeviceEnumerator::Release(void)
{
    m_realEnumerator->Release();
    ULONG RefCount = InterlockedDecrement(&m_RefCount);
    if (!RefCount)
        delete this;
    return RefCount;
}

HRESULT __stdcall MMXboxDeviceEnumerator::EnumAudioEndpoints(EDataFlow dataFlow, DWORD dwStateMask,
                                                             IMMDeviceCollection **ppDevices)
{
    return m_realEnumerator->EnumAudioEndpoints(dataFlow, dwStateMask, ppDevices);
}

HRESULT __stdcall MMXboxDeviceEnumerator::GetDefaultAudioEndpoint(EDataFlow dataFlow, ERole role,
                                                                  IMMDevice **ppEndpoint)
{
    return m_realEnumerator->GetDefaultAudioEndpoint(dataFlow, role, ppEndpoint);
}

HRESULT __stdcall MMXboxDeviceEnumerator::GetDevice(LPCWSTR pwstrId, IMMDevice **ppDevice)
{
    return m_realEnumerator->GetDevice(pwstrId, ppDevice);
}

HRESULT __stdcall MMXboxDeviceEnumerator::RegisterEndpointNotificationCallback(IMMNotificationClient *pClient)
{
    return m_realEnumerator->RegisterEndpointNotificationCallback(pClient);
}

HRESULT __stdcall MMXboxDeviceEnumerator::UnregisterEndpointNotificationCallback(IMMNotificationClient *pClient)
{
    return m_realEnumerator->UnregisterEndpointNotificationCallback(pClient);
}

HRESULT __stdcall MMXboxDeviceEnumerator::GetHdAudioChannelCounts(UINT *pHdmiChannelCount, UINT *pSpdifChannelCount)
{
    *pHdmiChannelCount = 8;
    *pSpdifChannelCount = 2;
    return S_OK;
}

HRESULT __stdcall MMXboxDeviceEnumerator::RegisterChannelCountNotificationCallback(UINT *pClient)
{
    return S_OK;
}

HRESULT __stdcall MMXboxDeviceEnumerator::UnregisterChannelCountNotificationCallback(UINT *pClient)
{
    return S_OK;
}
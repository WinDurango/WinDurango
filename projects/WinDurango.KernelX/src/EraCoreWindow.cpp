#include "EraCoreWindow.h"
#include <CoreWindow.h>
#include <windows.applicationmodel.core.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/windows.storage.provider.h>

HRESULT CoreWindowEra::GetIids(ULONG *iidCount, IID **iids)
{
    return m_realWindow->GetIids(iidCount, iids);
}

HRESULT CoreWindowEra::GetRuntimeClassName(HSTRING *className)
{
    return m_realWindow->GetRuntimeClassName(className);
}

HRESULT CoreWindowEra::GetTrustLevel(TrustLevel *trustLevel)
{
    return m_realWindow->GetTrustLevel(trustLevel);
}

HRESULT CoreWindowEra::_abi_get_Bounds(Rect *rect)
{
    return m_realWindow->get_Bounds(rect);
}

HRESULT CoreWindowEra::_abi_get_Dispatcher(ICoreDispatcher **dispatcher)
{
    return m_realWindow->get_Dispatcher(dispatcher);
}

HRESULT CoreWindowEra::_abi_get_IsInputEnabled(boolean *value)
{
    return m_realWindow->get_IsInputEnabled(value);
}

HRESULT CoreWindowEra::_abi_set_IsInputEnabled(boolean value)
{
    return m_realWindow->put_IsInputEnabled(value);
}

HRESULT CoreWindowEra::_abi_get_Visible(boolean *value)
{
    return m_realWindow->get_Visible(value);
}

HRESULT CoreWindowEra::Activate()
{
    return m_realWindow->Activate();
}

HRESULT CoreWindowEra::Close()
{
    return m_realWindow->Close();
}

HRESULT CoreWindowEra::GetAsyncKeyState(ABI::Windows::System::VirtualKey virtualKey,
                                        ABI::Windows::UI::Core::CoreVirtualKeyStates *KeyState)
{
    return m_realWindow->GetAsyncKeyState(virtualKey, KeyState);
}

HRESULT CoreWindowEra::GetKeyState(ABI::Windows::System::VirtualKey virtualKey,
                                   ABI::Windows::UI::Core::CoreVirtualKeyStates *KeyState)
{
    return m_realWindow->GetKeyState(virtualKey, KeyState);
}

HRESULT CoreWindowEra::_abi_add_Activated(ITypedEventHandler<CoreWindow *, WindowActivatedEventArgs *> *handler,
                                          EventRegistrationToken *token)
{
    HRESULT hr = m_realWindow->add_Activated(handler, token);

    if (FAILED(hr) || !token)
        *token = EventRegistrationToken();

    return S_OK;
}

HRESULT CoreWindowEra::_abi_remove_Activated(EventRegistrationToken token)
{
    return m_realWindow->remove_Activated(token);
}

HRESULT CoreWindowEra::_abi_add_CharacterReceived(
    ITypedEventHandler<CoreWindow *, CharacterReceivedEventArgs *> *handler, EventRegistrationToken *token)
{
    HRESULT hr = m_realWindow->add_CharacterReceived(handler, token);

    if (FAILED(hr) || !token)
        *token = EventRegistrationToken();

    return S_OK;
}

HRESULT CoreWindowEra::_abi_remove_CharacterReceived(EventRegistrationToken token)
{
    return m_realWindow->remove_CharacterReceived(token);
}

HRESULT CoreWindowEra::_abi_add_Closed(ITypedEventHandler<CoreWindow *, CoreWindowEventArgs *> *handler,
                                       EventRegistrationToken *token)
{
    HRESULT hr = m_realWindow->add_Closed(handler, token);

    if (FAILED(hr) || !token)
        *token = EventRegistrationToken();

    return S_OK;
}

HRESULT CoreWindowEra::_abi_remove_Closed(EventRegistrationToken token)
{
    return m_realWindow->remove_Closed(token);
}

HRESULT CoreWindowEra::_abi_add_InputEnabled(ITypedEventHandler<CoreWindow *, InputEnabledEventArgs *> *handler,
                                             EventRegistrationToken *token)
{
    HRESULT hr = m_realWindow->add_InputEnabled(handler, token);

    if (FAILED(hr) || !token)
        *token = EventRegistrationToken();

    return S_OK;
}

HRESULT CoreWindowEra::_abi_remove_InputEnabled(EventRegistrationToken token)
{
    return m_realWindow->remove_InputEnabled(token);
}

HRESULT CoreWindowEra::_abi_add_KeyDown(ITypedEventHandler<CoreWindow *, KeyEventArgs *> *handler,
                                        EventRegistrationToken *token)
{
    HRESULT hr = m_realWindow->add_KeyDown(handler, token);

    if (FAILED(hr) || !token)
        *token = EventRegistrationToken();

    return S_OK;
}

HRESULT CoreWindowEra::_abi_remove_KeyDown(EventRegistrationToken token)
{
    return m_realWindow->remove_KeyDown(token);
}

HRESULT CoreWindowEra::_abi_add_KeyUp(ITypedEventHandler<CoreWindow *, KeyEventArgs *> *handler,
                                      EventRegistrationToken *token)
{
    HRESULT hr = m_realWindow->add_KeyUp(handler, token);

    if (FAILED(hr) || !token)
        *token = EventRegistrationToken();

    return S_OK;
}

HRESULT CoreWindowEra::_abi_remove_KeyUp(EventRegistrationToken token)
{
    return m_realWindow->remove_KeyUp(token);
}

HRESULT CoreWindowEra::_abi_add_PointerMoved(ITypedEventHandler<CoreWindow *, PointerEventArgs *> *handler,
                                             EventRegistrationToken *token)
{
    HRESULT hr = m_realWindow->add_PointerMoved(handler, token);

    if (FAILED(hr) || !token)
        *token = EventRegistrationToken();

    return S_OK;
}

HRESULT CoreWindowEra::_abi_remove_PointerMoved(EventRegistrationToken token)
{
    return m_realWindow->remove_PointerMoved(token);
}

HRESULT CoreWindowEra::_abi_add_PointerEntered(ITypedEventHandler<CoreWindow *, PointerEventArgs *> *handler,
                                               EventRegistrationToken *token)
{
    HRESULT hr = m_realWindow->add_PointerEntered(handler, token);

    if (FAILED(hr) || !token)
        *token = EventRegistrationToken();

    return S_OK;
}

HRESULT CoreWindowEra::_abi_remove_PointerEntered(EventRegistrationToken token)
{
    return m_realWindow->remove_PointerEntered(token);
}

HRESULT CoreWindowEra::_abi_add_PointerExited(ITypedEventHandler<CoreWindow *, PointerEventArgs *> *handler,
                                              EventRegistrationToken *token)
{
    HRESULT hr = m_realWindow->add_PointerExited(handler, token);

    if (FAILED(hr) || !token)
        *token = EventRegistrationToken();

    return S_OK;
}

HRESULT CoreWindowEra::_abi_remove_PointerExited(EventRegistrationToken token)
{
    return m_realWindow->remove_PointerExited(token);
}

HRESULT CoreWindowEra::_abi_add_SizeChanged(ITypedEventHandler<CoreWindow *, WindowSizeChangedEventArgs *> *handler,
                                            EventRegistrationToken *token)
{
    HRESULT hr = m_realWindow->add_SizeChanged(handler, token);

    if (FAILED(hr) || !token)
        *token = EventRegistrationToken();

    return S_OK;
}

HRESULT CoreWindowEra::_abi_remove_SizeChanged(EventRegistrationToken token)
{
    return m_realWindow->remove_SizeChanged(token);
}

HRESULT CoreWindowEra::_abi_add_VisibilityChanged(
    ITypedEventHandler<CoreWindow *, VisibilityChangedEventArgs *> *handler, EventRegistrationToken *token)
{
    HRESULT hr = m_realWindow->add_VisibilityChanged(handler, token);

    if (FAILED(hr) || !token)
        *token = EventRegistrationToken();

    return S_OK;
}

HRESULT CoreWindowEra::_abi_remove_VisibilityChanged(EventRegistrationToken token)
{
    return m_realWindow->remove_VisibilityChanged(token);
}

HRESULT CoreWindowEra::QueryInterface(const IID &riid, void **ppvObject)
{
    if (riid == __uuidof(IUnknown) || riid == __uuidof(IInspectable) || riid == __uuidof(ICoreWindowEra) ||
        riid == __uuidof(IAgileObject))
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    char iidstr[sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}")];
    OLECHAR iidwstr[sizeof(iidstr)];
    StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
    WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
    MessageBoxA(nullptr, iidstr, typeid(*this).name(), MB_OK);
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

ULONG CoreWindowEra::AddRef()
{
    if (m_realWindow)
        m_realWindow->AddRef();
    return InterlockedIncrement(&m_RefCount);
}

ULONG CoreWindowEra::Release()
{
    if (m_realWindow)
        m_realWindow->Release();
    ULONG refCount = InterlockedDecrement(&m_RefCount);
    if (refCount == 0)
        delete this;
    return refCount;
}
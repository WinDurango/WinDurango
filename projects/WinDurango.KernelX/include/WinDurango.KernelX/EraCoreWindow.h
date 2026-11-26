#pragma once
#include <windows.foundation.h>
#include <windows.system.h>
#include <windows.ui.core.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <wrl.h>

using namespace Microsoft::WRL;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Core;
using namespace ABI::Windows::System;

MIDL_INTERFACE("79b9d5f2-879e-4b89-b798-79e47598030c")
ICoreWindowEra : public IInspectable
{
  public:
    virtual HRESULT _abi_get_Bounds(Rect * rect) = 0;
    virtual HRESULT _abi_get_Dispatcher(ICoreDispatcher * *dispatcher) = 0;
    virtual HRESULT _abi_get_IsInputEnabled(boolean * value) = 0;
    virtual HRESULT _abi_set_IsInputEnabled(boolean value) = 0;
    virtual HRESULT _abi_get_Visible(boolean * value) = 0;
    virtual HRESULT Activate() = 0;
    virtual HRESULT Close() = 0;
    virtual HRESULT GetAsyncKeyState(ABI::Windows::System::VirtualKey virtualKey,
                                     ABI::Windows::UI::Core::CoreVirtualKeyStates * KeyState) = 0;
    virtual HRESULT GetKeyState(ABI::Windows::System::VirtualKey virtualKey,
                                ABI::Windows::UI::Core::CoreVirtualKeyStates * KeyState) = 0;
    virtual HRESULT _abi_add_Activated(ITypedEventHandler<CoreWindow *, WindowActivatedEventArgs *> * handler,
                                       EventRegistrationToken * token) = 0;
    virtual HRESULT _abi_remove_Activated(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_CharacterReceived(ITypedEventHandler<CoreWindow *, CharacterReceivedEventArgs *> * handler,
                                               EventRegistrationToken * token) = 0;
    virtual HRESULT _abi_remove_CharacterReceived(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_Closed(ITypedEventHandler<CoreWindow *, CoreWindowEventArgs *> * handler,
                                    EventRegistrationToken * token) = 0;
    virtual HRESULT _abi_remove_Closed(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_InputEnabled(ITypedEventHandler<CoreWindow *, InputEnabledEventArgs *> * handler,
                                          EventRegistrationToken * token) = 0;
    virtual HRESULT _abi_remove_InputEnabled(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_KeyDown(ITypedEventHandler<CoreWindow *, KeyEventArgs *> * handler,
                                     EventRegistrationToken * token) = 0;
    virtual HRESULT _abi_remove_KeyDown(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_KeyUp(ITypedEventHandler<CoreWindow *, KeyEventArgs *> * handler,
                                   EventRegistrationToken * token) = 0;
    virtual HRESULT _abi_remove_KeyUp(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_PointerMoved(ITypedEventHandler<CoreWindow *, PointerEventArgs *> * handler,
                                          EventRegistrationToken * token) = 0;
    virtual HRESULT _abi_remove_PointerMoved(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_PointerEntered(ITypedEventHandler<CoreWindow *, PointerEventArgs *> * handler,
                                            EventRegistrationToken * token) = 0;
    virtual HRESULT _abi_remove_PointerEntered(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_PointerExited(ITypedEventHandler<CoreWindow *, PointerEventArgs *> * handler,
                                           EventRegistrationToken * token) = 0;
    virtual HRESULT _abi_remove_PointerExited(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_SizeChanged(ITypedEventHandler<CoreWindow *, WindowSizeChangedEventArgs *> * handler,
                                         EventRegistrationToken * token) = 0;
    virtual HRESULT _abi_remove_SizeChanged(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_VisibilityChanged(ITypedEventHandler<CoreWindow *, VisibilityChangedEventArgs *> * handler,
                                               EventRegistrationToken * token) = 0;
    virtual HRESULT _abi_remove_VisibilityChanged(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_PointerWheelChanged(ITypedEventHandler<CoreWindow *, PointerEventArgs*>* handler, EventRegistrationToken* token) = 0;
    virtual HRESULT _abi_remove_PointerWheelChanged(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_remove_PointerPressed(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_PointerPressed(ITypedEventHandler<CoreWindow *, PointerEventArgs*>* handler, EventRegistrationToken* token) = 0;
    virtual HRESULT _abi_remove_PointerReleased(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_PointerReleased(ITypedEventHandler<CoreWindow *, PointerEventArgs*>* handler, EventRegistrationToken* token) = 0;
    virtual HRESULT _abi_get_PointerCursor(ABI::Windows::UI::Core::ICoreCursor** PointerCursor) = 0;
    virtual HRESULT _abi_set_PointerCursor(ABI::Windows::UI::Core::ICoreCursor* PointerCursor) = 0;
    virtual HRESULT _abi_get_PointerPosition(ABI::Windows::Foundation::Point* PointerPosition) = 0;
};

class CoreWindowEra : public ICoreWindowEra
{
public:
    ICoreWindow *m_realWindow = nullptr;

    CoreWindowEra(CoreWindow *realWind)
    {
        m_realWindow = reinterpret_cast<ICoreWindow*>(realWind);
        InterlockedIncrement(&m_RefCount);
    }

    HRESULT _abi_get_Bounds(Rect *rect) override;
    HRESULT _abi_get_Dispatcher(ICoreDispatcher **dispatcher) override;
    HRESULT _abi_get_IsInputEnabled(boolean *value) override;
    HRESULT _abi_set_IsInputEnabled(boolean value) override;
    HRESULT _abi_get_Visible(boolean *value) override;
    HRESULT Activate() override;
    HRESULT Close() override;
    HRESULT GetAsyncKeyState(ABI::Windows::System::VirtualKey virtualKey,
                             ABI::Windows::UI::Core::CoreVirtualKeyStates *KeyState) override;
    HRESULT GetKeyState(ABI::Windows::System::VirtualKey virtualKey,
                        ABI::Windows::UI::Core::CoreVirtualKeyStates *KeyState) override;
    HRESULT _abi_add_Activated(ITypedEventHandler<CoreWindow *, WindowActivatedEventArgs *> *handler,
                               EventRegistrationToken *token) override;
    HRESULT _abi_remove_Activated(EventRegistrationToken token) override;
    HRESULT _abi_add_CharacterReceived(ITypedEventHandler<CoreWindow *, CharacterReceivedEventArgs *> *handler,
                                       EventRegistrationToken *token) override;
    HRESULT _abi_remove_CharacterReceived(EventRegistrationToken token) override;
    HRESULT _abi_add_Closed(ITypedEventHandler<CoreWindow *, CoreWindowEventArgs *> *handler,
                            EventRegistrationToken *token) override;
    HRESULT _abi_remove_Closed(EventRegistrationToken token) override;
    HRESULT _abi_add_InputEnabled(ITypedEventHandler<CoreWindow *, InputEnabledEventArgs *> *handler,
                                  EventRegistrationToken *token) override;
    HRESULT _abi_remove_InputEnabled(EventRegistrationToken token) override;
    HRESULT _abi_add_KeyDown(ITypedEventHandler<CoreWindow *, KeyEventArgs *> *handler,
                             EventRegistrationToken *token) override;
    HRESULT _abi_remove_KeyDown(EventRegistrationToken token) override;
    HRESULT _abi_add_KeyUp(ITypedEventHandler<CoreWindow *, KeyEventArgs *> *handler,
                           EventRegistrationToken *token) override;
    HRESULT _abi_remove_KeyUp(EventRegistrationToken token) override;
    HRESULT _abi_add_PointerMoved(ITypedEventHandler<CoreWindow *, PointerEventArgs *> *handler,
                                  EventRegistrationToken *token) override;
    HRESULT _abi_remove_PointerMoved(EventRegistrationToken token) override;
    HRESULT _abi_add_PointerEntered(ITypedEventHandler<CoreWindow *, PointerEventArgs *> *handler,
                                    EventRegistrationToken *token) override;
    HRESULT _abi_remove_PointerEntered(EventRegistrationToken token) override;
    HRESULT _abi_add_PointerExited(ITypedEventHandler<CoreWindow *, PointerEventArgs *> *handler,
                                   EventRegistrationToken *token) override;
    HRESULT _abi_remove_PointerExited(EventRegistrationToken token) override;
    HRESULT _abi_add_SizeChanged(ITypedEventHandler<CoreWindow *, WindowSizeChangedEventArgs *> *handler,
                                 EventRegistrationToken *token) override;
    HRESULT _abi_remove_SizeChanged(EventRegistrationToken token) override;
    HRESULT _abi_add_VisibilityChanged(ITypedEventHandler<CoreWindow *, VisibilityChangedEventArgs *> *handler,
                                       EventRegistrationToken *token) override;
    HRESULT _abi_remove_VisibilityChanged(EventRegistrationToken token) override;
    HRESULT _abi_add_PointerWheelChanged(ITypedEventHandler<CoreWindow *, PointerEventArgs*>* handler, EventRegistrationToken* token) override;
    HRESULT _abi_remove_PointerWheelChanged(EventRegistrationToken token) override;
    HRESULT _abi_remove_PointerPressed(EventRegistrationToken token) override;
    HRESULT _abi_add_PointerPressed(ITypedEventHandler<CoreWindow *, PointerEventArgs*>* handler, EventRegistrationToken* token) override;
    HRESULT _abi_remove_PointerReleased(EventRegistrationToken token) override;
    HRESULT _abi_add_PointerReleased(ITypedEventHandler<CoreWindow *, PointerEventArgs*>* handler, EventRegistrationToken* token) override;
    HRESULT _abi_get_PointerCursor(ABI::Windows::UI::Core::ICoreCursor** PointerCursor) override;
    HRESULT _abi_set_PointerCursor(ABI::Windows::UI::Core::ICoreCursor* PointerCursor) override;
    HRESULT _abi_get_PointerPosition(ABI::Windows::Foundation::Point* PointerPosition) override;

    // IInspectable + IUnknown
    HRESULT QueryInterface(const IID &riid, void **ppvObject) override;
    ULONG AddRef() override;
    ULONG Release() override;

    HRESULT GetIids(ULONG *iidCount, IID **iids) override;
    HRESULT GetRuntimeClassName(HSTRING *className) override;
    HRESULT GetTrustLevel(TrustLevel *trustLevel) override;


private:
    ULONG m_RefCount = 0;
};

MIDL_INTERFACE("88edf458-f2c8-49f4-be1f-c256b388bc11")
IMouseDeviceEra : public IInspectable
{
    virtual HRESULT _abi_add_MouseMoved(ITypedEventHandler<ABI::Windows::Devices::Input::MouseDevice*, ABI::Windows::Devices::Input::MouseEventArgs*>* handler, EventRegistrationToken* token) = 0;
    virtual HRESULT _abi_remove_MouseMoved(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_add_MouseWheelMoved(ITypedEventHandler<ABI::Windows::Devices::Input::MouseDevice*, ABI::Windows::Devices::Input::MouseEventArgs*>* handler, EventRegistrationToken* token) = 0;
    virtual HRESULT _abi_remove_MouseWheelMoved(EventRegistrationToken token) = 0;
    virtual HRESULT _abi_get_MousePositionDelta(ABI::Windows::Devices::Input::MouseDelta* mousePositionDelta) = 0;
    virtual HRESULT _abi_get_MouseWheelDelta(INT* mouseWheelDelta) = 0;
    virtual HRESULT _abi_get_HorizontalMouseWheelDelta(INT* horizontalMouseWheelDelta) = 0;
};

class MouseDeviceEra : public IMouseDeviceEra
{
public:
    ABI::Windows::Devices::Input::IMouseDevice *m_realDevice = nullptr;

    MouseDeviceEra(ABI::Windows::Devices::Input::IMouseDevice *realDev)
    {
        m_realDevice = realDev;
        InterlockedIncrement(&m_RefCount);
    }

    HRESULT _abi_add_MouseMoved(ITypedEventHandler<ABI::Windows::Devices::Input::MouseDevice*, ABI::Windows::Devices::Input::MouseEventArgs*>* handler, EventRegistrationToken* token) override
    {
        return m_realDevice->add_MouseMoved(handler, token);
    }

    HRESULT _abi_remove_MouseMoved(EventRegistrationToken token) override
    {
        return m_realDevice->remove_MouseMoved(token);
    }

    HRESULT _abi_add_MouseWheelMoved(ITypedEventHandler<ABI::Windows::Devices::Input::MouseDevice*, ABI::Windows::Devices::Input::MouseEventArgs*>* handler, EventRegistrationToken* token) override
    {
        *token = EventRegistrationToken();
        return S_OK;
    }

    HRESULT _abi_remove_MouseWheelMoved(EventRegistrationToken token) override
    {
        return S_OK;
    }

    HRESULT _abi_get_MousePositionDelta(ABI::Windows::Devices::Input::MouseDelta* mousePositionDelta) override
    {
        POINT Point{};
        GetCursorPos(&Point);
        mousePositionDelta->X = Point.x;
        mousePositionDelta->Y = Point.y;
        return S_OK;
    }

    HRESULT _abi_get_MouseWheelDelta(INT* mouseWheelDelta) override
    {
        *mouseWheelDelta = 0;
        return S_OK;
    }

    HRESULT _abi_get_HorizontalMouseWheelDelta(INT* horizontalMouseWheelDelta) override
    {
        *horizontalMouseWheelDelta = 0;
        return S_OK;
    }

    // IInspectable + IUnknown
    HRESULT QueryInterface(const IID& riid, void** ppvObject) override
    {
        if (riid == __uuidof(IUnknown) || riid == __uuidof(IInspectable) || riid == __uuidof(IMouseDeviceEra))
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

    ULONG AddRef() override
    {
        m_realDevice->AddRef();
        return InterlockedIncrement(&m_RefCount);
    }

    ULONG Release() override
    {
        m_realDevice->Release();
        ULONG RefCount = InterlockedDecrement(&m_RefCount);
        if (!RefCount) delete this;
        return RefCount;
    }

    HRESULT GetIids(ULONG* iidCount, IID** iids) override
    {
        return m_realDevice->GetIids(iidCount, iids);
    }

    HRESULT GetRuntimeClassName(HSTRING* className) override
    {
        return m_realDevice->GetRuntimeClassName(className);
    }

    HRESULT GetTrustLevel(TrustLevel* trustLevel) override
    {
        return m_realDevice->GetTrustLevel(trustLevel);
    }

private:
    ULONG m_RefCount = 0;
};


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
};

class CoreWindowEra : public ICoreWindowEra
{
  public:
    ICoreWindow *m_realWindow;

    CoreWindowEra(CoreWindow *realWind)
    {
        m_realWindow = reinterpret_cast<ICoreWindow *>(realWind);
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
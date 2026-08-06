#include "Windows.Xbox.System.h"

namespace winrt::Windows::Xbox::System::implementation
{
    hstring GetTokenAndSignatureResult::Signature()
    {
        return signature;
    }

    hstring GetTokenAndSignatureResult::Token()
    {
        return token;
    }

    winrt::Windows::Xbox::System::UserOnlineState OnlineStateChangedEventArgs::State()
    {
        return UserOnlineState::Offline;
    }

    winrt::hresult GetPictureResult::Result()
    {
        return result;
    }

    uint32_t GetPictureResult::RequiredBufferSize()
    {
        return bufferSize;
    }

    winrt::Windows::Xbox::System::User SignInCompletedEventArgs::User()
    {
        return user;
    }

    winrt::Windows::Xbox::System::SignOutDeferral SignOutStartedEventArgs::GetDeferral()
    {
        return deferral;
    }

    winrt::Windows::Xbox::System::User SignOutStartedEventArgs::User()
    {
        return user;
    }

    winrt::hresult SignOutCompletedEventArgs::Result()
    {
        return result;
    }

    winrt::Windows::Xbox::System::User SignOutCompletedEventArgs::User()
    {
        return user;
    }

    void SignOutDeferral::Complete()
    {
        
    }
}

#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerFactoryHosted.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer SpeechRecognizerFactoryHosted::CreateSpeechRecognizerForLocale(uint16_t requestedLanguageId, hstring const& aumid)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateSystemSpeechRecognizer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer SpeechRecognizerFactoryHosted::CreateSystemSpeechRecognizer(hstring const& aumid)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateSystemSpeechRecognizer");
        throw hresult_not_implemented();
    }
}

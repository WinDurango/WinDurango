#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerFactory.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer SpeechRecognizerFactory::CreateSpeechRecognizerForLocale(uint16_t requestedLanguageId)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateSpeechRecognizerForLocale");
        throw hresult_not_implemented();
    }
}

#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerFactory.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerAnalyzer.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer SpeechRecognizerFactory::CreateSpeechRecognizerForLocale(uint16_t requestedLanguageId)
    {
        return winrt::make<winrt::Windows::Xbox::Speech::Recognition::implementation::SpeechRecognizer>();
    }
}

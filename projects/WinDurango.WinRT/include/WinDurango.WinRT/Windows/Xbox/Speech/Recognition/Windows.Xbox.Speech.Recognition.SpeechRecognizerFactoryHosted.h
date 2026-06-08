#pragma once
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerFactoryHosted.g.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    struct SpeechRecognizerFactoryHosted
    {
        SpeechRecognizerFactoryHosted() = default;

        static winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer CreateSpeechRecognizerForLocale(uint16_t requestedLanguageId, hstring const& aumid);
        static winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer CreateSystemSpeechRecognizer(hstring const& aumid);
    };
}

namespace winrt::Windows::Xbox::Speech::Recognition::factory_implementation
{
    struct SpeechRecognizerFactoryHosted : SpeechRecognizerFactoryHostedT<SpeechRecognizerFactoryHosted, implementation::SpeechRecognizerFactoryHosted>
    {
    };
}

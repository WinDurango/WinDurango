#pragma once
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerFactory.g.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    struct SpeechRecognizerFactory
    {
        SpeechRecognizerFactory() = default;

        static winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer CreateSpeechRecognizerForLocale(uint16_t requestedLanguageId);
    };
}

namespace winrt::Windows::Xbox::Speech::Recognition::factory_implementation
{
    struct SpeechRecognizerFactory : SpeechRecognizerFactoryT<SpeechRecognizerFactory, implementation::SpeechRecognizerFactory>
    {
    };
}

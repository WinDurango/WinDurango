#pragma once
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerInformation.g.h"
#include "Windows.Xbox.Speech.Recognition.InstalledSpeechRecognizers.g.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    struct SpeechRecognizerInformation : SpeechRecognizerInformationT<SpeechRecognizerInformation>
    {
        SpeechRecognizerInformation() = default;

        hstring DisplayName();
        hstring Id();
        hstring Language();
        hstring Description();
    };
    
    struct InstalledSpeechRecognizers
    {
        InstalledSpeechRecognizers() = default;

        static winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerInformation> All();
        static winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerInformation Default();
    };
}

namespace winrt::Windows::Xbox::Speech::Recognition::factory_implementation
{
    struct InstalledSpeechRecognizers : InstalledSpeechRecognizersT<InstalledSpeechRecognizers, implementation::InstalledSpeechRecognizers>
    {
    };
}

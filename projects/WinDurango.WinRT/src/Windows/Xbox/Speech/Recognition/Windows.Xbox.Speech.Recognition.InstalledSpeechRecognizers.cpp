#include "Windows.Xbox.Speech.Recognition.InstalledSpeechRecognizers.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerInformation> InstalledSpeechRecognizers::All()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: All");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerInformation InstalledSpeechRecognizers::Default()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Default");
        throw hresult_not_implemented();
    }
    hstring SpeechRecognizerInformation::DisplayName()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: DisplayName");
        throw hresult_not_implemented();
    }
    hstring SpeechRecognizerInformation::Id()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Id");
        throw hresult_not_implemented();
    }
    hstring SpeechRecognizerInformation::Language()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Language");
        throw hresult_not_implemented();
    }
    hstring SpeechRecognizerInformation::Description()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Description");
        throw hresult_not_implemented();
    }
}

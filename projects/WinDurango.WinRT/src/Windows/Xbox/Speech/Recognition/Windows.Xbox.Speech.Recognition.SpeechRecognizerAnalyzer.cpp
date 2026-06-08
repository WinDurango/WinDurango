#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerAnalyzer.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    winrt::Windows::Foundation::IAsyncAction SpeechRecognizerAnalyzer::SerializeGrammarsToFolderAsync(winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer speechRecognizer, winrt::Windows::Foundation::Uri destinationFolder, winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarRuleInclusionMode inclusionMode)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SerializeGrammarsToFolderAsync");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResult> SpeechRecognizerAnalyzer::CheckResultFromPhraseAsync(winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer speechRecognizer, hstring phrase)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CheckResultFromPhraseAsync");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechPronunciationDetail> SpeechRecognizerAnalyzer::GetPronunciationFromPhrase(winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer const& speechRecognizer, hstring const& phrase)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: GetPronunciationFromPhrase");
        throw hresult_not_implemented();
    }

    hstring SpeechRecognitionResult::Text()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Text");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionConfidence SpeechRecognitionResult::TextConfidence()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: TextConfidence");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionSemanticProperty> SpeechRecognitionResult::Semantics()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Semantics");
        throw hresult_not_implemented();
    }

    hstring SpeechRecognitionResult::RuleName()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: RuleName");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResult> SpeechRecognitionResult::GetAlternates(uint32_t maxAlternates)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: GetAlternates");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResultDetail SpeechRecognitionResult::Details()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Details");
        throw hresult_not_implemented();
    }

    uint64_t SpeechRecognitionResultBodyCorrelation::BodyTrackingId()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: BodyTrackingId");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IVectorView<hstring> SpeechRecognitionResultDetail::RuleStack()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: RuleStack");
        throw hresult_not_implemented();
    }

    float SpeechRecognitionResultDetail::ConfidenceScore()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: ConfidenceScore");
        throw hresult_not_implemented();
    }

    hstring SpeechRecognitionResultDetail::Pronunciation()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Pronunciation");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResultToken> SpeechRecognitionResultDetail::Tokens()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Tokens");
        throw hresult_not_implemented();
    }

    uint64_t SpeechRecognitionResultDetail::AudioPosition()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AudioPosition");
        throw hresult_not_implemented();
    }

    uint32_t SpeechRecognitionResultDetail::AudioSize()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AudioSize");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResultBodyCorrelation> SpeechRecognitionResultDetail::BodyCorrelation()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: BodyCorrelation");
        throw hresult_not_implemented();
    }

    hstring SpeechRecognitionSemanticProperty::Name()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Name");
        throw hresult_not_implemented();
    }

    hstring SpeechRecognitionSemanticProperty::ValueAsString()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: ValueAsString");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionConfidence SpeechRecognitionSemanticProperty::ConfidenceLevel()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: ConfidenceLevel");
        throw hresult_not_implemented();
    }

    float SpeechRecognitionSemanticProperty::ConfidenceScore()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: ConfidenceScore");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionSemanticProperty> SpeechRecognitionSemanticProperty::Duplicates()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Duplicates");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResult> SpeechRecognizer::RecognizeAsync()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: RecognizeAsync");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::IAsyncAction SpeechRecognizer::PreloadGrammarsAsync()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: PreloadGrammarsAsync");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerSettings SpeechRecognizer::Settings()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Settings");
        throw hresult_not_implemented();
    }
    
    winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarSet SpeechRecognizer::Grammars()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Grammars");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::StartContinuousRecognition()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: StartContinuousRecognition");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::StopContinuousRecognition()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: StopContinuousRecognition");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::ResumeContinuousRecognition()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: ResumeContinuousRecognition");
        throw hresult_not_implemented();
    }

    bool SpeechRecognizer::PauseOnContinuousRecognitionResultAvailable()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: PauseOnContinuousRecognitionResultAvailable");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::PauseOnContinuousRecognitionResultAvailable(bool value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: PauseOnContinuousRecognitionResultAvailable");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerInformation SpeechRecognizer::GetRecognizer()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: GetRecognizer");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::SetRecognizer(winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerInformation const& recognizerInformation)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SetRecognizer");
        throw hresult_not_implemented();
    }
    
    winrt::event_token SpeechRecognizer::AudioProblemOccurred(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechAudioProblemOccurredEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AudioProblemOccurred");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::AudioProblemOccurred(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AudioProblemOccurred");
        throw hresult_not_implemented();
    }

    winrt::event_token SpeechRecognizer::AudioCaptureStateChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerAudioCaptureStateChangedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AudioCaptureStateChanged");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::AudioCaptureStateChanged(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AudioCaptureStateChanged");
        throw hresult_not_implemented();
    }

    winrt::event_token SpeechRecognizer::ContinuousRecognitionResultAvailable(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::ContinuousSpeechRecognitionResultEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: ContinuousRecognitionResultAvailable");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::ContinuousRecognitionResultAvailable(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: ContinuousRecognitionResultAvailable");
        throw hresult_not_implemented();
    }

    winrt::event_token SpeechRecognizer::ContinuousRecognitionStatusChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::ContinuousSpeechRecognitionStatusEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: ContinuousRecognitionStatusChanged");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::ContinuousRecognitionStatusChanged(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: ContinuousRecognitionStatusChanged");
        throw hresult_not_implemented();
    }

    winrt::event_token SpeechRecognizer::HypothesisAvailable(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechHypothesisResultEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: HypothesisAvailable");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::HypothesisAvailable(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: HypothesisAvailable");
        throw hresult_not_implemented();
    }

    winrt::event_token SpeechRecognizer::SoundStarted(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerSoundStartedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SoundStarted");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::SoundStarted(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SoundStarted");
        throw hresult_not_implemented();
    }

    winrt::event_token SpeechRecognizer::SoundEnded(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerSoundEndedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SoundEnded");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::SoundEnded(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SoundEnded");
        throw hresult_not_implemented();
    }

    winrt::event_token SpeechRecognizer::PhraseStarted(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerPhraseStartedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: PhraseStarted");
        throw hresult_not_implemented();
    }

    void SpeechRecognizer::PhraseStarted(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: PhraseStarted");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerAudioCaptureState SpeechRecognizerAudioCaptureStateChangedEventArgs::State()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: State");
        throw hresult_not_implemented();
    }

    uint64_t SpeechRecognizerAudioContext::AudioPosition()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AudioPosition");
        throw hresult_not_implemented();
    }

    void SpeechRecognizerInputSetting::SetInputToAudioStream(winrt::Windows::Storage::Streams::IRandomAccessStream const& inputStream)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SetInputToAudioStream");
        throw hresult_not_implemented();
    }

    void SpeechRecognizerInputSetting::SetInputToText(hstring const& text)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SetInputToText");
        throw hresult_not_implemented();
    }

    void SpeechRecognizerInputSetting::SetInputToPronunciation(hstring const& pronunciation)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SetInputToPronunciation");
        throw hresult_not_implemented();
    }

    void SpeechRecognizerInputSetting::SetInputToMicrophone()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SetInputToMicrophone");
        throw hresult_not_implemented();
    }

    void SpeechRecognizerInputSetting::SetInputToMicrophoneFeatureVector()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SetInputToMicrophoneFeatureVector");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerAudioContext SpeechRecognizerPhraseStartedEventArgs::AudioContext()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AudioContext");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::TimeSpan SpeechRecognizerSettings::InitialSilenceTimeout()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: InitialSilenceTimeout");
        throw hresult_not_implemented();
    }

    void SpeechRecognizerSettings::InitialSilenceTimeout(winrt::Windows::Foundation::TimeSpan const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: InitialSilenceTimeout");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::TimeSpan SpeechRecognizerSettings::EndSilenceTimeout()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: EndSilenceTimeout");
        throw hresult_not_implemented();
    }

    void SpeechRecognizerSettings::EndSilenceTimeout(winrt::Windows::Foundation::TimeSpan const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: EndSilenceTimeout");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::TimeSpan SpeechRecognizerSettings::BabbleTimeout()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: BabbleTimeout");
        throw hresult_not_implemented();
    }

    void SpeechRecognizerSettings::BabbleTimeout(winrt::Windows::Foundation::TimeSpan const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: BabbleTimeout");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerInputSetting SpeechRecognizerSettings::SpeechRecognizerInputSetting()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SpeechRecognizerInputSetting");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerAudioContext SpeechRecognizerSoundEndedEventArgs::AudioContext()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AudioContext");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerAudioContext SpeechRecognizerSoundStartedEventArgs::AudioContext()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AudioContext");
        throw hresult_not_implemented();
    }

    hstring SpeechRecognitionResultToken::DisplayForm()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: DisplayForm");
        throw hresult_not_implemented();
    }

    hstring SpeechRecognitionResultToken::LexicalForm()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: LexicalForm");
        throw hresult_not_implemented();
    }
    
    hstring SpeechRecognitionResultToken::PronunciationForm()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: PronunciationForm");
        throw hresult_not_implemented();
    }
}

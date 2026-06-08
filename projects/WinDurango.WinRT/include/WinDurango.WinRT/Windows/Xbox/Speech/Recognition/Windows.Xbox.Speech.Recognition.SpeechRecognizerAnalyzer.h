#pragma once
#include "Windows.Xbox.Speech.Recognition.SpeechRecognitionResult.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognitionResultBodyCorrelation.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognitionResultDetail.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognitionSemanticProperty.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizer.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerAudioCaptureStateChangedEventArgs.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerAudioContext.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerInputSetting.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerPhraseStartedEventArgs.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerSettings.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerSoundEndedEventArgs.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerSoundStartedEventArgs.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognitionResultToken.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRecognizerAnalyzer.g.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    struct SpeechRecognitionResult : SpeechRecognitionResultT<SpeechRecognitionResult>
    {
        SpeechRecognitionResult() = default;

        hstring Text();
        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionConfidence TextConfidence();
        winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionSemanticProperty> Semantics();
        hstring RuleName();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResult> GetAlternates(uint32_t maxAlternates);
        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResultDetail Details();
    };

    struct SpeechRecognitionResultBodyCorrelation : SpeechRecognitionResultBodyCorrelationT<SpeechRecognitionResultBodyCorrelation>
    {
        SpeechRecognitionResultBodyCorrelation() = default;

        uint64_t BodyTrackingId();
    };

    struct SpeechRecognitionResultDetail : SpeechRecognitionResultDetailT<SpeechRecognitionResultDetail>
    {
        SpeechRecognitionResultDetail() = default;

        winrt::Windows::Foundation::Collections::IVectorView<hstring> RuleStack();
        float ConfidenceScore();
        hstring Pronunciation();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResultToken> Tokens();
        uint64_t AudioPosition();
        uint32_t AudioSize();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResultBodyCorrelation> BodyCorrelation();
    };

    struct SpeechRecognitionResultToken : SpeechRecognitionResultTokenT<SpeechRecognitionResultToken>
    {
        SpeechRecognitionResultToken() = default;

        hstring DisplayForm();
        hstring LexicalForm();
        hstring PronunciationForm();
    };

    struct SpeechRecognitionSemanticProperty : SpeechRecognitionSemanticPropertyT<SpeechRecognitionSemanticProperty>
    {
        SpeechRecognitionSemanticProperty() = default;

        hstring Name();
        hstring ValueAsString();
        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionConfidence ConfidenceLevel();
        float ConfidenceScore();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionSemanticProperty> Duplicates();
    };

    struct SpeechRecognizer : SpeechRecognizerT<SpeechRecognizer>
    {
        SpeechRecognizer() = default;

        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResult> RecognizeAsync();
        winrt::Windows::Foundation::IAsyncAction PreloadGrammarsAsync();
        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerSettings Settings();
        winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarSet Grammars();
        void StartContinuousRecognition();
        void StopContinuousRecognition();
        void ResumeContinuousRecognition();
        bool PauseOnContinuousRecognitionResultAvailable();
        void PauseOnContinuousRecognitionResultAvailable(bool value);
        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerInformation GetRecognizer();
        void SetRecognizer(winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerInformation const& recognizerInformation);
        winrt::event_token AudioProblemOccurred(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechAudioProblemOccurredEventArgs> const& handler);
        void AudioProblemOccurred(winrt::event_token const& token) noexcept;
        winrt::event_token AudioCaptureStateChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerAudioCaptureStateChangedEventArgs> const& handler);
        void AudioCaptureStateChanged(winrt::event_token const& token) noexcept;
        winrt::event_token ContinuousRecognitionResultAvailable(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::ContinuousSpeechRecognitionResultEventArgs> const& handler);
        void ContinuousRecognitionResultAvailable(winrt::event_token const& token) noexcept;
        winrt::event_token ContinuousRecognitionStatusChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::ContinuousSpeechRecognitionStatusEventArgs> const& handler);
        void ContinuousRecognitionStatusChanged(winrt::event_token const& token) noexcept;
        winrt::event_token HypothesisAvailable(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechHypothesisResultEventArgs> const& handler);
        void HypothesisAvailable(winrt::event_token const& token) noexcept;
        winrt::event_token SoundStarted(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerSoundStartedEventArgs> const& handler);
        void SoundStarted(winrt::event_token const& token) noexcept;
        winrt::event_token SoundEnded(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerSoundEndedEventArgs> const& handler);
        void SoundEnded(winrt::event_token const& token) noexcept;
        winrt::event_token PhraseStarted(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer, winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerPhraseStartedEventArgs> const& handler);
        void PhraseStarted(winrt::event_token const& token) noexcept;
    };

    struct SpeechRecognizerAudioCaptureStateChangedEventArgs : SpeechRecognizerAudioCaptureStateChangedEventArgsT<SpeechRecognizerAudioCaptureStateChangedEventArgs>
    {
        SpeechRecognizerAudioCaptureStateChangedEventArgs() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerAudioCaptureState State();
    };

    struct SpeechRecognizerAudioContext : SpeechRecognizerAudioContextT<SpeechRecognizerAudioContext>
    {
        SpeechRecognizerAudioContext() = default;

        uint64_t AudioPosition();
    };

    struct SpeechRecognizerInputSetting : SpeechRecognizerInputSettingT<SpeechRecognizerInputSetting>
    {
        SpeechRecognizerInputSetting() = default;

        void SetInputToAudioStream(winrt::Windows::Storage::Streams::IRandomAccessStream const& inputStream);
        void SetInputToText(hstring const& text);
        void SetInputToPronunciation(hstring const& pronunciation);
        void SetInputToMicrophone();
        void SetInputToMicrophoneFeatureVector();
    };

    struct SpeechRecognizerPhraseStartedEventArgs : SpeechRecognizerPhraseStartedEventArgsT<SpeechRecognizerPhraseStartedEventArgs>
    {
        SpeechRecognizerPhraseStartedEventArgs() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerAudioContext AudioContext();
    };

    struct SpeechRecognizerSettings : SpeechRecognizerSettingsT<SpeechRecognizerSettings>
    {
        SpeechRecognizerSettings() = default;

        winrt::Windows::Foundation::TimeSpan InitialSilenceTimeout();
        void InitialSilenceTimeout(winrt::Windows::Foundation::TimeSpan const& value);
        winrt::Windows::Foundation::TimeSpan EndSilenceTimeout();
        void EndSilenceTimeout(winrt::Windows::Foundation::TimeSpan const& value);
        winrt::Windows::Foundation::TimeSpan BabbleTimeout();
        void BabbleTimeout(winrt::Windows::Foundation::TimeSpan const& value);
        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerInputSetting SpeechRecognizerInputSetting();
    };

    struct SpeechRecognizerSoundEndedEventArgs : SpeechRecognizerSoundEndedEventArgsT<SpeechRecognizerSoundEndedEventArgs>
    {
        SpeechRecognizerSoundEndedEventArgs() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerAudioContext AudioContext();
    };

    struct SpeechRecognizerSoundStartedEventArgs : SpeechRecognizerSoundStartedEventArgsT<SpeechRecognizerSoundStartedEventArgs>
    {
        SpeechRecognizerSoundStartedEventArgs() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizerAudioContext AudioContext();
    };

    struct SpeechRecognizerAnalyzer
    {
        SpeechRecognizerAnalyzer() = default;

        static winrt::Windows::Foundation::IAsyncAction SerializeGrammarsToFolderAsync(winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer speechRecognizer, winrt::Windows::Foundation::Uri destinationFolder, winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarRuleInclusionMode inclusionMode);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResult> CheckResultFromPhraseAsync(winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer speechRecognizer, hstring phrase);
        static winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechPronunciationDetail> GetPronunciationFromPhrase(winrt::Windows::Xbox::Speech::Recognition::SpeechRecognizer const& speechRecognizer, hstring const& phrase);
    };
}

namespace winrt::Windows::Xbox::Speech::Recognition::factory_implementation
{
    struct SpeechRecognizerAnalyzer : SpeechRecognizerAnalyzerT<SpeechRecognizerAnalyzer, implementation::SpeechRecognizerAnalyzer>
    {
    };
}

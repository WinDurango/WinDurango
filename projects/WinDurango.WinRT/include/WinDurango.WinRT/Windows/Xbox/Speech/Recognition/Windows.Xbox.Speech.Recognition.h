#pragma once
#include "Windows.Xbox.Speech.Recognition.ContinuousSpeechRecognitionResultEventArgs.g.h"
#include "Windows.Xbox.Speech.Recognition.ContinuousSpeechRecognitionStatusEventArgs.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechAudioProblemOccurredEventArgs.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechChoiceRule.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechGarbageItemFactory.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechGarbageItem.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechGraphRule.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechGraphState.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechHypothesisResultEventArgs.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechNullItem.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechPhraseItem.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechPronunciationDetail.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechRuleReferenceItem.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechSequenceRule.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechLanguage.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechLanguageInformation.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechLanguageSupportInternal.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechPhraseItemFactory.g.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    struct ContinuousSpeechRecognitionResultEventArgs : ContinuousSpeechRecognitionResultEventArgsT<ContinuousSpeechRecognitionResultEventArgs>
    {
        ContinuousSpeechRecognitionResultEventArgs() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResult Result();
    };

    struct ContinuousSpeechRecognitionStatusEventArgs : ContinuousSpeechRecognitionStatusEventArgsT<ContinuousSpeechRecognitionStatusEventArgs>
    {
        ContinuousSpeechRecognitionStatusEventArgs() = default;

        winrt::Windows::Xbox::Speech::Recognition::ContinuousSpeechRecognitionStatus Status();
        winrt::hresult ErrorCode();
    };

    struct SpeechAudioProblemOccurredEventArgs : SpeechAudioProblemOccurredEventArgsT<SpeechAudioProblemOccurredEventArgs>
    {
        SpeechAudioProblemOccurredEventArgs() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionAudioProblem Problem();
    };

    struct SpeechChoiceRule : SpeechChoiceRuleT<SpeechChoiceRule>
    {
        SpeechChoiceRule() = default;

        void AddItem(winrt::Windows::Xbox::Speech::Recognition::ISpeechRuleItem const& item);
        bool EnabledOnLoad();
        void EnabledOnLoad(bool value);
        void Clear();
    };

    struct SpeechGarbageItemFactory : SpeechGarbageItemFactoryT<SpeechGarbageItemFactory>
    {
        SpeechGarbageItemFactory() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechGarbageItem CreateRuleItemGarbageWithMatchType(winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& matchType);
    };

    struct SpeechGarbageItem : SpeechGarbageItemT<SpeechGarbageItem>
    {
        SpeechGarbageItem() = default;

        void AddItem(winrt::Windows::Xbox::Speech::Recognition::ISpeechRuleItem const& item);
        winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType MatchType();
        void MatchType(winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& value);
        hstring Semantics();
        void Semantics(hstring const& value);
    };

    struct SpeechGraphRule : SpeechGraphRuleT<SpeechGraphRule>
    {
        SpeechGraphRule() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechGraphState CreateGraphState(winrt::Windows::Xbox::Speech::Recognition::SpeechGraphStateType const& stateType);
        void StartState(winrt::Windows::Xbox::Speech::Recognition::SpeechGraphState const& value);
        winrt::Windows::Xbox::Speech::Recognition::SpeechGraphState StartState();
        bool EnabledOnLoad();
        void EnabledOnLoad(bool value);
        void Clear();
    };

    struct SpeechGraphState : SpeechGraphStateT<SpeechGraphState>
    {
        SpeechGraphState() = default;

        void AddTransition(winrt::Windows::Xbox::Speech::Recognition::ISpeechRuleItem const& item, float weight, winrt::Windows::Xbox::Speech::Recognition::SpeechGraphState const& targetState);
        winrt::Windows::Xbox::Speech::Recognition::SpeechGraphStateType StateType();
    };

    struct SpeechHypothesisResultEventArgs : SpeechHypothesisResultEventArgsT<SpeechHypothesisResultEventArgs>
    {
        SpeechHypothesisResultEventArgs() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResult Hypothesis();
    };

    struct SpeechNullItem : SpeechNullItemT<SpeechNullItem>
    {
        SpeechNullItem() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType MatchType();
        void MatchType(winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& value);
        hstring Semantics();
        void Semantics(hstring const& value);
    };

    struct SpeechPhraseItem : SpeechPhraseItemT<SpeechPhraseItem>
    {
        SpeechPhraseItem() = default;

        hstring Text();
        void Text(hstring const& value);
        hstring Pronunciation();
        void Pronunciation(hstring const& value);
        hstring DisplayForm();
        void DisplayForm(hstring const& value);
        winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseSubsetMatchMode SubsetMatchMode();
        void SubsetMatchMode(winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseSubsetMatchMode const& value);
        winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType MatchType();
        void MatchType(winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& value);
        hstring Semantics();
        void Semantics(hstring const& value);
    };

    struct SpeechPronunciationDetail : SpeechPronunciationDetailT<SpeechPronunciationDetail>
    {
        SpeechPronunciationDetail() = default;

        hstring Pronunciation();
        winrt::Windows::Xbox::Speech::Recognition::SpeechPronunciationSource Source();
        winrt::Windows::Xbox::Speech::Recognition::SpeechPronunciationFormat Format();
    };

    struct SpeechRuleReferenceItem : SpeechRuleReferenceItemT<SpeechRuleReferenceItem>
    {
        SpeechRuleReferenceItem() = default;

        hstring RuleName();
        void RuleName(hstring const& value);
        winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType MatchType();
        void MatchType(winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& value);
        hstring Semantics();
        void Semantics(hstring const& value);
    };

    struct SpeechSequenceRule : SpeechSequenceRuleT<SpeechSequenceRule>
    {
        SpeechSequenceRule() = default;

        void AppendItem(winrt::Windows::Xbox::Speech::Recognition::ISpeechRuleItem const& item);
        bool EnabledOnLoad();
        void EnabledOnLoad(bool value);
        void Clear();
    };

    struct SpeechLanguage : SpeechLanguageT<SpeechLanguage>
    {
        SpeechLanguage() = default;

        hstring LanguageTag();
        bool IsDefault();
        winrt::Windows::Xbox::Speech::Recognition::SpeechLanguageInformation SpeechLanguageInformation();
    };

    struct SpeechLanguageInformation : SpeechLanguageInformationT<SpeechLanguageInformation>
    {
        SpeechLanguageInformation() = default;

        bool IsWakeOnVoiceSupported();
        bool IsApplicationLocalSpeechRecognitionSupported();
        bool IsSystemLocalSpeechRecognitionSupported();
        bool IsSystemCloudSpeechRecognitionSupported();
        winrt::Windows::Xbox::Speech::Recognition::SpeechLanguageSupportLevel SpeechLanguageSupportLevel();
    };

    struct SpeechLanguageSupportInternal : SpeechLanguageSupportInternalT<SpeechLanguageSupportInternal>
    {
        SpeechLanguageSupportInternal() = default;

        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechLanguage> GetSupportedSpeechLanguages(hstring const& languageTag);
        winrt::Windows::Xbox::Speech::Recognition::SpeechLanguage DefaultSpeechLanguage();
    };

    struct SpeechPhraseItemFactory : SpeechPhraseItemFactoryT<SpeechPhraseItemFactory>
    {
        SpeechPhraseItemFactory() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseItem CreateRuleItemPhrase(hstring const& text);
        winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseItem CreateRuleItemPhraseWithSemantics(hstring const& text, hstring const& semantics);
        winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseItem CreateRuleItemPhraseWithSemanticsAndMatchType(hstring const& text, hstring const& semantics, winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& matchType);
        winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseItem CreateRuleItemPhraseWithSemanticsAndMatchTypeAndPhraseMatchMode(hstring const& text, hstring const& semantics, winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& itemMatchType, winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseSubsetMatchMode const& phraseSubsetMatchMode);
    };
}

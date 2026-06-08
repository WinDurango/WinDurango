#include "Windows.Xbox.Speech.Recognition.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResult ContinuousSpeechRecognitionResultEventArgs::Result()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Result");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::ContinuousSpeechRecognitionStatus ContinuousSpeechRecognitionStatusEventArgs::Status()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Status");
        throw hresult_not_implemented();
    }

    winrt::hresult ContinuousSpeechRecognitionStatusEventArgs::ErrorCode()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: ErrorCode");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionAudioProblem SpeechAudioProblemOccurredEventArgs::Problem()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Problem");
        throw hresult_not_implemented();
    }

    void SpeechChoiceRule::AddItem(winrt::Windows::Xbox::Speech::Recognition::ISpeechRuleItem const& item)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddItem");
        throw hresult_not_implemented();
    }

    bool SpeechChoiceRule::EnabledOnLoad()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: EnabledOnLoad");
        throw hresult_not_implemented();
    }

    void SpeechChoiceRule::EnabledOnLoad(bool value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: EnabledOnLoad");
        throw hresult_not_implemented();
    }

    void SpeechChoiceRule::Clear()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Clear");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGarbageItem SpeechGarbageItemFactory::CreateRuleItemGarbageWithMatchType(winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& matchType)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateRuleItemGarbageWithMatchType");
        throw hresult_not_implemented();
    }

    void SpeechGarbageItem::AddItem(winrt::Windows::Xbox::Speech::Recognition::ISpeechRuleItem const& item)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddItem");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType SpeechGarbageItem::MatchType()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: MatchType");
        throw hresult_not_implemented();
    }

    void SpeechGarbageItem::MatchType(winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: MatchType");
        throw hresult_not_implemented();
    }

    hstring SpeechGarbageItem::Semantics()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Semantics");
        throw hresult_not_implemented();
    }

    void SpeechGarbageItem::Semantics(hstring const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Semantics");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGraphState SpeechGraphRule::CreateGraphState(winrt::Windows::Xbox::Speech::Recognition::SpeechGraphStateType const& stateType)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateGraphState");
        throw hresult_not_implemented();
    }

    void SpeechGraphRule::StartState(winrt::Windows::Xbox::Speech::Recognition::SpeechGraphState const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: StartState");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGraphState SpeechGraphRule::StartState()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: StartState");
        throw hresult_not_implemented();
    }

    bool SpeechGraphRule::EnabledOnLoad()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: EnabledOnLoad");
        throw hresult_not_implemented();
    }

    void SpeechGraphRule::EnabledOnLoad(bool value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: EnabledOnLoad");
        throw hresult_not_implemented();
    }

    void SpeechGraphRule::Clear()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Clear");
        throw hresult_not_implemented();
    }

    void SpeechGraphState::AddTransition(winrt::Windows::Xbox::Speech::Recognition::ISpeechRuleItem const& item, float weight, winrt::Windows::Xbox::Speech::Recognition::SpeechGraphState const& targetState)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddTransition");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGraphStateType SpeechGraphState::StateType()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: StateType");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRecognitionResult SpeechHypothesisResultEventArgs::Hypothesis()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Hypothesis");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType SpeechNullItem::MatchType()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: MatchType");
        throw hresult_not_implemented();
    }

    void SpeechNullItem::MatchType(winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: MatchType");
        throw hresult_not_implemented();
    }

    hstring SpeechNullItem::Semantics()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Semantics");
        throw hresult_not_implemented();
    }

    void SpeechNullItem::Semantics(hstring const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Semantics");
        throw hresult_not_implemented();
    }
    
    hstring SpeechPhraseItem::Text()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Text");
        throw hresult_not_implemented();
    }

    void SpeechPhraseItem::Text(hstring const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Text");
        throw hresult_not_implemented();
    }

    hstring SpeechPhraseItem::Pronunciation()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Pronunciation");
        throw hresult_not_implemented();
    }

    void SpeechPhraseItem::Pronunciation(hstring const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Pronunciation");
        throw hresult_not_implemented();
    }

    hstring SpeechPhraseItem::DisplayForm()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: DisplayForm");
        throw hresult_not_implemented();
    }

    void SpeechPhraseItem::DisplayForm(hstring const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: DisplayForm");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseSubsetMatchMode SpeechPhraseItem::SubsetMatchMode()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SubsetMatchMode");
        throw hresult_not_implemented();
    }

    void SpeechPhraseItem::SubsetMatchMode(winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseSubsetMatchMode const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SubsetMatchMode");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType SpeechPhraseItem::MatchType()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: MatchType");
        throw hresult_not_implemented();
    }

    void SpeechPhraseItem::MatchType(winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: MatchType");
        throw hresult_not_implemented();
    }

    hstring SpeechPhraseItem::Semantics()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Semantics");
        throw hresult_not_implemented();
    }

    void SpeechPhraseItem::Semantics(hstring const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Semantics");
        throw hresult_not_implemented();
    }

    hstring SpeechPronunciationDetail::Pronunciation()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Pronunciation");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechPronunciationSource SpeechPronunciationDetail::Source()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Source");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechPronunciationFormat SpeechPronunciationDetail::Format()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Format");
        throw hresult_not_implemented();
    }

    hstring SpeechRuleReferenceItem::RuleName()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: RuleName");
        throw hresult_not_implemented();
    }

    void SpeechRuleReferenceItem::RuleName(hstring const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: RuleName");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType SpeechRuleReferenceItem::MatchType()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: MatchType");
        throw hresult_not_implemented();
    }

    void SpeechRuleReferenceItem::MatchType(winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: MatchType");
        throw hresult_not_implemented();
    }

    hstring SpeechRuleReferenceItem::Semantics()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Semantics");
        throw hresult_not_implemented();
    }

    void SpeechRuleReferenceItem::Semantics(hstring const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Semantics");
        throw hresult_not_implemented();
    }

    void SpeechSequenceRule::AppendItem(winrt::Windows::Xbox::Speech::Recognition::ISpeechRuleItem const& item)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AppendItem");
        throw hresult_not_implemented();
    }

    bool SpeechSequenceRule::EnabledOnLoad()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: EnabledOnLoad");
        throw hresult_not_implemented();
    }

    void SpeechSequenceRule::EnabledOnLoad(bool value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: EnabledOnLoad");
        throw hresult_not_implemented();
    }

    void SpeechSequenceRule::Clear()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Clear");
        throw hresult_not_implemented();
    }

    hstring SpeechLanguage::LanguageTag()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: LanguageTag");
        throw hresult_not_implemented();
    }

    bool SpeechLanguage::IsDefault()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: IsDefault");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechLanguageInformation SpeechLanguage::SpeechLanguageInformation()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SpeechLanguageInformation");
        throw hresult_not_implemented();
    }

    bool SpeechLanguageInformation::IsWakeOnVoiceSupported()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: IsWakeOnVoiceSupported");
        throw hresult_not_implemented();
    }

    bool SpeechLanguageInformation::IsApplicationLocalSpeechRecognitionSupported()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: IsApplicationLocalSpeechRecognitionSupported");
        throw hresult_not_implemented();
    }

    bool SpeechLanguageInformation::IsSystemLocalSpeechRecognitionSupported()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: IsSystemLocalSpeechRecognitionSupported");
        throw hresult_not_implemented();
    }

    bool SpeechLanguageInformation::IsSystemCloudSpeechRecognitionSupported()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: IsSystemCloudSpeechRecognitionSupported");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechLanguageSupportLevel SpeechLanguageInformation::SpeechLanguageSupportLevel()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SpeechLanguageSupportLevel");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Speech::Recognition::SpeechLanguage> SpeechLanguageSupportInternal::GetSupportedSpeechLanguages(hstring const& languageTag)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: GetSupportedSpeechLanguages");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechLanguage SpeechLanguageSupportInternal::DefaultSpeechLanguage()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: DefaultSpeechLanguage");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseItem SpeechPhraseItemFactory::CreateRuleItemPhrase(hstring const& text)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateRuleItemPhrase");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseItem SpeechPhraseItemFactory::CreateRuleItemPhraseWithSemantics(hstring const& text, hstring const& semantics)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateRuleItemPhraseWithSemantics");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseItem SpeechPhraseItemFactory::CreateRuleItemPhraseWithSemanticsAndMatchType(hstring const& text, hstring const& semantics, winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& matchType)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateRuleItemPhraseWithSemanticsAndMatchType");
        throw hresult_not_implemented();
    }
    
    winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseItem SpeechPhraseItemFactory::CreateRuleItemPhraseWithSemanticsAndMatchTypeAndPhraseMatchMode(hstring const& text, hstring const& semantics, winrt::Windows::Xbox::Speech::Recognition::SpeechRuleItemMatchType const& itemMatchType, winrt::Windows::Xbox::Speech::Recognition::SpeechPhraseSubsetMatchMode const& phraseSubsetMatchMode)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateRuleItemPhraseWithSemanticsAndMatchTypeAndPhraseMatchMode");
        throw hresult_not_implemented();
    }
}

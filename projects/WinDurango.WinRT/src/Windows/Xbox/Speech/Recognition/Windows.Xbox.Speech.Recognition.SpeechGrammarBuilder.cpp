#include "Windows.Xbox.Speech.Recognition.SpeechGrammarBuilder.h"
#include "WinDurangoWinRT.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilder> SpeechGrammarBuilder::CreateFromSpeechGrammarAsync(winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar speechGrammar)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateFromSpeechGrammarAsync");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilder> SpeechGrammarBuilder::CreateFromStreamAsync(winrt::Windows::Storage::Streams::IRandomAccessStream stream)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateFromStreamAsync");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilderRuleSet SpeechGrammarBuilder::Rules()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Rules");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilderSemanticsFormat SpeechGrammarBuilder::SemanticsFormat()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SemanticsFormat");
        throw hresult_not_implemented();
    }

    void SpeechGrammarBuilder::SemanticsFormat(winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilderSemanticsFormat const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SemanticsFormat");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::ISpeechRule SpeechGrammarBuilder::RootRule()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: RootRule");
        throw hresult_not_implemented();
    }

    void SpeechGrammarBuilder::SetRootRule(hstring const& ruleKey)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: SetRootRule");
        throw hresult_not_implemented();
    }

    void SpeechGrammarBuilder::PronunciationFormat(winrt::Windows::Xbox::Speech::Recognition::SpeechPronunciationFormat const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: PronunciationFormat");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechPronunciationFormat SpeechGrammarBuilder::PronunciationFormat()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: PronunciationFormat");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechChoiceRule SpeechGrammarBuilderRuleSet::AddChoiceRuleFromList(hstring const& key, winrt::Windows::Foundation::Collections::IIterable<hstring> const& phrases)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddChoiceRuleFromList");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechChoiceRule SpeechGrammarBuilderRuleSet::AddChoiceRule(hstring const& key)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddChoiceRule");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechSequenceRule SpeechGrammarBuilderRuleSet::AddSequenceRuleFromArray(hstring const& key, winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Xbox::Speech::Recognition::ISpeechRuleItem> const& items)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddSequenceRuleFromArray");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechSequenceRule SpeechGrammarBuilderRuleSet::AddSequenceRule(hstring const& key)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddSequenceRule");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGraphRule SpeechGrammarBuilderRuleSet::AddGraphRule(hstring const& key)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddGraphRule");
        throw hresult_not_implemented();
    }

    void SpeechGrammarBuilderRuleSet::Clear()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Clear");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::ISpeechRule SpeechGrammarBuilderRuleSet::Remove(hstring const& key)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Remove");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Xbox::Speech::Recognition::ISpeechRule>> SpeechGrammarBuilderRuleSet::First()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: First");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::ISpeechRule SpeechGrammarBuilderRuleSet::Lookup(hstring const& key)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Lookup");
        throw hresult_not_implemented();
    }
    
    uint32_t SpeechGrammarBuilderRuleSet::Size()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Size");
        throw hresult_not_implemented();
    }

    bool SpeechGrammarBuilderRuleSet::HasKey(hstring const& key)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: HasKey");
        throw hresult_not_implemented();
    }

    void SpeechGrammarBuilderRuleSet::Split(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Xbox::Speech::Recognition::ISpeechRule>& first, winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Xbox::Speech::Recognition::ISpeechRule>& second)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Split");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilder SpeechGrammarBuilderFactory::CreateSpeechGrammarBuilder(hstring const& language)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: CreateSpeechGrammarBuilder");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar SpeechGrammarSet::AddGrammarFromList(hstring const& key, winrt::Windows::Foundation::Collections::IIterable<hstring> const& phrases)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddGrammarFromList");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar SpeechGrammarSet::AddGrammarFromUri(hstring const& key, winrt::Windows::Foundation::Uri const& grammarUri)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddGrammarFromUri");
        throw hresult_not_implemented();
    }
    
    winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar SpeechGrammarSet::AddGrammarFromStream(hstring const& key, winrt::Windows::Storage::Streams::IRandomAccessStream const& stream)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddGrammarFromStream");
        throw hresult_not_implemented();
    }

    void SpeechGrammarSet::Clear()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Clear");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar SpeechGrammarSet::Remove(hstring const& key)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Remove");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar SpeechGrammarSet::AddGrammarFromBuilder(hstring const& key, winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilder const& grammar)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: AddGrammarFromBuilder");
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar>> SpeechGrammarSet::First()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: First");
        throw hresult_not_implemented();
    }

    winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar SpeechGrammarSet::Lookup(hstring const& key)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Lookup");
        throw hresult_not_implemented();
    }

    uint32_t SpeechGrammarSet::Size()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Size");
        throw hresult_not_implemented();
    }

    bool SpeechGrammarSet::HasKey(hstring const& key)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: HasKey");
        throw hresult_not_implemented();
    }

    void SpeechGrammarSet::Split(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar>& first, winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar>& second)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Split");
        throw hresult_not_implemented();
    }

    bool SpeechGrammar::Enabled()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Enabled");
        throw hresult_not_implemented();
    }

    void SpeechGrammar::Enabled(bool value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Enabled");
        throw hresult_not_implemented();
    }
    
    winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarProbability SpeechGrammar::Probability()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Probability");
        throw hresult_not_implemented();
    }

    void SpeechGrammar::Probability(winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarProbability const& value)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: Probability");
        throw hresult_not_implemented();
    }

    void SpeechGrammar::EnableRule(hstring const& ruleName)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: EnableRule");
        throw hresult_not_implemented();
    }
    
    void SpeechGrammar::DisableRule(hstring const& ruleName)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Speech::Recognition", "Unimplemented: DisableRule");
        throw hresult_not_implemented();
    }
}

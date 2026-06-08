#pragma once
#include "Windows.Xbox.Speech.Recognition.SpeechGrammarBuilderRuleSet.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechGrammarBuilderFactory.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechGrammarSet.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechGrammar.g.h"
#include "Windows.Xbox.Speech.Recognition.SpeechGrammarBuilder.g.h"

namespace winrt::Windows::Xbox::Speech::Recognition::implementation
{
    struct SpeechGrammarBuilderRuleSet : SpeechGrammarBuilderRuleSetT<SpeechGrammarBuilderRuleSet>
    {
        SpeechGrammarBuilderRuleSet() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechChoiceRule AddChoiceRuleFromList(hstring const& key, winrt::Windows::Foundation::Collections::IIterable<hstring> const& phrases);
        winrt::Windows::Xbox::Speech::Recognition::SpeechChoiceRule AddChoiceRule(hstring const& key);
        winrt::Windows::Xbox::Speech::Recognition::SpeechSequenceRule AddSequenceRuleFromArray(hstring const& key, winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::Xbox::Speech::Recognition::ISpeechRuleItem> const& items);
        winrt::Windows::Xbox::Speech::Recognition::SpeechSequenceRule AddSequenceRule(hstring const& key);
        winrt::Windows::Xbox::Speech::Recognition::SpeechGraphRule AddGraphRule(hstring const& key);
        void Clear();
        winrt::Windows::Xbox::Speech::Recognition::ISpeechRule Remove(hstring const& key);
        winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Xbox::Speech::Recognition::ISpeechRule>> First();
        winrt::Windows::Xbox::Speech::Recognition::ISpeechRule Lookup(hstring const& key);
        uint32_t Size();
        bool HasKey(hstring const& key);
        void Split(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Xbox::Speech::Recognition::ISpeechRule>& first, winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Xbox::Speech::Recognition::ISpeechRule>& second);
    };

    struct SpeechGrammarBuilderFactory : SpeechGrammarBuilderFactoryT<SpeechGrammarBuilderFactory>
    {
        SpeechGrammarBuilderFactory() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilder CreateSpeechGrammarBuilder(hstring const& language);
    };

    struct SpeechGrammarSet : SpeechGrammarSetT<SpeechGrammarSet>
    {
        SpeechGrammarSet() = default;

        winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar AddGrammarFromList(hstring const& key, winrt::Windows::Foundation::Collections::IIterable<hstring> const& phrases);
        winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar AddGrammarFromUri(hstring const& key, winrt::Windows::Foundation::Uri const& grammarUri);
        winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar AddGrammarFromStream(hstring const& key, winrt::Windows::Storage::Streams::IRandomAccessStream const& stream);
        void Clear();
        winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar Remove(hstring const& key);
        winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar AddGrammarFromBuilder(hstring const& key, winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilder const& grammar);
        winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar>> First();
        winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar Lookup(hstring const& key);
        uint32_t Size();
        bool HasKey(hstring const& key);
        void Split(winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar>& first, winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar>& second);
    };

    struct SpeechGrammar : SpeechGrammarT<SpeechGrammar>
    {
        SpeechGrammar() = default;

        bool Enabled();
        void Enabled(bool value);
        winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarProbability Probability();
        void Probability(winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarProbability const& value);
        void EnableRule(hstring const& ruleName);
        void DisableRule(hstring const& ruleName);
    };

    struct SpeechGrammarBuilder : SpeechGrammarBuilderT<SpeechGrammarBuilder>
    {
        SpeechGrammarBuilder() = default;

        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilder> CreateFromSpeechGrammarAsync(winrt::Windows::Xbox::Speech::Recognition::SpeechGrammar speechGrammar);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilder> CreateFromStreamAsync(winrt::Windows::Storage::Streams::IRandomAccessStream stream);
        winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilderRuleSet Rules();
        winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilderSemanticsFormat SemanticsFormat();
        void SemanticsFormat(winrt::Windows::Xbox::Speech::Recognition::SpeechGrammarBuilderSemanticsFormat const& value);
        winrt::Windows::Xbox::Speech::Recognition::ISpeechRule RootRule();
        void SetRootRule(hstring const& ruleKey);
        void PronunciationFormat(winrt::Windows::Xbox::Speech::Recognition::SpeechPronunciationFormat const& value);
        winrt::Windows::Xbox::Speech::Recognition::SpeechPronunciationFormat PronunciationFormat();
    };
}
namespace winrt::Windows::Xbox::Speech::Recognition::factory_implementation
{
    struct SpeechGrammarBuilder : SpeechGrammarBuilderT<SpeechGrammarBuilder, implementation::SpeechGrammarBuilder>
    {
    };
}

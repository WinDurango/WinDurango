#include "Windows.Xbox.Chat.ChatSession.h"
#include "Windows.Xbox.Chat.ChatEncoder.h"
#include "Windows.Xbox.Chat.ChatDecoder.h"
#include "Windows.Xbox.Chat.Format.h"
#include "WinDurangoWinRT.h"
#include "Windows.Xbox.System.User.h"

namespace winrt::Windows::Xbox::Chat::implementation
{
    hstring ChatCaptureSource::Id()
    {
        return L"";
    }
    winrt::Windows::Xbox::Chat::Format ChatCaptureSource::Format()
    {
        return winrt::make<implementation::Format>();
    }
    void ChatCaptureSource::GetNextBuffer(winrt::Windows::Storage::Streams::IBuffer& buffer, winrt::Windows::Xbox::Chat::CaptureBufferStatus& status)
    {

    }
    void ChatCaptureSource::GetNextBufferWithCorrelationInfo(winrt::Windows::Storage::Streams::IBuffer& buffer, winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Chat::ChatUserCorrelation>& info, winrt::Windows::Xbox::Chat::CaptureBufferStatus& status)
    {

    }
    winrt::Windows::Xbox::Chat::ChatRestriction ChatCaptureSource::GetRelationship(hstring const& targetId)
    {
        return ChatRestriction::None;
    }
    hstring ChatRenderTarget::Id()
    {
        return L"";
    }
    winrt::Windows::Xbox::Chat::ChatRestriction ChatRenderTarget::GetRelationship(hstring const& source)
    {
        return ChatRestriction::None;
    }
    void ChatRenderTarget::BeginMix()
    {

    }
    winrt::Windows::Xbox::Chat::ChatRestriction ChatRenderTarget::AddMixBuffer(hstring const& source, winrt::Windows::Xbox::Chat::Format const& format, winrt::Windows::Storage::Streams::IBuffer const& buffer)
    {
        return ChatRestriction::None;
    }
    void ChatRenderTarget::ResetMix()
    {

    }
    void ChatRenderTarget::SubmitMix()
    {

    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Chat::ChatCaptureSource> ChatSessionState::CaptureSources()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Chat::ChatSessionState", "Unimplemented: CaptureSources");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Chat::ChatRenderTarget> ChatSessionState::RenderTargets()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Chat::ChatSessionState", "Unimplemented: RenderTargets");
        throw hresult_not_implemented();
    }
    ChatSession::ChatSession(winrt::Windows::Foundation::TimeSpan const& time, winrt::Windows::Xbox::Chat::ChatFeatures const& enabledFeatures)
    {

    }
    ChatSession::ChatSession(winrt::Windows::Foundation::TimeSpan const& time, uint32_t processorAffinity, winrt::Windows::Xbox::Chat::ChatFeatures const& enabledFeatures)
    {

    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Chat::ChatChannel> ChatSession::Channels()
    {
        return winrt::single_threaded_vector<winrt::Windows::Xbox::Chat::ChatChannel>().GetView();
    }
    winrt::event_token ChatSession::StateChangedEvent(winrt::Windows::Xbox::Chat::ChatSessionStateChangedHandler const& handler)
    {
        return e_StateChangedEvent.add(handler);
    }
    void ChatSession::StateChangedEvent(winrt::event_token const& token) noexcept
    {
        e_StateChangedEvent.remove(token);
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Chat::ChatSessionState> ChatSession::GetStateAsync()
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Chat::ChatSession", "Unimplemented: GetStateAsync");
        throw hresult_not_implemented();
    }
    int32_t ChatSession::TranscriptionEnabled()
    {
        return transcriptionEnabled;
    }
    void ChatSession::TranscriptionEnabled(int32_t value)
    {
        transcriptionEnabled = value;
    }
    winrt::Windows::Xbox::Chat::ChatEncoder ChatSession::CreateTranscribingEncoder(winrt::Windows::Xbox::Chat::ChatParticipant const& participant, winrt::Windows::Xbox::Chat::Format const& format, winrt::Windows::Xbox::Chat::EncodingQuality const& quality)
    {
        return winrt::make<implementation::ChatEncoder>();
    }
    winrt::event_token ChatSession::TranscribedTextReadyEvent(winrt::Windows::Xbox::Chat::ChatParticipantTranscribedTextReadyHandler const& handler)
    {
        return e_TranscribedTextReadyEvent.add(handler);
    }
    void ChatSession::TranscribedTextReadyEvent(winrt::event_token const& token) noexcept
    {
        e_TranscribedTextReadyEvent.remove(token);
    }
    winrt::Windows::Xbox::Chat::ChatRestriction ChatSession::GetParticipantRelationship(winrt::Windows::Xbox::Chat::ChatParticipant const& source, winrt::Windows::Xbox::Chat::ChatParticipant const& target)
    {
        return ChatRestriction::None;
    }
    winrt::Windows::Xbox::System::AudioDeviceInfo ChatSession::GetDedicatedSynthesisDevice(winrt::Windows::Xbox::Chat::ChatParticipant const& participant)
    {
        p_wd->log.Warn("WinDurango::WinRT::Windows::Xbox::Chat::ChatSession", "Unimplemented: GetDedicatedSynthesisDevice");
        throw hresult_not_implemented();
    }
}

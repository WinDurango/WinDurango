#include "Windows.Kinect.Body.h"
#include "WinDurangoKinect.h"

namespace winrt::Windows::Kinect::implementation
{
    void BodyFrame::GetAndRefreshBodyData(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Kinect::Body> const& bodies)
    {

    }
    int32_t BodyFrame::BodyCount()
    {
        return 1;
    }
    winrt::Windows::Kinect::Vector4 BodyFrame::FloorClipPlane()
    {
        ::Vector4 pVector4{};
        m_pBodyFrame->get_FloorClipPlane(&pVector4);
        
        winrt::Windows::Kinect::Vector4 Return{};
        Return.X = pVector4.x;
        Return.Y = pVector4.y;
        Return.Z = pVector4.z;
        Return.W = pVector4.w;
        return Return;
    }
    winrt::Windows::Foundation::TimeSpan BodyFrame::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrame", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyFrameSource BodyFrame::BodyFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrame", "Unimplemented: BodyFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyFrameReference BodyFrameArrivedEventArgs::FrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrameArrivedEventArgs", "Unimplemented: FrameReference");
        throw hresult_not_implemented();
    }
    winrt::event_token BodyFrameReader::FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::BodyFrameReader, winrt::Windows::Kinect::BodyFrameArrivedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    void BodyFrameReader::FrameArrived(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyFrame BodyFrameReader::AcquireLatestFrame()
    {
        //p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrame", "Unimplemented: AcquireLatestFrame");
        throw hresult_not_implemented();
    }
    bool BodyFrameReader::IsPaused()
    {
        BOOLEAN isPaused = 0;
        m_pBodyFrameReader->get_IsPaused(&isPaused);
        return (bool)isPaused;
    }
    void BodyFrameReader::IsPaused(bool value)
    {
        m_pBodyFrameReader->put_IsPaused((BOOLEAN)value);
    }
    winrt::Windows::Kinect::BodyFrameSource BodyFrameReader::BodyFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrameReader", "Unimplemented: BodyFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyFrame BodyFrameReference::AcquireFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrameReference", "Unimplemented: AcquireFrame");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan BodyFrameReference::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrameReference", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::event_token BodyFrameSource::FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::BodyFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrameSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    void BodyFrameSource::FrameCaptured(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrameSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    bool BodyFrameSource::IsActive()
    {
        BOOLEAN isActive = 0;
        m_pBodyFrameSource->get_IsActive(&isActive);
        return (bool)isActive;
                                           
    }
    int32_t BodyFrameSource::BodyCount()
    {
        INT32 bodyCount = 0;
        m_pBodyFrameSource->get_BodyCount(&bodyCount);
        return bodyCount;
    }
    winrt::Windows::Kinect::BodyFrameReader BodyFrameSource::OpenReader()
    {
        ::IBodyFrameReader *pBodyFrameReader = nullptr;
        m_pBodyFrameSource->OpenReader(&pBodyFrameReader);
        return winrt::make<implementation::BodyFrameReader>(pBodyFrameReader);
    }
    winrt::Windows::Kinect::KinectSensor BodyFrameSource::KinectSensor()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyFrameSource", "Unimplemented: KinectSensor");
        throw hresult_not_implemented();
    }
    void BodyFrameSource::OverrideHandTracking(uint64_t trackingId)
    {
        m_pBodyFrameSource->OverrideHandTracking(trackingId);
    }
    void BodyFrameSource::OverrideAndReplaceHandTracking(uint64_t oldTrackingId, uint64_t newTrackingId)
    {
        m_pBodyFrameSource->OverrideAndReplaceHandTracking(oldTrackingId, newTrackingId);
    }
    com_array<uint8_t> BodyIndexFrame::CopyFrameDataToArray()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrame", "Unimplemented: CopyFrameDataToArray");
        throw hresult_not_implemented();
    }
    void BodyIndexFrame::CopyFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrame", "Unimplemented: CopyFrameDataToBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::Streams::IBuffer BodyIndexFrame::LockImageBuffer()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrame", "Unimplemented: LockImageBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameDescription BodyIndexFrame::FrameDescription()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrame", "Unimplemented: FrameDescription");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan BodyIndexFrame::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrame", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyIndexFrameSource BodyIndexFrame::BodyIndexFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrame", "Unimplemented: BodyIndexFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyIndexFrameReference BodyIndexFrameArrivedEventArgs::FrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameArrivedEventArgs", "Unimplemented: FrameReference");
        throw hresult_not_implemented();
    }
    winrt::event_token BodyIndexFrameReader::FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::BodyIndexFrameReader, winrt::Windows::Kinect::BodyIndexFrameArrivedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    void BodyIndexFrameReader::FrameArrived(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyIndexFrame BodyIndexFrameReader::AcquireLatestFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameReader", "Unimplemented: AcquireLatestFrame");
        throw hresult_not_implemented();
    }
    bool BodyIndexFrameReader::IsPaused()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    void BodyIndexFrameReader::IsPaused(bool value)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyIndexFrameSource BodyIndexFrameReader::BodyIndexFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameReader", "Unimplemented: BodyIndexFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyIndexFrame BodyIndexFrameReference::AcquireFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameReference", "Unimplemented: AcquireFrame");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan BodyIndexFrameReference::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameReference", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::event_token BodyIndexFrameSource::FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::BodyIndexFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    void BodyIndexFrameSource::FrameCaptured(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    bool BodyIndexFrameSource::IsActive()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameSource", "Unimplemented: IsActive");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyIndexFrameReader BodyIndexFrameSource::OpenReader()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameSource", "Unimplemented: OpenReader");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameDescription BodyIndexFrameSource::FrameDescription()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameSource", "Unimplemented: FrameDescription");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::KinectSensor BodyIndexFrameSource::KinectSensor()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::BodyIndexFrameSource", "Unimplemented: KinectSensor");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IMapView<winrt::Windows::Kinect::JointType, winrt::Windows::Kinect::Joint> Body::Joints()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: Joints");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IMapView<winrt::Windows::Kinect::JointType, winrt::Windows::Kinect::JointOrientation> Body::JointOrientations()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: JointOrientations");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::DetectionResult Body::Engaged()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: Engaged");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IMapView<winrt::Windows::Kinect::Expression, winrt::Windows::Kinect::DetectionResult> Body::Expressions()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: Expressions");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IMapView<winrt::Windows::Kinect::Activity, winrt::Windows::Kinect::DetectionResult> Body::Activities()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: Activities");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IMapView<winrt::Windows::Kinect::Appearance, winrt::Windows::Kinect::DetectionResult> Body::Appearance()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: Appearance");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::HandState Body::HandLeftState()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: HandLeftState");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::TrackingConfidence Body::HandLeftConfidence()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: HandLeftConfidence");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::HandState Body::HandRightState()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: HandRightState");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::TrackingConfidence Body::HandRightConfidence()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: HandRightConfidence");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameEdges Body::ClippedEdges()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: ClippedEdges");
        throw hresult_not_implemented();
    }
    uint64_t Body::TrackingId()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: TrackingId");
        throw hresult_not_implemented();
    }
    bool Body::IsTracked()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: IsTracked");
        throw hresult_not_implemented();
    }
    bool Body::IsRestricted()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: IsRestricted");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Point Body::Lean()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: Lean");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::TrackingState Body::LeanTrackingState()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::Body", "Unimplemented: LeanTrackingState");
        throw hresult_not_implemented();
    }
}

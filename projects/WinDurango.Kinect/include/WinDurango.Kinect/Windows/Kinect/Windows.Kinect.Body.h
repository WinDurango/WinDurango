#pragma once
#include <Kinect.h>
#include "Windows.Kinect.BodyFrame.g.h"
#include "Windows.Kinect.BodyFrameArrivedEventArgs.g.h"
#include "Windows.Kinect.BodyFrameReader.g.h"
#include "Windows.Kinect.BodyFrameReference.g.h"
#include "Windows.Kinect.BodyFrameSource.g.h"
#include "Windows.Kinect.BodyIndexFrame.g.h"
#include "Windows.Kinect.BodyIndexFrameArrivedEventArgs.g.h"
#include "Windows.Kinect.BodyIndexFrameReader.g.h"
#include "Windows.Kinect.BodyIndexFrameReference.g.h"
#include "Windows.Kinect.BodyIndexFrameSource.g.h"
#include "Windows.Kinect.Body.g.h"

namespace winrt::Windows::Kinect::implementation
{
    struct BodyFrame : BodyFrameT<BodyFrame>
    {
        BodyFrame(::IBodyFrame *pBodyFrame) : m_pBodyFrame(pBodyFrame) {}

        void GetAndRefreshBodyData(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Kinect::Body> const& bodies);
        int32_t BodyCount();
        winrt::Windows::Kinect::Vector4 FloorClipPlane();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
        winrt::Windows::Kinect::BodyFrameSource BodyFrameSource();

    private:
        ::IBodyFrame *m_pBodyFrame = nullptr;
    };

    struct BodyFrameArrivedEventArgs : BodyFrameArrivedEventArgsT<BodyFrameArrivedEventArgs>
    {
        BodyFrameArrivedEventArgs() = default;

        winrt::Windows::Kinect::BodyFrameReference FrameReference();
    };

    struct BodyFrameReader : BodyFrameReaderT<BodyFrameReader>
    {
        BodyFrameReader(::IBodyFrameReader *pBodyFrameReader) : m_pBodyFrameReader(pBodyFrameReader) {}

        winrt::event_token FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::BodyFrameReader, winrt::Windows::Kinect::BodyFrameArrivedEventArgs> const& handler);
        void FrameArrived(winrt::event_token const& token) noexcept;
        winrt::Windows::Kinect::BodyFrame AcquireLatestFrame();
        bool IsPaused();
        void IsPaused(bool value);
        winrt::Windows::Kinect::BodyFrameSource BodyFrameSource();

    private:
        ::IBodyFrameReader *m_pBodyFrameReader = nullptr;
    };

    struct BodyFrameReference : BodyFrameReferenceT<BodyFrameReference>
    {
        BodyFrameReference() = default;

        winrt::Windows::Kinect::BodyFrame AcquireFrame();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
    };

    struct BodyFrameSource : BodyFrameSourceT<BodyFrameSource>
    {
        BodyFrameSource(::IBodyFrameSource *pBodyFrameSource) : m_pBodyFrameSource(pBodyFrameSource) {}

        winrt::event_token FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::BodyFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler);
        void FrameCaptured(winrt::event_token const& token) noexcept;
        bool IsActive();
        int32_t BodyCount();
        winrt::Windows::Kinect::BodyFrameReader OpenReader();
        winrt::Windows::Kinect::KinectSensor KinectSensor();
        void OverrideHandTracking(uint64_t trackingId);
        void OverrideAndReplaceHandTracking(uint64_t oldTrackingId, uint64_t newTrackingId);

    private:
        ::IBodyFrameSource *m_pBodyFrameSource = nullptr;
    };

    struct BodyIndexFrame : BodyIndexFrameT<BodyIndexFrame>
    {
        BodyIndexFrame() = default;

        com_array<uint8_t> CopyFrameDataToArray();
        void CopyFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer);
        winrt::Windows::Storage::Streams::IBuffer LockImageBuffer();
        winrt::Windows::Kinect::FrameDescription FrameDescription();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
        winrt::Windows::Kinect::BodyIndexFrameSource BodyIndexFrameSource();
    };

    struct BodyIndexFrameArrivedEventArgs : BodyIndexFrameArrivedEventArgsT<BodyIndexFrameArrivedEventArgs>
    {
        BodyIndexFrameArrivedEventArgs() = default;

        winrt::Windows::Kinect::BodyIndexFrameReference FrameReference();
    };

    struct BodyIndexFrameReader : BodyIndexFrameReaderT<BodyIndexFrameReader>
    {
        BodyIndexFrameReader() = default;

        winrt::event_token FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::BodyIndexFrameReader, winrt::Windows::Kinect::BodyIndexFrameArrivedEventArgs> const& handler);
        void FrameArrived(winrt::event_token const& token) noexcept;
        winrt::Windows::Kinect::BodyIndexFrame AcquireLatestFrame();
        bool IsPaused();
        void IsPaused(bool value);
        winrt::Windows::Kinect::BodyIndexFrameSource BodyIndexFrameSource();
    };

    struct BodyIndexFrameReference : BodyIndexFrameReferenceT<BodyIndexFrameReference>
    {
        BodyIndexFrameReference() = default;

        winrt::Windows::Kinect::BodyIndexFrame AcquireFrame();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
    };

    struct BodyIndexFrameSource : BodyIndexFrameSourceT<BodyIndexFrameSource>
    {
        BodyIndexFrameSource() = default;

        winrt::event_token FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::BodyIndexFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler);
        void FrameCaptured(winrt::event_token const& token) noexcept;
        bool IsActive();
        winrt::Windows::Kinect::BodyIndexFrameReader OpenReader();
        winrt::Windows::Kinect::FrameDescription FrameDescription();
        winrt::Windows::Kinect::KinectSensor KinectSensor();
    };

    struct Body : BodyT<Body>
    {
        Body() = default;

        winrt::Windows::Foundation::Collections::IMapView<winrt::Windows::Kinect::JointType, winrt::Windows::Kinect::Joint> Joints();
        winrt::Windows::Foundation::Collections::IMapView<winrt::Windows::Kinect::JointType, winrt::Windows::Kinect::JointOrientation> JointOrientations();
        winrt::Windows::Kinect::DetectionResult Engaged();
        winrt::Windows::Foundation::Collections::IMapView<winrt::Windows::Kinect::Expression, winrt::Windows::Kinect::DetectionResult> Expressions();
        winrt::Windows::Foundation::Collections::IMapView<winrt::Windows::Kinect::Activity, winrt::Windows::Kinect::DetectionResult> Activities();
        winrt::Windows::Foundation::Collections::IMapView<winrt::Windows::Kinect::Appearance, winrt::Windows::Kinect::DetectionResult> Appearance();
        winrt::Windows::Kinect::HandState HandLeftState();
        winrt::Windows::Kinect::TrackingConfidence HandLeftConfidence();
        winrt::Windows::Kinect::HandState HandRightState();
        winrt::Windows::Kinect::TrackingConfidence HandRightConfidence();
        winrt::Windows::Kinect::FrameEdges ClippedEdges();
        uint64_t TrackingId();
        bool IsTracked();
        bool IsRestricted();
        winrt::Windows::Foundation::Point Lean();
        winrt::Windows::Kinect::TrackingState LeanTrackingState();
    };
}
namespace winrt::Windows::Kinect::factory_implementation
{
    struct Body : BodyT<Body, implementation::Body>
    {
    };
}

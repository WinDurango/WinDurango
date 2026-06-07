#pragma once
#pragma comment(lib, "kinect20.lib")
#include <kinect.h>
#include "Windows.Kinect.AudioBeam.g.h"
#include "Windows.Kinect.AudioBeamFrame.g.h"
#include "Windows.Kinect.AudioBeamFrameArrivedEventArgs.g.h"
#include "Windows.Kinect.AudioBeamFrameReader.g.h"
#include "Windows.Kinect.AudioBeamFrameReference.g.h"
#include "Windows.Kinect.AudioBeamSubFrame.g.h"
#include "Windows.Kinect.AudioBodyCorrelation.g.h"
#include "Windows.Kinect.AudioSource.g.h"
#include "Windows.Kinect.ColorCameraSettings.g.h"
#include "Windows.Kinect.ColorFrame.g.h"
#include "Windows.Kinect.ColorFrameArrivedEventArgs.g.h"
#include "Windows.Kinect.ColorFrameReader.g.h"
#include "Windows.Kinect.ColorFrameReference.g.h"
#include "Windows.Kinect.ColorFrameSource.g.h"
#include "Windows.Kinect.DepthFrame.g.h"
#include "Windows.Kinect.DepthFrameArrivedEventArgs.g.h"
#include "Windows.Kinect.DepthFrameReader.g.h"
#include "Windows.Kinect.DepthFrameReference.g.h"
#include "Windows.Kinect.DepthFrameSource.g.h"
#include "Windows.Kinect.InfraredFrame.g.h"
#include "Windows.Kinect.InfraredFrameArrivedEventArgs.g.h"
#include "Windows.Kinect.InfraredFrameReader.g.h"
#include "Windows.Kinect.InfraredFrameReference.g.h"
#include "Windows.Kinect.InfraredFrameSource.g.h"
#include "Windows.Kinect.LongExposureInfraredFrame.g.h"
#include "Windows.Kinect.LongExposureInfraredFrameArrivedEventArgs.g.h"
#include "Windows.Kinect.LongExposureInfraredFrameReader.g.h"
#include "Windows.Kinect.LongExposureInfraredFrameReference.g.h"
#include "Windows.Kinect.LongExposureInfraredFrameSource.g.h"
#include "Windows.Kinect.MultiSourceFrame.g.h"
#include "Windows.Kinect.MultiSourceFrameArrivedEventArgs.g.h"
#include "Windows.Kinect.MultiSourceFrameReader.g.h"
#include "Windows.Kinect.MultiSourceFrameReference.g.h"
#include "Windows.Kinect.CoordinateMapper.g.h"
#include "Windows.Kinect.CoordinateMappingChangedEventArgs.g.h"
#include "Windows.Kinect.FrameDescription.g.h"
#include "Windows.Kinect.FrameCapturedEventArgs.g.h"
#include "Windows.Kinect.IsAvailableChangedEventArgs.g.h"
#include "Windows.Kinect.KinectSensor.g.h"

namespace winrt::Windows::Kinect::implementation
{
    struct AudioBeam : AudioBeamT<AudioBeam>
    {
        AudioBeam() = default;

        winrt::Windows::Kinect::AudioSource AudioSource();
        winrt::Windows::Kinect::AudioBeamMode AudioBeamMode();
        void AudioBeamMode(winrt::Windows::Kinect::AudioBeamMode const& value);
        float BeamAngle();
        void BeamAngle(float value);
        float BeamAngleConfidence();
        winrt::Windows::Storage::Streams::IInputStream OpenInputStream();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
    };

    struct AudioBeamFrame : AudioBeamFrameT<AudioBeamFrame>
    {
        AudioBeamFrame() = default;

        winrt::Windows::Kinect::AudioSource AudioSource();
        winrt::Windows::Foundation::TimeSpan Duration();
        winrt::Windows::Kinect::AudioBeam AudioBeam();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Kinect::AudioBeamSubFrame> SubFrames();
        winrt::Windows::Foundation::TimeSpan RelativeTimeStart();
    };

    struct AudioBeamFrameArrivedEventArgs : AudioBeamFrameArrivedEventArgsT<AudioBeamFrameArrivedEventArgs>
    {
        AudioBeamFrameArrivedEventArgs() = default;

        winrt::Windows::Kinect::AudioBeamFrameReference FrameReference();
    };

    struct AudioBeamFrameReader : AudioBeamFrameReaderT<AudioBeamFrameReader>
    {
        AudioBeamFrameReader() = default;

        winrt::event_token FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::AudioBeamFrameReader, winrt::Windows::Kinect::AudioBeamFrameArrivedEventArgs> const& handler);
        void FrameArrived(winrt::event_token const& token) noexcept;
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Kinect::AudioBeamFrame> AcquireLatestBeamFrames();
        bool IsPaused();
        void IsPaused(bool value);
        winrt::Windows::Kinect::AudioSource AudioSource();
    };

    struct AudioBeamFrameReference : AudioBeamFrameReferenceT<AudioBeamFrameReference>
    {
        AudioBeamFrameReference() = default;

        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Kinect::AudioBeamFrame> AcquireBeamFrames();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
    };

    struct AudioBeamSubFrame : AudioBeamSubFrameT<AudioBeamSubFrame>
    {
        AudioBeamSubFrame() = default;

        uint32_t FrameLengthInBytes();
        winrt::Windows::Foundation::TimeSpan Duration();
        float BeamAngle();
        float BeamAngleConfidence();
        winrt::Windows::Kinect::AudioBeamMode AudioBeamMode();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Kinect::AudioBodyCorrelation> AudioBodyCorrelations();
        com_array<uint8_t> CopyFrameDataToArray();
        void CopyFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer);
        winrt::Windows::Storage::Streams::IBuffer LockAudioBuffer();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
    };

    struct AudioBodyCorrelation : AudioBodyCorrelationT<AudioBodyCorrelation>
    {
        AudioBodyCorrelation() = default;

        uint64_t BodyTrackingId();
    };

    struct AudioSource : AudioSourceT<AudioSource>
    {
        AudioSource() = default;

        winrt::Windows::Kinect::KinectAudioCalibrationState AudioCalibrationState();
        winrt::event_token FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::AudioSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler);
        void FrameCaptured(winrt::event_token const& token) noexcept;
        winrt::Windows::Kinect::KinectSensor KinectSensor();
        bool IsActive();
        uint32_t SubFrameLengthInBytes();
        winrt::Windows::Foundation::TimeSpan SubFrameDuration();
        uint32_t MaxSubFrameCount();
        winrt::Windows::Kinect::AudioBeamFrameReader OpenReader();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Kinect::AudioBeam> AudioBeams();
    };

    struct ColorCameraSettings : ColorCameraSettingsT<ColorCameraSettings>
    {
        ColorCameraSettings() = default;

        winrt::Windows::Foundation::TimeSpan ExposureTime();
        winrt::Windows::Foundation::TimeSpan FrameInterval();
        float Gain();
        float Gamma();
    };

    struct ColorFrame : ColorFrameT<ColorFrame>
    {
        ColorFrame() = default;

        winrt::Windows::Kinect::ColorImageFormat RawColorImageFormat();
        winrt::Windows::Kinect::FrameDescription FrameDescription();
        com_array<uint8_t> CopyRawFrameDataToArray();
        void CopyRawFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer);
        winrt::Windows::Storage::Streams::IBuffer LockRawImageBuffer();
        com_array<uint8_t> CopyConvertedFrameDataToArray(winrt::Windows::Kinect::ColorImageFormat const& colorFormat);
        void CopyConvertedFrameDataToBuffer(winrt::Windows::Storage::Streams::Buffer const& buffer, winrt::Windows::Kinect::ColorImageFormat const& colorFormat);
        winrt::Windows::Kinect::FrameDescription CreateFrameDescription(winrt::Windows::Kinect::ColorImageFormat const& format);
        winrt::Windows::Kinect::ColorCameraSettings ColorCameraSettings();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
        winrt::Windows::Kinect::ColorFrameSource ColorFrameSource();
    };

    struct ColorFrameArrivedEventArgs : ColorFrameArrivedEventArgsT<ColorFrameArrivedEventArgs>
    {
        ColorFrameArrivedEventArgs() = default;

        winrt::Windows::Kinect::ColorFrameReference FrameReference();
    };

    struct ColorFrameReader : ColorFrameReaderT<ColorFrameReader>
    {
        ColorFrameReader() = default;

        winrt::event_token FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::ColorFrameReader, winrt::Windows::Kinect::ColorFrameArrivedEventArgs> const& handler);
        void FrameArrived(winrt::event_token const& token) noexcept;
        winrt::Windows::Kinect::ColorFrame AcquireLatestFrame();
        bool IsPaused();
        void IsPaused(bool value);
        winrt::Windows::Kinect::ColorFrameSource ColorFrameSource();
    };

    struct ColorFrameReference : ColorFrameReferenceT<ColorFrameReference>
    {
        ColorFrameReference() = default;

        winrt::Windows::Kinect::ColorFrame AcquireFrame();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
    };

    struct ColorFrameSource : ColorFrameSourceT<ColorFrameSource>
    {
        ColorFrameSource(::IColorFrameSource *pColorFrameSource) : m_pColorFrameSource(pColorFrameSource) {}

        winrt::event_token FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::ColorFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler);
        void FrameCaptured(winrt::event_token const& token) noexcept;
        bool IsActive();
        winrt::Windows::Kinect::ColorFrameReader OpenReader();
        winrt::Windows::Kinect::FrameDescription CreateFrameDescription(winrt::Windows::Kinect::ColorImageFormat const& format);
        winrt::Windows::Kinect::FrameDescription FrameDescription();
        winrt::Windows::Kinect::KinectSensor KinectSensor();

        private:
        ::IColorFrameSource *m_pColorFrameSource = nullptr;
    };

    struct DepthFrame : DepthFrameT<DepthFrame>
    {
        DepthFrame() = default;

        com_array<uint16_t> CopyFrameDataToArray();
        void CopyFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer);
        winrt::Windows::Storage::Streams::IBuffer LockImageBuffer();
        winrt::Windows::Kinect::FrameDescription FrameDescription();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
        winrt::Windows::Kinect::DepthFrameSource DepthFrameSource();
        uint16_t DepthMinReliableDistance();
        uint16_t DepthMaxReliableDistance();
    };

    struct DepthFrameArrivedEventArgs : DepthFrameArrivedEventArgsT<DepthFrameArrivedEventArgs>
    {
        DepthFrameArrivedEventArgs() = default;

        winrt::Windows::Kinect::DepthFrameReference FrameReference();
    };

    struct DepthFrameReader : DepthFrameReaderT<DepthFrameReader>
    {
        DepthFrameReader() = default;

        winrt::event_token FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::DepthFrameReader, winrt::Windows::Kinect::DepthFrameArrivedEventArgs> const& handler);
        void FrameArrived(winrt::event_token const& token) noexcept;
        winrt::Windows::Kinect::DepthFrame AcquireLatestFrame();
        bool IsPaused();
        void IsPaused(bool value);
        winrt::Windows::Kinect::DepthFrameSource DepthFrameSource();
    };

    struct DepthFrameReference : DepthFrameReferenceT<DepthFrameReference>
    {
        DepthFrameReference() = default;

        winrt::Windows::Kinect::DepthFrame AcquireFrame();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
    };

    struct DepthFrameSource : DepthFrameSourceT<DepthFrameSource>
    {
        DepthFrameSource() = default;

        winrt::event_token FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::DepthFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler);
        void FrameCaptured(winrt::event_token const& token) noexcept;
        bool IsActive();
        winrt::Windows::Kinect::DepthFrameReader OpenReader();
        uint16_t DepthMinReliableDistance();
        uint16_t DepthMaxReliableDistance();
        winrt::Windows::Kinect::FrameDescription FrameDescription();
        winrt::Windows::Kinect::KinectSensor KinectSensor();
    };

    struct InfraredFrame : InfraredFrameT<InfraredFrame>
    {
        InfraredFrame() = default;

        com_array<uint16_t> CopyFrameDataToArray();
        void CopyFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer);
        winrt::Windows::Storage::Streams::IBuffer LockImageBuffer();
        winrt::Windows::Kinect::FrameDescription FrameDescription();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
        winrt::Windows::Kinect::InfraredFrameSource InfraredFrameSource();
    };

    struct InfraredFrameArrivedEventArgs : InfraredFrameArrivedEventArgsT<InfraredFrameArrivedEventArgs>
    {
        InfraredFrameArrivedEventArgs() = default;

        winrt::Windows::Kinect::InfraredFrameReference FrameReference();
    };

    struct InfraredFrameReader : InfraredFrameReaderT<InfraredFrameReader>
    {
        InfraredFrameReader() = default;

        winrt::event_token FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::InfraredFrameReader, winrt::Windows::Kinect::InfraredFrameArrivedEventArgs> const& handler);
        void FrameArrived(winrt::event_token const& token) noexcept;
        winrt::Windows::Kinect::InfraredFrame AcquireLatestFrame();
        bool IsPaused();
        void IsPaused(bool value);
        winrt::Windows::Kinect::InfraredFrameSource InfraredFrameSource();
    };

    struct InfraredFrameReference : InfraredFrameReferenceT<InfraredFrameReference>
    {
        InfraredFrameReference() = default;

        winrt::Windows::Kinect::InfraredFrame AcquireFrame();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
    };

    struct InfraredFrameSource : InfraredFrameSourceT<InfraredFrameSource>
    {
        InfraredFrameSource() = default;

        winrt::event_token FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::InfraredFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler);
        void FrameCaptured(winrt::event_token const& token) noexcept;
        bool IsActive();
        winrt::Windows::Kinect::InfraredFrameReader OpenReader();
        winrt::Windows::Kinect::FrameDescription FrameDescription();
        winrt::Windows::Kinect::KinectSensor KinectSensor();
    };

    struct LongExposureInfraredFrame : LongExposureInfraredFrameT<LongExposureInfraredFrame>
    {
        LongExposureInfraredFrame() = default;

        com_array<uint16_t> CopyFrameDataToArray();
        void CopyFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer);
        winrt::Windows::Storage::Streams::IBuffer LockImageBuffer();
        winrt::Windows::Kinect::FrameDescription FrameDescription();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
        winrt::Windows::Kinect::LongExposureInfraredFrameSource LongExposureInfraredFrameSource();
    };

    struct LongExposureInfraredFrameArrivedEventArgs : LongExposureInfraredFrameArrivedEventArgsT<LongExposureInfraredFrameArrivedEventArgs>
    {
        LongExposureInfraredFrameArrivedEventArgs() = default;

        winrt::Windows::Kinect::LongExposureInfraredFrameReference FrameReference();
    };

    struct LongExposureInfraredFrameReader : LongExposureInfraredFrameReaderT<LongExposureInfraredFrameReader>
    {
        LongExposureInfraredFrameReader() = default;

        winrt::event_token FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::LongExposureInfraredFrameReader, winrt::Windows::Kinect::LongExposureInfraredFrameArrivedEventArgs> const& handler);
        void FrameArrived(winrt::event_token const& token) noexcept;
        winrt::Windows::Kinect::LongExposureInfraredFrame AcquireLatestFrame();
        bool IsPaused();
        void IsPaused(bool value);
        winrt::Windows::Kinect::LongExposureInfraredFrameSource LongExposureInfraredFrameSource();
    };

    struct LongExposureInfraredFrameReference : LongExposureInfraredFrameReferenceT<LongExposureInfraredFrameReference>
    {
        LongExposureInfraredFrameReference() = default;

        winrt::Windows::Kinect::LongExposureInfraredFrame AcquireFrame();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
    };

    struct LongExposureInfraredFrameSource : LongExposureInfraredFrameSourceT<LongExposureInfraredFrameSource>
    {
        LongExposureInfraredFrameSource() = default;

        winrt::event_token FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::LongExposureInfraredFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler);
        void FrameCaptured(winrt::event_token const& token) noexcept;
        bool IsActive();
        winrt::Windows::Kinect::LongExposureInfraredFrameReader OpenReader();
        winrt::Windows::Kinect::FrameDescription FrameDescription();
        winrt::Windows::Kinect::KinectSensor KinectSensor();
    };

    struct MultiSourceFrame : MultiSourceFrameT<MultiSourceFrame>
    {
        MultiSourceFrame() = default;

        winrt::Windows::Kinect::ColorFrameReference ColorFrameReference();
        winrt::Windows::Kinect::DepthFrameReference DepthFrameReference();
        winrt::Windows::Kinect::BodyFrameReference BodyFrameReference();
        winrt::Windows::Kinect::BodyIndexFrameReference BodyIndexFrameReference();
        winrt::Windows::Kinect::InfraredFrameReference InfraredFrameReference();
        winrt::Windows::Kinect::LongExposureInfraredFrameReference LongExposureInfraredFrameReference();
    };

    struct MultiSourceFrameArrivedEventArgs : MultiSourceFrameArrivedEventArgsT<MultiSourceFrameArrivedEventArgs>
    {
        MultiSourceFrameArrivedEventArgs() = default;

        winrt::Windows::Kinect::MultiSourceFrameReference FrameReference();
    };

    struct MultiSourceFrameReader : MultiSourceFrameReaderT<MultiSourceFrameReader>
    {
        MultiSourceFrameReader() = default;

        winrt::event_token MultiSourceFrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::MultiSourceFrameReader, winrt::Windows::Kinect::MultiSourceFrameArrivedEventArgs> const& handler);
        void MultiSourceFrameArrived(winrt::event_token const& token) noexcept;
        winrt::Windows::Kinect::MultiSourceFrame AcquireLatestFrame();
        winrt::Windows::Kinect::FrameSourceTypes FrameSourceTypes();
        bool IsPaused();
        void IsPaused(bool value);
        winrt::Windows::Kinect::KinectSensor KinectSensor();
    };

    struct MultiSourceFrameReference : MultiSourceFrameReferenceT<MultiSourceFrameReference>
    {
        MultiSourceFrameReference() = default;

        winrt::Windows::Kinect::MultiSourceFrame AcquireFrame();
    };

    struct CoordinateMapper : CoordinateMapperT<CoordinateMapper>
    {
        CoordinateMapper() = default;

        winrt::Windows::Kinect::CameraIntrinsics GetDepthCameraIntrinsics();
        winrt::event_token CoordinateMappingChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::CoordinateMapper, winrt::Windows::Kinect::CoordinateMappingChangedEventArgs> const& handler);
        void CoordinateMappingChanged(winrt::event_token const& token) noexcept;
        winrt::Windows::Kinect::DepthSpacePoint MapCameraPointToDepthSpace(winrt::Windows::Kinect::CameraSpacePoint const& cameraPoint);
        winrt::Windows::Kinect::ColorSpacePoint MapCameraPointToColorSpace(winrt::Windows::Kinect::CameraSpacePoint const& cameraPoint);
        winrt::Windows::Kinect::CameraSpacePoint MapDepthPointToCameraSpace(winrt::Windows::Kinect::DepthSpacePoint const& depthPoint, uint16_t depth);
        winrt::Windows::Kinect::ColorSpacePoint MapDepthPointToColorSpace(winrt::Windows::Kinect::DepthSpacePoint const& depthPoint, uint16_t depth);
        com_array<winrt::Windows::Kinect::DepthSpacePoint> MapCameraPointsToDepthSpace(array_view<winrt::Windows::Kinect::CameraSpacePoint const> cameraPoints);
        com_array<winrt::Windows::Kinect::ColorSpacePoint> MapCameraPointsToColorSpace(array_view<winrt::Windows::Kinect::CameraSpacePoint const> cameraPoints);
        com_array<winrt::Windows::Kinect::CameraSpacePoint> MapDepthPointsToCameraSpace(array_view<winrt::Windows::Kinect::DepthSpacePoint const> depthPoints, array_view<uint16_t const> depths);
        com_array<winrt::Windows::Kinect::ColorSpacePoint> MapDepthPointsToColorSpace(array_view<winrt::Windows::Kinect::DepthSpacePoint const> depthPoints, array_view<uint16_t const> depths);
        com_array<winrt::Windows::Kinect::CameraSpacePoint> MapDepthFrameToCameraSpace(array_view<uint16_t const> depthFrameData);
        com_array<winrt::Windows::Kinect::ColorSpacePoint> MapDepthFrameToColorSpace(array_view<uint16_t const> depthFrameData);
        com_array<winrt::Windows::Kinect::CameraSpacePoint> MapDepthFrameToCameraSpaceUsingIBuffer(winrt::Windows::Storage::Streams::IBuffer const& depthFrameData);
        com_array<winrt::Windows::Kinect::ColorSpacePoint> MapDepthFrameToColorSpaceUsingIBuffer(winrt::Windows::Storage::Streams::IBuffer const& depthFrameData);
        com_array<winrt::Windows::Kinect::DepthSpacePoint> MapColorFrameToDepthSpace(array_view<uint16_t const> depthFrameData);
        com_array<winrt::Windows::Kinect::CameraSpacePoint> MapColorFrameToCameraSpace(array_view<uint16_t const> depthFrameData);
        com_array<winrt::Windows::Kinect::DepthSpacePoint> MapColorFrameToDepthSpaceUsingIBuffer(winrt::Windows::Storage::Streams::IBuffer const& depthFrameData);
        com_array<winrt::Windows::Kinect::CameraSpacePoint> MapColorFrameToCameraSpaceUsingIBuffer(winrt::Windows::Storage::Streams::IBuffer const& depthFrameData);
        com_array<winrt::Windows::Foundation::Point> GetDepthFrameToCameraSpaceTable();
    };

    struct CoordinateMappingChangedEventArgs : CoordinateMappingChangedEventArgsT<CoordinateMappingChangedEventArgs>
    {
        CoordinateMappingChangedEventArgs() = default;
    };

    struct IsAvailableChangedEventArgs : IsAvailableChangedEventArgsT<IsAvailableChangedEventArgs>
    {
        IsAvailableChangedEventArgs() = default;

        bool IsAvailable();
    };

    struct FrameCapturedEventArgs : FrameCapturedEventArgsT<FrameCapturedEventArgs>
    {
        FrameCapturedEventArgs() = default;

        winrt::Windows::Kinect::FrameSourceTypes FrameType();
        winrt::Windows::Kinect::FrameCapturedStatus FrameStatus();
        winrt::Windows::Foundation::TimeSpan RelativeTime();
    };

    struct FrameDescription : FrameDescriptionT<FrameDescription>
    {
        FrameDescription(::IFrameDescription *pFrameDescription) : m_pFrameDescription(pFrameDescription) {}

        int32_t Width();
        int32_t Height();
        float HorizontalFieldOfView();
        float VerticalFieldOfView();
        float DiagonalFieldOfView();
        uint32_t LengthInPixels();
        uint32_t BytesPerPixel();

        private:
        ::IFrameDescription *m_pFrameDescription = nullptr;
    };

    struct KinectSensor : KinectSensorT<KinectSensor>
    {
        KinectSensor()
        {
            GetDefaultKinectSensor(&m_pKinectSensor);
        }

        static winrt::Windows::Kinect::KinectSensor GetDefault();
        static winrt::Windows::Foundation::Collections::IObservableMap<hstring, winrt::Windows::Kinect::KinectSensor> Sensors();
        winrt::event_token IsAvailableChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::KinectSensor, winrt::Windows::Kinect::IsAvailableChangedEventArgs> const& handler);
        void IsAvailableChanged(winrt::event_token const& token) noexcept;
        void Open();
        void Close();
        bool IsOpen();
        bool IsAvailable();
        winrt::Windows::Kinect::ColorFrameSource ColorFrameSource();
        winrt::Windows::Kinect::DepthFrameSource DepthFrameSource();
        winrt::Windows::Kinect::BodyFrameSource BodyFrameSource();
        winrt::Windows::Kinect::BodyIndexFrameSource BodyIndexFrameSource();
        winrt::Windows::Kinect::InfraredFrameSource InfraredFrameSource();
        winrt::Windows::Kinect::LongExposureInfraredFrameSource LongExposureInfraredFrameSource();
        winrt::Windows::Kinect::AudioSource AudioSource();
        winrt::Windows::Kinect::MultiSourceFrameReader OpenMultiSourceFrameReader(winrt::Windows::Kinect::FrameSourceTypes const& enabledFrameSourceTypes);
        winrt::Windows::Kinect::CoordinateMapper CoordinateMapper();
        hstring UniqueKinectId();
        winrt::Windows::Kinect::KinectCapabilities KinectCapabilities();

        private:
        ::IKinectSensor *m_pKinectSensor = nullptr;
    };
}
namespace winrt::Windows::Kinect::factory_implementation
{
    struct KinectSensor : KinectSensorT<KinectSensor, implementation::KinectSensor>
    {
    };
}

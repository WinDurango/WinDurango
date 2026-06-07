#include "Windows.Kinect.KinectSensor.h"
#include "Windows.Kinect.Body.h"
#include "WinDurangoKinect.h"

namespace winrt::Windows::Kinect::implementation
{
    winrt::Windows::Kinect::AudioSource AudioBeam::AudioSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeam", "Unimplemented: AudioSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::AudioBeamMode AudioBeam::AudioBeamMode()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeam", "Unimplemented: AudioBeamMode");
        throw hresult_not_implemented();
    }
    void AudioBeam::AudioBeamMode(winrt::Windows::Kinect::AudioBeamMode const& value)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeam", "Unimplemented: AudioBeamMode");
        throw hresult_not_implemented();
    }
    float AudioBeam::BeamAngle()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeam", "Unimplemented: BeamAngle");
        throw hresult_not_implemented();
    }
    void AudioBeam::BeamAngle(float value)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeam", "Unimplemented: BeamAngle");
        throw hresult_not_implemented();
    }
    float AudioBeam::BeamAngleConfidence()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeam", "Unimplemented: BeamAngleConfidence");
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::Streams::IInputStream AudioBeam::OpenInputStream()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeam", "Unimplemented: OpenInputStream");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan AudioBeam::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeam", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::AudioSource AudioBeamFrame::AudioSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrame", "Unimplemented: AudioSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan AudioBeamFrame::Duration()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrame", "Unimplemented: Duration");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::AudioBeam AudioBeamFrame::AudioBeam()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrame", "Unimplemented: AudioBeam");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Kinect::AudioBeamSubFrame> AudioBeamFrame::SubFrames()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrame", "Unimplemented: SubFrames");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan AudioBeamFrame::RelativeTimeStart()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrame", "Unimplemented: RelativeTimeStart");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::AudioBeamFrameReference AudioBeamFrameArrivedEventArgs::FrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrameArrivedEventArgs", "Unimplemented: FrameReference");
        throw hresult_not_implemented();
    }
    winrt::event_token AudioBeamFrameReader::FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::AudioBeamFrameReader, winrt::Windows::Kinect::AudioBeamFrameArrivedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    void AudioBeamFrameReader::FrameArrived(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Kinect::AudioBeamFrame> AudioBeamFrameReader::AcquireLatestBeamFrames()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrameReader", "Unimplemented: AcquireLatestBeamFrames");
        throw hresult_not_implemented();
    }
    bool AudioBeamFrameReader::IsPaused()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    void AudioBeamFrameReader::IsPaused(bool value)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::AudioSource AudioBeamFrameReader::AudioSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrameReader", "Unimplemented: AudioSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Kinect::AudioBeamFrame> AudioBeamFrameReference::AcquireBeamFrames()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrameReference", "Unimplemented: AcquireBeamFrames");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan AudioBeamFrameReference::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamFrameReference", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    uint32_t AudioBeamSubFrame::FrameLengthInBytes()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamSubFrame", "Unimplemented: FrameLengthInBytes");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan AudioBeamSubFrame::Duration()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamSubFrame", "Unimplemented: Duration");
        throw hresult_not_implemented();
    }
    float AudioBeamSubFrame::BeamAngle()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamSubFrame", "Unimplemented: BeamAngle");
        throw hresult_not_implemented();
    }
    float AudioBeamSubFrame::BeamAngleConfidence()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamSubFrame", "Unimplemented: BeamAngleConfidence");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::AudioBeamMode AudioBeamSubFrame::AudioBeamMode()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamSubFrame", "Unimplemented: AudioBeamMode");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Kinect::AudioBodyCorrelation> AudioBeamSubFrame::AudioBodyCorrelations()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamSubFrame", "Unimplemented: AudioBodyCorrelations");
        throw hresult_not_implemented();
    }
    com_array<uint8_t> AudioBeamSubFrame::CopyFrameDataToArray()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamSubFrame", "Unimplemented: CopyFrameDataToArray");
        throw hresult_not_implemented();
    }
    void AudioBeamSubFrame::CopyFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamSubFrame", "Unimplemented: CopyFrameDataToBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::Streams::IBuffer AudioBeamSubFrame::LockAudioBuffer()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamSubFrame", "Unimplemented: LockAudioBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan AudioBeamSubFrame::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBeamSubFrame", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    uint64_t AudioBodyCorrelation::BodyTrackingId()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioBodyCorrelation", "Unimplemented: BodyTrackingId");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::KinectAudioCalibrationState AudioSource::AudioCalibrationState()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioSource", "Unimplemented: AudioCalibrationState");
        throw hresult_not_implemented();
    }
    winrt::event_token AudioSource::FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::AudioSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    void AudioSource::FrameCaptured(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::KinectSensor AudioSource::KinectSensor()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioSource", "Unimplemented: KinectSensor");
        throw hresult_not_implemented();
    }
    bool AudioSource::IsActive()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioSource", "Unimplemented: IsActive");
        throw hresult_not_implemented();
    }
    uint32_t AudioSource::SubFrameLengthInBytes()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioSource", "Unimplemented: SubFrameLengthInBytes");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan AudioSource::SubFrameDuration()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioSource", "Unimplemented: SubFrameDuration");
        throw hresult_not_implemented();
    }
    uint32_t AudioSource::MaxSubFrameCount()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioSource", "Unimplemented: MaxSubFrameCount");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::AudioBeamFrameReader AudioSource::OpenReader()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioSource", "Unimplemented: OpenReader");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Kinect::AudioBeam> AudioSource::AudioBeams()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::AudioSource", "Unimplemented: AudioBeams");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan ColorCameraSettings::ExposureTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorCameraSettings", "Unimplemented: ExposureTime");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan ColorCameraSettings::FrameInterval()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorCameraSettings", "Unimplemented: FrameInterval");
        throw hresult_not_implemented();
    }
    float ColorCameraSettings::Gain()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorCameraSettings", "Unimplemented: Gain");
        throw hresult_not_implemented();
    }
    float ColorCameraSettings::Gamma()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorCameraSettings", "Unimplemented: Gamma");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::ColorImageFormat ColorFrame::RawColorImageFormat()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrame", "Unimplemented: RawColorImageFormat");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameDescription ColorFrame::FrameDescription()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrame", "Unimplemented: FrameDescription");
        throw hresult_not_implemented();
    }
    com_array<uint8_t> ColorFrame::CopyRawFrameDataToArray()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrame", "Unimplemented: CopyRawFrameDataToArray");
        throw hresult_not_implemented();
    }
    void ColorFrame::CopyRawFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrame", "Unimplemented: CopyRawFrameDataToBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::Streams::IBuffer ColorFrame::LockRawImageBuffer()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrame", "Unimplemented: LockRawImageBuffer");
        throw hresult_not_implemented();
    }
    com_array<uint8_t> ColorFrame::CopyConvertedFrameDataToArray(winrt::Windows::Kinect::ColorImageFormat const& colorFormat)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrame", "Unimplemented: CopyConvertedFrameDataToArray");
        throw hresult_not_implemented();
    }
    void ColorFrame::CopyConvertedFrameDataToBuffer(winrt::Windows::Storage::Streams::Buffer const& buffer, winrt::Windows::Kinect::ColorImageFormat const& colorFormat)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrame", "Unimplemented: CopyConvertedFrameDataToBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameDescription ColorFrame::CreateFrameDescription(winrt::Windows::Kinect::ColorImageFormat const& format)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrame", "Unimplemented: CreateFrameDescription");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::ColorCameraSettings ColorFrame::ColorCameraSettings()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrame", "Unimplemented: ColorCameraSettings");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan ColorFrame::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrame", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::ColorFrameSource ColorFrame::ColorFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrame", "Unimplemented: ColorFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::ColorFrameReference ColorFrameArrivedEventArgs::FrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrameArrivedEventArgs", "Unimplemented: FrameReference");
        throw hresult_not_implemented();
    }
    winrt::event_token ColorFrameReader::FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::ColorFrameReader, winrt::Windows::Kinect::ColorFrameArrivedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    void ColorFrameReader::FrameArrived(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::ColorFrame ColorFrameReader::AcquireLatestFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrameReader", "Unimplemented: AcquireLatestFrame");
        throw hresult_not_implemented();
    }
    bool ColorFrameReader::IsPaused()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    void ColorFrameReader::IsPaused(bool value)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::ColorFrameSource ColorFrameReader::ColorFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrameReader", "Unimplemented: ColorFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::ColorFrame ColorFrameReference::AcquireFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrameReference", "Unimplemented: AcquireFrame");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan ColorFrameReference::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrameReference", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::event_token ColorFrameSource::FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::ColorFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler)
    {
        return {};
    }
    void ColorFrameSource::FrameCaptured(winrt::event_token const& token) noexcept
    {
    }
    bool ColorFrameSource::IsActive()
    {
        BOOLEAN isActive = 0;
        m_pColorFrameSource->get_IsActive(&isActive);
        return (bool)isActive;
    }
    winrt::Windows::Kinect::ColorFrameReader ColorFrameSource::OpenReader()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrameSource", "Unimplemented: OpenReader");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameDescription ColorFrameSource::CreateFrameDescription(winrt::Windows::Kinect::ColorImageFormat const& format)
    {
        ::IFrameDescription *pFrameDescription = nullptr;
        m_pColorFrameSource->CreateFrameDescription((::ColorImageFormat)format, &pFrameDescription);
        return winrt::make<implementation::FrameDescription>(pFrameDescription);
    }
    winrt::Windows::Kinect::FrameDescription ColorFrameSource::FrameDescription()
    {
        ::IFrameDescription *pFrameDescription = nullptr;
        m_pColorFrameSource->get_FrameDescription(&pFrameDescription);
        return winrt::make<implementation::FrameDescription>(pFrameDescription);
    }
    winrt::Windows::Kinect::KinectSensor ColorFrameSource::KinectSensor()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::ColorFrameSource", "Unimplemented: KinectSensor");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::CameraIntrinsics CoordinateMapper::GetDepthCameraIntrinsics()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: GetDepthCameraIntrinsics");
        throw hresult_not_implemented();
    }
    winrt::event_token CoordinateMapper::CoordinateMappingChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::CoordinateMapper, winrt::Windows::Kinect::CoordinateMappingChangedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: CoordinateMappingChanged");
        throw hresult_not_implemented();
    }
    void CoordinateMapper::CoordinateMappingChanged(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: CoordinateMappingChanged");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::DepthSpacePoint CoordinateMapper::MapCameraPointToDepthSpace(winrt::Windows::Kinect::CameraSpacePoint const& cameraPoint)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapCameraPointToDepthSpace");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::ColorSpacePoint CoordinateMapper::MapCameraPointToColorSpace(winrt::Windows::Kinect::CameraSpacePoint const& cameraPoint)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapCameraPointToColorSpace");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::CameraSpacePoint CoordinateMapper::MapDepthPointToCameraSpace(winrt::Windows::Kinect::DepthSpacePoint const& depthPoint, uint16_t depth)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapDepthPointToCameraSpace");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::ColorSpacePoint CoordinateMapper::MapDepthPointToColorSpace(winrt::Windows::Kinect::DepthSpacePoint const& depthPoint, uint16_t depth)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapDepthPointToColorSpace");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::DepthSpacePoint> CoordinateMapper::MapCameraPointsToDepthSpace(array_view<winrt::Windows::Kinect::CameraSpacePoint const> cameraPoints)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapCameraPointsToDepthSpace");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::ColorSpacePoint> CoordinateMapper::MapCameraPointsToColorSpace(array_view<winrt::Windows::Kinect::CameraSpacePoint const> cameraPoints)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapCameraPointsToColorSpace");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::CameraSpacePoint> CoordinateMapper::MapDepthPointsToCameraSpace(array_view<winrt::Windows::Kinect::DepthSpacePoint const> depthPoints, array_view<uint16_t const> depths)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapDepthPointsToCameraSpace");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::ColorSpacePoint> CoordinateMapper::MapDepthPointsToColorSpace(array_view<winrt::Windows::Kinect::DepthSpacePoint const> depthPoints, array_view<uint16_t const> depths)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapDepthPointsToColorSpace");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::CameraSpacePoint> CoordinateMapper::MapDepthFrameToCameraSpace(array_view<uint16_t const> depthFrameData)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapDepthFrameToCameraSpace");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::ColorSpacePoint> CoordinateMapper::MapDepthFrameToColorSpace(array_view<uint16_t const> depthFrameData)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapDepthFrameToColorSpace");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::CameraSpacePoint> CoordinateMapper::MapDepthFrameToCameraSpaceUsingIBuffer(winrt::Windows::Storage::Streams::IBuffer const& depthFrameData)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapDepthFrameToCameraSpaceUsingIBuffer");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::ColorSpacePoint> CoordinateMapper::MapDepthFrameToColorSpaceUsingIBuffer(winrt::Windows::Storage::Streams::IBuffer const& depthFrameData)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapDepthFrameToColorSpaceUsingIBuffer");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::DepthSpacePoint> CoordinateMapper::MapColorFrameToDepthSpace(array_view<uint16_t const> depthFrameData)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapColorFrameToDepthSpace");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::CameraSpacePoint> CoordinateMapper::MapColorFrameToCameraSpace(array_view<uint16_t const> depthFrameData)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapColorFrameToCameraSpace");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::DepthSpacePoint> CoordinateMapper::MapColorFrameToDepthSpaceUsingIBuffer(winrt::Windows::Storage::Streams::IBuffer const& depthFrameData)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapColorFrameToDepthSpaceUsingIBuffer");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Kinect::CameraSpacePoint> CoordinateMapper::MapColorFrameToCameraSpaceUsingIBuffer(winrt::Windows::Storage::Streams::IBuffer const& depthFrameData)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: MapColorFrameToCameraSpaceUsingIBuffer");
        throw hresult_not_implemented();
    }
    com_array<winrt::Windows::Foundation::Point> CoordinateMapper::GetDepthFrameToCameraSpaceTable()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::CoordinateMapper", "Unimplemented: GetDepthFrameToCameraSpaceTable");
        throw hresult_not_implemented();
    }
    com_array<uint16_t> DepthFrame::CopyFrameDataToArray()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrame", "Unimplemented: CopyFrameDataToArray");
        throw hresult_not_implemented();
    }
    void DepthFrame::CopyFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrame", "Unimplemented: CopyFrameDataToBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::Streams::IBuffer DepthFrame::LockImageBuffer()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrame", "Unimplemented: LockImageBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameDescription DepthFrame::FrameDescription()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrame", "Unimplemented: FrameDescription");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan DepthFrame::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrame", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::DepthFrameSource DepthFrame::DepthFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrame", "Unimplemented: DepthFrameSource");
        throw hresult_not_implemented();
    }
    uint16_t DepthFrame::DepthMinReliableDistance()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrame", "Unimplemented: DepthMinReliableDistance");
        throw hresult_not_implemented();
    }
    uint16_t DepthFrame::DepthMaxReliableDistance()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrame", "Unimplemented: DepthMaxReliableDistance");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::DepthFrameReference DepthFrameArrivedEventArgs::FrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameArrivedEventArgs", "Unimplemented: FrameReference");
        throw hresult_not_implemented();
    }
    winrt::event_token DepthFrameReader::FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::DepthFrameReader, winrt::Windows::Kinect::DepthFrameArrivedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    void DepthFrameReader::FrameArrived(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::DepthFrame DepthFrameReader::AcquireLatestFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameReader", "Unimplemented: AcquireLatestFrame");
        throw hresult_not_implemented();
    }
    bool DepthFrameReader::IsPaused()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    void DepthFrameReader::IsPaused(bool value)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::DepthFrameSource DepthFrameReader::DepthFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameReader", "Unimplemented: DepthFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::DepthFrame DepthFrameReference::AcquireFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameReference", "Unimplemented: AcquireFrame");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan DepthFrameReference::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameReference", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::event_token DepthFrameSource::FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::DepthFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    void DepthFrameSource::FrameCaptured(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    bool DepthFrameSource::IsActive()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameSource", "Unimplemented: IsActive");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::DepthFrameReader DepthFrameSource::OpenReader()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameSource", "Unimplemented: OpenReader");
        throw hresult_not_implemented();
    }
    uint16_t DepthFrameSource::DepthMinReliableDistance()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameSource", "Unimplemented: DepthMinReliableDistance");
        throw hresult_not_implemented();
    }
    uint16_t DepthFrameSource::DepthMaxReliableDistance()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameSource", "Unimplemented: DepthMaxReliableDistance");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameDescription DepthFrameSource::FrameDescription()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameSource", "Unimplemented: FrameDescription");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::KinectSensor DepthFrameSource::KinectSensor()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::DepthFrameSource", "Unimplemented: KinectSensor");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameSourceTypes FrameCapturedEventArgs::FrameType()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::FrameCapturedEventArgs", "Unimplemented: FrameType");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameCapturedStatus FrameCapturedEventArgs::FrameStatus()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::FrameCapturedEventArgs", "Unimplemented: FrameStatus");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan FrameCapturedEventArgs::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::FrameCapturedEventArgs", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    int32_t FrameDescription::Width()
    {
        int32_t Width = 0;
        m_pFrameDescription->get_Width(&Width);
        return Width;
    }
    int32_t FrameDescription::Height()
    {
        int32_t Height = 0;
        m_pFrameDescription->get_Height(&Height);
        return Height;
    }
    float FrameDescription::HorizontalFieldOfView()
    {
        float HorizontalFieldOfView = 0;
        m_pFrameDescription->get_HorizontalFieldOfView(&HorizontalFieldOfView);
        return HorizontalFieldOfView;
    }
    float FrameDescription::VerticalFieldOfView()
    {
        float VerticalFieldOfView = 0;
        m_pFrameDescription->get_VerticalFieldOfView(&VerticalFieldOfView);
        return VerticalFieldOfView;
    }
    float FrameDescription::DiagonalFieldOfView()
    {
        float DiagonalFieldOfView = 0;
        m_pFrameDescription->get_DiagonalFieldOfView(&DiagonalFieldOfView);
        return DiagonalFieldOfView;
    }
    uint32_t FrameDescription::LengthInPixels()
    {
        uint32_t LengthInPixels = 0;
        m_pFrameDescription->get_LengthInPixels(&LengthInPixels);
        return LengthInPixels;
    }
    uint32_t FrameDescription::BytesPerPixel()
    {
        uint32_t BytesPerPixel = 0;
        m_pFrameDescription->get_BytesPerPixel(&BytesPerPixel);
        return BytesPerPixel;
    }
    com_array<uint16_t> InfraredFrame::CopyFrameDataToArray()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrame", "Unimplemented: CopyFrameDataToArray");
        throw hresult_not_implemented();
    }
    void InfraredFrame::CopyFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrame", "Unimplemented: CopyFrameDataToBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::Streams::IBuffer InfraredFrame::LockImageBuffer()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrame", "Unimplemented: LockImageBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameDescription InfraredFrame::FrameDescription()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrame", "Unimplemented: FrameDescription");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan InfraredFrame::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrame", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::InfraredFrameSource InfraredFrame::InfraredFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrame", "Unimplemented: InfraredFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::InfraredFrameReference InfraredFrameArrivedEventArgs::FrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameArrivedEventArgs", "Unimplemented: FrameReference");
        throw hresult_not_implemented();
    }
    winrt::event_token InfraredFrameReader::FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::InfraredFrameReader, winrt::Windows::Kinect::InfraredFrameArrivedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    void InfraredFrameReader::FrameArrived(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::InfraredFrame InfraredFrameReader::AcquireLatestFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameReader", "Unimplemented: AcquireLatestFrame");
        throw hresult_not_implemented();
    }
    bool InfraredFrameReader::IsPaused()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    void InfraredFrameReader::IsPaused(bool value)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::InfraredFrameSource InfraredFrameReader::InfraredFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameReader", "Unimplemented: InfraredFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::InfraredFrame InfraredFrameReference::AcquireFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameReference", "Unimplemented: AcquireFrame");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan InfraredFrameReference::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameReference", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::event_token InfraredFrameSource::FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::InfraredFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    void InfraredFrameSource::FrameCaptured(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    bool InfraredFrameSource::IsActive()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameSource", "Unimplemented: IsActive");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::InfraredFrameReader InfraredFrameSource::OpenReader()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameSource", "Unimplemented: OpenReader");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameDescription InfraredFrameSource::FrameDescription()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameSource", "Unimplemented: FrameDescription");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::KinectSensor InfraredFrameSource::KinectSensor()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::InfraredFrameSource", "Unimplemented: KinectSensor");
        throw hresult_not_implemented();
    }
    bool IsAvailableChangedEventArgs::IsAvailable()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::IsAvailableChangedEventArgs", "Unimplemented: IsAvailable");
        throw hresult_not_implemented();
    }
    com_array<uint16_t> LongExposureInfraredFrame::CopyFrameDataToArray()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrame", "Unimplemented: CopyFrameDataToArray");
        throw hresult_not_implemented();
    }
    void LongExposureInfraredFrame::CopyFrameDataToBuffer(winrt::Windows::Storage::Streams::IBuffer const& buffer)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrame", "Unimplemented: CopyFrameDataToBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Storage::Streams::IBuffer LongExposureInfraredFrame::LockImageBuffer()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrame", "Unimplemented: LockImageBuffer");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameDescription LongExposureInfraredFrame::FrameDescription()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrame", "Unimplemented: FrameDescription");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan LongExposureInfraredFrame::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrame", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::LongExposureInfraredFrameSource LongExposureInfraredFrame::LongExposureInfraredFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrame", "Unimplemented: LongExposureInfraredFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::LongExposureInfraredFrameReference LongExposureInfraredFrameArrivedEventArgs::FrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameArrivedEventArgs", "Unimplemented: FrameReference");
        throw hresult_not_implemented();
    }
    winrt::event_token LongExposureInfraredFrameReader::FrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::LongExposureInfraredFrameReader, winrt::Windows::Kinect::LongExposureInfraredFrameArrivedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    void LongExposureInfraredFrameReader::FrameArrived(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameReader", "Unimplemented: FrameArrived");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::LongExposureInfraredFrame LongExposureInfraredFrameReader::AcquireLatestFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameReader", "Unimplemented: AcquireLatestFrame");
        throw hresult_not_implemented();
    }
    bool LongExposureInfraredFrameReader::IsPaused()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    void LongExposureInfraredFrameReader::IsPaused(bool value)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::LongExposureInfraredFrameSource LongExposureInfraredFrameReader::LongExposureInfraredFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameReader", "Unimplemented: LongExposureInfraredFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::LongExposureInfraredFrame LongExposureInfraredFrameReference::AcquireFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameReference", "Unimplemented: AcquireFrame");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::TimeSpan LongExposureInfraredFrameReference::RelativeTime()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameReference", "Unimplemented: RelativeTime");
        throw hresult_not_implemented();
    }
    winrt::event_token LongExposureInfraredFrameSource::FrameCaptured(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::LongExposureInfraredFrameSource, winrt::Windows::Kinect::FrameCapturedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    void LongExposureInfraredFrameSource::FrameCaptured(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameSource", "Unimplemented: FrameCaptured");
        throw hresult_not_implemented();
    }
    bool LongExposureInfraredFrameSource::IsActive()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameSource", "Unimplemented: IsActive");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::LongExposureInfraredFrameReader LongExposureInfraredFrameSource::OpenReader()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameSource", "Unimplemented: OpenReader");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameDescription LongExposureInfraredFrameSource::FrameDescription()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameSource", "Unimplemented: FrameDescription");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::KinectSensor LongExposureInfraredFrameSource::KinectSensor()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::LongExposureInfraredFrameSource", "Unimplemented: KinectSensor");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::ColorFrameReference MultiSourceFrame::ColorFrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrame", "Unimplemented: ColorFrameReference");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::DepthFrameReference MultiSourceFrame::DepthFrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrame", "Unimplemented: DepthFrameReference");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyFrameReference MultiSourceFrame::BodyFrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrame", "Unimplemented: BodyFrameReference");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyIndexFrameReference MultiSourceFrame::BodyIndexFrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrame", "Unimplemented: BodyIndexFrameReference");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::InfraredFrameReference MultiSourceFrame::InfraredFrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrame", "Unimplemented: InfraredFrameReference");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::LongExposureInfraredFrameReference MultiSourceFrame::LongExposureInfraredFrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrame", "Unimplemented: LongExposureInfraredFrameReference");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::MultiSourceFrameReference MultiSourceFrameArrivedEventArgs::FrameReference()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrameArrivedEventArgs", "Unimplemented: FrameReference");
        throw hresult_not_implemented();
    }
    winrt::event_token MultiSourceFrameReader::MultiSourceFrameArrived(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::MultiSourceFrameReader, winrt::Windows::Kinect::MultiSourceFrameArrivedEventArgs> const& handler)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrameReader", "Unimplemented: MultiSourceFrameArrived");
        throw hresult_not_implemented();
    }
    void MultiSourceFrameReader::MultiSourceFrameArrived(winrt::event_token const& token) noexcept
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrameReader", "Unimplemented: MultiSourceFrameArrived");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::MultiSourceFrame MultiSourceFrameReader::AcquireLatestFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrameReader", "Unimplemented: AcquireLatestFrame");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::FrameSourceTypes MultiSourceFrameReader::FrameSourceTypes()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrameReader", "Unimplemented: FrameSourceTypes");
        throw hresult_not_implemented();
    }
    bool MultiSourceFrameReader::IsPaused()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    void MultiSourceFrameReader::IsPaused(bool value)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrameReader", "Unimplemented: IsPaused");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::KinectSensor MultiSourceFrameReader::KinectSensor()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrameReader", "Unimplemented: KinectSensor");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::MultiSourceFrame MultiSourceFrameReference::AcquireFrame()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::MultiSourceFrameReference", "Unimplemented: AcquireFrame");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::KinectSensor KinectSensor::GetDefault()
    {
        return winrt::make<implementation::KinectSensor>();
    }
    winrt::Windows::Foundation::Collections::IObservableMap<hstring, winrt::Windows::Kinect::KinectSensor> KinectSensor::Sensors()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::KinectSensor", "Unimplemented: Sensors");
        throw hresult_not_implemented();
    }
    winrt::event_token KinectSensor::IsAvailableChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Kinect::KinectSensor, winrt::Windows::Kinect::IsAvailableChangedEventArgs> const& handler)
    {
        return {};
    }
    void KinectSensor::IsAvailableChanged(winrt::event_token const& token) noexcept
    {

    }
    void KinectSensor::Open()
    {
        m_pKinectSensor->Open();
    }
    void KinectSensor::Close()
    {
        m_pKinectSensor->Close();
    }
    bool KinectSensor::IsOpen()
    {
        BOOLEAN isOpen = 0;
        m_pKinectSensor->get_IsOpen(&isOpen);
        return (bool)isOpen;
    }
    bool KinectSensor::IsAvailable()
    {
        BOOLEAN isAvailable = 0;
        m_pKinectSensor->get_IsAvailable(&isAvailable);
        return (bool)isAvailable;
    }
    winrt::Windows::Kinect::ColorFrameSource KinectSensor::ColorFrameSource()
    {
        ::IColorFrameSource *pColorFrameSource = nullptr;
        m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
        return winrt::make<implementation::ColorFrameSource>(pColorFrameSource);
    }
    winrt::Windows::Kinect::DepthFrameSource KinectSensor::DepthFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::KinectSensor", "Unimplemented: DepthFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::BodyFrameSource KinectSensor::BodyFrameSource()
    {
        ::IBodyFrameSource *pBodyFrameSource = nullptr;
        m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
        return winrt::make<implementation::BodyFrameSource>(pBodyFrameSource);
    }
    winrt::Windows::Kinect::BodyIndexFrameSource KinectSensor::BodyIndexFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::KinectSensor", "Unimplemented: BodyIndexFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::InfraredFrameSource KinectSensor::InfraredFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::KinectSensor", "Unimplemented: InfraredFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::LongExposureInfraredFrameSource KinectSensor::LongExposureInfraredFrameSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::KinectSensor", "Unimplemented: LongExposureInfraredFrameSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::AudioSource KinectSensor::AudioSource()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::KinectSensor", "Unimplemented: AudioSource");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::MultiSourceFrameReader KinectSensor::OpenMultiSourceFrameReader(winrt::Windows::Kinect::FrameSourceTypes const& enabledFrameSourceTypes)
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::KinectSensor", "Unimplemented: OpenMultiSourceFrameReader");
        throw hresult_not_implemented();
    }
    winrt::Windows::Kinect::CoordinateMapper KinectSensor::CoordinateMapper()
    {
        p_wd->log.Warn("WinDurango::Kinect::Windows::Kinect::KinectSensor", "Unimplemented: CoordinateMapper");
        throw hresult_not_implemented();
    }
    hstring KinectSensor::UniqueKinectId()
    {
        return L"0";
    }
    winrt::Windows::Kinect::KinectCapabilities KinectSensor::KinectCapabilities()
    {
        DWORD kinectCapabilities = 0;
        m_pKinectSensor->get_KinectCapabilities(&kinectCapabilities);
        return static_cast<winrt::Windows::Kinect::KinectCapabilities>(kinectCapabilities);
    }
}
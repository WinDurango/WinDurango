//Source: SlimEra from XWine1 (https://github.com/XWine1/SlimEra)
#pragma once
#include <Windows.h>

union PIXCaptureParameters
{
    enum PIXCaptureStorage
    {
        Memory = 0,
        MemoryCircular = 1, // Xbox only
        FileCircular = 2, // PC only
    };

    struct GpuCaptureParameters
    {
        PCWSTR FileName;
    } GpuCaptureParameters;

    struct TimingCaptureParameters
    {
        PCWSTR FileName;
        UINT32 MaximumToolingMemorySizeMb;
        PIXCaptureStorage CaptureStorage;

        BOOL CaptureGpuTiming;

        BOOL CaptureCallstacks;
        BOOL CaptureCpuSamples;
        UINT32 CpuSamplesPerSecond;

        BOOL CaptureFileIO;

        BOOL CaptureVirtualAllocEvents;
        BOOL CaptureHeapAllocEvents;
        BOOL CaptureXMemEvents; // Xbox only
        BOOL CapturePixMemEvents;
        BOOL CapturePageFaultEvents;
        BOOL CaptureVideoFrames; // Xbox only
    } TimingCaptureParameters;
};

typedef PIXCaptureParameters* PPIXCaptureParameters;
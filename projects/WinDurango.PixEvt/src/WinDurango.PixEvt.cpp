#include "WinDurango.PixEvt.h"

EXTERN_C HRESULT WINAPI ConfigureL2IPMCs(
    _In_ UINT eventIndex10,
    _In_ UINT eventIndex11,
    _In_ UINT eventIndex12,
    _In_ UINT eventIndex13)
{
    UNREFERENCED_PARAMETER(eventIndex10);
    UNREFERENCED_PARAMETER(eventIndex11);
    UNREFERENCED_PARAMETER(eventIndex12);
    UNREFERENCED_PARAMETER(eventIndex13);
    return S_OK;
}

EXTERN_C HRESULT WINAPI ConfigureNBPMCs(
    _In_ UINT eventIndex6,
    _In_ UINT eventIndex7,
    _In_ UINT eventIndex8,
    _In_ UINT eventIndex9)
{
    UNREFERENCED_PARAMETER(eventIndex6);
    UNREFERENCED_PARAMETER(eventIndex7);
    UNREFERENCED_PARAMETER(eventIndex8);
    UNREFERENCED_PARAMETER(eventIndex9);
    return S_OK;
}

EXTERN_C HRESULT WINAPI ConfigurePMCs(
    _In_ UINT eventIndex0,
    _In_ UINT eventIndex1,
    _In_ UINT eventIndex2,
    _In_ UINT eventIndex3)
{
    UNREFERENCED_PARAMETER(eventIndex0);
    UNREFERENCED_PARAMETER(eventIndex1);
    UNREFERENCED_PARAMETER(eventIndex2);
    UNREFERENCED_PARAMETER(eventIndex3);
    return S_OK;
}

EXTERN_C HRESULT WINAPI PIXBeginCapture(
    _In_ DWORD captureFlags,
    _In_opt_ const PPIXCaptureParameters captureParameters)
{
    UNREFERENCED_PARAMETER(captureFlags);
    UNREFERENCED_PARAMETER(captureParameters);
    return S_OK;
}

EXTERN_C HRESULT WINAPI PIXEndCapture(
    _In_ BOOL discard)
{
    UNREFERENCED_PARAMETER(discard);
    return S_OK;
}

EXTERN_C UINT64 WINAPI PIXEventsReplaceBlock(
    _In_ bool getEarliestTime)
{
    UNREFERENCED_PARAMETER(getEarliestTime);
    return 0;
}

EXTERN_C DWORD WINAPI PIXGetCaptureState()
{
    return 0;
}

EXTERN_C void WINAPI PIXReportCounter(
    _In_ PCWSTR Name,
    _In_ float value)
{
    UNREFERENCED_PARAMETER(Name);
    UNREFERENCED_PARAMETER(value);
}

EXTERN_C UINT64 WINAPI GetCaptureControlState()
{
    return 0;
}

EXTERN_C UINT64 WINAPI RegisterForCaptureControl()
{
    return 0;
}

EXTERN_C UINT64 WINAPI SetCaptureCallgraphState()
{
    return 0;
}

EXTERN_C UINT64 WINAPI SetCaptureFunctionDetailsState()
{
    return 0;
}

EXTERN_C UINT64 WINAPI SetCaptureFunctionSummaryState()
{
    return 0;
}

EXTERN_C UINT64 WINAPI SetCaptureInstructionTraceState()
{
    return 0;
}

EXTERN_C UINT64 WINAPI UnregisterForCaptureControl()
{
    return 0;
}

//
// Exports
//
#pragma comment(linker, "/export:ConfigureL2IPMCs")
#pragma comment(linker, "/export:ConfigureNBPMCs")
#pragma comment(linker, "/export:ConfigurePMCs")
#pragma comment(linker, "/export:GetCaptureControlState")
#pragma comment(linker, "/export:PIXBeginCapture")
#pragma comment(linker, "/export:PIXEndCapture")
#pragma comment(linker, "/export:PIXEventsReplaceBlock")
#pragma comment(linker, "/export:PIXGetCaptureState")
#pragma comment(linker, "/export:PIXReportCounter")
#pragma comment(linker, "/export:RegisterForCaptureControl")
#pragma comment(linker, "/export:SetCaptureCallgraphState")
#pragma comment(linker, "/export:SetCaptureFunctionDetailsState")
#pragma comment(linker, "/export:SetCaptureFunctionSummaryState")
#pragma comment(linker, "/export:SetCaptureInstructionTraceState")
#pragma comment(linker, "/export:UnregisterForCaptureControl")
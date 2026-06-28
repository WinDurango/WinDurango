//Source: SlimEra from XWine1 (https://github.com/XWine1/SlimEra)
#include "WinDurango.ToolHelpX.h"

EXTERN_C HRESULT WINAPI GetSourceLineFromAddress(
    _In_ ResolveDisposition Disposition,
    _In_ DWORD FrameCount,
    _In_ PULONG_PTR Addresses,
    _In_ BOOL(*Callback)(
        _In_ LPVOID Context,
        _In_ ULONG_PTR Address,
        _In_ HRESULT Result,
        _In_ PCWSTR FilePath,
        _In_ ULONG LineNumber),
    _In_ LPVOID Context)
{
    UNREFERENCED_PARAMETER(Disposition);
    UNREFERENCED_PARAMETER(FrameCount);
    UNREFERENCED_PARAMETER(Addresses);
    UNREFERENCED_PARAMETER(Callback);
    UNREFERENCED_PARAMETER(Context);
    return E_NOTIMPL;
}

EXTERN_C HRESULT WINAPI GetSymbolFromAddress(
    _In_ ResolveDisposition Disposition,
    _In_ DWORD FrameCount,
    _In_ PULONG_PTR Addresses,
    _In_ BOOL(*Callback)(
        _In_ LPVOID Context,
        _In_ ULONG_PTR Address,
        _In_ HRESULT Result,
        _In_ PCWSTR Name,
        _In_ ULONG Offset),
    _In_ LPVOID Context)
{
    UNREFERENCED_PARAMETER(Disposition);
    UNREFERENCED_PARAMETER(FrameCount);
    UNREFERENCED_PARAMETER(Addresses);
    UNREFERENCED_PARAMETER(Callback);
    UNREFERENCED_PARAMETER(Context);
    return E_NOTIMPL;
}

EXTERN_C BOOL WINAPI QuerySystemHardwareInfo()
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

//
// Exports
//
#pragma comment(linker, "/export:CloseTrace=advapi32.CloseTrace")
#pragma comment(linker, "/export:ContinueDebugEvent=kernel32.ContinueDebugEvent")
#pragma comment(linker, "/export:ControlTraceW=advapi32.ControlTraceW")
#pragma comment(linker, "/export:DebugActiveProcess=kernel32.DebugActiveProcess")
#pragma comment(linker, "/export:DebugActiveProcessStop=kernel32.DebugActiveProcessStop")
#pragma comment(linker, "/export:EnableTrace=advapi32.EnableTrace")
#pragma comment(linker, "/export:EnableTraceEx=advapi32.EnableTraceEx")
#pragma comment(linker, "/export:EnableTraceEx2=advapi32.EnableTraceEx2")
#pragma comment(linker, "/export:EnumerateTraceGuidsEx=advapi32.EnumerateTraceGuidsEx")
#pragma comment(linker, "/export:GetSourceLineFromAddress")
#pragma comment(linker, "/export:GetSymbolFromAddress")
#pragma comment(linker, "/export:GetThreadName=kernelx.GetThreadName")
#pragma comment(linker, "/export:K32EnumDeviceDrivers=kernel32.K32EnumDeviceDrivers")
#pragma comment(linker, "/export:K32EnumProcessModules=kernel32.K32EnumProcessModules")
#pragma comment(linker, "/export:K32EnumProcessModulesEx=kernel32.K32EnumProcessModulesEx")
#pragma comment(linker, "/export:K32EnumProcesses=kernel32.K32EnumProcesses")
#pragma comment(linker, "/export:K32GetDeviceDriverBaseNameA=kernel32.K32GetDeviceDriverBaseNameA")
#pragma comment(linker, "/export:K32GetDeviceDriverBaseNameW=kernel32.K32GetDeviceDriverBaseNameW")
#pragma comment(linker, "/export:K32GetDeviceDriverFileNameA=kernel32.K32GetDeviceDriverFileNameA")
#pragma comment(linker, "/export:K32GetDeviceDriverFileNameW=kernel32.K32GetDeviceDriverFileNameW")
#pragma comment(linker, "/export:K32GetMappedFileNameA=kernel32.K32GetMappedFileNameA")
#pragma comment(linker, "/export:K32GetMappedFileNameW=kernel32.K32GetMappedFileNameW")
#pragma comment(linker, "/export:K32GetModuleBaseNameA=kernel32.K32GetModuleBaseNameA")
#pragma comment(linker, "/export:K32GetModuleBaseNameW=kernel32.K32GetModuleBaseNameW")
#pragma comment(linker, "/export:K32GetModuleFileNameExA=kernel32.K32GetModuleFileNameExA")
#pragma comment(linker, "/export:K32GetModuleFileNameExW=kernel32.K32GetModuleFileNameExW")
#pragma comment(linker, "/export:K32GetModuleInformation=kernel32.K32GetModuleInformation")
#pragma comment(linker, "/export:K32GetPerformanceInfo=kernel32.K32GetPerformanceInfo")
#pragma comment(linker, "/export:K32GetProcessImageFileNameA=kernel32.K32GetProcessImageFileNameA")
#pragma comment(linker, "/export:K32GetProcessImageFileNameW=kernel32.K32GetProcessImageFileNameW")
#pragma comment(linker, "/export:K32GetProcessMemoryInfo=kernel32.K32GetProcessMemoryInfo")
#pragma comment(linker, "/export:K32GetWsChanges=kernel32.K32GetWsChanges")
#pragma comment(linker, "/export:K32GetWsChangesEx=kernel32.K32GetWsChangesEx")
#pragma comment(linker, "/export:K32InitializeProcessForWsWatch=kernel32.K32InitializeProcessForWsWatch")
#pragma comment(linker, "/export:K32QueryWorkingSet=kernel32.K32QueryWorkingSet")
#pragma comment(linker, "/export:K32QueryWorkingSetEx=kernel32.K32QueryWorkingSetEx")
#pragma comment(linker, "/export:MiniDumpWriteDump=dbghelp.MiniDumpWriteDump")
#pragma comment(linker, "/export:OpenTraceW=advapi32.OpenTraceW")
#pragma comment(linker, "/export:ProcessTrace=advapi32.ProcessTrace")
#pragma comment(linker, "/export:QueryAllTracesW=advapi32.QueryAllTracesW")
#pragma comment(linker, "/export:QueryFullProcessImageNameW=kernel32.QueryFullProcessImageNameW")
#pragma comment(linker, "/export:QuerySystemHardwareInfo")
#pragma comment(linker, "/export:SetThreadName=kernelx.SetThreadName")
#pragma comment(linker, "/export:StartTraceW=advapi32.StartTraceW")
#pragma comment(linker, "/export:StopTraceW=advapi32.StopTraceW")
#pragma comment(linker, "/export:TraceQueryInformation=advapi32.TraceQueryInformation")
#pragma comment(linker, "/export:TraceSetInformation=advapi32.TraceSetInformation")
#pragma comment(linker, "/export:WaitForDebugEvent=kernel32.WaitForDebugEvent")

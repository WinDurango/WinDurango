#pragma once
// CPU-side emulation helpers for the Xbox GPU memory-sync operations
// (InsertWaitOnMemory*, WriteValueEndOfPipe64, WriteTimestampTo*).
// Header-only and free of globals so it can be unit-tested on its own.

#include <windows.h>
#include <d3d11.h>
#include <cstdint>
#include <cstdio>

namespace wd::memsync
{
    // Longest time a CPU-emulated wait may block before giving up. On hardware the GPU waits; here the
    // calling CPU thread does, so a value that is never written would otherwise hang the title forever.
    inline constexpr ULONGLONG WaitTimeoutMs = 1000;

    // Evaluates "Value <Func> Reference". Unknown functions are treated as satisfied so we never block on them.
    template <typename T> constexpr bool Compare(D3D11_COMPARISON_FUNC Func, T Value, T Reference) noexcept
    {
        switch (Func)
        {
        case D3D11_COMPARISON_NEVER:
            return false;
        case D3D11_COMPARISON_LESS:
            return Value < Reference;
        case D3D11_COMPARISON_EQUAL:
            return Value == Reference;
        case D3D11_COMPARISON_LESS_EQUAL:
            return Value <= Reference;
        case D3D11_COMPARISON_GREATER:
            return Value > Reference;
        case D3D11_COMPARISON_NOT_EQUAL:
            return Value != Reference;
        case D3D11_COMPARISON_GREATER_EQUAL:
            return Value >= Reference;
        case D3D11_COMPARISON_ALWAYS:
        default:
            return true;
        }
    }

    inline uint32_t Load32(void const *pAddress) noexcept
    {
        return *static_cast<uint32_t const volatile *>(pAddress);
    }

    inline uint64_t Load64(void const *pAddress) noexcept
    {
        return *static_cast<uint64_t const volatile *>(pAddress);
    }

    // Calls Pump() and yields until Satisfied() is true or TimeoutMs elapses. Returns whether it was satisfied.
    template <typename Pred, typename PumpFn> bool WaitUntil(Pred Satisfied, PumpFn Pump, ULONGLONG TimeoutMs)
    {
        ULONGLONG const Deadline = GetTickCount64() + TimeoutMs;

        while (!Satisfied())
        {
            if (GetTickCount64() >= Deadline)
                return false;

            Pump();
            SwitchToThread();
        }

        return true;
    }

    // Monotonic 64-bit timestamp in QueryPerformanceFrequency() ticks.
    inline uint64_t ReadTimestamp() noexcept
    {
        LARGE_INTEGER Now;
        QueryPerformanceCounter(&Now);
        return static_cast<uint64_t>(Now.QuadPart);
    }

    inline void LogWaitTimeout(char const *pFunction, void const *pAddress)
    {
        char Message[160];
        sprintf_s(Message, "[d3d11_x] %s: value at %p not reached after %llu ms, continuing\n", pFunction, pAddress,
                  WaitTimeoutMs);
        OutputDebugStringA(Message);
    }
}

#pragma once
// Present history and v-blank emulation for DXGIXGetFrameStatistics / DXGIXSetVLineNotification.
// Header-only and free of namespace-scope globals so it can be unit-tested on its own.
// All times are QueryPerformanceCounter ticks.

#include <windows.h>
#include <dxgi.h>
#include <wrl/client.h>

#include <condition_variable>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>

namespace wd::display
{
    inline uint64_t Now() noexcept
    {
        LARGE_INTEGER Value;
        QueryPerformanceCounter(&Value);
        return static_cast<uint64_t>(Value.QuadPart);
    }

    // Length of one refresh of the primary display, in QPC ticks (60 Hz if the rate is unknown).
    inline uint64_t RefreshPeriodTicks() noexcept
    {
        DEVMODEW Mode{};
        Mode.dmSize = sizeof(Mode);
        DWORD Hz = 60;
        if (EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &Mode) && Mode.dmDisplayFrequency > 1)
            Hz = Mode.dmDisplayFrequency;

        LARGE_INTEGER Freq;
        QueryPerformanceFrequency(&Freq);
        return static_cast<uint64_t>(Freq.QuadPart) / Hz;
    }

    // Number of whole refresh periods between Start and At.
    constexpr uint64_t VSyncCountAt(uint64_t At, uint64_t Start, uint64_t Period) noexcept
    {
        return (Period == 0 || At < Start) ? 0 : (At - Start) / Period;
    }

    struct FrameRecord
    {
        uint64_t CpuPresentCalled = 0; // before the swap chains were presented
        uint64_t CpuPresentDone = 0;   // after Present returned
        void *Cookie = nullptr;        // DXGIX_PRESENTARRAY_PARAMETERS::Cookie of the first swap chain
    };

    // The most recent N presents. Not synchronised; callers hold their own lock.
    template <uint32_t N> class FrameRing
    {
      public:
        void Push(FrameRecord const &Record) noexcept
        {
            m_Items[m_Pushed % N] = Record;
            ++m_Pushed;
        }

        uint32_t Count() const noexcept
        {
            return m_Pushed < N ? static_cast<uint32_t>(m_Pushed) : N;
        }

        // Index 0 is the newest frame. Precondition: Index < Count().
        FrameRecord const &Recent(uint32_t Index) const noexcept
        {
            return m_Items[(m_Pushed - 1 - Index) % N];
        }

      private:
        FrameRecord m_Items[N]{};
        uint64_t m_Pushed = 0;
    };

    // Signals the registered events once per v-blank from a worker thread. The thread starts with the first
    // registration and idles (blocked on a condition variable) while nothing is registered.
    class VLineNotifier
    {
      public:
        static constexpr uint32_t MaxCounters = 4;
        using WaitFn = std::function<void()>; // blocks until the next v-blank

        explicit VLineNotifier(WaitFn Wait) : m_Wait(std::move(Wait))
        {
        }

        VLineNotifier(VLineNotifier const &) = delete;
        VLineNotifier &operator=(VLineNotifier const &) = delete;

        ~VLineNotifier()
        {
            {
                std::lock_guard Lock(m_Mutex);
                m_Stop = true;
            }
            m_Cv.notify_all();
            if (m_Thread.joinable())
                m_Thread.join();

            for (HANDLE &Event : m_Events)
                CloseIfSet(Event);
        }

        // Registers hEvent for Counter (replacing any earlier one); nullptr unregisters. The handle is
        // duplicated, so the caller may close its own copy.
        HRESULT Set(uint32_t Counter, HANDLE hEvent)
        {
            if (Counter >= MaxCounters)
                return E_INVALIDARG;

            HANDLE Owned = nullptr;
            if (hEvent && !DuplicateHandle(GetCurrentProcess(), hEvent, GetCurrentProcess(), &Owned,
                                           EVENT_MODIFY_STATE, FALSE, 0))
                return HRESULT_FROM_WIN32(GetLastError());

            {
                std::lock_guard Lock(m_Mutex);
                CloseIfSet(m_Events[Counter]);
                m_Events[Counter] = Owned;

                if (Owned && !m_Thread.joinable())
                    m_Thread = std::thread([this] { Run(); });
            }
            m_Cv.notify_all();
            return S_OK;
        }

        uint64_t SignalCount() const
        {
            std::lock_guard Lock(m_Mutex);
            return m_Signals;
        }

      private:
        static void CloseIfSet(HANDLE &Handle)
        {
            if (Handle)
            {
                CloseHandle(Handle);
                Handle = nullptr;
            }
        }

        bool AnyRegistered() const
        {
            for (HANDLE Event : m_Events)
                if (Event)
                    return true;
            return false;
        }

        void Run()
        {
            std::unique_lock Lock(m_Mutex);
            for (;;)
            {
                m_Cv.wait(Lock, [this] { return m_Stop || AnyRegistered(); });
                if (m_Stop)
                    return;

                Lock.unlock();
                m_Wait();
                Lock.lock();

                if (m_Stop)
                    return;

                for (HANDLE Event : m_Events)
                    if (Event)
                        SetEvent(Event);
                ++m_Signals;
            }
        }

        WaitFn m_Wait;
        mutable std::mutex m_Mutex;
        std::condition_variable m_Cv;
        HANDLE m_Events[MaxCounters]{};
        uint64_t m_Signals = 0;
        bool m_Stop = false;
        std::thread m_Thread;
    };

    // Waits for the next v-blank of the primary output. Falls back to pacing at the refresh rate when there is
    // no output or WaitForVBlank returns early (headless machines, WARP).
    class VBlankWaiter
    {
      public:
        VBlankWaiter() : m_Period(RefreshPeriodTicks()), m_Last(Now())
        {
            Microsoft::WRL::ComPtr<IDXGIFactory1> Factory;
            Microsoft::WRL::ComPtr<IDXGIAdapter1> Adapter;
            if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&Factory))) && SUCCEEDED(Factory->EnumAdapters1(0, &Adapter)))
                Adapter->EnumOutputs(0, &m_Output);

            m_Timer = CreateWaitableTimerExW(nullptr, nullptr, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
            if (!m_Timer)
                m_Timer = CreateWaitableTimerW(nullptr, TRUE, nullptr);
        }

        VBlankWaiter(VBlankWaiter const &) = delete;
        VBlankWaiter &operator=(VBlankWaiter const &) = delete;

        ~VBlankWaiter()
        {
            if (m_Timer)
                CloseHandle(m_Timer);
        }

        void operator()()
        {
            if (m_Output)
                m_Output->WaitForVBlank();

            // Never report v-blanks much faster than the display refreshes. The quarter-period slack keeps a
            // real v-blank that arrives a little early from being delayed.
            uint64_t const Due = m_Last + m_Period;
            uint64_t Current = Now();
            if (Current + m_Period / 4 < Due)
            {
                SleepTicks(Due - Current);
                Current = Now();
            }
            m_Last = Current;
        }

      private:
        void SleepTicks(uint64_t Ticks)
        {
            LARGE_INTEGER Freq;
            QueryPerformanceFrequency(&Freq);
            // Relative due time in 100 ns units (negative = relative).
            LARGE_INTEGER DueTime;
            DueTime.QuadPart = -static_cast<LONGLONG>(Ticks * 10'000'000ull / static_cast<uint64_t>(Freq.QuadPart));

            if (m_Timer && SetWaitableTimer(m_Timer, &DueTime, 0, nullptr, nullptr, FALSE))
                WaitForSingleObject(m_Timer, INFINITE);
            else
                Sleep(static_cast<DWORD>(-DueTime.QuadPart / 10'000) + 1);
        }

        Microsoft::WRL::ComPtr<IDXGIOutput> m_Output;
        HANDLE m_Timer = nullptr;
        uint64_t m_Period;
        uint64_t m_Last;
    };

    // Process-wide present history. A function-local static avoids adding globals to d3d11.x.h.
    struct PresentHistory
    {
        std::mutex Mutex;
        FrameRing<16> Frames;
        uint64_t Start = Now();
        uint64_t Period = RefreshPeriodTicks();
    };

    inline PresentHistory &GetPresentHistory()
    {
        static PresentHistory History;
        return History;
    }

    // Intentionally leaked: joining the worker from a static destructor would run under the loader lock at
    // DLL unload. The thread ends with the process.
    inline VLineNotifier &GetVLineNotifier()
    {
        static VLineNotifier *Notifier =
            new VLineNotifier([Waiter = std::make_shared<VBlankWaiter>()] { (*Waiter)(); });
        return *Notifier;
    }
}

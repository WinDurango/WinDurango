#pragma once
#include "ACPLoganTypes.h"

BOOL(WINAPI *TrueDeviceIoControl)(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize,
                                  LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned,
                                  LPOVERLAPPED lpOverlapped) = DeviceIoControl;
HANDLE hLoganMap{};
DWORD m_pBumpAllocStart = 0x10000;

DWORD BumpAlloc(_In_ SIZE_T size)
{
    DWORD allocatedBlock = m_pBumpAllocStart;
    m_pBumpAllocStart += (size + 0xFFFF) & ~0xFFFF;
    return allocatedBlock;
}

class LoganHeap
{
  public:
    PVOID _declspec(dllexport) GetVirtualAddress(_In_ APU_ADDRESS ApuAddress, _In_ SIZE_T SizeInBytes);

    template <typename T> 
    T *GetVirtualAddress(_In_ APU_ADDRESS ApuAddress, _In_ SIZE_T Count = 1);

    HRESULT _declspec(dllexport) GetDriverMemory(UINT32 index, LOGAN_PHYSICAL_MEMORY *memory);

    void _declspec(dllexport) AllocateDriverMemory();

    HRESULT _declspec(dllexport) Map(PVOID cpuAddress, APU_ADDRESS apuAddress, UINT32 sizeInBytes);

    PVOID _view;
    SIZE_T _sizeInBytes;
    LOGAN_PHYSICAL_MEMORY _driverMemory[3];
    static ULONGLONG constexpr c_XMemAttributes = 0xEC810000; 
    ACP_COMMAND_REGISTER_CONTEXT_ARRAYS _acpContextArrays;
    ACP_COMMAND_CONNECT _acpConnectCommand[4]; //There can be 4 IAcpHal instances! (even though there are not any known games that use more than one)
    UINT32 _enabledMessages = 0;
};

template <typename T> void _declspec(dllexport) DispatchLoganCommand(LOGAN_COMMAND_TYPE cmdType, T cmd);

LoganHeap g_LoganHeap;

_Use_decl_annotations_ DWORD DispatchGetDriverMemory(DWORD IoControlCode, PVOID InBuffer, DWORD InBufferSize,
                                                     PVOID OutBuffer, DWORD OutBufferSize, PDWORD BytesReturned,
                                                     LPOVERLAPPED Overlapped);

template <typename T>
static BOOL ReadFromRingBuffer(T *OutBuffer, T *InBuffer, LOGAN_RING_BUFFER_DESCRIPTOR *InBufferDesc)
{
    if (InBufferDesc->offsetRead == InBufferDesc->offsetWrite)
        return FALSE;

    *OutBuffer = InBuffer[InBufferDesc->offsetRead];
    InBufferDesc->offsetRead =
        InBufferDesc->offsetRead + 1 < InBufferDesc->sizeInBlocks ? InBufferDesc->offsetRead + 1 : 0;
    return TRUE;
}

static BOOL ReadFromInternalACPRingBuffer(AcpCommand *OutBuffer, AcpInternalCommandQueueEntry* InBuffer, AcpState *InBufferDesc)
{
    if (InBufferDesc->internalCommandQueueReadCounter == InBufferDesc->internalCommandQueueSendCounter)
        return FALSE;

    *OutBuffer = InBuffer[InBufferDesc->internalCommandQueueReadPointer].command;
    InBuffer[InBufferDesc->internalCommandQueueReadPointer].state = 0;
    InBufferDesc->internalCommandQueueReadPointer++;
    InBufferDesc->internalCommandQueueReadCounter++;

    if (InBufferDesc->internalCommandQueueReadPointer >= 16)
        InBufferDesc->internalCommandQueueReadPointer = 0;

    return TRUE;
}

static BOOL ReadFromClientACPRingBuffer(AcpCommand *OutBuffer, AcpCommandQueueEntry *InBuffer, AcpState *InBufferDesc, UINT ClientIndex)
{
    if (InBufferDesc->clientCommandQueueReadCounter[ClientIndex] == InBufferDesc->clientCommandQueueSendCounter[ClientIndex])
        return FALSE;

    *OutBuffer = InBuffer[InBufferDesc->clientCommandQueueReadPointer[ClientIndex]].command;
    InBuffer[InBufferDesc->clientCommandQueueReadPointer[ClientIndex]].state = 0;
    InBufferDesc->clientCommandQueueReadPointer[ClientIndex]++;
    InBufferDesc->clientCommandQueueReadCounter[ClientIndex]++;

    if (InBufferDesc->clientCommandQueueReadPointer[ClientIndex] >= 16)
        InBufferDesc->clientCommandQueueReadPointer[ClientIndex] = 0;

    return TRUE;
}

LOGAN_COMMAND_ACP_INIT *InitialCommand;

template <typename T> 
inline void DispatchACPCommand(ACP_COMMAND_TYPE_INTERNAL cmdType, AcpState *acpState, T Cmd);

template <typename T> 
inline void DispatchClientACPCommand(ACP_COMMAND_TYPE cmdType, AcpState *acpState, T Cmd);

template <typename T> 
inline void DispatchLoganCommand(LOGAN_COMMAND_TYPE cmdType, T cmd);

static DWORD WINAPI LoganChannelProc(LPVOID lpThreadParameter)
{
    SetThreadDescription(GetCurrentThread(), L"Logan Thread");

    auto channel = (LOGAN_CHANNEL *)lpThreadParameter;
    auto commands = g_LoganHeap.GetVirtualAddress<LOGAN_COMMAND_INTERNAL>(channel->commands.apuAddress,
                                                                          channel->commands.sizeInBlocks);
    auto messages = g_LoganHeap.GetVirtualAddress<LOGAN_MESSAGE_INTERNAL>(channel->messages.apuAddress,
                                                                          channel->messages.sizeInBlocks);
    do
    {
        LOGAN_COMMAND_INTERNAL command;
        while (ReadFromRingBuffer(&command, commands, &channel->commands))
        {
            DispatchLoganCommand((LOGAN_COMMAND_TYPE)command.commandType, g_LoganHeap.GetVirtualAddress(command.apuAddress, sizeof((LOGAN_COMMAND_TYPE)command.commandType)));
            messages[channel->messages.offsetWrite].status = ACP_MESSAGE_TYPE_COMMAND_COMPLETED;
            messages[channel->messages.offsetWrite].time = GetTickCount();
            messages[channel->messages.offsetWrite].unknown0 = 1;
            channel->messages.offsetWrite = (channel->messages.offsetWrite + 1 < channel->messages.sizeInBlocks) ? channel->messages.offsetWrite + 1 : 0;
        }       

        if (InitialCommand != nullptr)
        {
            AcpInternalCommandQueueEntry *AcpInternalCommandQueue = g_LoganHeap.GetVirtualAddress<AcpInternalCommandQueueEntry>(InitialCommand->acpCommandQueue);
            AcpState *pAcpState = g_LoganHeap.GetVirtualAddress<AcpState>(InitialCommand->acpState);

            if (pAcpState != nullptr && AcpInternalCommandQueue->command.commandType != 0)
            {
                AcpCommand Command{};
                while (ReadFromInternalACPRingBuffer(&Command, AcpInternalCommandQueue, pAcpState))
                {
                    if (Command.commandType)
                    {
                        DispatchACPCommand((ACP_COMMAND_TYPE_INTERNAL)Command.commandType, pAcpState, Command);
                    }
                }
            }
        }

        for (UINT i = 0; i < 4; i++)
        {
            if (g_LoganHeap._acpConnectCommand[i].commandQueue != 0)
            {
                AcpCommandQueueEntry *AcpClientCommandQueue = g_LoganHeap.GetVirtualAddress<AcpCommandQueueEntry>(g_LoganHeap._acpConnectCommand[i].commandQueue);
                AcpState *pAcpState = g_LoganHeap.GetVirtualAddress<AcpState>(InitialCommand->acpState);

                if (pAcpState != nullptr && AcpClientCommandQueue->command.commandType != 0)
                {
                    AcpCommand Command{};
                    while (ReadFromClientACPRingBuffer(&Command, AcpClientCommandQueue, pAcpState, i))
                    {
                        if (Command.commandType)
                        {
                            DispatchClientACPCommand((ACP_COMMAND_TYPE)Command.commandType, pAcpState, Command);
                            if (g_LoganHeap._enabledMessages & ACP_MESSAGE_TYPE_COMMAND_COMPLETED)
                            {
                                ACP_MESSAGE AcpMessage{};
                                AcpMessage.type = ACP_MESSAGE_TYPE_COMMAND_COMPLETED;
                                AcpMessage.commandCompleted.commandType = Command.commandType;
                                AcpMessage.commandCompleted.audioFrame = Command.frame;
                                AcpMessage.commandCompleted.commandId = Command.commandId;
                            }
                        }
                    }
                }
            }
        }

    } while (true);

    return 0;
}

HANDLE LoganHandle = nullptr;

EXTERN_C BOOL __stdcall EraDeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer,
                                           DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize,
                                           LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped)
{
    if (hDevice != LoganHandle)
    {
        return TrueDeviceIoControl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize,
                               lpBytesReturned, lpOverlapped);
    }
    else
    {
        if (dwIoControlCode == IOCTL_LOGAN_ALLOC_MAP) // 0x800E007
        {
            LOGAN_IOCTL_IN_ALLOC_MAP *InMap = reinterpret_cast<LOGAN_IOCTL_IN_ALLOC_MAP *>(lpInBuffer);

            UINT Size = (InMap->sizeInBytes + ((1ULL << 16) - 1)) & ~((1ULL << 16) - 1);
            UINT NumPages = Size / (1ULL << 16);
            DWORD ApuAddress = BumpAlloc(Size);
            g_LoganHeap.Map(InMap->address, ApuAddress, (1ULL << 16));

            LOGAN_IOCTL_OUT_ALLOC_MAP outMap{};
            outMap.allocated = InMap->sizeInBytes;
            outMap.address = InMap->address;
            outMap.apuAddress = ApuAddress;
            outMap.reserved0 = 0;

            *reinterpret_cast<LOGAN_IOCTL_OUT_ALLOC_MAP *>(lpOutBuffer) = outMap;
            *lpBytesReturned = 32;
            SetLastError(ERROR_SUCCESS);
        }
        else if (dwIoControlCode == IOCTL_LOGAN_ATTACH_CHANNEL) // 0x800E00B
        {
            LOGAN_IOCTL_IN_ATTACH_CHANNEL *In = reinterpret_cast<LOGAN_IOCTL_IN_ATTACH_CHANNEL *>(lpInBuffer);
            LOGAN_CHANNEL *Channel = g_LoganHeap.GetVirtualAddress<LOGAN_CHANNEL>(In->apuAddress);
            std::thread LoganThread(LoganChannelProc, Channel);
            LoganThread.detach();
            SetLastError(ERROR_SUCCESS);
        }
        else if (dwIoControlCode == IOCTL_LOGAN_GET_MEMORY_STATISTICS)
        {
            MessageBoxA(NULL, "IOCTL_LOGAN_GET_MEMORY_STATISTICS", "DeviceIoControl", MB_OK);
        }
        else if (dwIoControlCode == IOCTL_LOGAN_GET_NUI_BUFFER_STATE)
        {
            MessageBoxA(NULL, "IOCTL_LOGAN_GET_NUI_BUFFER_STATE", "DeviceIoControl", MB_OK);
        }
        else if (dwIoControlCode == IOCTL_LOGAN_SET_NUI_MEC_BUFFER_WRITE_OFFSET)
        {
            MessageBoxA(NULL, "IOCTL_LOGAN_SET_NUI_MEC_BUFFER_WRITE_OFFSET", "DeviceIoControl", MB_OK);
        }
        else if (dwIoControlCode == IOCTL_LOGAN_LOAD_ACP_FIRMWARE)
        {
            SetLastError(ERROR_SUCCESS);
            return TRUE;
        }
        else if (dwIoControlCode == IOCTL_LOGAN_SET_USB_CAPTURE_STATE)
        {
            MessageBoxA(NULL, "IOCTL_LOGAN_SET_USB_CAPTURE_STATE", "DeviceIoControl", MB_OK);
        }
        else if (dwIoControlCode == IOCTL_LOGAN_GET_DRIVER_MEMORY)
        {
            DispatchGetDriverMemory(dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize,
                                    lpBytesReturned, lpOverlapped);
            SetLastError(ERROR_SUCCESS);
        }
        else
        {
            //This shouldn't happen since these are all known codes.
            MessageBoxA(NULL, "Unknown Logan code!", "DeviceIoControl", MB_OK);
        }

        return TRUE;
    }
}

void LoganInit()
{
    hLoganMap = CreateFileMapping2(INVALID_HANDLE_VALUE, nullptr, FILE_MAP_READ | FILE_MAP_WRITE, PAGE_READWRITE, SEC_RESERVE, 0x20000000, nullptr, nullptr, 0);
    g_LoganHeap.AllocateDriverMemory();
    g_LoganHeap._view = MapViewOfFile(hLoganMap, FILE_MAP_WRITE, 0, 0, 0);

    printf("Logan was initialized.\n");
}

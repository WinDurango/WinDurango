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
    PVOID GetVirtualAddress(_In_ APU_ADDRESS ApuAddress, _In_ SIZE_T SizeInBytes);

    template <typename T> 
    T *GetVirtualAddress(_In_ APU_ADDRESS ApuAddress, _In_ SIZE_T Count = 1);

    APU_ADDRESS GetAPUAddress(_In_ PVOID CpuAddress);

    HRESULT GetDriverMemory(UINT32 index, LOGAN_PHYSICAL_MEMORY *memory);
    void AllocateDriverMemory();
    HRESULT Map(PVOID cpuAddress, APU_ADDRESS apuAddress, UINT32 sizeInBytes);
    BOOL CheckForBlockedSampleRateConverterContexts(UINT *BlockedIndex);
    BOOL CheckForBlockedDMAContexts(UINT *BlockedIndex);

    PVOID _view;
    SIZE_T _sizeInBytes;
    LOGAN_PHYSICAL_MEMORY _driverMemory[3];
    static ULONGLONG constexpr c_XMemAttributes = 0xEC810000; 
    ACP_COMMAND_REGISTER_CONTEXT_ARRAYS _acpContextArrays;
    AcpCommand *_acpConnectCommand[4]{};
    AcpCommand_Old *_acpConnectCommandOld[4]{};
    SHAPE_FLOWGRAPH_COMMAND *_flowgraph{};
    UINT32 _numCommandsInFlowgraph = 0;
    UINT32 _enabledMessages = 0;
    UINT32 _droppedMessages = 0;
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

    InBuffer[InBufferDesc->internalCommandQueueReadPointer].state = 0;
    *OutBuffer = InBuffer[InBufferDesc->internalCommandQueueReadPointer].command;

    InBufferDesc->internalCommandQueueReadPointer++;
    InBufferDesc->internalCommandQueueReadCounter++;

    if (InBufferDesc->internalCommandQueueReadPointer >= 16)
        InBufferDesc->internalCommandQueueReadPointer = 0;

    return TRUE;
}

static BOOL ReadFromInternalACPRingBufferOld(AcpCommand_Old *OutBuffer, AcpInternalCommandQueueEntry_Old* InBuffer, AcpState_Old *InBufferDesc)
{
    if (!InBuffer[InBufferDesc->internalCommandQueueReadPointer].command.commandType)
        return FALSE;

    InBuffer[InBufferDesc->internalCommandQueueReadPointer].state = 0;
    *OutBuffer = InBuffer[InBufferDesc->internalCommandQueueReadPointer].command;

    InBufferDesc->internalCommandQueueReadPointer++;

    if (InBufferDesc->internalCommandQueueReadPointer >= 16)
        InBufferDesc->internalCommandQueueReadPointer = 0;

    return TRUE;
}

static BOOL ReadFromXmaContext(SHAPE_XMA_CONTEXT *OutBuffer, SHAPE_XMA_CONTEXT *InBuffer, UINT ContextIndex)
{
    *OutBuffer = InBuffer[ContextIndex];
    return TRUE;
}

static BOOL ReadFromClientACPRingBuffer(AcpCommand *OutBuffer, AcpCommandQueueEntry *InBuffer, AcpState *InBufferDesc, UINT ClientIndex)
{
    if (InBufferDesc->clientCommandQueueReadCounter[ClientIndex] == InBufferDesc->clientCommandQueueSendCounter[ClientIndex])
        return FALSE;

    InBuffer[InBufferDesc->clientCommandQueueReadPointer[ClientIndex]].state = 0;
    *OutBuffer = InBuffer[InBufferDesc->clientCommandQueueReadPointer[ClientIndex]].command;

    InBufferDesc->clientCommandQueueReadPointer[ClientIndex]++;
    InBufferDesc->clientCommandQueueReadCounter[ClientIndex]++;

    if (InBufferDesc->clientCommandQueueReadPointer[ClientIndex] >= 16)
        InBufferDesc->clientCommandQueueReadPointer[ClientIndex] = 0;

    return TRUE;
}

static BOOL ReadFromClientACPRingBufferOld(AcpCommand_Old *OutBuffer, AcpCommandQueueEntry_Old *InBuffer, AcpState_Old *InBufferDesc, UINT ClientIndex)
{
    if (!InBuffer[InBufferDesc->clientCommandQueueReadPointer[ClientIndex]].command.commandType)
        return FALSE;

    InBuffer[InBufferDesc->clientCommandQueueReadPointer[ClientIndex]].state = 0;
    *OutBuffer = InBuffer[InBufferDesc->clientCommandQueueReadPointer[ClientIndex]].command;

    InBufferDesc->clientCommandQueueReadPointer[ClientIndex]++;

    if (InBufferDesc->clientCommandQueueReadPointer[ClientIndex] >= 16)
        InBufferDesc->clientCommandQueueReadPointer[ClientIndex] = 0;

    return TRUE;
}

BOOL(*P_PopMessage)(LPVOID, ACP_MESSAGE_OLD*);
std::vector<ACP_MESSAGE> g_MessageQueue;

//THIS IS MEANT TO BE A WORKAROUND.
BOOL __fastcall D_PopMessage(LPVOID pIAcpHal, ACP_MESSAGE_OLD *pMessage)
{
    BOOL Result = P_PopMessage(pIAcpHal, pMessage);

    if (Result)
        printf("PopMessage returned a message!\n");

    return Result;
}

void SendMessageFromACP(ACP_MESSAGE *pMessage, AcpMessageQueueEntry *pMessageQueue, AcpState *pAcpState, UINT ClientIndex);

LOGAN_COMMAND_ACP_INIT *InitialCommand = nullptr;
LOGAN_COMMAND_ACP_INIT_OLD *InitialCommandOld = nullptr;

inline void DispatchACPCommand(ACP_COMMAND_TYPE_INTERNAL cmdType, AcpState *acpState, AcpCommand Cmd);
inline void DispatchACPCommandOld(ACP_COMMAND_TYPE_INTERNAL cmdType, AcpState_Old *acpState, AcpCommand_Old Cmd);

template <typename T> 
inline void DispatchClientACPCommand(ACP_COMMAND_TYPE cmdType, AcpState *acpState, T Cmd);

template <typename T> 
inline void DispatchClientACPCommandOld(ACP_COMMAND_TYPE cmdType, AcpState_Old *acpState, T Cmd);

template <typename T> 
inline void DispatchLoganCommand(LOGAN_COMMAND_TYPE cmdType, T cmd);

void SendMessageFromACP(ACP_MESSAGE *pMessage, AcpMessageQueueEntry *pMessageQueue, AcpState *pAcpState, UINT ClientIndex);

void SendMessageFromACPOld(ACP_MESSAGE_OLD *pMessage, AcpMessageQueueEntry_Old *pMessageQueue, AcpState *pAcpState, UINT ClientIndex);

void SendMessageFromACPOlder(ACP_MESSAGE_OLD *pMessage, AcpMessageQueueEntry_Old *pMessageQueue, AcpState_Old *pAcpState, UINT ClientIndex);

static DWORD WINAPI LoganChannelProc(LPVOID lpThreadParameter)
{
    SetThreadDescription(GetCurrentThread(), L"Logan Thread");

    auto channel = (LOGAN_CHANNEL *)lpThreadParameter;
    auto commands = g_LoganHeap.GetVirtualAddress<LOGAN_COMMAND_INTERNAL>(channel->commands.apuAddress,
                                                                          channel->commands.sizeInBlocks);
    auto messages = g_LoganHeap.GetVirtualAddress<LOGAN_MESSAGE_INTERNAL>(channel->messages.apuAddress,
                                                                          channel->messages.sizeInBlocks);

    AcpState *pAcpState = nullptr;
    AcpState_Old *pAcpStateOld = nullptr;
    CpuState *pCpuState = nullptr;
    while (true)
    {
        LOGAN_COMMAND_INTERNAL command{};

        while (ReadFromRingBuffer(&command, commands, &channel->commands))
        {
            DispatchLoganCommand((LOGAN_COMMAND_TYPE)command.commandType, g_LoganHeap.GetVirtualAddress(command.apuAddress, sizeof((LOGAN_COMMAND_TYPE)command.commandType)));
        }       

        if (InitialCommand != nullptr)
        {
            AcpInternalCommandQueueEntry *AcpInternalCommandQueue = g_LoganHeap.GetVirtualAddress<AcpInternalCommandQueueEntry>(InitialCommand->acpCommandQueue);
            if (!pAcpState) pAcpState = g_LoganHeap.GetVirtualAddress<AcpState>(InitialCommand->acpState);

            if (pAcpState && AcpInternalCommandQueue)
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
        else if (InitialCommandOld != nullptr)
        {
            AcpInternalCommandQueueEntry_Old *AcpInternalCommandQueue = g_LoganHeap.GetVirtualAddress<AcpInternalCommandQueueEntry_Old>(InitialCommandOld->acpCommandQueue);
            if (!pAcpStateOld) pAcpStateOld = g_LoganHeap.GetVirtualAddress<AcpState_Old>(InitialCommandOld->acpState);
            if (!pCpuState) pCpuState = g_LoganHeap.GetVirtualAddress<CpuState>(InitialCommandOld->cpuState);
            if (pAcpStateOld && AcpInternalCommandQueue)
            {
                AcpCommand_Old Command{};
                while (ReadFromInternalACPRingBufferOld(&Command, AcpInternalCommandQueue, pAcpStateOld))
                {
                    if (Command.commandType)
                    {
                        DispatchACPCommandOld((ACP_COMMAND_TYPE_INTERNAL)Command.commandType, pAcpStateOld, Command);
                    }
                }
            }
        }

        for (UINT i = 0; i < 4; i++)
        {
            if (g_LoganHeap._acpConnectCommand[i] && pAcpState)
            {
                AcpCommandQueueEntry *AcpClientCommandQueue = g_LoganHeap.GetVirtualAddress<AcpCommandQueueEntry>(g_LoganHeap._acpConnectCommand[i]->connect.commandQueue, g_LoganHeap._acpConnectCommand[i]->connect.numCommands);
                AcpPendingCommand *AcpClientPendingCommand = g_LoganHeap.GetVirtualAddress<AcpPendingCommand>(g_LoganHeap._acpConnectCommand[i]->connect.pendingCommandList);
                AcpMessageQueueEntry *AcpClientMessageQueue = nullptr;
                AcpMessageQueueEntry_Old *AcpClientMessageQueueOld = nullptr;
                UINT BlockedIndex = 0;
                if (g_ABI >= abi_t{6,2,11785,0})
                    AcpClientMessageQueue = g_LoganHeap.GetVirtualAddress<AcpMessageQueueEntry>(g_LoganHeap._acpConnectCommand[i]->connect.messageQueue, g_LoganHeap._acpConnectCommand[i]->connect.numMessages);
                else
                    AcpClientMessageQueueOld = g_LoganHeap.GetVirtualAddress<AcpMessageQueueEntry_Old>(g_LoganHeap._acpConnectCommand[i]->connect.messageQueue, g_LoganHeap._acpConnectCommand[i]->connect.numMessages);

                if (pAcpState && AcpClientCommandQueue)
                {
                    AcpCommand Command{};
                    while (ReadFromClientACPRingBuffer(&Command, AcpClientCommandQueue, pAcpState, i))
                    {
                        if (Command.commandType)
                        {
                            DispatchClientACPCommand((ACP_COMMAND_TYPE)Command.commandType, pAcpState, Command);
                            if ((g_LoganHeap._enabledMessages & ACP_MESSAGE_TYPE_COMMAND_COMPLETED) && AcpClientMessageQueueOld)
                            {
                                ACP_MESSAGE_OLD Message{};
                                Message.type = ACP_MESSAGE_TYPE_COMMAND_COMPLETED;
                                Message.commandCompleted.commandId = Command.commandId;
                                Message.commandCompleted.commandType = Command.commandType;
                                Message.commandCompleted.audioFrame = Command.frame;
                                Message.droppedMessageCount = g_LoganHeap._droppedMessages;
                                g_LoganHeap._droppedMessages++;
                                SendMessageFromACPOld(&Message, AcpClientMessageQueueOld, pAcpState, i);
                            }
                            else if ((g_LoganHeap._enabledMessages & ACP_MESSAGE_TYPE_COMMAND_COMPLETED) && AcpClientMessageQueue)
                            {
                                ACP_MESSAGE Message{};
                                Message.type = ACP_MESSAGE_TYPE_COMMAND_COMPLETED;
                                Message.commandCompleted.commandId = Command.commandId;
                                Message.commandCompleted.commandType = Command.commandType;
                                Message.commandCompleted.audioFrame = Command.frame;
                                Message.droppedMessageCount = g_LoganHeap._droppedMessages;
                                g_LoganHeap._droppedMessages++;
                                SendMessageFromACP(&Message, AcpClientMessageQueue, pAcpState, i);
                            }

                            if ((g_LoganHeap._enabledMessages & ACP_MESSAGE_TYPE_FLOWGRAPH_COMPLETED) && AcpClientMessageQueueOld && Command.commandType == ACP_COMMAND_TYPE_LOAD_SHAPE_FLOWGRAPH)
                            {
                                ACP_MESSAGE_OLD Message{};
                                Message.type = ACP_MESSAGE_TYPE_FLOWGRAPH_COMPLETED;
                                Message.flowgraphCompleted.flowgraph = g_LoganHeap.GetAPUAddress(g_LoganHeap._flowgraph);
                                Message.droppedMessageCount = g_LoganHeap._droppedMessages;
                                g_LoganHeap._droppedMessages++;
                                SendMessageFromACPOld(&Message, AcpClientMessageQueueOld, pAcpState, i);
                            }
                            else if ((g_LoganHeap._enabledMessages & ACP_MESSAGE_TYPE_FLOWGRAPH_COMPLETED) && AcpClientMessageQueue && Command.commandType == ACP_COMMAND_TYPE_LOAD_SHAPE_FLOWGRAPH)
                            {
                                ACP_MESSAGE Message{};
                                Message.type = ACP_MESSAGE_TYPE_FLOWGRAPH_COMPLETED;
                                Message.flowgraphCompleted.flowgraph = g_LoganHeap.GetAPUAddress(g_LoganHeap._flowgraph);
                                Message.droppedMessageCount = g_LoganHeap._droppedMessages;
                                g_LoganHeap._droppedMessages++;
                                SendMessageFromACP(&Message, AcpClientMessageQueue, pAcpState, i);
                            }
                        }
                    }
                }
            }
            else if (g_LoganHeap._acpConnectCommandOld[i] && pAcpStateOld)
            {
                AcpCommandQueueEntry_Old *AcpClientCommandQueue = g_LoganHeap.GetVirtualAddress<AcpCommandQueueEntry_Old>(g_LoganHeap._acpConnectCommandOld[i]->connect.commandQueue, g_LoganHeap._acpConnectCommandOld[i]->connect.numCommands);
                AcpMessageQueueEntry_Old *AcpClientMessageQueue = g_LoganHeap.GetVirtualAddress<AcpMessageQueueEntry_Old>(g_LoganHeap._acpConnectCommandOld[i]->connect.messageQueue, g_LoganHeap._acpConnectCommandOld[i]->connect.numMessages);
                AcpPendingCommand *AcpClientPendingCommand = g_LoganHeap.GetVirtualAddress<AcpPendingCommand>(g_LoganHeap._acpConnectCommandOld[i]->connect.pendingCommandList);
                UINT BlockedIndex = 0;

                if (pAcpStateOld && AcpClientCommandQueue)
                {
                    AcpCommand_Old Command{};
                    while (ReadFromClientACPRingBufferOld(&Command, AcpClientCommandQueue, pAcpStateOld, i))
                    {
                        if (Command.commandType)
                        {
                            DispatchClientACPCommandOld((ACP_COMMAND_TYPE)Command.commandType, pAcpStateOld, Command);
                            if (g_LoganHeap._enabledMessages & ACP_MESSAGE_TYPE_COMMAND_COMPLETED)
                            {
                                ACP_MESSAGE_OLD Message{};
                                Message.type = ACP_MESSAGE_TYPE_COMMAND_COMPLETED;
                                Message.commandCompleted.commandId = Command.commandId;
                                Message.commandCompleted.commandType = Command.commandType;
                                Message.commandCompleted.audioFrame = Command.frame;
                                Message.droppedMessageCount = g_LoganHeap._droppedMessages;
                                g_LoganHeap._droppedMessages++;
                                SendMessageFromACPOlder(&Message, AcpClientMessageQueue, pAcpStateOld, i);
                            }
                        }
                    }
                }
            }
        }
    }

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
            g_LoganHeap.Map(InMap->address, ApuAddress, Size);

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

            if (In->core == LOGAN_CORE_SHAPE)
            {
                printf("Logan Core is LOGAN_CORE_SHAPE.\n");
            }
            else if (In->core == LOGAN_CORE_ACP)
            {
                printf("Logan Core is LOGAN_CORE_ACP.\n");
            }
            else if (In->core == LOGAN_CORE_NONE)
            {
                printf("Logan Core is LOGAN_CORE_NONE.\n");
            }
            else if (In->core == LOGAN_CORE_AVP)
            {
                printf("Logan Core is LOGAN_CORE_AVP.\n");
            }
            else if (In->core == LOGAN_CORE_ASP)
            {
                printf("Logan Core is LOGAN_CORE_ASP.\n");
            }

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
    GetCombaseVersion();
    hLoganMap = CreateFileMapping2(INVALID_HANDLE_VALUE, nullptr, FILE_MAP_READ | FILE_MAP_WRITE, PAGE_READWRITE, SEC_RESERVE, 0x20000000, nullptr, nullptr, 0);
    g_LoganHeap.AllocateDriverMemory();
    g_LoganHeap._view = MapViewOfFile(hLoganMap, FILE_MAP_WRITE, 0, 0, 0);
    g_LoganHeap._sizeInBytes = 0x20000000;
    printf("Logan was initialized.\n");
}

#include "Logan.h"
#include <algorithm>
#include <math.h>

PVOID LoganHeap::GetVirtualAddress(APU_ADDRESS ApuAddress, SIZE_T SizeInBytes)
{
    if (!ApuAddress || (ApuAddress + SizeInBytes) >= _sizeInBytes)
        return nullptr;
    return (PVOID)((ULONG_PTR)_view + ApuAddress);
}

APU_ADDRESS LoganHeap::GetAPUAddress(PVOID CpuAddress)
{
    return (UINT64)CpuAddress - (UINT64)_view;
}

HRESULT LoganHeap::GetDriverMemory(UINT32 index, LOGAN_PHYSICAL_MEMORY *memory)
{
    *memory = _driverMemory[index];
    return S_OK;
}

template <typename T> T *LoganHeap::GetVirtualAddress(APU_ADDRESS ApuAddress, SIZE_T Count)
{
    return (T *)GetVirtualAddress(ApuAddress, sizeof(T) * Count);
}

_Use_decl_annotations_
HRESULT LoganHeap::Map(PVOID cpuAddress, APU_ADDRESS apuAddress,UINT32 sizeInBytes)
{
    if (!cpuAddress)
        return E_INVALIDARG;
    if (apuAddress == 0)
        return E_INVALIDARG;
    if (sizeInBytes == 0)
        return E_INVALIDARG;
    if (!!(sizeInBytes & (PAGE_SIZE_4KB - 1)))
        return E_INVALIDARG;

    sizeInBytes = (sizeInBytes + (PAGE_SIZE_64K - 1)) & ~(PAGE_SIZE_64K - 1);

    // It is assumed that the virtual address is the start of a range of 64K placeholders.
    for (UINT32 i = 0; i < sizeInBytes / PAGE_SIZE_64K; i++)
    {
        LPVOID pageAddress = (LPVOID)((ULONG_PTR)cpuAddress + PAGE_SIZE_64K * i);

        // If the page is already mapped, we need to unmap it first.
        UnmapViewOfFileEx(pageAddress, MEM_PRESERVE_PLACEHOLDER);

        // Any failures here are treated as fatal errors, we expect these to succeed.
        PVOID Mapped = MapViewOfFile3(hLoganMap, nullptr, pageAddress, apuAddress + PAGE_SIZE_64K * i, PAGE_SIZE_64K, MEM_REPLACE_PLACEHOLDER, PAGE_READWRITE, nullptr, 0);
        if (!Mapped)
        {
            printf("LoganHeap::Map: MapViewOfFile3 failed!\n");
        }

        PVOID Allocated = VirtualAlloc2(nullptr, pageAddress, PAGE_SIZE_64K, MEM_COMMIT, PAGE_READWRITE, nullptr, 0);
        if (!Allocated)
        {
            printf("LoganHeap::Map: VirtualAlloc2 failed!\n");
        }
    }

    return S_OK;
}

void LoganHeap::AllocateDriverMemory()
{
    for (SIZE_T i = 0; i < ARRAYSIZE(_driverMemory); i++)
    {
        _driverMemory[i].sizeInBytes = 0x100000;
        UINT Size = (_driverMemory[i].sizeInBytes + ((1ULL << 16) - 1)) & ~((1ULL << 16) - 1);
        UINT NumPages = Size / (1ULL << 16);
        _driverMemory[i].address = XMemAlloc(_driverMemory[i].sizeInBytes, c_XMemAttributes);
        if (_driverMemory[i].address == 0)
        {
            throw GetLastError();
        }
        _driverMemory[i].apuAddress = BumpAlloc(_driverMemory[i].sizeInBytes);
        Map(_driverMemory[i].address, _driverMemory[i].apuAddress, _driverMemory[i].sizeInBytes);
    }
}

_Use_decl_annotations_ DWORD DispatchGetDriverMemory(DWORD IoControlCode, PVOID InBuffer, DWORD InBufferSize,
                                                     PVOID OutBuffer, DWORD OutBufferSize, PDWORD BytesReturned,
                                                     LPOVERLAPPED Overlapped)
{
    auto In = reinterpret_cast<LOGAN_IOCTL_IN_GET_DRIVER_MEMORY const *>(InBuffer);
    auto Out = reinterpret_cast<LOGAN_IOCTL_OUT_GET_DRIVER_MEMORY *>(OutBuffer);

    LOGAN_PHYSICAL_MEMORY memory{};
    g_LoganHeap.GetDriverMemory(In->type, &memory);

    ZeroMemory(Out, sizeof(LOGAN_IOCTL_OUT_GET_DRIVER_MEMORY));
    Out->address = memory.address;
    Out->apuAddress = memory.apuAddress;
    Out->sizeInBytes = memory.sizeInBytes;

    if (BytesReturned)
        *BytesReturned = sizeof(LOGAN_IOCTL_OUT_GET_DRIVER_MEMORY);

    return ERROR_SUCCESS;
}
 
inline void DispatchACPCommand(ACP_COMMAND_TYPE_INTERNAL cmdType, AcpState *acpState, AcpCommand Cmd)
{
    if (cmdType == INTERNAL_ACP_COMMAND_TYPE_CONNECT)
    {
        g_LoganHeap._acpConnectStorage[Cmd.connect.index] = Cmd;
        g_LoganHeap._acpConnectCommand[Cmd.connect.index] = &g_LoganHeap._acpConnectStorage[Cmd.connect.index];
        printf("Registered main ACP command and message queues.\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_DISCONNECT)
    {
        printf("Received Internal ACP command (INTERNAL_ACP_COMMAND_TYPE_DISCONNECT)\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_REGISTER_CONTEXT_ARRAYS)
    {
        g_LoganHeap._acpContextArrays = Cmd.registerContextArrays;
        printf("Registered ACP context arrays.\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_INIT)
    {
        printf("Received Internal ACP command (INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_INIT)\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_ENABLE)
    {
        printf("Received Internal ACP command (INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_ENABLE)\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_DISABLE)
    {
        printf("Received Internal ACP command (INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_DISABLE)\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_TERMINATE)
    {
        printf("Received Internal ACP command (INTERNAL_ACP_COMMAND_TYPE_TERMINATE)\n");
    }
    else
    {
        printf("Received unknown Internal ACP command of type 0x%x\n", cmdType);
    }
}

inline void DispatchACPCommandOld(ACP_COMMAND_TYPE_INTERNAL cmdType, AcpState_Old *acpState, AcpCommand_Old Cmd)
{
    if (cmdType == INTERNAL_ACP_COMMAND_TYPE_CONNECT)
    {
        g_LoganHeap._acpConnectStorageOld[Cmd.connect.instance - 1] = Cmd;
        g_LoganHeap._acpConnectCommandOld[Cmd.connect.instance - 1] = &g_LoganHeap._acpConnectStorageOld[Cmd.connect.instance - 1];
        printf("Registered main ACP command and message queues.\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_DISCONNECT)
    {
        printf("Received Internal ACP command (INTERNAL_ACP_COMMAND_TYPE_DISCONNECT)\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_REGISTER_CONTEXT_ARRAYS)
    {
        g_LoganHeap._acpContextArrays = Cmd.registerContextArrays;
        printf("Registered ACP context arrays.\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_INIT)
    {
        printf("Received Internal ACP command (INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_INIT)\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_ENABLE)
    {
        printf("Received Internal ACP command (INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_ENABLE)\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_DISABLE)
    {
        printf("Received Internal ACP command (INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_DISABLE)\n");
    }
    else if (cmdType == INTERNAL_ACP_COMMAND_TYPE_TERMINATE)
    {
        printf("Received Internal ACP command (INTERNAL_ACP_COMMAND_TYPE_TERMINATE)\n");
    }
    else
    {
        printf("Received unknown Internal ACP command of type 0x%x\n", cmdType);
    }
}

template <typename T>
inline void DispatchClientACPCommand(ACP_COMMAND_TYPE cmdType, AcpState* acpState, T Cmd)
{
    if (cmdType == ACP_COMMAND_TYPE_REGISTER_MESSAGE)
    {
        //Enables one or more message types. Uses the same struct as ACP_COMMAND_TYPE_UNREGISTER_MESSAGE
        g_LoganHeap._enabledMessages |= Cmd.registerMessage.message;

        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_COMMAND_COMPLETED)
        {
            printf("Enabled command completed message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_ERROR)
        {
            printf("Enabled error message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_AUDIO_FRAME_START)
        {
            printf("Enabled frame start message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_DISCONNECTED)
        {
            printf("Enabled disconnected message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_FLOWGRAPH_COMPLETED)
        {
            printf("Enabled flowgraph completed message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_SRC_BLOCKED)
        {
            printf("Enabled Sample Rate Converter blocked message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_DMA_BLOCKED)
        {
            printf("Enabled DMA blocked message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_FLOWGRAPH_TERMINATED)
        {
            printf("Enabled flowgraph terminated message type.\n");
        }
    }
    else if (cmdType == ACP_COMMAND_TYPE_UNREGISTER_MESSAGE)
    {
        //Disables one or more message types. Uses the same struct as ACP_COMMAND_TYPE_REGISTER_MESSAGE
        g_LoganHeap._enabledMessages &= ~Cmd.registerMessage.message;

        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_COMMAND_COMPLETED)
        {
            printf("Disabled command completed message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_ERROR)
        {
            printf("Disabled error message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_AUDIO_FRAME_START)
        {
            printf("Disabled frame start message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_DISCONNECTED)
        {
            printf("Disabled disconnected message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_FLOWGRAPH_COMPLETED)
        {
            printf("Disabled flowgraph completed message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_SRC_BLOCKED)
        {
            printf("Disabled Sample Rate Converter blocked message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_DMA_BLOCKED)
        {
            printf("Disabled DMA blocked message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_FLOWGRAPH_TERMINATED)
        {
            printf("Disabled flowgraph terminated message type.\n");
        }
    }
    else if (cmdType == ACP_COMMAND_TYPE_DISABLE_XMA_CONTEXT)
    {
        ACP_COMMAND_ENABLE_OR_DISABLE_XMA_CONTEXT Command = Cmd.enableOrDisableXmaContext;
        g_LoganHeap._disabledXmaContexts[Command.contextIndex] = !g_LoganHeap._disabledXmaContexts[Command.contextIndex];
        if (g_LoganHeap._disabledXmaContexts[Command.contextIndex] == true)
            printf("Disabled Xma Context at index %u.\n", Command.contextIndex);
        else
            printf("Enabled Xma Context at index %u.\n", Command.contextIndex);
    }
    else if (cmdType == ACP_COMMAND_TYPE_UPDATE_XMA_CONTEXT)
    {
        g_LoganHeap.UpdateXmaContext(Cmd.updateXmaContext);
    }
    else if (cmdType == ACP_COMMAND_TYPE_DISABLE_XMA_CONTEXTS)
    {
        ACP_COMMAND_ENABLE_OR_DISABLE_XMA_CONTEXTS Command = Cmd.enableOrDisableXmaContexts;
        printf("TODO: Disable Xma Contexts.\n");
    }
    else if (cmdType == ACP_COMMAND_TYPE_UPDATE_XMA_READ_BUFFER)
    {
        g_LoganHeap.UpdateXmaReadBuffer(Cmd.updateXmaReadBuffer);
    }
    else if (cmdType == ACP_COMMAND_TYPE_INCREMENT_XMA_WRITE_BUFFER_OFFSET_READ)
    {
        g_LoganHeap.IncrementXmaWriteBufferOffsetRead(Cmd.incrementXmaWriteBufferOffsetRead.contextIndex,
                                                      Cmd.incrementXmaWriteBufferOffsetRead.increment);
    }
    else if (cmdType == ACP_COMMAND_TYPE_INCREMENT_DMA_READ_POINTER)
    {
        g_LoganHeap.IncrementDmaPointer(Cmd.incrementDmaPointer.contextIndex,
                                        Cmd.incrementDmaPointer.increment, false);
    }
    else if (cmdType == ACP_COMMAND_TYPE_INCREMENT_DMA_WRITE_POINTER)
    {
        g_LoganHeap.IncrementDmaPointer(Cmd.incrementDmaPointer.contextIndex,
                                        Cmd.incrementDmaPointer.increment, true);
    }
    else if (cmdType == ACP_COMMAND_TYPE_LOAD_SHAPE_FLOWGRAPH)
    {
        ACP_COMMAND_LOAD_SHAPE_FLOWGRAPH Command = Cmd.loadFlowgraph;
        g_LoganHeap._flowgraph = Command.flowgraph;
        g_LoganHeap._numCommandsInFlowgraph = Command.numCommands;
        g_LoganHeap.RecordFlowgraph(Command);
    }
    else
    {
        printf("Received unknown Client ACP command of type 0x%x\n", cmdType);
    }
}

template <typename T> 
inline void DispatchClientACPCommandOld(ACP_COMMAND_TYPE cmdType, AcpState_Old *acpState, T Cmd)
{
    if (cmdType == ACP_COMMAND_TYPE_REGISTER_MESSAGE)
    {
        //Enables one or more message types. Uses the same struct as ACP_COMMAND_TYPE_UNREGISTER_MESSAGE
        g_LoganHeap._enabledMessages |= Cmd.registerMessage.message;

        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_COMMAND_COMPLETED)
        {
            printf("Enabled command completed message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_ERROR)
        {
            printf("Enabled error message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_AUDIO_FRAME_START)
        {
            printf("Enabled frame start message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_DISCONNECTED)
        {
            printf("Enabled disconnected message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_FLOWGRAPH_COMPLETED)
        {
            printf("Enabled flowgraph completed message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_SRC_BLOCKED)
        {
            printf("Enabled Sample Rate Converter blocked message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_DMA_BLOCKED)
        {
            printf("Enabled DMA blocked message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_FLOWGRAPH_TERMINATED)
        {
            printf("Enabled flowgraph terminated message type.\n");
        }
    }
    else if (cmdType == ACP_COMMAND_TYPE_UNREGISTER_MESSAGE)
    {
        //Disables one or more message types. Uses the same struct as ACP_COMMAND_TYPE_REGISTER_MESSAGE
        g_LoganHeap._enabledMessages &= ~Cmd.registerMessage.message;

        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_COMMAND_COMPLETED)
        {
            printf("Disabled command completed message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_ERROR)
        {
            printf("Disabled error message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_AUDIO_FRAME_START)
        {
            printf("Disabled frame start message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_DISCONNECTED)
        {
            printf("Disabled disconnected message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_FLOWGRAPH_COMPLETED)
        {
            printf("Disabled flowgraph completed message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_SRC_BLOCKED)
        {
            printf("Disabled Sample Rate Converter blocked message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_DMA_BLOCKED)
        {
            printf("Disabled DMA blocked message type.\n");
        }
        if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_FLOWGRAPH_TERMINATED)
        {
            printf("Disabled flowgraph terminated message type.\n");
        }
    }
    else if (cmdType == ACP_COMMAND_TYPE_DISABLE_XMA_CONTEXT)
    {
        ACP_COMMAND_ENABLE_OR_DISABLE_XMA_CONTEXT Command = Cmd.enableOrDisableXmaContext;
        g_LoganHeap._disabledXmaContexts[Command.contextIndex] = !g_LoganHeap._disabledXmaContexts[Command.contextIndex];
        if (g_LoganHeap._disabledXmaContexts[Command.contextIndex] == true)
            printf("Disabled Xma Context at index %u.\n", Command.contextIndex);
        else
            printf("Enabled Xma Context at index %u.\n", Command.contextIndex);
    }
    else if (cmdType == ACP_COMMAND_TYPE_UPDATE_XMA_CONTEXT)
    {
        g_LoganHeap.UpdateXmaContext(Cmd.updateXmaContext);
    }
    else if (cmdType == ACP_COMMAND_TYPE_DISABLE_XMA_CONTEXTS)
    {
        ACP_COMMAND_ENABLE_OR_DISABLE_XMA_CONTEXTS Command = Cmd.enableOrDisableXmaContexts;
        printf("TODO: Disable Xma Contexts.\n");
    }
    else if (cmdType == ACP_COMMAND_TYPE_UPDATE_XMA_READ_BUFFER)
    {
        g_LoganHeap.UpdateXmaReadBuffer(Cmd.updateXmaReadBuffer);
    }
    else if (cmdType == ACP_COMMAND_TYPE_INCREMENT_XMA_WRITE_BUFFER_OFFSET_READ)
    {
        g_LoganHeap.IncrementXmaWriteBufferOffsetRead(Cmd.incrementXmaWriteBufferOffsetRead.contextIndex,
                                                      Cmd.incrementXmaWriteBufferOffsetRead.increment);
    }
    else if (cmdType == ACP_COMMAND_TYPE_INCREMENT_DMA_READ_POINTER)
    {
        g_LoganHeap.IncrementDmaPointer(Cmd.incrementDmaPointer.contextIndex,
                                        Cmd.incrementDmaPointer.increment, false);
    }
    else if (cmdType == ACP_COMMAND_TYPE_INCREMENT_DMA_WRITE_POINTER)
    {
        g_LoganHeap.IncrementDmaPointer(Cmd.incrementDmaPointer.contextIndex,
                                        Cmd.incrementDmaPointer.increment, true);
    }
    else if (cmdType == ACP_COMMAND_TYPE_LOAD_SHAPE_FLOWGRAPH)
    {
        ACP_COMMAND_LOAD_SHAPE_FLOWGRAPH Command = Cmd.loadFlowgraph;
        g_LoganHeap._flowgraph = Command.flowgraph;
        g_LoganHeap._numCommandsInFlowgraph = Command.numCommands;
        g_LoganHeap.RecordFlowgraph(Command);
    }
    else
    {
        printf("Received unknown Client ACP command of type 0x%x\n", cmdType);
    }
}

template <typename T> 
inline void DispatchLoganCommand(LOGAN_COMMAND_TYPE cmdType, T cmd)
{
    if (cmdType == LOGAN_COMMAND_TYPE_ACP_INIT)
    {
        printf("Received Logan command (LOGAN_COMMAND_TYPE_ACP_INIT)\n");

        if (g_ABI <= abi_t{6,2,9894,0})
            InitialCommandOld = reinterpret_cast<LOGAN_COMMAND_ACP_INIT_OLD*>(cmd);
        else
            InitialCommand = reinterpret_cast<LOGAN_COMMAND_ACP_INIT*>(cmd);
    }
    else
    {
        printf("Received unimplemented Logan command: 0x%u.\n", cmdType);
    }
}

void SendMessageFromACP(ACP_MESSAGE *pMessage, AcpMessageQueueEntry *pMessageQueue, AcpState *pAcpState, UINT ClientIndex)
{
    if (!pMessageQueue || !pMessage || !pAcpState)
        return;

    UINT32 const slot = pAcpState->clientMessageQueueWritePointer[ClientIndex];
    if (pMessageQueue[slot].state)
    {
        ++g_LoganHeap._droppedMessages;
        return;
    }

    pMessageQueue[slot].message = *pMessage;
    pMessageQueue[slot].state = 1;

    pAcpState->clientMessageQueueWritePointer[ClientIndex] = (slot + 1 < g_LoganHeap._acpConnectCommand[ClientIndex]->connect.numMessages) ? slot + 1 : 0;
}

void SendMessageFromACPOld(ACP_MESSAGE_OLD *pMessage, AcpMessageQueueEntry_Old *pMessageQueue, AcpState *pAcpState, UINT ClientIndex)
{
    if (!pMessageQueue || !pMessage || !pAcpState)
        return;

    UINT32 const slot = pAcpState->clientMessageQueueWritePointer[ClientIndex];
    if (pMessageQueue[slot].state)
    {
        ++g_LoganHeap._droppedMessages;
        return;
    }

    pMessageQueue[slot].message = *pMessage;
    pMessageQueue[slot].state = 1;

    pAcpState->clientMessageQueueWritePointer[ClientIndex] = (slot + 1 < g_LoganHeap._acpConnectCommand[ClientIndex]->connect.numMessages) ? slot + 1 : 0;
}

void SendMessageFromACPOlder(ACP_MESSAGE_OLD *pMessage, AcpMessageQueueEntry_Old *pMessageQueue, AcpState_Old *pAcpState, UINT ClientIndex)
{
    if (!pMessageQueue || !pMessage || !pAcpState)
        return;

    UINT32 const slot = pAcpState->clientMessageQueueWritePointer[ClientIndex];
    if (pMessageQueue[slot].state)
    {
        ++g_LoganHeap._droppedMessages;
        return;
    }

    pMessageQueue[slot].message = *pMessage;
    pMessageQueue[slot].state = 1;

    pAcpState->clientMessageQueueWritePointer[ClientIndex] = (slot + 1 < g_LoganHeap._acpConnectCommandOld[ClientIndex]->connect.numMessages) ? slot + 1 : 0;
}

void LoganHeap::RecordFlowgraph(ACP_COMMAND_LOAD_SHAPE_FLOWGRAPH const &command)
{
    SHAPE_FLOWGRAPH_COMMAND *Flowgraph = GetVirtualAddress<SHAPE_FLOWGRAPH_COMMAND>(command.flowgraph, command.numCommands);

    for (UINT32 i = 0; i < command.numCommands; ++i)
    {
        SHAPE_FLOWGRAPH_COMMAND entry = Flowgraph[i];
        if (entry.header.disabled)
            continue;

        if (entry.header.command == SHAPE_FLOWGRAPH_COMMAND_TYPE_SRC)
        {
            UINT64 buffers[2] = {entry.src.mixBuffer0, entry.src.mixBuffer1};
            for (UINT64 channel = 0; channel < 2; ++channel)
            {
                if (buffers[channel] < 8192)
                {
                    MixSource &mix = _mixSources[buffers[channel]];
                    mix.context = entry.src.contextId;
                    mix.channel = channel;
                    mix.set = true;
                }
            }
        }
        else if (entry.header.command == SHAPE_FLOWGRAPH_COMMAND_TYPE_DMA)
        {
            UINT32 target = entry.dma.contextId;
            UINT32 buffer = entry.dma.mixBuffer;
            if (target >= 256 || buffer >= 8192 || !_mixSources[buffer].set)
                continue;

            _dmaSource[target].xmaContext = _mixSources[buffer].context;
            _dmaSource[target].channel = _mixSources[buffer].channel;
            _dmaSource[target].set = true;
        }
        else if (entry.header.command == SHAPE_FLOWGRAPH_COMMAND_TYPE_ALLOCMIXBUFFER)
        {
            UINT32 virtualId = entry.allocMixBuffer.virtualId;
            UINT32 numIn = entry.allocMixBuffer.numIn;
            UINT32 numOut = entry.allocMixBuffer.numOut;

            UINT64 buffers[2] = {entry.src.mixBuffer0, entry.src.mixBuffer1};
            for (UINT32 Channel = 0; Channel < 2; ++Channel)
            {
                _mixSources[Channel].numIn = numIn;
                _mixSources[Channel].numOut = numOut;
                _mixSources[Channel].channel = Channel;
                _mixSources[Channel].virtualId = virtualId;
                _mixSources[Channel].set = true;
                virtualId++;
            }
        }
    }
}

void LoganHeap::IncrementDmaPointer(UINT32 contextIndex, UINT32 increment, bool writePointer)
{
    auto *contexts =
        GetVirtualAddress<SHAPE_DMA_CONTEXT>(_acpContextArrays.dmaContextArray, _acpContextArrays.numDmaContexts);
    if (!contexts || contextIndex >= _acpContextArrays.numDmaContexts)
        return;

    SHAPE_DMA_CONTEXT &context = contexts[contextIndex];
    UINT32 const blocks = context.numFrames + 1;
    if (!blocks || !increment)
        return;

    if (writePointer)
    {
        context.writePointer = (context.writePointer + increment) % blocks;
        if (context.writePointer == context.readPointer)
            context.full = 1;
    }
    else
    {
        context.readPointer = (context.readPointer + increment) % blocks;
        context.full = 0;
    }

    if (!writePointer)
        RunFlowgraph();
}

void LoganHeap::IncrementXmaWriteBufferOffsetRead(UINT32 contextIndex, UINT32 increment)
{
    auto *Contexts = GetVirtualAddress<SHAPE_XMA_CONTEXT>(_acpContextArrays.xmaContextArray, _acpContextArrays.numXmaContexts);
    if (!Contexts || contextIndex >= _acpContextArrays.numXmaContexts || !Contexts[contextIndex].sizeWrite)
        return;

    SHAPE_XMA_CONTEXT &Context = Contexts[contextIndex];
    Context.writeBufferOffsetRead = (Context.writeBufferOffsetRead + increment) % Context.sizeWrite;

    printf("Incremented Xma Write Buffer Offset Read for context %u by %u.\n", contextIndex, increment);
}

void LoganHeap::OweFrames(UINT32 frames)
{
    if (!frames)
        return;

    auto *DmaContexts = GetVirtualAddress<SHAPE_DMA_CONTEXT>(_acpContextArrays.dmaContextArray, _acpContextArrays.numDmaContexts);

    for (UINT32 index = 0; index < c_TrackedDmaContexts; ++index)
    {
        if (!_dmaSource[index].set)
            continue;

        UINT MaxOwed = c_MaxOwed;
        if (DmaContexts && index < _acpContextArrays.numDmaContexts)
            MaxOwed = DmaContexts[index].numFrames + 1;

        _dmaOwed[index] += frames;
        if (_dmaOwed[index] > MaxOwed)
            _dmaOwed[index] = MaxOwed;
    }
}

void LoganHeap::RunFlowgraph()
{

    auto *dmaContexts = GetVirtualAddress<SHAPE_DMA_CONTEXT>(_acpContextArrays.dmaContextArray, _acpContextArrays.numDmaContexts);
    auto *xmaContexts = GetVirtualAddress<SHAPE_XMA_CONTEXT>(_acpContextArrays.xmaContextArray, _acpContextArrays.numXmaContexts);
    if (!dmaContexts || !xmaContexts)
        return;

    for (UINT32 index = 0; index < _acpContextArrays.numDmaContexts; ++index)
    {
        if (!_dmaSource[index].set)
            continue;

        SHAPE_DMA_CONTEXT &context = dmaContexts[index];
        if (!context.address)
            continue;

        while (_dmaOwed[index])
        {
            if (context.full)
                break;

            UINT32 const blocks = context.numFrames + 1;
            UINT32 const block = context.writePointer;
            if (block >= blocks)
                break;

            auto *samples = GetVirtualAddress<float>(context.address + block * c_SamplesPerFrame * sizeof(float), c_SamplesPerFrame);
            if (!samples)
                break;

            UINT32 produced = 0;
            if (_dmaSource[index].xmaContext < _acpContextArrays.numXmaContexts && _disabledXmaContexts[_dmaSource[index].xmaContext] == false)
                produced = ServiceXmaContext(_dmaSource[index].xmaContext, _dmaSource[index].channel, samples, c_SamplesPerFrame);

            for (UINT32 s = produced; s < c_SamplesPerFrame; ++s)
                samples[s] = 0.0f;

            context.writePointer = (context.writePointer + 1) % blocks;
            if (context.writePointer == context.readPointer)
                context.full = 1;

            --_dmaOwed[index];
        }
    }
}

void LoganHeap::UpdateXmaReadBuffer(ACP_COMMAND_UPDATE_XMA_READ_BUFFER const &command)
{
    auto *contexts = GetVirtualAddress<SHAPE_XMA_CONTEXT>(_acpContextArrays.xmaContextArray, _acpContextArrays.numXmaContexts);
    if (!contexts || command.contextIndex >= _acpContextArrays.numXmaContexts)
        return;

    SHAPE_XMA_CONTEXT &context = contexts[command.contextIndex];
    UINT32 const buffer = command.bufferIndex & 1;
    bool const sizeUsable = command.bufferSize > 0 && command.bufferSize < 0x1000;

    if (command.bufferAddress)
    {
        if (buffer)
        {
            context.ptrRead1 = command.bufferAddress;
            if (sizeUsable)
                context.sizeRead1 = command.bufferSize;
        }
        else
        {
            context.ptrRead0 = command.bufferAddress;
            if (sizeUsable)
                context.sizeRead0 = command.bufferSize;
        }
    }

    context.validBuffer = context.validBuffer | (1u << buffer);
}

void LoganHeap::UpdateXmaContext(ACP_COMMAND_UPDATE_XMA_CONTEXT const &command)
{
    auto *contexts = GetVirtualAddress<SHAPE_XMA_CONTEXT>(_acpContextArrays.xmaContextArray, _acpContextArrays.numXmaContexts);
    if (!contexts || command.contextIndex >= _acpContextArrays.numXmaContexts)
        return;

    SHAPE_XMA_CONTEXT &context = contexts[command.contextIndex];
    SHAPE_XMA_CONTEXT *UpdateData = GetVirtualAddress<SHAPE_XMA_CONTEXT>(command.contextData);

    if (command.updateMask & SHAPE_XMA_UPDATE_SIZE_READ0)
        context.sizeRead0 = UpdateData->sizeRead0;
    if (command.updateMask & SHAPE_XMA_UPDATE_SIZE_READ1)
        context.sizeRead1 = UpdateData->sizeRead1;
    if (command.updateMask & SHAPE_XMA_UPDATE_NUM_LOOPS)
        context.numLoops = UpdateData->numLoops;
    if (command.updateMask & SHAPE_XMA_UPDATE_VALID_BUFFER)
        context.validBuffer = UpdateData->validBuffer;
    if (command.updateMask & SHAPE_XMA_UPDATE_SIZE_WRITE)
        context.sizeWrite = UpdateData->sizeWrite;
    if (command.updateMask & SHAPE_XMA_UPDATE_LOOP_SUBFRAME_END)
        context.loopSubframeEnd = UpdateData->loopSubframeEnd;
    if (command.updateMask & SHAPE_XMA_UPDATE_LOOP_SUBFRAME_SKIP)
        context.loopSubframeSkip = UpdateData->loopSubframeSkip;
    if (command.updateMask & SHAPE_XMA_UPDATE_NUM_SUBFRAME_TO_DECODE)
        context.numSubframesToDecode = UpdateData->numSubframesToDecode;
    if (command.updateMask & SHAPE_XMA_UPDATE_NUM_SUBFRAMES_TO_SKIP)
        context.numSubframesToSkip = UpdateData->numSubframesToSkip;
    if (command.updateMask & SHAPE_XMA_UPDATE_SAMPLERATE)
        context.sampleRate = UpdateData->sampleRate;
    if (command.updateMask & SHAPE_XMA_UPDATE_NUM_CHANNELS)
        context.numChannels = UpdateData->numChannels;
    if (command.updateMask & SHAPE_XMA_UPDATE_VALID_WRITE)
        context.validWrite = UpdateData->validWrite;
    if (command.updateMask & SHAPE_XMA_UPDATE_OFFSET_READ)
        context.offsetRead = UpdateData->offsetRead;
    if (command.updateMask & SHAPE_XMA_UPDATE_LOOP_START_OFFSET)
        context.loopStartOffset = UpdateData->loopStartOffset;
    if (command.updateMask & SHAPE_XMA_UPDATE_LOOP_END_OFFSET)
        context.loopEndOffset = UpdateData->loopEndOffset;
    if (command.updateMask & SHAPE_XMA_UPDATE_PACKET_METADATA)
        context.packetMetaData = UpdateData->packetMetaData;
    if (command.updateMask & SHAPE_XMA_UPDATE_CURRENT_BUFFER)
        context.currentBuffer = UpdateData->currentBuffer;
    if (command.updateMask & SHAPE_XMA_UPDATE_PTR_READ0)
        context.ptrRead0 = UpdateData->ptrRead0;
    if (command.updateMask & SHAPE_XMA_UPDATE_PTR_READ1)
        context.ptrRead1 = UpdateData->ptrRead1;
    if (command.updateMask & SHAPE_XMA_UPDATE_PTR_WRITE)
        context.ptrWrite = UpdateData->ptrWrite;
    if (command.updateMask & SHAPE_XMA_UPDATE_PTR_OVERLAPADD)
        context.ptrOverlapAdd = UpdateData->ptrOverlapAdd;
    if (command.updateMask & SHAPE_XMA_UPDATE_WRITE_BUFFER_OFFSET_READ)
        context.writeBufferOffsetRead = UpdateData->writeBufferOffsetRead;

    printf("Updated Xma Context at index %u.\n", command.contextIndex);
}

UINT32 LoganHeap::ServiceXmaContext(UINT32 index, UINT32 channel, float *out, UINT32 count)
{
    auto *contexts = GetVirtualAddress<SHAPE_XMA_CONTEXT>(_acpContextArrays.xmaContextArray, _acpContextArrays.numXmaContexts);
    if (!contexts || index >= _acpContextArrays.numXmaContexts || index >= 512)
        return 0;

    SHAPE_XMA_CONTEXT &context = contexts[index];

    if (!_xmaVoices[index])
        _xmaVoices[index] = new XmaVoice();

    XmaVoice &voice = *_xmaVoices[index];

    UINT32 const current = context.currentBuffer;
    UINT32 const pointer = current ? context.ptrRead1 : context.ptrRead0;
    UINT32 const packets = current ? context.sizeRead1 : context.sizeRead0;
    bool const bufferValid = ((context.validBuffer >> current) & 1) != 0;

    if (bufferValid && pointer && packets)
    {
        auto *buffer = GetVirtualAddress<unsigned char>(pointer, static_cast<SIZE_T>(packets) * XmaVoice::c_PacketBytes);
        if (buffer)
        {
            UINT32 const limit = packets * XmaVoice::c_PacketBits;
            UINT32 const start = (context.offsetRead >= XmaVoice::c_HeaderBits && context.offsetRead < limit) ? context.offsetRead : XmaVoice::c_HeaderBits;

            voice.SetInput(buffer, packets, start, context.numChannels + 1, context.numSubframesToSkip * 128);
        }
    }

    UINT32 const taken = voice.Take(channel, out, count);
    UINT32 const newOffset = voice.BitOffset();

    if (voice.Exhausted() && bufferValid)
    {
        context.validBuffer &= ~(1u << current);
        context.currentBuffer = current ^ 1;
        context.offsetRead = XmaVoice::c_HeaderBits;

        voice.ReleaseInput();
    }
    else
    {
        context.offsetRead = newOffset;
    }

    return taken;
}

static inline int16_t ToPcm16(float v)
{
    v *= 32768.0f;
    if (v > 32767.0f)  v = 32767.0f;
    if (v < -32768.0f) v = -32768.0f;
    return static_cast<int16_t>(v);
}

void LoganHeap::ServiceXmaContextWithoutFlowgraph()
{
    auto *Contexts = GetVirtualAddress<SHAPE_XMA_CONTEXT>(_acpContextArrays.xmaContextArray, _acpContextArrays.numXmaContexts);
    if (!Contexts || _flowgraph)
        return;

    for (UINT i = 0; i < _acpContextArrays.numXmaContexts; ++i)
    {
        if (!_xmaVoices[i])
            _xmaVoices[i] = new XmaVoice();
        XmaVoice &voice = *_xmaVoices[i];

        SHAPE_XMA_CONTEXT &Context = Contexts[i];
        if (_disabledXmaContexts[i])
            continue;
        if (!Context.validWrite || !Context.ptrWrite || !Context.sizeWrite)
            continue;

        for (UINT Channel = 0; Channel < Context.numChannels; ++Channel)
        {
            UINT32 const used = (Context.offsetWrite + Context.sizeWrite - Context.writeBufferOffsetRead) % Context.sizeWrite;
            if ((Context.sizeWrite - used - 1) < Channel)
                continue;

            float PCMProduced[2][128]{};
            UINT32 const current = Context.currentBuffer;
            UINT32 const pointer = current ? Context.ptrRead1 : Context.ptrRead0;
            UINT32 const packets = current ? Context.sizeRead1 : Context.sizeRead0;
            bool const valid = ((Context.validBuffer >> current) & 1) != 0;

            if (valid && pointer && packets)
            {
                auto *buffer = GetVirtualAddress<unsigned char>(pointer, static_cast<SIZE_T>(packets) * XmaVoice::c_PacketBytes);
                if (buffer)
                {
                    UINT32 const limit = packets * XmaVoice::c_PacketBits;
                    UINT32 const start = (Context.offsetRead >= XmaVoice::c_HeaderBits && Context.offsetRead < limit) ? Context.offsetRead : XmaVoice::c_HeaderBits;
                    voice.SetInput(buffer, packets, start, Context.numChannels + 1, Context.numSubframesToSkip * 128);
                    UINT32 const got = voice.Take(0, PCMProduced[0], 128);
                    if (Context.numChannels > 1)
                        voice.Take(1, PCMProduced[1], 128);

                    if (voice.Exhausted() && valid)
                    {
                        Context.validBuffer &= ~(1u << current);
                        Context.currentBuffer = current ^ 1;
                        Context.offsetRead = XmaVoice::c_HeaderBits;
                        voice.ReleaseInput();
                    }
                    else
                        Context.offsetRead = voice.BitOffset();

                    if (!got)
                        break;

                    int16_t frame[128 * 2];
                    for (UINT32 s = 0; s < 128; ++s)
                        frame[s * Context.numChannels + Channel] = ToPcm16(PCMProduced[Channel][s]);

                    auto const *bytes = reinterpret_cast<uint8_t const *>(frame);
                    auto *dst = GetVirtualAddress<uint8_t>(Context.ptrWrite + Context.offsetWrite * 32, 32);
                    if (!dst)
                        return;
                    memcpy(dst, bytes + Channel * 32, 32);
                    Context.offsetWrite = (Context.offsetWrite + 1) % Context.sizeWrite;
                }
            }
        }
    }
}

BOOL LoganHeap::CheckForBlockedSampleRateConverterContexts(UINT *BlockedIndex)
{
    if (_acpContextArrays.srcContextArray)
    {
        SHAPE_SRC_CONTEXT *SrcContextArray = GetVirtualAddress<SHAPE_SRC_CONTEXT>(_acpContextArrays.srcContextArray, _acpContextArrays.numSrcContexts);
        for (UINT i = 0; i < _acpContextArrays.numSrcContexts; ++i)
        {
            if (!SrcContextArray[i].samplePointer)
            {
                (*BlockedIndex) = i;
                return TRUE;
            }
        }
    }

    return FALSE;
}

BOOL LoganHeap::CheckForBlockedDMAContexts(UINT *BlockedIndex)
{
    if (_acpContextArrays.dmaContextArray)
    {
        SHAPE_DMA_CONTEXT *DmaContextArray = GetVirtualAddress<SHAPE_DMA_CONTEXT>(_acpContextArrays.dmaContextArray, _acpContextArrays.numDmaContexts);
        for (UINT i = 0; i < _acpContextArrays.numDmaContexts; ++i)
        {
            if (!DmaContextArray[i].address)
            {
                (*BlockedIndex) = i;
                return TRUE;
            }
        }
    }

    return FALSE;
}

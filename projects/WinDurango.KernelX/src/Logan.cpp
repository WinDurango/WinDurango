#include "Logan.h"

PVOID LoganHeap::GetVirtualAddress(APU_ADDRESS ApuAddress, SIZE_T SizeInBytes)
{
    if (!ApuAddress)
        return nullptr;
    return (PVOID)((ULONG_PTR)_view + ApuAddress);
}

HRESULT LoganHeap::GetDriverMemory(UINT32 index, LOGAN_PHYSICAL_MEMORY *memory)
{
    *memory = _driverMemory[index];
    return S_OK;
}

template <typename T> T *LoganHeap::GetVirtualAddress(APU_ADDRESS ApuAddress, SIZE_T Count)
{
    if (Count != 1)
        Count = 1;
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

template <typename T> 
inline void DispatchACPCommand(ACP_COMMAND_TYPE_INTERNAL cmdType, AcpState *acpState, T Cmd)
{
    if (cmdType == INTERNAL_ACP_COMMAND_TYPE_CONNECT)
    {
        g_LoganHeap._acpConnectCommand[Cmd.connect.index] = Cmd.connect;
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
        else if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_ERROR)
        {
            printf("Enabled error message type.\n");
        }
        else if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_DISCONNECTED)
        {
            printf("Enabled disconnected message type.\n");
        }
        else
        {
            printf("Enabled message type 0x%x.\n", Cmd.registerMessage.message);
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
        else if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_ERROR)
        {
            printf("Disabled error message type.\n");
        }
        else if (Cmd.registerMessage.message & ACP_MESSAGE_TYPE_DISCONNECTED)
        {
            printf("Disabled disconnected message type.\n");
        }
        else
        {
            printf("Disabled message type 0x%x.\n", Cmd.registerMessage.message);
        }
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
        InitialCommand = reinterpret_cast<LOGAN_COMMAND_ACP_INIT*>(cmd);
    }
}
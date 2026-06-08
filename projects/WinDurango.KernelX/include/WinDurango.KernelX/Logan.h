#pragma once
#include "kernelx.h"
#include <Windows.h>
#include <thread>

// All of the types were provided by DaZombieKiller, a huge thanks to him!
#include <winioctl.h>

#define FILE_DEVICE_LOGAN 0x00008000
#define LOGAN_DEVICE_PATH "ACPI_HAL#Logan#0#{F764922A-DE30-40A5-A66E-C46CB191A1CD}"
#define LOGAN_DEVICE_WPATH L"ACPI_HAL#Logan#0#{F764922A-DE30-40A5-A66E-C46CB191A1CD}"

// {f764922a-de30-40a5-a66e-c46cb191a1cd}
DEFINE_GUID(GUID_DEVINTERFACE_LOGAN, 0xF764922A, 0xDE30, 0x40A5, 0xA6, 0x6E, 0xC4, 0x6C, 0xB1, 0x91, 0xA1, 0xCD);

//
// IOCTLs
//

#define IOCTL_LOGAN_BASE FILE_DEVICE_LOGAN
#define IOCTL_LOGAN_ALLOC_MAP CTL_CODE(FILE_DEVICE_LOGAN, 0x0801, METHOD_NEITHER, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_LOGAN_ATTACH_CHANNEL                                                                                     \
    CTL_CODE(FILE_DEVICE_LOGAN, 0x0802, METHOD_NEITHER, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_LOGAN_GET_MEMORY_STATISTICS                                                                              \
    CTL_CODE(FILE_DEVICE_LOGAN, 0x0803, METHOD_NEITHER, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_LOGAN_GET_NUI_BUFFER_STATE                                                                               \
    CTL_CODE(FILE_DEVICE_LOGAN, 0x0804, METHOD_NEITHER, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_LOGAN_SET_NUI_MEC_BUFFER_WRITE_OFFSET                                                                    \
    CTL_CODE(FILE_DEVICE_LOGAN, 0x0805, METHOD_NEITHER, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_LOGAN_LOAD_ACP_FIRMWARE                                                                                  \
    CTL_CODE(FILE_DEVICE_LOGAN, 0x0806, METHOD_NEITHER, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_LOGAN_SET_USB_CAPTURE_STATE                                                                              \
    CTL_CODE(FILE_DEVICE_LOGAN, 0x0807, METHOD_NEITHER, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_LOGAN_GET_DRIVER_MEMORY                                                                                  \
    CTL_CODE(FILE_DEVICE_LOGAN, 0x0808, METHOD_NEITHER, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

//
// Types
// Genuine names obtained from PDBs
//

// Represents a physical memory address on the APU.
typedef UINT32 APU_ADDRESS;

typedef enum LOGAN_CORE
{
    LOGAN_CORE_NONE = 0x00,  // (UNCONFIRMED)
    LOGAN_CORE_AVP = 0x01,   // Audio Vector Processor
    LOGAN_CORE_ASP = 0x02,   // Audio Scalar Processor
    LOGAN_CORE_ACP = 0x03,   // Audio Control Processor
    LOGAN_CORE_SHAPE = 0xFF, // Scalable Hardware Audio Processing Engine (UNCONFIRMED)
} LOGAN_CORE, *PLOGAN_CORE;

typedef struct LOGAN_COMMAND // HAL representation of a command
{
    UINT32 commandType;     // Type of the command (LOGAN_COMMAND_TYPE)
    APU_ADDRESS apuAddress; // Physical address of the command's data
} LOGAN_COMMAND, *PLOGAN_COMMAND;

typedef struct _LOGAN_COMMAND_INTERNAL // Device representation of a command
{
    UINT32 commandType;     // Type of the command (LOGAN_COMMAND_TYPE)
    APU_ADDRESS apuAddress; // Physical address of the command's data
    UINT32 reserved[62];
} LOGAN_COMMAND_INTERNAL, *PLOGAN_COMMAND_INTERNAL;

typedef struct _LOGAN_MESSAGE // HAL representation of a message
{
    UINT32 unknown;
    UINT32 status;
    UINT32 time; // Message creation time
} LOGAN_MESSAGE, *PLOGAN_MESSAGE;

typedef struct _LOGAN_MESSAGE_INTERNAL // Device representation of a message
{
    UINT32 unknown0; // If non-zero, causes LoganHAL::RetrieveMessage to return E_FAIL
    UINT32 unknown1;
    UINT32 status;
    UINT32 time; // Message creation time
    UINT32 reserved[60];
} LOGAN_MESSAGE_INTERNAL, *PLOGAN_MESSAGE_INTERNAL;

typedef struct LOGAN_RING_BUFFER_DESCRIPTOR
{
    UINT32 offsetRead; // Read offset in 256 byte blocks
    UINT32 reserved0[63];
    UINT32 offsetWrite;     // Write offset in 256 byte blocks
    APU_ADDRESS apuAddress; // Physical address of ring buffer
    UINT32 sizeInBlocks;    // Size of buffer in 256 byte blocks
    UINT32 reserved1[61];
} LOGAN_RING_BUFFER_DESCRIPTOR, *PLOGAN_RING_BUFFER_DESCRIPTOR;

typedef struct _LOGAN_PHYSICAL_MEMORY
{
    LPVOID address;         // Virtual address of memory
    APU_ADDRESS apuAddress; // Physical address of memory
    UINT32 sizeInBytes;     // Size of memory in bytes
} LOGAN_PHYSICAL_MEMORY, *PLOGAN_PHYSICAL_MEMORY;

typedef struct _LOGAN_MEMORY_STATS
{
    UINT32 unknown[54];
} LOGAN_MEMORY_STATS, *PLOGAN_MEMORY_STATS;

typedef struct _LOGAN_NUI_BUFFER_STATE
{
    UINT32 unknown[20];
} LOGAN_NUI_BUFFER_STATE, *PLOGAN_NUI_BUFFER_STATE;

typedef struct LOGAN_CONTEXT_ASP_SILK_ENC_ENCODE
{
    UINT32 unknown[6];
} LOGAN_CONTEXT_ASP_SILK_ENC_ENCODE, *PLOGAN_CONTEXT_ASP_SILK_ENC_ENCODE;

typedef struct LOGAN_CONTEXT_ASP_SILK_DEC_DECODE
{
    UINT32 unknown[6];
} LOGAN_CONTEXT_ASP_SILK_DEC_DECODE, *PLOGAN_CONTEXT_ASP_SILK_DEC_DECODE;

//
// Types
//

#define LOGAN_COMMAND_OFFSET_ASP 0xA0000000
#define LOGAN_COMMAND_OFFSET_ACP 0xD0000000

typedef enum LOGAN_COMMAND_TYPE
{
    // AcpHal
    LOGAN_COMMAND_TYPE_ACP_INIT = LOGAN_COMMAND_OFFSET_ACP + 0x0,

    // SILKHardwareInterfaceImpl::Initialize
    LOGAN_COMMAND_TYPE_ASP_0 = LOGAN_COMMAND_OFFSET_ASP + 0x0,
    LOGAN_COMMAND_TYPE_ASP_1 = LOGAN_COMMAND_OFFSET_ASP + 0x1,
    LOGAN_COMMAND_TYPE_ASP_5 = LOGAN_COMMAND_OFFSET_ASP + 0x5,
    LOGAN_COMMAND_TYPE_ASP_6 = LOGAN_COMMAND_OFFSET_ASP + 0x6,

    // SILKHardwareInterfaceImpl::xa_silk_dec_init
    LOGAN_COMMAND_TYPE_ASP_2 = LOGAN_COMMAND_OFFSET_ASP + 0x2,

    // SILKHardwareInterfaceImpl::xa_silk_dec
    LOGAN_COMMAND_TYPE_ASP_4 = LOGAN_COMMAND_OFFSET_ASP + 0x4,
    LOGAN_COMMAND_TYPE_ASP_D = LOGAN_COMMAND_OFFSET_ASP + 0xD,

    // SILKHardwareInterfaceImpl::xa_silk_enc_init
    LOGAN_COMMAND_TYPE_ASP_7 = LOGAN_COMMAND_OFFSET_ASP + 0x7,

    // SILKHardwareInterfaceImpl::xa_silk_enc
    LOGAN_COMMAND_TYPE_ASP_8 = LOGAN_COMMAND_OFFSET_ASP + 0x8,
} LOGAN_COMMAND_TYPE, *PLOGAN_COMMAND_TYPE;

typedef enum ACP_COMMAND_TYPE_INTERNAL
{
  INTERNAL_ACP_COMMAND_TYPE_CONNECT = -2147483648,
  INTERNAL_ACP_COMMAND_TYPE_DISCONNECT = -2147483647,
  INTERNAL_ACP_COMMAND_TYPE_REGISTER_CONTEXT_ARRAYS = -2147483646,
  INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_INIT = -2147483645,
  INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_ENABLE = -2147483644,
  INTERNAL_ACP_COMMAND_TYPE_EVENT_LOG_DISABLE = -2147483643,
  INTERNAL_ACP_COMMAND_TYPE_TERMINATE = -2147483642
} ACP_COMMAND_TYPE_INTERNAL, *PACP_COMMAND_TYPE_INTERNAL;

typedef enum ACP_COMMAND_TYPE
{
  ACP_COMMAND_TYPE_LOAD_SHAPE_FLOWGRAPH = 0x0001,
  ACP_COMMAND_TYPE_REGISTER_MESSAGE = 0x0002,
  ACP_COMMAND_TYPE_UNREGISTER_MESSAGE = 0x0003,
  ACP_COMMAND_TYPE_START_FLOWGRAPH = 0x0004,
  ACP_COMMAND_TYPE_ENABLE_XMA_CONTEXT = 0x0005,
  ACP_COMMAND_TYPE_ENABLE_XMA_CONTEXTS = 0x0006,
  ACP_COMMAND_TYPE_DISABLE_XMA_CONTEXT = 0x0007,
  ACP_COMMAND_TYPE_DISABLE_XMA_CONTEXTS = 0x0008,
  ACP_COMMAND_TYPE_UPDATE_SRC_CONTEXT = 0x0009,
  ACP_COMMAND_TYPE_UPDATE_EQCOMP_CONTEXT = 0x000a,
  ACP_COMMAND_TYPE_UPDATE_FILTVOL_CONTEXT = 0x000b,
  ACP_COMMAND_TYPE_UPDATE_DMA_CONTEXT = 0x000c,
  ACP_COMMAND_TYPE_UPDATE_PCM_CONTEXT = 0x000d,
  ACP_COMMAND_TYPE_UPDATE_XMA_CONTEXT = 0x000e,
  ACP_COMMAND_TYPE_INCREMENT_DMA_WRITE_POINTER = 0x000f,
  ACP_COMMAND_TYPE_INCREMENT_DMA_READ_POINTER = 0x0010,
  ACP_COMMAND_TYPE_INCREMENT_PCM_WRITE_POINTER = 0x0011,
  ACP_COMMAND_TYPE_INCREMENT_XMA_WRITE_BUFFER_OFFSET_READ = 0x0012,
  ACP_COMMAND_TYPE_UPDATE_XMA_READ_BUFFER = 0x0013,
  ACP_COMMAND_TYPE_UPDATE_ALL_CONTEXTS = 0x0014,
  ACP_COMMAND_TYPE_UPDATE_SRC_CONTEXTS = 0x0015,
  ACP_COMMAND_TYPE_UPDATE_EQCOMP_CONTEXTS = 0x0016,
  ACP_COMMAND_TYPE_UPDATE_FILTVOL_CONTEXTS = 0x0017,
  ACP_COMMAND_TYPE_UPDATE_DMA_READ_CONTEXTS = 0x0018,
  ACP_COMMAND_TYPE_UPDATE_DMA_WRITE_CONTEXTS = 0x0019,
  ACP_COMMAND_TYPE_UPDATE_PCM_CONTEXTS = 0x001a,
  ACP_COMMAND_TYPE_UPDATE_XMA_CONTEXTS = 0x001b,
  ACP_COMMAND_TYPE_COUNT = 0x001b
} ACP_COMMAND_TYPE, *PACP_COMMAND_TYPE;

typedef struct ACP_COMMAND_CONNECT
{
    UINT32 instance;
    UINT32 index;
    UINT32 numCommands;
    UINT32 numMessages;
    APU_ADDRESS commandQueue;
    APU_ADDRESS pendingCommandList;
    APU_ADDRESS messageQueue;
};

typedef enum ACP_MESSAGE_TYPE
{
  ACP_MESSAGE_TYPE_AUDIO_FRAME_START = 0x0001,
  ACP_MESSAGE_TYPE_FLOWGRAPH_COMPLETED = 0x0002,
  ACP_MESSAGE_TYPE_SRC_BLOCKED = 0x0004,
  ACP_MESSAGE_TYPE_DMA_BLOCKED = 0x0008,
  ACP_MESSAGE_TYPE_COMMAND_COMPLETED = 0x0010,
  ACP_MESSAGE_TYPE_FLOWGRAPH_TERMINATED = 0x0020,
  ACP_MESSAGE_TYPE_ERROR = 0x0040,
  ACP_MESSAGE_TYPE_DISCONNECTED = 0x0080,
  ACP_MESSAGE_TYPE_MASK = 0x00ff
} ACP_MESSAGE_TYPE, *PACP_MESSAGE_TYPE;

typedef struct ACP_COMMAND_DISCONNECT
{
    UINT32 instance;
};

typedef struct ACP_COMMAND_INIT_EVENT_LOG
{
    UINT32 buffer;
    UINT32 bufferSize;
};

typedef struct ACP_COMMAND_REGISTER_CONTEXT_ARRAYS
{
    UINT32 numSrcContexts;
    UINT32 numEqCompContexts;
    UINT32 numFiltVolContexts;
    UINT32 numDmaContexts;
    UINT32 numXmaContexts;
    UINT32 numPcmContexts;
    APU_ADDRESS srcContextArray;
    APU_ADDRESS eqCompContextArray;
    APU_ADDRESS filtVolContextArray;
    APU_ADDRESS dmaContextArray;
    APU_ADDRESS xmaContextArray;
    APU_ADDRESS pcmContextArray;
};


//There can be 4 IAcpHal instances, which means 4 main command and message queues, hence client pointers/counters are arrays of 4.
typedef struct AcpState
{
    uint32_t internalCommandQueueReadPointer;
    uint32_t internalCommandQueueSendCounter;
    uint32_t internalCommandQueueReadCounter;
    uint32_t clientCommandQueueReadPointer[4];
    uint32_t clientCommandQueueSendCounter[4];
    uint32_t clientCommandQueueReadCounter[4];
    uint32_t clientMessageQueueWritePointer[4];
};

typedef struct _LOGAN_COMMAND_ACP_INIT
{
    UINT32 unknown0;             // Always '1'
    APU_ADDRESS acpCommandQueue; // Physical address of the ACP internal command queue
    APU_ADDRESS acpState;        // Store the command queue read/write addresses
    UINT32 unknown2[2];
} LOGAN_COMMAND_ACP_INIT, *PLOGAN_COMMAND_ACP_INIT;

typedef enum _LOGAN_ALLOC_MAP_FLAGS
{
    LOGAN_ALLOC_MAP_FLAG_NONE = 0,
    LOGAN_ALLOC_MAP_FLAG_NOCACHE = 1 << 0, // Allocated memory will not be cached
} LOGAN_ALLOC_MAP_FLAGS, *PLOGAN_ALLOC_MAP_FLAGS;

typedef struct _LOGAN_IOCTL_IN_ALLOC_MAP
{
    UINT32 sizeInBytes; // Number of bytes to allocate (aligned to 4K)
    UINT32 flags;       // Bitmask of LOGAN_ALLOC_MAP_FLAGS values
    LPVOID address;     // Virtual address to map APU memory into
    LPVOID reserved[2];
} LOGAN_IOCTL_IN_ALLOC_MAP, *PLOGAN_IOCTL_IN_ALLOC_MAP;

typedef struct _LOGAN_IOCTL_OUT_ALLOC_MAP
{
    UINT32 allocated; // Number of bytes that were allocated
    UINT32 reserved0;
    LPVOID address;         // Virtual address that was mapped
    APU_ADDRESS apuAddress; // Physical address of the mapped memory
    UINT32 reserved1[3];
} LOGAN_IOCTL_OUT_ALLOC_MAP, *PLOGAN_IOCTL_OUT_ALLOC_MAP;

typedef struct _LOGAN_TRACE_MESSAGE
{
    UINT32 length;
    CHAR buffer[252];
} LOGAN_TRACE_MESSAGE, *PLOGAN_TRACE_MESSAGE;

typedef struct _LOGAN_CHANNEL
{
    LOGAN_RING_BUFFER_DESCRIPTOR commands; // Command ring buffer
    LOGAN_RING_BUFFER_DESCRIPTOR messages; // Message ring buffer
    LOGAN_TRACE_MESSAGE trace;             // Trace message buffer (debug)
} LOGAN_CHANNEL, *PLOGAN_CHANNEL;

typedef struct _LOGAN_IOCTL_IN_ATTACH_CHANNEL
{
    LOGAN_CORE core;
    APU_ADDRESS apuAddress; // Physical address of a LOGAN_CHANNEL structure
} LOGAN_IOCTL_IN_ATTACH_CHANNEL, *PLOGAN_IOCTL_IN_ATTACH_CHANNEL;

typedef struct _LOGAN_IOCTL_IN_LOAD_ACP_FIRMWARE
{
    UINT32 reserved[3];
} LOGAN_IOCTL_IN_LOAD_ACP_FIRMWARE, *PLOGAN_IOCTL_IN_LOAD_ACP_FIRMWARE;

typedef struct _LOGAN_IOCTL_IN_GET_DRIVER_MEMORY
{
    UINT32 type; // [0,3) (LoganHAL::GetXMA uses '1')
    UINT32 reserved0[2];
    UINT32 unknown0; // '1' when 'type' is not '2'
    UINT32 unknown1; // '1' when 'type' is '2'
    LOGAN_CORE core;
    UINT32 reserved1;
} LOGAN_IOCTL_IN_GET_DRIVER_MEMORY, *PLOGAN_IOCTL_IN_GET_DRIVER_MEMORY;

typedef struct _LOGAN_IOCTL_OUT_GET_DRIVER_MEMORY
{
    LPVOID address;         // Virtual address of the memory
    UINT32 sizeInBytes;     // Size of the memory in bytes
    APU_ADDRESS apuAddress; // Physical address of the memory
    UINT32 reserved[2];
} LOGAN_IOCTL_OUT_GET_DRIVER_MEMORY, *PLOGAN_IOCTL_OUT_GET_DRIVER_MEMORY;

typedef struct ACP_COMMAND_INCREMENT_PCM_WRITE_POINTER
{
    uint32_t contextIndex;
    uint32_t increment;
};

typedef struct ACP_COMMAND_ENABLE_OR_DISABLE_XMA_CONTEXTS
{
    uint32_t context[16];
};

typedef struct ACP_COMMAND_INCREMENT_DMA_POINTER
{
    uint32_t contextIndex;
    uint32_t increment;
};

typedef struct ACP_COMMAND_UPDATE_CONTEXTS
{
    uint32_t entryCount;
    uint32_t entries;
    uint32_t indexCount;
    uint32_t indices;
};

typedef struct ACP_COMMAND_INCREMENT_XMA_WRITE_BUFFER_OFFSET_READ
{
    uint32_t contextIndex;
    uint32_t increment;
};

typedef struct ACP_COMMAND_UPDATE_SRC_CONTEXT
{
    uint32_t contextIndex;
    uint32_t updateMask;
    uint32_t contextData;
};

typedef struct ACP_COMMAND_ENABLE_OR_DISABLE_XMA_CONTEXT
{
    uint32_t contextIndex;
};

typedef struct ACP_COMMAND_UPDATE_PCM_CONTEXT
{
    uint32_t contextIndex;
    uint32_t updateMask;
    uint32_t contextData;
};

typedef struct ACP_COMMAND_UPDATE_XMA_CONTEXT
{
    uint32_t contextIndex;
    uint32_t updateMask;
    uint32_t contextData;
};

typedef struct ACP_COMMAND_UPDATE_ALL_CONTEXTS
{
    uint32_t srcEntryCount;
    uint32_t eqCompEntryCount;
    uint32_t filtVolEntryCount;
    uint32_t dmaReadEntryCount;
    uint32_t dmaWriteEntryCount;
    uint32_t pcmEntryCount;
    uint32_t xmaEntryCount;
    uint32_t srcEntries;
    uint32_t eqCompEntries;
    uint32_t filtVolEntries;
    uint32_t dmaReadEntries;
    uint32_t dmaWriteEntries;
    uint32_t pcmEntries;
    uint32_t xmaEntries;
    uint32_t srcIndexCount;
    uint32_t eqCompIndexCount;
    uint32_t filtVolIndexCount;
    uint32_t dmaReadIndexCount;
    uint32_t dmaWriteIndexCount;
    uint32_t pcmIndexCount;
    uint32_t xmaIndexCount;
    uint32_t srcIndices;
    uint32_t eqCompIndices;
    uint32_t filtVolIndices;
    uint32_t dmaReadIndices;
    uint32_t dmaWriteIndices;
    uint32_t pcmIndices;
    uint32_t xmaIndices;
};

typedef struct ACP_COMMAND_MESSAGE
{
    uint32_t message;
};

typedef struct ACP_COMMAND_UPDATE_FILTVOL_CONTEXT
{
    uint32_t contextIndex;
    uint32_t updateMask;
    uint32_t contextData;
};

typedef struct ACP_COMMAND_UPDATE_DMA_CONTEXT
{
    uint32_t contextIndex;
    uint32_t updateMask;
    uint32_t contextData;
};

typedef struct ACP_COMMAND_UPDATE_EQCOMP_CONTEXT
{
    uint32_t contextIndex;
    uint32_t updateMask;
    uint32_t contextData;
};

typedef struct ACP_COMMAND_UPDATE_XMA_READ_BUFFER
{
    uint32_t contextIndex;
    uint32_t bufferIndex;
    uint32_t bufferSize;
    uint32_t changeSize;
    uint32_t changeAddress;
    uint32_t bufferAddress;
};

typedef struct ACP_COMMAND_LOAD_SHAPE_FLOWGRAPH
{
    uint32_t numCommands;
    uint32_t flowgraph;
    uint32_t persist;
    uint32_t waitForStart;
};

typedef struct AcpCommand
{
    uint32_t frame;
    uint64_t commandId;
    uint32_t commandType;
    uint32_t notification;
  union
  {
    ACP_COMMAND_LOAD_SHAPE_FLOWGRAPH loadFlowgraph;
    ACP_COMMAND_MESSAGE registerMessage;
    ACP_COMMAND_ENABLE_OR_DISABLE_XMA_CONTEXT enableOrDisableXmaContext;
    ACP_COMMAND_UPDATE_SRC_CONTEXT updateSrcContext;
    ACP_COMMAND_UPDATE_XMA_CONTEXT updateXmaContext;
    ACP_COMMAND_UPDATE_PCM_CONTEXT updatePcmContext;
    ACP_COMMAND_UPDATE_EQCOMP_CONTEXT updateEqCompContext;
    ACP_COMMAND_UPDATE_FILTVOL_CONTEXT updateFiltVolContext;
    ACP_COMMAND_UPDATE_DMA_CONTEXT updateDmaContext;
    ACP_COMMAND_ENABLE_OR_DISABLE_XMA_CONTEXTS enableOrDisableXmaContexts;
    ACP_COMMAND_INCREMENT_DMA_POINTER incrementDmaPointer;
    ACP_COMMAND_INCREMENT_PCM_WRITE_POINTER incrementPcmWritePointer;
    ACP_COMMAND_INCREMENT_XMA_WRITE_BUFFER_OFFSET_READ incrementXmaWriteBufferOffsetRead;
    ACP_COMMAND_UPDATE_XMA_READ_BUFFER updateXmaReadBuffer;
    ACP_COMMAND_UPDATE_ALL_CONTEXTS updateAllContexts;
    ACP_COMMAND_UPDATE_CONTEXTS updateContexts;
    ACP_COMMAND_CONNECT connect;
    ACP_COMMAND_DISCONNECT disconnect;
    ACP_COMMAND_REGISTER_CONTEXT_ARRAYS registerContextArrays;
    ACP_COMMAND_INIT_EVENT_LOG eventLog;
  };
};

typedef struct AcpCommandQueueEntry
{ 
    uint32_t state;
    AcpCommand command;
    uint8_t padToAcpCacheLineSize[120];
};

typedef union AcpInternalCommandQueueEntry
{ 
    uint32_t state;
    AcpCommand command;
    uint8_t padToAcpCacheLineSize[256];
};

typedef struct ACP_MESSAGE_FLOWGRAPH_COMPLETED
{
    uint32_t flowgraph;
};

typedef struct ACP_MESSAGE_SHAPE_COMMAND_BLOCKED
{
    uint32_t contextIndex;
    uint32_t flowgraph;
};

typedef struct ACP_MESSAGE_COMMAND_COMPLETED
{
    uint32_t commandType;
    uint64_t commandId;
    uint32_t audioFrame;
};

typedef struct ACP_MESSAGE_ERROR
{
    int32_t errorCode;
    uint32_t additionalData;
};

typedef struct ACP_MESSAGE_FLOWGRAPH_TERMINATED
{
    uint32_t flowgraph;
    uint32_t numCommandsCompleted;
    uint32_t reason;
};

typedef struct ACP_MESSAGE_AUDIO_FRAME_START
{
    uint32_t audioFrame;
};

typedef struct ACP_MESSAGE
{
    uint32_t type;
    uint32_t droppedMessageCount;
    union
    {
        ACP_MESSAGE_AUDIO_FRAME_START audioFrameStart;
        ACP_MESSAGE_FLOWGRAPH_COMPLETED flowgraphCompleted;
        ACP_MESSAGE_SHAPE_COMMAND_BLOCKED shapeCommandBlocked;
        ACP_MESSAGE_COMMAND_COMPLETED commandCompleted;
        ACP_MESSAGE_FLOWGRAPH_TERMINATED flowgraphTerminated;
        ACP_MESSAGE_ERROR error;
    };
};

typedef struct AcpMessageQueueEntry
{
    uint32_t state;
    ACP_MESSAGE message;
    uint8_t padToAcpCacheLineSize[228];
};

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

LPVOID Map(_In_ UINT NumPages, _In_ LPVOID Address, _In_ DWORD ApuAddress, _In_ UINT PageSize)
{
    for (UINT i = 0; i < NumPages; i++)
    {
        LPVOID pageAddress = (LPVOID)((ULONG_PTR)Address + PageSize * i);
        UnmapViewOfFileEx(pageAddress, MEM_PRESERVE_PLACEHOLDER);
        MapViewOfFile3(hLoganMap, nullptr, pageAddress, ApuAddress + PageSize * i, PageSize, MEM_REPLACE_PLACEHOLDER, PAGE_READWRITE, nullptr, 0);
        VirtualAlloc2(nullptr, pageAddress, PageSize, MEM_COMMIT, PAGE_READWRITE, nullptr, 0);
    }

    return Address;
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
    ACP_COMMAND_CONNECT _acpConnectCommand[4]; //There can be 4 IAcpHal instances :)
};

template <typename T> void _declspec(dllexport) DispatchLoganCommand(LOGAN_COMMAND_TYPE cmdType, T cmd);

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

LoganHeap g_LoganHeap;

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
        printf("Received Client ACP command (ACP_COMMAND_TYPE_REGISTER_MESSAGE)\n");
    }
    else if (cmdType == ACP_COMMAND_TYPE_UNREGISTER_MESSAGE)
    {
        printf("Received Client ACP command (ACP_COMMAND_TYPE_UNREGISTER_MESSAGE)\n");
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

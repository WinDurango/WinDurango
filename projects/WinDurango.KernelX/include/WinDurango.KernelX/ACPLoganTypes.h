#pragma once
#include "kernelx.h"
#include <Windows.h>
#include <thread>

struct abi_t
{
    uint32_t Major = 0;
    uint32_t Minor = 0;
    uint32_t Build = 0;
    uint32_t Revision = 0;
    auto operator<=>(abi_t const &other) const noexcept = default;
    bool operator==(abi_t const &other) const noexcept = default;
};

abi_t g_ABI;

void GetCombaseVersion()
{
    DWORD FileVersionSize = GetFileVersionInfoSizeW(L".\\EmbeddedXvd\\Windows\\System32\\combase.dll", NULL);
    if (!FileVersionSize)
    {
        MessageBoxW(nullptr,
                    L"Couldn't get the combase version info size! Make sure you have EmbeddedXvd in the game root/Mount folder.",
                    L"Logan Error!", MB_ICONERROR);
    }

    BYTE *Data = new BYTE[FileVersionSize];
    BOOL ret = GetFileVersionInfoW(L".\\EmbeddedXvd\\Windows\\System32\\combase.dll", NULL, FileVersionSize, Data);
    if (!ret)
    {
        MessageBoxW(
            nullptr,
            L"Couldn't get the combase version info! Make sure you have EmbeddedXvd in the game root/Mount folder.",
            L"Logan Error!", MB_ICONERROR);
        delete[] Data;
    }

    VS_FIXEDFILEINFO *pFixedFileInfo{};
    UINT Length = 0;

    VerQueryValueW(Data, L"\\", (LPVOID *)&pFixedFileInfo, &Length);
    if (!pFixedFileInfo)
    {
        MessageBoxW(
            nullptr,
            L"Couldn't get the combase version value! Make sure you have EmbeddedXvd in the game root/Mount folder.",
            L"Logan Error!", MB_ICONERROR);
        delete[] Data;
    }

    DWORD major = HIWORD(pFixedFileInfo->dwProductVersionMS);
    DWORD minor = LOWORD(pFixedFileInfo->dwProductVersionMS);
    DWORD build = HIWORD(pFixedFileInfo->dwProductVersionLS);
    DWORD revision = LOWORD(pFixedFileInfo->dwProductVersionLS);

    g_ABI.Major = major;
    g_ABI.Minor = minor;
    g_ABI.Build = build;
    g_ABI.Revision = revision;
}

// All of the types were provided by DaZombieKiller, a huge thanks to him!
#include <winioctl.h>

#define FILE_DEVICE_LOGAN 0x00008000
#define LOGAN_DEVICE_PATH "ACPI_HAL#Logan#0#{F764922A-DE30-40A5-A66E-C46CB191A1CD}"
#define LOGAN_DEVICE_WPATH L"ACPI_HAL#Logan#0#{F764922A-DE30-40A5-A66E-C46CB191A1CD}"

// {f764922a-de30-40a5-a66e-c46cb191a1cd}
DEFINE_GUID(GUID_DEVINTERFACE_LOGAN, 0xF764922A, 0xDE30, 0x40A5, 0xA6, 0x6E, 0xC4, 0x6C, 0xB1, 0x91, 0xA1, 0xCD);

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

// Represents a physical memory address on the APU.
typedef UINT32 APU_ADDRESS;

//Logan
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

typedef struct _LOGAN_COMMAND_ACP_INIT
{
    UINT32 unknown0;             // Always '1'
    APU_ADDRESS acpCommandQueue; // Physical address of the ACP internal command queue
    APU_ADDRESS acpState;        // Store the command queue read/write addresses
    UINT32 unknown2[2];
} LOGAN_COMMAND_ACP_INIT, *PLOGAN_COMMAND_ACP_INIT;

typedef struct _LOGAN_COMMAND_ACP_INIT_OLD
{
    UINT32 unknown0;             // Always '1'
    APU_ADDRESS acpCommandQueue; // Physical address of the ACP internal command queue
    APU_ADDRESS acpState;        // Store the command queue read/write addresses
    APU_ADDRESS cpuState;        // Store the command queue read/write addresses
    UINT32 unknown2[2];
} LOGAN_COMMAND_ACP_INIT_OLD, *PLOGAN_COMMAND_ACP_INIT_OLD;

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


//ACP
#pragma pack(push)
#pragma pack(1)
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

typedef struct ACP_COMMAND_CONNECT_OLD
{
    UINT32 instance;
    UINT32 numCommands;
    UINT32 numMessages;
    APU_ADDRESS commandQueue;
    APU_ADDRESS pendingCommandList;
    APU_ADDRESS messageQueue;
};

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

typedef struct AcpState_Old
{
    uint32_t internalCommandQueueReadPointer;
    uint32_t clientCommandQueueReadPointer[4];
    uint32_t clientMessageQueueWritePointer[4];
};

typedef struct CpuState
{
    uint32_t internalCommandQueueWritePointer;
    uint32_t clientCommandQueueWritePointer[4];
    uint32_t clientMessageQueueReadPointer[4];
};

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

typedef struct AcpCommand_Old
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
        ACP_COMMAND_CONNECT_OLD connect;
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

typedef struct AcpCommandQueueEntry_Old
{ 
    uint32_t state;
    AcpCommand_Old command;
    uint8_t padToAcpCacheLineSize[120];
};

typedef struct AcpInternalCommandQueueEntry
{ 
    uint32_t state;
    AcpCommand command;
    uint8_t padToAcpCacheLineSize[120];
};

typedef struct AcpInternalCommandQueueEntry_Old
{ 
    uint32_t state;
    AcpCommand_Old command;
    uint8_t padToAcpCacheLineSize[120];
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
    uint32_t usec;
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

typedef struct ACP_MESSAGE_OLD
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

typedef struct AcpMessageQueueEntry_Old
{
    uint32_t state;
    ACP_MESSAGE_OLD message;
    uint8_t padToAcpCacheLineSize[228];
};

typedef struct ACP_COMMAND_UPDATE_XMA_CONTEXT_ENTRY
{
    uint32_t contextIndex;
    uint32_t ptrRead0;
    uint32_t ptrRead1;
    uint16_t sizeRead0;
    uint16_t sizeRead1;
    uint16_t writeBufferOffsetRead;
    uint16_t validBuffer;
};

typedef struct SHAPE_XMA_CONTEXT
{
    uint32_t sizeRead0 : 12;
    uint32_t numLoops : 8;
    uint32_t validBuffer : 2;
    uint32_t sizeWrite : 5;
    uint32_t offsetWrite : 5;
    uint32_t : 0;
    uint32_t sizeRead1 : 12;
    uint32_t loopSubframeEnd : 2;
    uint32_t : 3;
    uint32_t loopSubframeSkip : 3;
    uint32_t numSubframesToDecode : 4;
    uint32_t numSubframesToSkip : 3;
    uint32_t sampleRate : 2;
    uint32_t numChannels : 1;
    uint32_t : 1;
    uint32_t validWrite : 1;
    uint32_t : 0;
    uint32_t offsetRead : 26;
    uint32_t errorStatus : 5;
    uint32_t errorSet : 1;
    uint32_t : 0;
    uint32_t loopStartOffset : 26;
    uint32_t parserErrorStatus : 5;
    uint32_t parserErrorSet : 1;
    uint32_t : 0;
    uint32_t loopEndOffset : 26;
    uint32_t packetMetaData : 5;
    uint32_t currentBuffer : 1;
    uint32_t ptrRead0;
    uint32_t ptrRead1;
    uint32_t ptrWrite;
    uint32_t ptrOverlapAdd;
    uint32_t writeBufferOffsetRead : 5;
    uint32_t : 25;
    uint32_t stopWhenDone : 1;
    uint32_t interruptWhenDone : 1;
    uint32_t reserved[6];
};

typedef enum SHAPE_XMA_SAMPLE_RATE
{
  SHAPE_XMA_SAMPLE_RATE_24K = 0x0000,
  SHAPE_XMA_SAMPLE_RATE_32K = 0x0001,
  SHAPE_XMA_SAMPLE_RATE_44_1K = 0x0002,
  SHAPE_XMA_SAMPLE_RATE_48K = 0x0003,
};

#pragma pack(pop)
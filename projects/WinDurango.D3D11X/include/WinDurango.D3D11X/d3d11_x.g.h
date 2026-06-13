#pragma once
#ifndef __d3d11_x_g_h__
#define __d3d11_x_g_h__

#include "xcom/base.h"

#include "unknown.g.h"
#include <d3d11_4.h>
#include <dxgi1_6.h>

namespace gfx
{
    struct D3D11XTinyDevice;
    
    template<abi_t ABI>
    struct D3D11XShaderUserDataManagerDraw;
    
    struct D3D11X_DESCRIPTOR_RESOURCE;
    
    template<abi_t ABI>
    struct ID3D11DeviceChild;
    
    template<abi_t ABI>
    struct ID3D11DeviceChildVtbl;
    
    template<abi_t ABI>
    struct ID3D11Resource;
    
    template<abi_t ABI>
    struct ID3D11ResourceVtbl;
    
    template<abi_t ABI>
    struct ID3D11Texture1D;
    
    template<abi_t ABI>
    struct ID3D11Texture1DVtbl;
    
    template<abi_t ABI>
    struct ID3D11Texture2D;
    
    template<abi_t ABI>
    struct ID3D11Texture2DVtbl;
    
    template<abi_t ABI>
    struct ID3D11Texture3D;
    
    template<abi_t ABI>
    struct ID3D11Texture3DVtbl;
    
    template<abi_t ABI>
    struct ID3D11Buffer;
    
    template<abi_t ABI>
    struct ID3D11BufferVtbl;
    
    template<abi_t ABI>
    struct ID3D11VertexShader;
    
    template<abi_t ABI>
    struct ID3D11VertexShaderVtbl;
    
    template<abi_t ABI>
    struct ID3D11PixelShader;
    
    template<abi_t ABI>
    struct ID3D11PixelShaderVtbl;
    
    template<abi_t ABI>
    struct ID3D11ComputeShader;
    
    template<abi_t ABI>
    struct ID3D11ComputeShaderVtbl;
    
    template<abi_t ABI>
    struct ID3D11GeometryShader;
    
    template<abi_t ABI>
    struct ID3D11GeometryShaderVtbl;
    
    template<abi_t ABI>
    struct ID3D11HullShader;
    
    template<abi_t ABI>
    struct ID3D11HullShaderVtbl;
    
    template<abi_t ABI>
    struct ID3D11DomainShader;
    
    template<abi_t ABI>
    struct ID3D11DomainShaderVtbl;
    
    struct D3D11X_DESCRIPTOR_SAMPLER_STATE;
    
    template<abi_t ABI>
    struct ID3D11SamplerState;
    
    template<abi_t ABI>
    struct ID3D11SamplerStateVtbl;
    
    template<abi_t ABI>
    struct ID3D11RasterizerState;
    
    template<abi_t ABI>
    struct ID3D11RasterizerStateVtbl;
    
    template<abi_t ABI>
    struct ID3D11BlendState;
    
    template<abi_t ABI>
    struct ID3D11BlendStateVtbl;
    
    template<abi_t ABI>
    struct ID3D11DepthStencilState;
    
    template<abi_t ABI>
    struct ID3D11DepthStencilStateVtbl;
    
    struct D3D11X_DESCRIPTOR_TEXTURE_VIEW;
    
    template<abi_t ABI>
    struct ID3D11View;
    
    template<abi_t ABI>
    struct ID3D11ViewVtbl;
    
    template<abi_t ABI>
    struct ID3D11ShaderResourceView;
    
    template<abi_t ABI>
    struct ID3D11ShaderResourceViewVtbl;
    
    template<abi_t ABI>
    struct ID3D11RenderTargetView;
    
    template<abi_t ABI>
    struct ID3D11RenderTargetViewVtbl;
    
    template<abi_t ABI>
    struct ID3D11DepthStencilView;
    
    template<abi_t ABI>
    struct ID3D11DepthStencilViewVtbl;
    
    template<abi_t ABI>
    struct ID3D11UnorderedAccessView;
    
    template<abi_t ABI>
    struct ID3D11UnorderedAccessViewVtbl;
    
    template<abi_t ABI>
    struct ID3D11DeviceContext;
    
    template<abi_t ABI>
    struct ID3D11DeviceContextVtbl;
    
    template<abi_t ABI>
    struct ID3D11DeviceContext1;
    
    template<abi_t ABI>
    struct ID3D11DeviceContext1Vtbl;
    
    template<abi_t ABI>
    struct ID3D11DeviceContext2;
    
    template<abi_t ABI>
    struct ID3D11DeviceContext2Vtbl;
    
    template<abi_t ABI>
    struct ID3D11DeviceContextX;
    
    template<abi_t ABI>
    struct ID3D11DeviceContextXVtbl;
    
    template<abi_t ABI>
    struct ID3D11PerformanceContextX;
    
    template<abi_t ABI>
    struct ID3D11PerformanceContextXVtbl;

    template <abi_t ABI>
    struct ID3D11UserDefinedAnnotationX;

    template <abi_t ABI>
    struct ID3D11UserDefinedAnnotationXVtbl;
    
    template<abi_t ABI>
    struct ID3D11Device;
    
    template<abi_t ABI>
    struct ID3D11DeviceVtbl;
    
    template<abi_t ABI>
    struct ID3D11Device1;
    
    template<abi_t ABI>
    struct ID3D11Device1Vtbl;
    
    template<abi_t ABI>
    struct ID3D11Device2;
    
    template<abi_t ABI>
    struct ID3D11Device2Vtbl;
    
    template<abi_t ABI>
    struct ID3D11DMAEngineContextX;
    
    template<abi_t ABI>
    struct ID3D11DMAEngineContextXVtbl;
    
    template<abi_t ABI>
    struct ID3D11DeviceX;
    
    template<abi_t ABI>
    struct ID3D11DeviceXVtbl;
    
    template<abi_t ABI>
    struct ID3D11PerformanceDeviceX;
    
    template<abi_t ABI>
    struct ID3D11PerformanceDeviceXVtbl;

    template <abi_t ABI>
    struct IDXGIObject;

    template <abi_t ABI>
    struct IDXGIObjectVtbl;

    template <abi_t ABI>
    struct IDXGIDevice;

    template <abi_t ABI>
    struct IDXGIDeviceVtbl;

    template <abi_t ABI>
    struct IDXGIDevice1;

    template <abi_t ABI>
    struct IDXGIDevice1Vtbl;

    template <abi_t ABI>
    struct IDXGIDevice2;

    template <abi_t ABI>
    struct IDXGIDevice2Vtbl;

    template <abi_t ABI>
    struct IDXGIAdapter;

    template <abi_t ABI>
    struct IDXGIAdapterVtbl;

    template <abi_t ABI>
    struct IDXGIAdapter1;

    template <abi_t ABI>
    struct IDXGIAdapter1Vtbl;

    template <abi_t ABI>
    struct IDXGIDeviceSubObject;

    template <abi_t ABI>
    struct IDXGIDeviceSubObjectVtbl;

    template <abi_t ABI>
    struct IDXGISwapChain;

    template <abi_t ABI>
    struct IDXGISwapChainVtbl;

    template <abi_t ABI>
    struct IDXGISwapChain1;

    template <abi_t ABI>
    struct IDXGISwapChain1Vtbl;

    template <abi_t ABI>
    struct IDXGIFactory;

    template <abi_t ABI>
    struct IDXGIFactoryVtbl;

    template <abi_t ABI>
    struct IDXGIFactory1;

    template <abi_t ABI>
    struct IDXGIFactory1Vtbl;

    template <abi_t ABI>
    struct IDXGIFactory2;

    template <abi_t ABI>
    struct IDXGIFactory2Vtbl;
    
enum D3D11X_IMG_NUM_FORMAT
    {
        D3D11X_IMG_NUM_FORMAT_INVALID = 0x00ff,
        D3D11X_IMG_NUM_FORMAT_UNORM = 0x0000,
        D3D11X_IMG_NUM_FORMAT_SNORM = 0x0001,
        D3D11X_IMG_NUM_FORMAT_USCALED = 0x0002,
        D3D11X_IMG_NUM_FORMAT_SSCALED = 0x0003,
        D3D11X_IMG_NUM_FORMAT_UINT = 0x0004,
        D3D11X_IMG_NUM_FORMAT_SINT = 0x0005,
        D3D11X_IMG_NUM_FORMAT_SNORM_OGL = 0x0006,
        D3D11X_IMG_NUM_FORMAT_FLOAT = 0x0007,
        D3D11X_IMG_NUM_FORMAT_RESERVED_8 = 0x0008,
        D3D11X_IMG_NUM_FORMAT_SRGB = 0x0009,
        D3D11X_IMG_NUM_FORMAT_UBNORM = 0x000a,
        D3D11X_IMG_NUM_FORMAT_UBNORM_OGL = 0x000b,
        D3D11X_IMG_NUM_FORMAT_UBINT = 0x000c,
        D3D11X_IMG_NUM_FORMAT_UBSCALED = 0x000d,
    };

    enum D3D11X_SWIZZLE
    {
        D3D11X_SWIZZLE_INVALID = 0x00ff,
        D3D11X_SWIZZLE_0 = 0x0000,
        D3D11X_SWIZZLE_1 = 0x0001,
        D3D11X_SWIZZLE_X = 0x0004,
        D3D11X_SWIZZLE_Y = 0x0005,
        D3D11X_SWIZZLE_Z = 0x0006,
        D3D11X_SWIZZLE_W = 0x0007,
    };

    enum D3D11X_IMG_DATA_FORMAT
    {
        D3D11X_IMG_DATA_FORMAT_INVALID = 0x0000,
        D3D11X_IMG_DATA_FORMAT_8 = 0x0001,
        D3D11X_IMG_DATA_FORMAT_16 = 0x0002,
        D3D11X_IMG_DATA_FORMAT_8_8 = 0x0003,
        D3D11X_IMG_DATA_FORMAT_32 = 0x0004,
        D3D11X_IMG_DATA_FORMAT_16_16 = 0x0005,
        D3D11X_IMG_DATA_FORMAT_10_11_11 = 0x0006,
        D3D11X_IMG_DATA_FORMAT_11_11_10 = 0x0007,
        D3D11X_IMG_DATA_FORMAT_10_10_10_2 = 0x0008,
        D3D11X_IMG_DATA_FORMAT_2_10_10_10 = 0x0009,
        D3D11X_IMG_DATA_FORMAT_8_8_8_8 = 0x000a,
        D3D11X_IMG_DATA_FORMAT_32_32 = 0x000b,
        D3D11X_IMG_DATA_FORMAT_16_16_16_16 = 0x000c,
        D3D11X_IMG_DATA_FORMAT_32_32_32 = 0x000d,
        D3D11X_IMG_DATA_FORMAT_32_32_32_32 = 0x000e,
        D3D11X_IMG_DATA_FORMAT_5_6_5 = 0x0010,
        D3D11X_IMG_DATA_FORMAT_1_5_5_5 = 0x0011,
        D3D11X_IMG_DATA_FORMAT_5_5_5_1 = 0x0012,
        D3D11X_IMG_DATA_FORMAT_4_4_4_4 = 0x0013,
        D3D11X_IMG_DATA_FORMAT_8_24 = 0x0014,
        D3D11X_IMG_DATA_FORMAT_24_8 = 0x0015,
        D3D11X_IMG_DATA_FORMAT_X24_8_32 = 0x0016,
        D3D11X_IMG_DATA_FORMAT_DXT3A = 0x0018,
        D3D11X_IMG_DATA_FORMAT_DXT3A_AS_1_1_1_1 = 0x0019,
        D3D11X_IMG_DATA_FORMAT_DXT5A = 0x001a,
        D3D11X_IMG_DATA_FORMAT_DXN = 0x001b,
        D3D11X_IMG_DATA_FORMAT_CTX1 = 0x001c,
        D3D11X_IMG_DATA_FORMAT_YCBCR = 0x001d,
        D3D11X_IMG_DATA_FORMAT_7E3 = 0x001e,
        D3D11X_IMG_DATA_FORMAT_6E4 = 0x001f,
        D3D11X_IMG_DATA_FORMAT_GB_GR = 0x0020,
        D3D11X_IMG_DATA_FORMAT_BG_RG = 0x0021,
        D3D11X_IMG_DATA_FORMAT_5_9_9_9 = 0x0022,
        D3D11X_IMG_DATA_FORMAT_BC1 = 0x0023,
        D3D11X_IMG_DATA_FORMAT_BC2 = 0x0024,
        D3D11X_IMG_DATA_FORMAT_BC3 = 0x0025,
        D3D11X_IMG_DATA_FORMAT_BC4 = 0x0026,
        D3D11X_IMG_DATA_FORMAT_BC5 = 0x0027,
        D3D11X_IMG_DATA_FORMAT_BC6 = 0x0028,
        D3D11X_IMG_DATA_FORMAT_BC7 = 0x0029,
        D3D11X_IMG_DATA_FORMAT_FMASK8_S2_F1 = 0x002c,
        D3D11X_IMG_DATA_FORMAT_FMASK8_S4_F1 = 0x002d,
        D3D11X_IMG_DATA_FORMAT_FMASK8_S8_F1 = 0x002e,
        D3D11X_IMG_DATA_FORMAT_FMASK8_S2_F2 = 0x002f,
        D3D11X_IMG_DATA_FORMAT_FMASK8_S4_F2 = 0x0030,
        D3D11X_IMG_DATA_FORMAT_FMASK8_S4_F4 = 0x0031,
        D3D11X_IMG_DATA_FORMAT_FMASK16_S16_F1 = 0x0032,
        D3D11X_IMG_DATA_FORMAT_FMASK16_S8_F2 = 0x0033,
        D3D11X_IMG_DATA_FORMAT_FMASK32_S16_F2 = 0x0034,
        D3D11X_IMG_DATA_FORMAT_FMASK32_S8_F4 = 0x0035,
        D3D11X_IMG_DATA_FORMAT_FMASK32_S8_F8 = 0x0036,
        D3D11X_IMG_DATA_FORMAT_FMASK64_S16_F4 = 0x0037,
        D3D11X_IMG_DATA_FORMAT_FMASK64_S16_F8 = 0x0038,
        D3D11X_IMG_DATA_FORMAT_4_4 = 0x0039,
        D3D11X_IMG_DATA_FORMAT_6_5_5 = 0x003a,
        D3D11X_IMG_DATA_FORMAT_1 = 0x003b,
        D3D11X_IMG_DATA_FORMAT_1_REVERSED = 0x003c,
        D3D11X_IMG_DATA_FORMAT_32_AS_8 = 0x003d,
        D3D11X_IMG_DATA_FORMAT_32_AS_8_8 = 0x003e,
        D3D11X_IMG_DATA_FORMAT_32_AS_32_32_32_32 = 0x003f,
    };

    struct D3D11X_SRV_FORMAT
    {
        D3D11X_IMG_DATA_FORMAT DataFormat;
        D3D11X_IMG_NUM_FORMAT NumFormat;
        D3D11X_SWIZZLE Swizzle[4];
    };

    enum D3D11X_CERAM_RESOURCE_TYPE
    {
        D3D11X_CERAM_RESOURCE_TYPE_TEXTURE_VIEW = 0x0000,
        D3D11X_CERAM_RESOURCE_TYPE_BUFFER_VIEW = 0x0001,
        D3D11X_CERAM_RESOURCE_TYPE_SAMPLER_STATE = 0x0002,
    };

    struct D3D11X_DESCRIPTOR_BUFFER_VIEW
    {
        union
        {
            __m128i Oword;
            uint64_t Qword[2];
            uint32_t Dword[4];
        };
        static const uint32_t DescriptorSize;
        static const D3D11X_CERAM_RESOURCE_TYPE CeRamType;
    };

    typedef enum _D3D11X_GDS_REGION_TYPE
    {
        D3D11X_GDS_REGION_PS = 0,
        D3D11X_GDS_REGION_CS = 1
    } D3D11X_GDS_REGION_TYPE;

    typedef struct D3D11X_COUNTER_DATA
    {
        uint64_t SRBM[2];
        uint64_t CP[1];
        uint64_t CB[4][8];
        uint64_t DB[4][8];
        uint64_t GRBM[2];
        uint64_t GRBMSE[1][2];
        uint64_t RLC[2];
        uint64_t PAPC[4][2];
        uint64_t SC[8][4];
        uint64_t SX[4][4];
        uint64_t SPI[4][2];
        uint64_t SQ[8][2];
        uint64_t TA[2][28];
        uint64_t TD[1][28];
        uint64_t TCP[4][28];
        uint64_t TCC[4][12];
        uint64_t TCA[4][2];
        uint64_t GDS[4];
        uint64_t VGT[4][2];
        uint64_t MCMCB[4];
        uint64_t IA[4];
        uint64_t SDMA[2];
        uint64_t MCL2[2];
        uint64_t MCMCD[4][2];
        uint64_t MCHVL2[2];
        uint64_t MCHVMCB[4];
        uint64_t MCHVMCD[4][2];
        uint64_t MCARB[4][2];
        uint64_t MCCITF[4][2];
        uint64_t MCHUB[4];
    } D3D11X_COUNTER_DATA;

    typedef enum D3D11_STAGE : UINT
    {
        D3D11_STAGE_VS = 0,
        D3D11_STAGE_HS = 1,
        D3D11_STAGE_DS = 2,
        D3D11_STAGE_GS = 3,
        D3D11_STAGE_PS = 4,
        D3D11_STAGE_CS = 5
    } D3D11_STAGE;
    typedef struct D3D11X_TESSELLATION_PARAMETERS
    {
        UINT Size;
        UINT Flags;
        UINT PatchesPerThreadgroup;
        float TfThreshold;
        UINT DsWaveThreshold;
    } D3D11X_TESSELLATION_PARAMETERS;

    typedef enum D3D11X_GPU_PIPELINED_EVENT
    {
        D3D11X_GPU_PIPELINED_EVENT_STREAMOUT_FLUSH = 0x0000001f,
        D3D11X_GPU_PIPELINED_EVENT_FLUSH_AND_INV_CB_PIXEL_DATA = 0x00000031,
        D3D11X_GPU_PIPELINED_EVENT_DB_CACHE_FLUSH_AND_INV = 0x0000002a,
        D3D11X_GPU_PIPELINED_EVENT_FLUSH_AND_INV_CB_META = 0x0000002e,
        D3D11X_GPU_PIPELINED_EVENT_FLUSH_AND_INV_DB_META = 0x0000002c,
        D3D11X_GPU_PIPELINED_EVENT_CS_PARTIAL_FLUSH = 0x00000407,
        D3D11X_GPU_PIPELINED_EVENT_VS_PARTIAL_FLUSH = 0x0000040f,
        D3D11X_GPU_PIPELINED_EVENT_PS_PARTIAL_FLUSH = 0x00000410,
        D3D11X_GPU_PIPELINED_EVENT_PFP_SYNC_ME = 0x80000001,

    } D3D11X_GPU_PIPELINED_EVENT;

    struct D3D11X_GRAPHICS_SHADER_LIMITS
    {
        UINT MaxWavesWithLateAllocParameterCache;

        UINT VSDisableCuMask;
        UINT DSDisableCuMask;
        UINT GSDisableCuMask;
        UINT PSDisableCuMask;

        UINT VSMaxWaves;
        UINT HSMaxWaves;
        UINT DSMaxWaves;
        UINT GSMaxWaves;
        UINT PSMaxWaves;

        UINT VSMaxWavesForCuLocking;
        UINT HSMaxWavesForCuLocking;
        UINT DSMaxWavesForCuLocking;
        UINT GSMaxWavesForCuLocking;
        UINT PSMaxWavesForCuLocking;
    };

    enum D3D11X_SHADER_CS_SIMD_WALK_ALGORITHM : UINT
    {
        D3D11X_SHADER_CS_SIMD_WALK_ALGORITHM_DEFAULT = 0,
        D3D11X_SHADER_CS_SIMD_WALK_ALGORITHM_GLOBAL_BALANCED = 1,
        D3D11X_SHADER_CS_SIMD_WALK_ALGORITHM_GLOBAL_STRICT = 2,
        D3D11X_SHADER_CS_SIMD_WALK_ALGORITHM_PER_CU = 3,
    };

    struct D3D11X_COMPUTE_SHADER_LIMITS
    {
        UINT DisableCuMask[2];
        UINT MaxWaves;
        UINT MaxThreadgroupsPerCu;
        UINT MaxWavesForCuLocking;
        UINT NumThreadgroupsWalkedPerCu;
        D3D11X_SHADER_CS_SIMD_WALK_ALGORITHM SimdWalkAlgorithm;
    };

    typedef enum D3D11X_THREAD_TRACE_SCOPE
    {
        D3D11X_THREAD_TRACE_SCOPE_TITLE_ONLY = 0,
        D3D11X_THREAD_TRACE_SCOPE_SYSTEM_WIDE = 1,
        D3D11X_THREAD_TRACE_SCOPE_SYSTEM_AND_DETAILED_TITLE = 2,
    } D3D11X_THREAD_TRACE_SCOPE;

    typedef enum D3D11X_THREAD_TRACE_PIPELINE_ENABLE
    {
        D3D11X_THREAD_TRACE_PIPELINE_ENABLE_NONE = 0x00000000,
        D3D11X_THREAD_TRACE_PIPELINE_ENABLE_ALL = 0x00000001,
    } D3D11X_THREAD_TRACE_PIPELINE_ENABLE;

    struct D3D11X_THREAD_TRACE_DESC
    {
        BOOL PipelineFlushBeforeAndAfter;
        UINT TargetComputeUnitIndex;
        D3D11X_THREAD_TRACE_SCOPE TraceScope;
        BOOL AllowSamplingGpuStalls;
        D3D11X_THREAD_TRACE_PIPELINE_ENABLE PsEnable;
        D3D11X_THREAD_TRACE_PIPELINE_ENABLE VsEnable;
        D3D11X_THREAD_TRACE_PIPELINE_ENABLE GsEnable;
        D3D11X_THREAD_TRACE_PIPELINE_ENABLE EsEnable;
        D3D11X_THREAD_TRACE_PIPELINE_ENABLE HsEnable;
        D3D11X_THREAD_TRACE_PIPELINE_ENABLE LsEnable;
        D3D11X_THREAD_TRACE_PIPELINE_ENABLE CsEnable;
        USHORT TokenMask;
        USHORT InstructionMask;
        BYTE RegisterMask;
    };

    typedef struct D3D11X_GS_PARAMETERS
    {
        UINT Size;
        UINT Flags;
        UINT VerticesPerSubgroup;
        UINT PrimitivesPerSubgroup;
        float VerticesPerPrimitiveRatio;
        UINT LdsAllocationLimit;
    } D3D11X_GS_PARAMETERS;

    typedef struct _D3D11X_MSAA_SCAN_CONVERTER_SETTINGS
    {
        UINT NumSamplesMsaaLog2 : 3;
        UINT MaxSampleDistanceInSubpixels : 4;
        UINT NumSamplesMsaaExposedToPSLog2 : 3;
        UINT DetailToExposedMode : 2;
        UINT ApplyMaskAfterCentroid : 1;
    } D3D11X_MSAA_SCAN_CONVERTER_SETTINGS;

    typedef POINT D3D11X_POINT;

    typedef struct _D3D11X_MSAA_EQAA_SETTINGS
    {
        UINT MaxAnchorSamplesLog2 : 3;
        UINT NumSamplesForPSIterationLog2 : 3;
        UINT NumSamplesForMaskExportLog2 : 3;
        UINT NumSamplesForAlphaToMaskLog2 : 3;
        UINT HightQualityIntersections : 1;
        UINT InterpolateCompZ : 1;
        UINT InterpolateSrcZ : 1;
        UINT StaticAnchorAssociations : 1;
        UINT OverrasterizationAmount : 3;
        UINT EnablePostZOverrasterization : 1;
    } D3D11X_MSAA_EQAA_SETTINGS;

    typedef struct _D3D11X_MSAA_SAMPLE_PRIORITIES
    {
        BYTE CentroidPriorities[16];
    } D3D11X_MSAA_SAMPLE_PRIORITIES;

    typedef struct _D3D11X_MSAA_SAMPLE_POSITIONS
    {
        INT8 SampleLocs00[16][2];
        INT8 SampleLocs10[16][2];
        INT8 SampleLocs01[16][2];
        INT8 SampleLocs11[16][2];
    } D3D11X_MSAA_SAMPLE_POSITIONS;

    typedef D3D11_RECT D3D11X_RECT;

    typedef struct D3D11X_FORMAT
    {
        union {
            struct
            {
                UINT DataFormat;
                UINT NumberFormat;
            };
            UINT32 Dword[2];
            UINT64 Qword;
        };
    } D3D11X_FORMAT;

    typedef enum D3D11X_HW_STAGE : UINT
    {
        D3D11X_HW_STAGE_PS = 0,
        D3D11X_HW_STAGE_VS = 1,
        D3D11X_HW_STAGE_GS = 2,
        D3D11X_HW_STAGE_ES = 3,
        D3D11X_HW_STAGE_HS = 4,
        D3D11X_HW_STAGE_LS = 5,
        D3D11X_HW_STAGE_CS = 6,
    } D3D11X_HW_STAGE;

    struct D3D11X_COUNTER_SET_DESC;
    struct D3D11X_DESCRIPTOR_RESOURCE;
    struct D3D11_DMA_ENGINE_CONTEXT_DESC
    {
        UINT CreateFlags;
        UINT RingBufferSizeBytes;
        UINT SegmentSizeBytes;
    };
    enum D3D11X_TEX_CLAMP
    {
        D3D11X_TEX_CLAMP_WRAP = 0x0000,
        D3D11X_TEX_CLAMP_MIRROR = 0x0001,
        D3D11X_TEX_CLAMP_LAST_TEXEL = 0x0002,
        D3D11X_TEX_CLAMP_MIRROR_ONCE_LAST_TEXEL = 0x0003,
        D3D11X_TEX_CLAMP_HALF_BORDER = 0x0004,
        D3D11X_TEX_CLAMP_MIRROR_ONCE_HALF_BORDER = 0x0005,
        D3D11X_TEX_CLAMP_BORDER = 0x0006,
        D3D11X_TEX_CLAMP_MIRROR_ONCE_BORDER = 0x0007,
    };

    enum D3D11X_TEX_XY_FILTER
    {
        D3D11X_TEX_XY_FILTER_POINT = 0x0000,
        D3D11X_TEX_XY_FILTER_BILINEAR = 0x0001,
        D3D11X_TEX_XY_FILTER_ANISO_POINT = 0x0002,
        D3D11X_TEX_XY_FILTER_ANISO_BILINEAR = 0x0003,
    };

    enum D3D11X_TEX_DEPTH_COMPARE
    {
        D3D11X_TEX_DEPTH_COMPARE_NEVER = 0x0000,
        D3D11X_TEX_DEPTH_COMPARE_LESS = 0x0001,
        D3D11X_TEX_DEPTH_COMPARE_EQUAL = 0x0002,
        D3D11X_TEX_DEPTH_COMPARE_LESSEQUAL = 0x0003,
        D3D11X_TEX_DEPTH_COMPARE_GREATER = 0x0004,
        D3D11X_TEX_DEPTH_COMPARE_NOTEQUAL = 0x0005,
        D3D11X_TEX_DEPTH_COMPARE_GREATEREQUAL = 0x0006,
        D3D11X_TEX_DEPTH_COMPARE_ALWAYS = 0x0007,
    };

    enum D3D11X_TEX_ANISO_RATIO
    {
        D3D11X_TEX_ANISO_RATIO_1 = 0x0000,
        D3D11X_TEX_ANISO_RATIO_2 = 0x0001,
        D3D11X_TEX_ANISO_RATIO_4 = 0x0002,
        D3D11X_TEX_ANISO_RATIO_8 = 0x0003,
        D3D11X_TEX_ANISO_RATIO_16 = 0x0004,
    };

    enum D3D11X_TEX_BORDER_COLOR
    {
        D3D11X_TEX_BORDER_COLOR_TRANS_BLACK = 0x0000,
        D3D11X_TEX_BORDER_COLOR_OPAQUE_BLACK = 0x0001,
        D3D11X_TEX_BORDER_COLOR_OPAQUE_WHITE = 0x0002,
        D3D11X_TEX_BORDER_COLOR_INDEX = 0x0003,
    };

    enum D3D11X_TEX_FILTER_MODE
    {
        D3D11X_TEX_FILTER_MODE_LERP = 0x0000,
        D3D11X_TEX_FILTER_MODE_MIN = 0x0001,
        D3D11X_TEX_FILTER_MODE_MAX = 0x0002,
    };

    enum D3D11X_TEX_Z_FILTER
    {
        D3D11X_TEX_Z_FILTER_NONE = 0x0000,
        D3D11X_TEX_Z_FILTER_POINT = 0x0001,
        D3D11X_TEX_Z_FILTER_LINEAR = 0x0002,
    };

    enum D3D11X_TEX_MIP_FILTER
    {
        D3D11X_TEX_MIP_FILTER_NONE = 0x0000,
        D3D11X_TEX_MIP_FILTER_POINT = 0x0001,
        D3D11X_TEX_MIP_FILTER_LINEAR = 0x0002,
    };

    struct D3D11X_SAMPLER_DESC
    {
        D3D11X_TEX_CLAMP ClampX : 3;
        D3D11X_TEX_CLAMP ClampY : 3;
        D3D11X_TEX_CLAMP ClampZ : 3;
        D3D11X_TEX_ANISO_RATIO MaxAnisotropicRatio : 3;
        D3D11X_TEX_DEPTH_COMPARE DepthCompareFunction : 3;
        int32_t ForceUnnormalized : 1;
        uint32_t AnisotropicThreshold : 3;
        int32_t MCCoordTrunc : 1;
        int32_t ForceDegamma : 1;
        uint32_t AnisotropicBias : 6;
        int32_t TruncateCoordinates : 1;
        int32_t DisableCubemapWrap : 1;
        D3D11X_TEX_FILTER_MODE FilterMode : 3;
        D3D11X_TEX_FILTER_MODE : 0;
        uint32_t MinLOD : 12;
        uint32_t MaxLOD : 12;
        uint32_t PerfMip : 4;
        uint32_t PerfZ : 4;
        uint32_t : 0;
        int32_t LODBias : 14;
        int32_t LODBiasSecondary : 6;
        D3D11X_TEX_XY_FILTER XYMagFilter : 2;
        D3D11X_TEX_XY_FILTER XYMinFilter : 2;
        D3D11X_TEX_Z_FILTER ZFilter : 2;
        D3D11X_TEX_MIP_FILTER MipFilter : 2;
        int32_t MipPointPreclamp : 1;
        int32_t DisableLSBCeil : 1;
        int32_t FilterPrecisionFix : 2;
        int32_t : 0;
        uint32_t BorderColorIndex : 30;
        D3D11X_TEX_BORDER_COLOR BorderColorType : 2;
    };
    struct _unnamed_0x173c2
    {
        void *pColorSamples;
        void *pCMask;
    };

    struct _unnamed_0x173be
    {
        void *pDepthSamples;
        void *pHTile;
    };

    struct _unnamed_0x173c0
    {
        void *pColorSamples;
        void *pCMask;
        void *pFragmentMask;
    };

    struct _unnamed_0x173bc
    {
        void *pDepthSamples;
        void *pHTile;
        void *pStencilSamples;
    };

    struct D3D11X_RENDERABLE_TEXTURE_ADDRESSES
    {
        union {
            _unnamed_0x173c2 NonAARenderTarget;
            _unnamed_0x173c0 AARenderTarget;
            _unnamed_0x173be DepthTarget;
            _unnamed_0x173bc DepthStencilTarget;
        };
    };

    struct D3D11X_DRIVER_STATISTICS;
    struct D3D11_COMPUTE_CONTEXT_DESC;
    struct D3D11X_RESOURCE_VIEW_DESC;
    struct D3D11X_DESCRIPTOR_SHADER_RESOURCE_VIEW;
    struct D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW;
    struct D3D11X_DESCRIPTOR_CONSTANT_BUFFER_VIEW;
    struct D3D11X_DESCRIPTOR_VERTEX_BUFFER_VIEW;
    struct D3D11X_SAMPLER_STATE_DESC;
    struct D3D11X_COUNTER_SET_DESC;
    struct D3D11X_DESCRIPTOR_RESOURCE;
    struct D3D11_DMA_ENGINE_CONTEXT_DESC;
    struct D3D11X_DRIVER_STATISTICS;
    struct D3D11_COMPUTE_CONTEXT_DESC;
    struct D3D11X_RESOURCE_VIEW_DESC;
    struct D3D11X_DESCRIPTOR_SHADER_RESOURCE_VIEW;
    struct D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW;
    struct D3D11X_DESCRIPTOR_CONSTANT_BUFFER_VIEW;
    struct D3D11X_DESCRIPTOR_VERTEX_BUFFER_VIEW;
    struct D3D11X_SAMPLER_STATE_DESC;
    struct D3D11X_DESCRIPTOR_SAMPLER_STATE;
    class ID3D11CounterSetX;
    class ID3D11CounterSampleX;
    typedef enum D3D11X_HARDWARE_VERSION
    {
        D3D11X_HARDWARE_VERSION_XBOX_ONE = 0,
        D3D11X_HARDWARE_VERSION_XBOX_ONE_S = 1,
        D3D11X_HARDWARE_VERSION_XBOX_ONE_X = 2,
        D3D11X_HARDWARE_VERSION_XBOX_ONE_X_DEVKIT = 3
    } D3D11X_HARDWARE_VERSION;

    struct D3D11X_GPU_HARDWARE_CONFIGURATION
    {
        UINT64 GpuFrequency;
        D3D11X_HARDWARE_VERSION HardwareVersion;
        UINT32 GpuCuCount;
    };

    enum D3D11X_DESCRIPTOR_TYPE
    {
        D3D11X_DESCRIPTOR_TYPE_RESOURCE = 0x0000,
        D3D11X_DESCRIPTOR_TYPE_SHADER_RESOURCE_VIEW = 0x0001,
        D3D11X_DESCRIPTOR_TYPE_UNORDERED_ACCESS_VIEW = 0x0002,
        D3D11X_DESCRIPTOR_TYPE_CONSTANT_BUFFER_VIEW = 0x0003,
        D3D11X_DESCRIPTOR_TYPE_VERTEX_BUFFER_VIEW = 0x0004,
        D3D11X_DESCRIPTOR_TYPE_SAMPLER_STATE = 0x0009,
    };

    struct D3D11X_DESCRIPTOR_TEXTURE_VIEW
    {
        union {
            __m128i Oword[2];
            uint64_t Qword[4];
            uint32_t Dword[8];
        };
        uint32_t DescriptorSize;
        D3D11X_CERAM_RESOURCE_TYPE CeRamType;
    };

    struct D3D11XTinyDevice
    {
        uint32_t m_Reserved1[8];
        uint32_t *m_pBatchCurrent;
        uint32_t *m_pBatchLimit;
        uint32_t *m_pCeCurrent;
        uint32_t *m_pCeBiasedLimit;
        uint32_t *m_pCeLimit;
        uint32_t m_Reserved2[64];
        static const uint32_t BiasDwordCount = 70;
        static const uint32_t MakeCeSpaceDwordCount = 1024;
    };

    template <abi_t ABI>
    struct D3D11XShaderUserDataManagerDraw
    {
        uint32_t m_DirtyFlags;
        uint32_t m_Reserved1;
        uint64_t m_Topology;
        ID3D11InputLayout *m_pInputLayout;
        gfx::ID3D11VertexShader<ABI> *m_pVs;
        gfx::ID3D11PixelShader<ABI> *m_pPs;
        uint32_t m_Reserved2[128];
    };

    typedef UINT (*D3D11XHANGBEGINCALLBACK)(UINT64 Flags);
    typedef void (*D3D11XHANGPRINTCALLBACK)(const CHAR *strLine);
    typedef void (*D3D11XHANGDUMPCALLBACK)(const WCHAR *strFileName);

    class ID3D11ComputeContextX;
    
    namespace details
    {
        template <abi_t ABI> struct ID3D11DeviceChildData
        {
            gfx::ID3D11Device<ABI> *m_pDevice;
            void *m_pPrivateData;
        };
    }

    template<abi_t ABI> struct ID3D11DeviceChild : xbox::IGraphicsUnknown<ABI>, details::ID3D11DeviceChildData<ABI>
    {
        virtual void GetDevice(gfx::ID3D11Device<ABI> **ppDevice) = 0;
        virtual HRESULT GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData) = 0;
        virtual HRESULT SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData) = 0;
        virtual HRESULT SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData) = 0;
        virtual HRESULT SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData) = 0;
    };
  
    template<abi_t ABI> requires (ABI >= abi_t{ 6,2,13004,0 }) struct ID3D11DeviceChild<ABI> : xbox::IGraphicsUnknown<ABI>, details::ID3D11DeviceChildData<ABI>
    {
        virtual void GetDevice(gfx::ID3D11Device<ABI>** ppDevice) = 0;
        virtual HRESULT GetPrivateData(_GUID const& guid, uint32_t* pDataSize, void* pData) = 0;
        virtual HRESULT SetPrivateData(_GUID const& guid, uint32_t DataSize, void const* pData) = 0;
        virtual HRESULT SetPrivateDataInterface(_GUID const& guid, IUnknown const* pData) = 0;
        virtual HRESULT SetPrivateDataInterfaceGraphics(_GUID const& guid, xbox::IGraphicsUnknown<ABI> const* pData) = 0;
        virtual HRESULT SetName(LPCWSTR pName) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11DeviceChildVtbl : xbox::IGraphicsUnknownVtbl<ABI>
    {
        void(*GetDevice)(void *, gfx::ID3D11Device<ABI> **ppDevice);
        HRESULT(*GetPrivateData)(void *, _GUID const &guid, uint32_t *pDataSize, void *pData);
        HRESULT(*SetPrivateData)(void *, _GUID const &guid, uint32_t DataSize, void const *pData);
        HRESULT(*SetPrivateDataInterface)(void *, _GUID const &guid, IUnknown const *pData);
        HRESULT(*SetPrivateDataInterfaceGraphics)(void *, _GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData);
    };
 
    template<abi_t ABI> requires (ABI >= abi_t{ 6,2,13004,0 }) struct ID3D11DeviceChildVtbl<ABI> : xbox::IGraphicsUnknownVtbl<ABI>
    {
        void(*GetDevice)(void*, gfx::ID3D11Device<ABI>** ppDevice);
        HRESULT(*GetPrivateData)(void*, _GUID const& guid, uint32_t* pDataSize, void* pData);
        HRESULT(*SetPrivateData)(void*, _GUID const& guid, uint32_t DataSize, void const* pData);
        HRESULT(*SetPrivateDataInterface)(void*, _GUID const& guid, IUnknown const* pData);
        HRESULT(*SetPrivateDataInterfaceGraphics)(void*, _GUID const& guid, xbox::IGraphicsUnknown<ABI> const* pData);
        HRESULT(*SetName)(void*, LPCWSTR pName);
    };
    
    namespace details
    {
        template<abi_t ABI>
        struct ID3D11ResourceData
        {
            void *m_pAllocationStart;
        };
    }
    
    template<abi_t ABI>
    struct ID3D11Resource : gfx::ID3D11DeviceChild<ABI>, details::ID3D11ResourceData<ABI>
    {
        virtual void GetType(D3D11_RESOURCE_DIMENSION *pDimension) = 0;
        virtual void SetEvictionPriority(uint32_t EvictionPriority) = 0;
        virtual uint32_t GetEvictionPriority() = 0;
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11Resource<ABI> : gfx::ID3D11DeviceChild<ABI>, details::ID3D11ResourceData<ABI>
    {
        virtual void GetType(D3D11_RESOURCE_DIMENSION *pDimension) = 0;
        virtual void SetEvictionPriority(uint32_t EvictionPriority) = 0;
        virtual uint32_t GetEvictionPriority() = 0;
        virtual void GetDescriptor(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11ResourceVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void(*GetType)(void *, D3D11_RESOURCE_DIMENSION *pDimension);
        void(*SetEvictionPriority)(void *, uint32_t EvictionPriority);
        uint32_t(*GetEvictionPriority)(void *);
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11ResourceVtbl<ABI> : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void(*GetType)(void *, D3D11_RESOURCE_DIMENSION *pDimension);
        void(*SetEvictionPriority)(void *, uint32_t EvictionPriority);
        uint32_t(*GetEvictionPriority)(void *);
        void(*GetDescriptor)(void *, gfx::D3D11X_DESCRIPTOR_RESOURCE *pDesc);
    };
    
    template<abi_t ABI>
    struct ID3D11Texture1D : gfx::ID3D11Resource<ABI>
    {
        virtual void GetDesc(D3D11_TEXTURE1D_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11Texture1DVtbl : gfx::ID3D11ResourceVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_TEXTURE1D_DESC *pDesc);
    };
    
    template<abi_t ABI>
    struct ID3D11Texture2D : gfx::ID3D11Resource<ABI>
    {
        virtual void GetDesc(D3D11_TEXTURE2D_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11Texture2DVtbl : gfx::ID3D11ResourceVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_TEXTURE2D_DESC *pDesc);
    };
    
    template<abi_t ABI>
    struct ID3D11Texture3D : gfx::ID3D11Resource<ABI>
    {
        virtual void GetDesc(D3D11_TEXTURE3D_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11Texture3DVtbl : gfx::ID3D11ResourceVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_TEXTURE3D_DESC *pDesc);
    };
    
    namespace details
    {
        template<abi_t ABI>
        struct ID3D11BufferData
        {
        };
        
        template<abi_t ABI>
        requires (ABI >= abi_t{6,2,11274,0})
        struct ID3D11BufferData<ABI>
        {
            uint32_t DescriptorSize;
            gfx::D3D11X_CERAM_RESOURCE_TYPE CeRamType;
        };
    }
    
    template<abi_t ABI>
    struct ID3D11Buffer : gfx::ID3D11Resource<ABI>, details::ID3D11BufferData<ABI>
    {
        virtual void GetDesc(D3D11_BUFFER_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11BufferVtbl : gfx::ID3D11ResourceVtbl<ABI>
    {
        void (*GetDesc)(void *, D3D11_BUFFER_DESC *pDesc);
    };
    
    template<abi_t ABI>
    struct ID3D11VertexShader : gfx::ID3D11DeviceChild<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11VertexShaderVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11PixelShader : gfx::ID3D11DeviceChild<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11PixelShaderVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11ComputeShader : gfx::ID3D11DeviceChild<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11ComputeShaderVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11GeometryShader : gfx::ID3D11DeviceChild<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11GeometryShaderVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11HullShader : gfx::ID3D11DeviceChild<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11HullShaderVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11DomainShader : gfx::ID3D11DeviceChild<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11DomainShaderVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
    };
    
    struct D3D11X_DESCRIPTOR_SAMPLER_STATE
    {
        union
        {
            __m128i Oword;
            uint64_t Qword[2];
            uint32_t Dword[4];
        };
        uint32_t DescriptorSize;
        gfx::D3D11X_CERAM_RESOURCE_TYPE CeRamType;
    };
    
    namespace details
    {
        template<abi_t ABI>
        struct ID3D11SamplerStateData
        {
        };
        
        template<abi_t ABI>
        requires (ABI >= abi_t{6,2,11274,0})
        struct ID3D11SamplerStateData<ABI>
        {
            gfx::D3D11X_DESCRIPTOR_SAMPLER_STATE m_Descriptor;
            uint32_t DescriptorSize;
            gfx::D3D11X_CERAM_RESOURCE_TYPE CeRamType;
        };
    }
    
    template<abi_t ABI>
    struct ID3D11SamplerState : gfx::ID3D11DeviceChild<ABI>, details::ID3D11SamplerStateData<ABI>
    {
        virtual void GetDesc(D3D11_SAMPLER_DESC *pDesc) = 0;
        virtual void GetDescX(D3D11X_SAMPLER_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11SamplerStateVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_SAMPLER_DESC *pDesc);
        void(*GetDescX)(void *, D3D11X_SAMPLER_DESC *pDesc);
    };
    
    template<abi_t ABI>
    struct ID3D11RasterizerState : gfx::ID3D11DeviceChild<ABI>
    {
        virtual void GetDesc(D3D11_RASTERIZER_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11RasterizerStateVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_RASTERIZER_DESC *pDesc);
    };
    
    template<abi_t ABI>
    struct ID3D11BlendState : gfx::ID3D11DeviceChild<ABI>
    {
        virtual void GetDesc(D3D11_BLEND_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11BlendStateVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_BLEND_DESC *pDesc);
    };
    
    template<abi_t ABI>
    struct ID3D11DepthStencilState : gfx::ID3D11DeviceChild<ABI>
    {
        virtual void GetDesc(D3D11_DEPTH_STENCIL_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11DepthStencilState<ABI> : gfx::ID3D11DeviceChild<ABI>
    {
        virtual void GetDesc(D3D11_DEPTH_STENCIL_DESC *pDesc) = 0;
        virtual void GetDescX(D3D11_DEPTH_STENCIL_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11DepthStencilStateVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_DEPTH_STENCIL_DESC *pDesc);
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11DepthStencilStateVtbl<ABI> : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_DEPTH_STENCIL_DESC *pDesc);
        void(*GetDescX)(void *, D3D11_DEPTH_STENCIL_DESC *pDesc);
    };
    
    namespace details
    {
        template<abi_t ABI>
        struct ID3D11ViewData
        {
            gfx::ID3D11Resource<ABI> *m_pResource;
            uint32_t m_Type;
        };
    }
    
    template<abi_t ABI>
    struct ID3D11View : gfx::ID3D11DeviceChild<ABI>, details::ID3D11ViewData<ABI>
    {
        virtual void GetResource(gfx::ID3D11Resource<ABI> **ppResource) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11ViewVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void(*GetResource)(void *, gfx::ID3D11Resource<ABI> **ppResource);
    };
    
    namespace details
    {
        template<abi_t ABI>
        struct ID3D11ShaderResourceViewData
        {
            void *m_pAllocationStart;
        };
        
        template<abi_t ABI>
        requires (ABI >= abi_t{6,2,11274,0})
        struct ID3D11ShaderResourceViewData<ABI>
        {
            gfx::D3D11X_DESCRIPTOR_TEXTURE_VIEW m_Descriptor;
            void *m_pAllocationStart;
            uint32_t DescriptorSize;
            gfx::D3D11X_CERAM_RESOURCE_TYPE CeRamType;
        };
    }
    
    template<abi_t ABI>
    struct ID3D11ShaderResourceView : gfx::ID3D11View<ABI>, details::ID3D11ShaderResourceViewData<ABI>
    {
        virtual void GetDesc(D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11ShaderResourceView<ABI> : gfx::ID3D11View<ABI>, details::ID3D11ShaderResourceViewData<ABI>
    {
        virtual void GetDesc(D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc) = 0;
        virtual void GetFormatX(D3D11X_SRV_FORMAT *) = 0;
        virtual int32_t SetFormatX(D3D11X_SRV_FORMAT const *) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11ShaderResourceViewVtbl : gfx::ID3D11ViewVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc);
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11ShaderResourceViewVtbl<ABI> : gfx::ID3D11ViewVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc);
        void(*GetFormatX)(void *, D3D11X_SRV_FORMAT *);
        int32_t(*SetFormatX)(void *, D3D11X_SRV_FORMAT const *);
    };
    
    template<abi_t ABI>
    struct ID3D11RenderTargetView : gfx::ID3D11View<ABI>
    {
        virtual void GetDesc(D3D11_RENDER_TARGET_VIEW_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11RenderTargetViewVtbl : gfx::ID3D11ViewVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_RENDER_TARGET_VIEW_DESC *pDesc);
    };
    
    template<abi_t ABI>
    struct ID3D11DepthStencilView : gfx::ID3D11View<ABI>
    {
        virtual void GetDesc(D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11DepthStencilViewVtbl : gfx::ID3D11ViewVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc);
    };
    
    namespace details
    {
        template<abi_t ABI>
        struct ID3D11UnorderedAccessViewData
        {
            void *m_pAllocationStart;
        };
        
        template<abi_t ABI>
        requires (ABI >= abi_t{6,2,11274,0})
        struct ID3D11UnorderedAccessViewData<ABI>
        {
            gfx::D3D11X_DESCRIPTOR_TEXTURE_VIEW m_Descriptor;
            void *m_pAllocationStart;
            uint32_t DescriptorSize;
            gfx::D3D11X_CERAM_RESOURCE_TYPE CeRamType;
        };
    }
    
    template<abi_t ABI>
    struct ID3D11UnorderedAccessView : gfx::ID3D11View<ABI>, details::ID3D11UnorderedAccessViewData<ABI>
    {
        virtual void GetDesc(D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11UnorderedAccessViewVtbl : gfx::ID3D11ViewVtbl<ABI>
    {
        void(*GetDesc)(void *, D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc);
    };
    
    namespace details
    {
        template<abi_t ABI>
        struct ID3D11DeviceContextData
        {
            gfx::ID3D11DeviceContextXVtbl<ABI> m_Function;
        };
        
        template<abi_t ABI>
        requires (ABI >= abi_t{6,2,10698,0} && ABI < abi_t{6,2,11274,0})
        struct ID3D11DeviceContextData<ABI>
        {
            union
            {
                uint8_t m_OutOfLineFlags = 1; // Let us use SetFastResources_Debug instead of MakeCeSpace
                uint32_t m_Reserved[16];
            };
            gfx::ID3D11DeviceContextXVtbl<ABI> m_Function;
        };
        
        template<abi_t ABI>
        requires (ABI >= abi_t{6,2,11274,0} && ABI < abi_t{6,2,11294,0})
        struct ID3D11DeviceContextData<ABI>
        {
            gfx::D3D11XTinyDevice m_TinyDevice;
            union
            {
                uint8_t m_OutOfLineFlags = 1; // Let us use SetFastResources_Debug instead of MakeCeSpace
                uint32_t m_Reserved[16];
            };
            gfx::ID3D11DeviceContextXVtbl<ABI> m_Function;
        };
        
        template<abi_t ABI>
        requires (ABI >= abi_t{6,2,11294,0})
        struct ID3D11DeviceContextData<ABI>
        {
            gfx::D3D11XTinyDevice m_TinyDevice;
            gfx::D3D11XShaderUserDataManagerDraw<ABI> m_ShaderUserDataManagerDraw;
            union
            {
                uint8_t m_OutOfLineFlags = 1; // Let us use SetFastResources_Debug instead of MakeCeSpace
                uint32_t m_Reserved[16];
            };
            gfx::ID3D11DeviceContextXVtbl<ABI> m_Function;
        };
    }
    
    template<abi_t ABI>
    struct ID3D11DeviceContext : gfx::ID3D11DeviceChild<ABI>, details::ID3D11DeviceContextData<ABI>
    {
        virtual void VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void PSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void PSSetShader(gfx::ID3D11PixelShader<ABI> *pPixelShader) = 0;
        virtual void PSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void VSSetShader(gfx::ID3D11VertexShader<ABI> *pVertexShader) = 0;
        virtual void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) = 0;
        virtual void Draw(UINT VertexCount, UINT StartVertexLocation) = 0;
        virtual HRESULT Map(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE *pMappedResource) = 0;
        virtual void Unmap(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource) = 0;
        virtual void PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void IASetInputLayout(ID3D11InputLayout *pInputLayout) = 0;
        virtual void IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppVertexBuffers, UINT const *pStrides, UINT const *pOffsets) = 0;
        virtual void IASetIndexBuffer(gfx::ID3D11Buffer<ABI> *pIndexBuffer, UINT HardwareIndexFormat, UINT Offset) = 0;
        virtual void DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation) = 0;
        virtual void DrawInstanced(UINT VertexCountPerInstance, UINT64 StartVertexLocationAndStartInstanceLocation, UINT InstanceCount) = 0;
        virtual void GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void GSSetShader(gfx::ID3D11GeometryShader<ABI> *pShader) = 0;
        virtual void IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY PrimitiveTopology) = 0;
        virtual void VSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void VSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void Begin(ID3D11Asynchronous *pAsync) = 0;
        virtual void End(ID3D11Asynchronous *pAsync) = 0;
        virtual HRESULT GetData(ID3D11Asynchronous *pAsync, void *pData, UINT DataSize, UINT GetDataFlags) = 0;
        virtual void SetPredication(ID3D11Predicate *pPredicate, BOOL PredicateValue) = 0;
        virtual void GSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void GSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void OMSetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI> *const *, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView) = 0;
        virtual void OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> *const *ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews, UINT const *pUAVInitialCounts) = 0;
        virtual void OMSetBlendState(gfx::ID3D11BlendState<ABI> *pBlendState, FLOAT const BlendFactor[4], UINT SampleMask) = 0;
        virtual void OMSetDepthStencilState(gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState, UINT StencilRef) = 0;
        virtual void SOSetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppSOTargets, UINT const *pOffsets) = 0;
        virtual void DrawAuto() = 0;
        virtual void DrawIndexedInstancedIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs) = 0;
        virtual void DrawInstancedIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs) = 0;
        virtual void Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ) = 0;
        virtual void DispatchIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs) = 0;
        virtual void RSSetState(gfx::ID3D11RasterizerState<ABI> *pRasterizerState) = 0;
        virtual void RSSetViewports(UINT NumViewports, D3D11_VIEWPORT const *pViewports) = 0;
        virtual void RSSetScissorRects(UINT NumRects, D3D11_RECT const *pRects) = 0;
        virtual void CopySubresourceRegion(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, D3D11_BOX const *pSrcBox) = 0;
        virtual void CopyResource(gfx::ID3D11Resource<ABI> *pDstResource, gfx::ID3D11Resource<ABI> *pSrcResource) = 0;
        virtual void UpdateSubresource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) = 0;
        virtual void CopyStructureCount(gfx::ID3D11Buffer<ABI> *pDstBuffer, UINT DstAlignedByteOffset, gfx::ID3D11UnorderedAccessView<ABI> *pSrcView) = 0;
        virtual void ClearRenderTargetView(gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView, FLOAT const ColorRGBA[4]) = 0;
        virtual void ClearUnorderedAccessViewUint(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView, UINT const Values[4]) = 0;
        virtual void ClearUnorderedAccessViewFloat(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView, FLOAT const Values[4]) = 0;
        virtual void ClearDepthStencilView(gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil) = 0;
        virtual void GenerateMips(gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void SetResourceMinLOD(gfx::ID3D11Resource<ABI> *pResource, FLOAT MinLOD) = 0;
        virtual FLOAT GetResourceMinLOD(gfx::ID3D11Resource<ABI> *pResource) = 0;
        virtual void ResolveSubresource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format) = 0;
        virtual void ExecuteCommandList(ID3D11CommandList *pCommandList, BOOL RestoreContextState) = 0;
        virtual void HSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void HSSetShader(gfx::ID3D11HullShader<ABI> *pHullShader) = 0;
        virtual void HSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void DSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void DSSetShader(gfx::ID3D11DomainShader<ABI> *pDomainShader) = 0;
        virtual void DSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void CSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews, UINT const *pUAVInitialCounts) = 0;
        virtual void CSSetShader(gfx::ID3D11ComputeShader<ABI> *pComputeShader) = 0;
        virtual void CSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void PSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void PSGetShader(gfx::ID3D11PixelShader<ABI> **ppPixelShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void PSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void VSGetShader(gfx::ID3D11VertexShader<ABI> **ppVertexShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void IAGetInputLayout(ID3D11InputLayout **ppInputLayout) = 0;
        virtual void IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppVertexBuffers, UINT *pStrides, UINT *pOffsets) = 0;
        virtual void IAGetIndexBuffer(gfx::ID3D11Buffer<ABI> **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset) = 0;
        virtual void GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void GSGetShader(gfx::ID3D11GeometryShader<ABI> **ppGeometryShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY *pTopology) = 0;
        virtual void VSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void VSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void GetPredication(ID3D11Predicate **ppPredicate, BOOL *pPredicateValue) = 0;
        virtual void GSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void GSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void OMGetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView) = 0;
        virtual void OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews) = 0;
        virtual void OMGetBlendState(gfx::ID3D11BlendState<ABI> **ppBlendState, FLOAT BlendFactor[4], UINT *pSampleMask) = 0;
        virtual void OMGetDepthStencilState(gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState, UINT *pStencilRef) = 0;
        virtual void SOGetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppSOTargets) = 0;
        virtual void RSGetState(gfx::ID3D11RasterizerState<ABI> **ppRasterizerState) = 0;
        virtual void RSGetViewports(UINT *pNumViewports, D3D11_VIEWPORT *pViewports) = 0;
        virtual void RSGetScissorRects(UINT *pNumRects, D3D11_RECT *pRects) = 0;
        virtual void HSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void HSGetShader(gfx::ID3D11HullShader<ABI> **ppHullShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void HSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void DSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void DSGetShader(gfx::ID3D11DomainShader<ABI> **ppDomainShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void DSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void CSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews) = 0;
        virtual void CSGetShader(gfx::ID3D11ComputeShader<ABI> **ppComputeShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void CSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void ClearState() = 0;
        virtual void Flush() = 0;
        virtual D3D11_DEVICE_CONTEXT_TYPE GetType() = 0;
        virtual UINT GetContextFlags() = 0;
        virtual HRESULT FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList **ppCommandList) = 0;
    };

    template <abi_t ABI>
        requires(ABI >= abi_t{6,2,11064,0} && ABI < abi_t{6,2,11294,0})
    struct ID3D11DeviceContext<ABI> : gfx::ID3D11DeviceChild<ABI>, details::ID3D11DeviceContextData<ABI>
    {
        virtual void VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void PSSetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void PSSetShader(gfx::ID3D11PixelShader<ABI> *pPixelShader) = 0;
        virtual void PSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                   gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void VSSetShader(gfx::ID3D11VertexShader<ABI> *pVertexShader) = 0;
        virtual void DrawIndexed(UINT64 StartIndexLocationAndIndexCount, INT BaseVertexLocation) = 0;
        virtual void Draw(UINT VertexCount, UINT StartVertexLocation) = 0;
        virtual HRESULT Map(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags,
                            D3D11_MAPPED_SUBRESOURCE *pMappedResource) = 0;
        virtual void Unmap(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource) = 0;
        virtual void PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void IASetInputLayout(ID3D11InputLayout *pInputLayout) = 0;
        virtual void IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppVertexBuffers,
                                        UINT const *pStrides, UINT const *pOffsets) = 0;
        virtual void IASetIndexBuffer(gfx::ID3D11Buffer<ABI> *pIndexBuffer, UINT HardwareIndexFormat, UINT Offset) = 0;
        virtual void DrawIndexedInstanced(UINT64 StartIndexLocationAndIndexCountPerInstance,
                                          UINT64 BaseVertexLocationAndStartInstanceLocation, UINT InstanceCount) = 0;
        virtual void DrawInstanced(UINT VertexCountPerInstance, UINT64 StartVertexLocationAndStartInstanceLocation,
                                   UINT InstanceCount) = 0;
        virtual void GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void GSSetShader(gfx::ID3D11GeometryShader<ABI> *pShader) = 0;
        virtual void IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY PrimitiveTopology) = 0;
        virtual void VSSetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void VSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                   gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void Begin(ID3D11Asynchronous *pAsync) = 0;
        virtual void End(ID3D11Asynchronous *pAsync) = 0;
        virtual HRESULT GetData(ID3D11Asynchronous *pAsync, void *pData, UINT DataSize, UINT GetDataFlags) = 0;
        virtual void SetPredication(ID3D11Predicate *pPredicate, BOOL PredicateValue) = 0;
        virtual void GSSetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void GSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                   gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void OMSetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI> *const *ppRTVs,
                                        gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView) = 0;
        virtual void OMSetRenderTargetsAndUnorderedAccessViews(
            UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> *const *ppRTVs,
            gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs,
            gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews, UINT const *pUAVInitialCounts) = 0;
        virtual void OMSetBlendState(gfx::ID3D11BlendState<ABI> *pBlendState, FLOAT const BlendFactor[4],
                                     UINT SampleMask) = 0;
        virtual void OMSetDepthStencilState(gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState, UINT StencilRef) = 0;
        virtual void SOSetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppSOTargets,
                                  UINT const *pOffsets) = 0;
        virtual void DrawAuto() = 0;
        virtual void DrawIndexedInstancedIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                                  UINT AlignedByteOffsetForArgs) = 0;
        virtual void DrawInstancedIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs) = 0;
        virtual void Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ) = 0;
        virtual void DispatchIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs) = 0;
        virtual void RSSetState(gfx::ID3D11RasterizerState<ABI> *pRasterizerState) = 0;
        virtual void RSSetViewports(UINT NumViewports, D3D11_VIEWPORT const *pViewports) = 0;
        virtual void RSSetScissorRects(UINT NumRects, D3D11_RECT const *pRects) = 0;
        virtual void CopySubresourceRegion(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, UINT DstX,
                                           UINT DstY, UINT DstZ, gfx::ID3D11Resource<ABI> *pSrcResource,
                                           UINT SrcSubresource, D3D11_BOX const *pSrcBox) = 0;
        virtual void CopyResource(gfx::ID3D11Resource<ABI> *pDstResource, gfx::ID3D11Resource<ABI> *pSrcResource) = 0;
        virtual void UpdateSubresource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                       D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch,
                                       UINT SrcDepthPitch) = 0;
        virtual void CopyStructureCount(gfx::ID3D11Buffer<ABI> *pDstBuffer, UINT DstAlignedByteOffset,
                                        gfx::ID3D11UnorderedAccessView<ABI> *pSrcView) = 0;
        virtual void ClearRenderTargetView(gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView,
                                           FLOAT const ColorRGBA[4]) = 0;
        virtual void ClearUnorderedAccessViewUint(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView,
                                                  UINT const Values[4]) = 0;
        virtual void ClearUnorderedAccessViewFloat(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView,
                                                   FLOAT const Values[4]) = 0;
        virtual void ClearDepthStencilView(gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT ClearFlags,
                                           FLOAT Depth, UINT8 Stencil) = 0;
        virtual void GenerateMips(gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void SetResourceMinLOD(gfx::ID3D11Resource<ABI> *pResource, FLOAT MinLOD) = 0;
        virtual FLOAT GetResourceMinLOD(gfx::ID3D11Resource<ABI> *pResource) = 0;
        virtual void ResolveSubresource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                        gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource,
                                        DXGI_FORMAT Format) = 0;
        virtual void ExecuteCommandList(ID3D11CommandList *pCommandList, BOOL RestoreContextState) = 0;
        virtual void HSSetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void HSSetShader(gfx::ID3D11HullShader<ABI> *pHullShader) = 0;
        virtual void HSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                   gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void DSSetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void DSSetShader(gfx::ID3D11DomainShader<ABI> *pDomainShader) = 0;
        virtual void DSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                   gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void CSSetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs,
                                               gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews,
                                               UINT const *pUAVInitialCounts) = 0;
        virtual void CSSetShader(gfx::ID3D11ComputeShader<ABI> *pComputeShader) = 0;
        virtual void CSSetSamplers(UINT StartSlot, UINT NumSamplers,
                                   gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void PSGetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void PSGetShader(gfx::ID3D11PixelShader<ABI> **ppPixelShader, ID3D11ClassInstance **ppClassInstances,
                                 UINT *pNumClassInstances) = 0;
        virtual void PSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void VSGetShader(gfx::ID3D11VertexShader<ABI> **ppVertexShader, ID3D11ClassInstance **ppClassInstances,
                                 UINT *pNumClassInstances) = 0;
        virtual void PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void IAGetInputLayout(ID3D11InputLayout **ppInputLayout) = 0;
        virtual void IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppVertexBuffers,
                                        UINT *pStrides, UINT *pOffsets) = 0;
        virtual void IAGetIndexBuffer(gfx::ID3D11Buffer<ABI> **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset) = 0;
        virtual void GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void GSGetShader(gfx::ID3D11GeometryShader<ABI> **ppGeometryShader,
                                 ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY *pTopology) = 0;
        virtual void VSGetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void VSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void GetPredication(ID3D11Predicate **ppPredicate, BOOL *pPredicateValue) = 0;
        virtual void GSGetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void GSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void OMGetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews,
                                        gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView) = 0;
        virtual void OMGetRenderTargetsAndUnorderedAccessViews(
            UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews,
            gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs,
            gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews) = 0;
        virtual void OMGetBlendState(gfx::ID3D11BlendState<ABI> **ppBlendState, FLOAT BlendFactor[4],
                                     UINT *pSampleMask) = 0;
        virtual void OMGetDepthStencilState(gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState,
                                            UINT *pStencilRef) = 0;
        virtual void SOGetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppSOTargets) = 0;
        virtual void RSGetState(gfx::ID3D11RasterizerState<ABI> **ppRasterizerState) = 0;
        virtual void RSGetViewports(UINT *pNumViewports, D3D11_VIEWPORT *pViewports) = 0;
        virtual void RSGetScissorRects(UINT *pNumRects, D3D11_RECT *pRects) = 0;
        virtual void HSGetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void HSGetShader(gfx::ID3D11HullShader<ABI> **ppHullShader, ID3D11ClassInstance **ppClassInstances,
                                 UINT *pNumClassInstances) = 0;
        virtual void HSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void DSGetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void DSGetShader(gfx::ID3D11DomainShader<ABI> **ppDomainShader, ID3D11ClassInstance **ppClassInstances,
                                 UINT *pNumClassInstances) = 0;
        virtual void DSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void CSGetShaderResources(UINT StartSlot, UINT NumViews,
                                          gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs,
                                               gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews) = 0;
        virtual void CSGetShader(gfx::ID3D11ComputeShader<ABI> **ppComputeShader,
                                 ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void CSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers,
                                          gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void ClearState() = 0;
        virtual void Flush() = 0;
        virtual D3D11_DEVICE_CONTEXT_TYPE GetType() = 0;
        virtual UINT GetContextFlags() = 0;
        virtual HRESULT FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList **ppCommandList) = 0;
    };

    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11294,0} && ABI < abi_t{ 6,2,13004,0 })
    struct ID3D11DeviceContext<ABI> : gfx::ID3D11DeviceChild<ABI>, details::ID3D11DeviceContextData<ABI>
    {
        virtual void VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void PSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void PSSetShader(gfx::ID3D11PixelShader<ABI> *pPixelShader) = 0;
        virtual void PSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void VSSetShader(gfx::ID3D11VertexShader<ABI> *pVertexShader) = 0;
        virtual void DrawIndexed(UINT64 StartIndexLocationAndIndexCount, INT BaseVertexLocation) = 0;
        virtual void Draw(UINT VertexCount, UINT StartVertexLocation) = 0;
        virtual HRESULT Map(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE *pMappedResource) = 0;
        virtual void Unmap(gfx::ID3D11Resource<ABI> *pResource, UINT Subresource) = 0;
        virtual void PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void IASetInputLayout(ID3D11InputLayout *pInputLayout) = 0;
        virtual void IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppVertexBuffers, UINT const *pStrides, UINT const *pOffsets) = 0;
        virtual void IASetIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer, UINT Offset) = 0;
        virtual void DrawIndexedInstanced(UINT64 StartIndexLocationAndIndexCountPerInstance, UINT64 BaseVertexLocationAndStartInstanceLocation, UINT InstanceCount) = 0;
        virtual void DrawInstanced(UINT VertexCountPerInstance, UINT64 StartVertexLocationAndStartInstanceLocation, UINT InstanceCount) = 0;
        virtual void GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void GSSetShader(gfx::ID3D11GeometryShader<ABI> *pShader) = 0;
        virtual void VSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void VSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void Begin(ID3D11Asynchronous *pAsync) = 0;
        virtual void End(ID3D11Asynchronous *pAsync) = 0;
        virtual HRESULT GetData(ID3D11Asynchronous *pAsync, void *pData, UINT DataSize, UINT GetDataFlags) = 0;
        virtual void SetPredication(ID3D11Predicate *pPredicate, BOOL PredicateValue) = 0;
        virtual void GSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void GSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void OMSetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI> *const *, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView) = 0;
        virtual void OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> *const *ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews, UINT const *pUAVInitialCounts) = 0;
        virtual void OMSetBlendState(gfx::ID3D11BlendState<ABI> *pBlendState, FLOAT const BlendFactor[4], UINT SampleMask) = 0;
        virtual void OMSetDepthStencilState(gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState, UINT StencilRef) = 0;
        virtual void SOSetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppSOTargets, UINT const *pOffsets) = 0;
        virtual void DrawAuto() = 0;
        virtual void DrawIndexedInstancedIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs) = 0;
        virtual void DrawInstancedIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs) = 0;
        virtual void Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ) = 0;
        virtual void DispatchIndirect(gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs) = 0;
        virtual void RSSetState(gfx::ID3D11RasterizerState<ABI> *pRasterizerState) = 0;
        virtual void RSSetViewports(UINT NumViewports, D3D11_VIEWPORT const *pViewports) = 0;
        virtual void RSSetScissorRects(UINT NumRects, D3D11_RECT const *pRects) = 0;
        virtual void CopySubresourceRegion(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, D3D11_BOX const *pSrcBox) = 0;
        virtual void CopyResource(gfx::ID3D11Resource<ABI> *pDstResource, gfx::ID3D11Resource<ABI> *pSrcResource) = 0;
        virtual void UpdateSubresource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) = 0;
        virtual void CopyStructureCount(gfx::ID3D11Buffer<ABI> *pDstBuffer, UINT DstAlignedByteOffset, gfx::ID3D11UnorderedAccessView<ABI> *pSrcView) = 0;
        virtual void ClearRenderTargetView(gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView, FLOAT const ColorRGBA[4]) = 0;
        virtual void ClearUnorderedAccessViewUint(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView, UINT const Values[4]) = 0;
        virtual void ClearUnorderedAccessViewFloat(gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView, FLOAT const Values[4]) = 0;
        virtual void ClearDepthStencilView(gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil) = 0;
        virtual void GenerateMips(gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void SetResourceMinLOD(gfx::ID3D11Resource<ABI> *pResource, FLOAT MinLOD) = 0;
        virtual FLOAT GetResourceMinLOD(gfx::ID3D11Resource<ABI> *pResource) = 0;
        virtual void ResolveSubresource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format) = 0;
        virtual void ExecuteCommandList(ID3D11CommandList *pCommandList, BOOL RestoreContextState) = 0;
        virtual void HSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void HSSetShader(gfx::ID3D11HullShader<ABI> *pHullShader) = 0;
        virtual void HSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void DSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void DSSetShader(gfx::ID3D11DomainShader<ABI> *pDomainShader) = 0;
        virtual void DSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void CSSetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews) = 0;
        virtual void CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews, UINT const *pUAVInitialCounts) = 0;
        virtual void CSSetShader(gfx::ID3D11ComputeShader<ABI> *pComputeShader) = 0;
        virtual void CSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers) = 0;
        virtual void CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers) = 0;
        virtual void VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void PSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void PSGetShader(gfx::ID3D11PixelShader<ABI> **ppPixelShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void PSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void VSGetShader(gfx::ID3D11VertexShader<ABI> **ppVertexShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void IAGetInputLayout(ID3D11InputLayout **ppInputLayout) = 0;
        virtual void IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppVertexBuffers, UINT *pStrides, UINT *pOffsets) = 0;
        virtual void IAGetIndexBuffer(gfx::ID3D11Buffer<ABI> **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset) = 0;
        virtual void GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void GSGetShader(gfx::ID3D11GeometryShader<ABI> **ppGeometryShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY *pTopology) = 0;
        virtual void VSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void VSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void GetPredication(ID3D11Predicate **ppPredicate, BOOL *pPredicateValue) = 0;
        virtual void GSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void GSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void OMGetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView) = 0;
        virtual void OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews) = 0;
        virtual void OMGetBlendState(gfx::ID3D11BlendState<ABI> **ppBlendState, FLOAT BlendFactor[4], UINT *pSampleMask) = 0;
        virtual void OMGetDepthStencilState(gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState, UINT *pStencilRef) = 0;
        virtual void SOGetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppSOTargets) = 0;
        virtual void RSGetState(gfx::ID3D11RasterizerState<ABI> **ppRasterizerState) = 0;
        virtual void RSGetViewports(UINT *pNumViewports, D3D11_VIEWPORT *pViewports) = 0;
        virtual void RSGetScissorRects(UINT *pNumRects, D3D11_RECT *pRects) = 0;
        virtual void HSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void HSGetShader(gfx::ID3D11HullShader<ABI> **ppHullShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void HSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void DSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void DSGetShader(gfx::ID3D11DomainShader<ABI> **ppDomainShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void DSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void CSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews) = 0;
        virtual void CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews) = 0;
        virtual void CSGetShader(gfx::ID3D11ComputeShader<ABI> **ppComputeShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances) = 0;
        virtual void CSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers) = 0;
        virtual void CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers) = 0;
        virtual void ClearState() = 0;
        virtual void Flush() = 0;
        virtual D3D11_DEVICE_CONTEXT_TYPE GetType() = 0;
        virtual UINT GetContextFlags() = 0;
        virtual HRESULT FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList **ppCommandList) = 0;
    };

    template<abi_t ABI>
        requires (ABI >= abi_t{ 6,2,13004,0 })
    struct ID3D11DeviceContext<ABI> : gfx::ID3D11DeviceChild<ABI>, details::ID3D11DeviceContextData<ABI>
    {
        virtual void VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>* const* ppConstantBuffers) = 0;
        virtual void PSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader) = 0;
        virtual void PSSetShader(gfx::ID3D11PixelShader<ABI>* pPixelShader) = 0;
        virtual void PSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>* const* ppSamplers) = 0;
        virtual void VSSetShader(gfx::ID3D11VertexShader<ABI>* pVertexShader) = 0;
        virtual void DrawIndexed(UINT64 StartIndexLocationAndIndexCount, INT BaseVertexLocation) = 0;
        virtual void Draw(UINT VertexCount, UINT StartVertexLocation) = 0;
        virtual HRESULT Map(gfx::ID3D11Resource<ABI>* pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE* pMappedResource) = 0;
        virtual void Unmap(gfx::ID3D11Resource<ABI>* pResource, UINT Subresource) = 0;
        virtual void PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>* const* ppConstantBuffers) = 0;
        virtual void IASetInputLayout(ID3D11InputLayout* pInputLayout) = 0;
        virtual void IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>* const* ppVertexBuffers, UINT const* pStrides, UINT const* pOffsets) = 0;
        virtual void IASetIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI>* pIndexBuffer, UINT Offset) = 0;
        virtual void DrawIndexedInstanced(UINT64 StartIndexLocationAndIndexCountPerInstance, UINT64 BaseVertexLocationAndStartInstanceLocation, UINT InstanceCount) = 0;
        virtual void DrawInstanced(UINT VertexCountPerInstance, UINT64 StartVertexLocationAndStartInstanceLocation, UINT InstanceCount) = 0;
        virtual void GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>* const* ppConstantBuffers) = 0;
        virtual void GSSetShader(gfx::ID3D11GeometryShader<ABI>* pShader) = 0;
        virtual void VSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader) = 0;
        virtual void VSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>* const* ppSamplers) = 0;
        virtual void Begin(ID3D11Asynchronous* pAsync) = 0;
        virtual void End(ID3D11Asynchronous* pAsync) = 0;
        virtual HRESULT GetData(ID3D11Asynchronous* pAsync, void* pData, UINT DataSize, UINT GetDataFlags) = 0;
        virtual void SetPredication(ID3D11Predicate* pPredicate, BOOL PredicateValue) = 0;
        virtual void GSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader) = 0;
        virtual void GSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>* const* ppSamplers) = 0;
        virtual void OMSetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI>* const* ppRTVs, gfx::ID3D11DepthStencilView<ABI>* pDepthStencilView) = 0;
        virtual void OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI>* const* ppRTVs, gfx::ID3D11DepthStencilView<ABI>* pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI>* const* ppUnorderedAccessViews, UINT const* pUAVInitialCounts) = 0;
        virtual void OMSetBlendState(gfx::ID3D11BlendState<ABI>* pBlendState, FLOAT const BlendFactor[4], UINT SampleMask) = 0;
        virtual void OMSetDepthStencilState(gfx::ID3D11DepthStencilState<ABI>* pDepthStencilState, UINT StencilRef) = 0;
        virtual void SOSetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI>* const* ppSOTargets, UINT const* pOffsets) = 0;
        virtual void DrawAuto() = 0;
        virtual void DrawIndexedInstancedIndirect(gfx::ID3D11Buffer<ABI>* pBufferForArgs, UINT AlignedByteOffsetForArgs) = 0;
        virtual void DrawInstancedIndirect(gfx::ID3D11Buffer<ABI>* pBufferForArgs, UINT AlignedByteOffsetForArgs) = 0;
        virtual void Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ) = 0;
        virtual void DispatchIndirect(gfx::ID3D11Buffer<ABI>* pBufferForArgs, UINT AlignedByteOffsetForArgs) = 0;
        virtual void RSSetState(gfx::ID3D11RasterizerState<ABI>* pRasterizerState) = 0;
        virtual void RSSetViewports(UINT NumViewports, D3D11_VIEWPORT const* pViewports) = 0;
        virtual void RSSetScissorRects(UINT NumRects, D3D11_RECT const* pRects) = 0;
        virtual void CopySubresourceRegion(gfx::ID3D11Resource<ABI>* pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, gfx::ID3D11Resource<ABI>* pSrcResource, UINT SrcSubresource, D3D11_BOX const* pSrcBox) = 0;
        virtual void CopyResource(gfx::ID3D11Resource<ABI>* pDstResource, gfx::ID3D11Resource<ABI>* pSrcResource) = 0;
        virtual void UpdateSubresource(gfx::ID3D11Resource<ABI>* pDstResource, UINT DstSubresource, D3D11_BOX const* pDstBox, void const* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) = 0;
        virtual void CopyStructureCount(gfx::ID3D11Buffer<ABI>* pDstBuffer, UINT DstAlignedByteOffset, gfx::ID3D11UnorderedAccessView<ABI>* pSrcView) = 0;
        virtual void ClearRenderTargetView(gfx::ID3D11RenderTargetView<ABI>* pRenderTargetView, FLOAT const ColorRGBA[4]) = 0;
        virtual void ClearUnorderedAccessViewUint(gfx::ID3D11UnorderedAccessView<ABI>* pUnorderedAccessView, UINT const Values[4]) = 0;
        virtual void ClearUnorderedAccessViewFloat(gfx::ID3D11UnorderedAccessView<ABI>* pUnorderedAccessView, FLOAT const Values[4]) = 0;
        virtual void ClearDepthStencilView(gfx::ID3D11DepthStencilView<ABI>* pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil) = 0;
        virtual void GenerateMips(gfx::ID3D11ShaderResourceView<ABI>* pShaderResourceView) = 0;
        virtual void SetResourceMinLOD(gfx::ID3D11Resource<ABI>* pResource, FLOAT MinLOD) = 0;
        virtual FLOAT GetResourceMinLOD(gfx::ID3D11Resource<ABI>* pResource) = 0;
        virtual void ResolveSubresource(gfx::ID3D11Resource<ABI>* pDstResource, UINT DstSubresource, gfx::ID3D11Resource<ABI>* pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format) = 0;
        virtual void ExecuteCommandList(ID3D11CommandList* pCommandList, BOOL RestoreContextState) = 0;
        virtual void HSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader) = 0;
        virtual void HSSetShader(gfx::ID3D11HullShader<ABI>* pHullShader) = 0;
        virtual void HSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>* const* ppSamplers) = 0;
        virtual void HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>* const* ppConstantBuffers) = 0;
        virtual void DSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader) = 0;
        virtual void DSSetShader(gfx::ID3D11DomainShader<ABI>* pDomainShader) = 0;
        virtual void DSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>* const* ppSamplers) = 0;
        virtual void DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>* const* ppConstantBuffers) = 0;
        virtual void CSSetShaderResources(gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader) = 0;
        virtual void CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI>* const* ppUnorderedAccessViews, UINT const* pUAVInitialCounts) = 0;
        virtual void CSSetShader(gfx::ID3D11ComputeShader<ABI>* pComputeShader) = 0;
        virtual void CSSetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>* const* ppSamplers) = 0;
        virtual void CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>* const* ppConstantBuffers) = 0;
        virtual void VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers) = 0;
        virtual void PSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews) = 0;
        virtual void PSGetShader(gfx::ID3D11PixelShader<ABI>** ppPixelShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) = 0;
        virtual void PSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers) = 0;
        virtual void VSGetShader(gfx::ID3D11VertexShader<ABI>** ppVertexShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) = 0;
        virtual void PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers) = 0;
        virtual void IAGetInputLayout(ID3D11InputLayout** ppInputLayout) = 0;
        virtual void IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppVertexBuffers, UINT* pStrides, UINT* pOffsets) = 0;
        virtual void IAGetIndexBuffer(gfx::ID3D11Buffer<ABI>** pIndexBuffer, DXGI_FORMAT* Format, UINT* Offset) = 0;
        virtual void GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers) = 0;
        virtual void GSGetShader(gfx::ID3D11GeometryShader<ABI>** ppGeometryShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) = 0;
        virtual void IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY* pTopology) = 0;
        virtual void VSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews) = 0;
        virtual void VSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers) = 0;
        virtual void GetPredication(ID3D11Predicate** ppPredicate, BOOL* pPredicateValue) = 0;
        virtual void GSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews) = 0;
        virtual void GSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers) = 0;
        virtual void OMGetRenderTargets(UINT NumViews, gfx::ID3D11RenderTargetView<ABI>** ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI>** ppDepthStencilView) = 0;
        virtual void OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI>** ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI>** ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI>** ppUnorderedAccessViews) = 0;
        virtual void OMGetBlendState(gfx::ID3D11BlendState<ABI>** ppBlendState, FLOAT BlendFactor[4], UINT* pSampleMask) = 0;
        virtual void OMGetDepthStencilState(gfx::ID3D11DepthStencilState<ABI>** ppDepthStencilState, UINT* pStencilRef) = 0;
        virtual void SOGetTargets(UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppSOTargets) = 0;
        virtual void RSGetState(gfx::ID3D11RasterizerState<ABI>** ppRasterizerState) = 0;
        virtual void RSGetViewports(UINT* pNumViewports, D3D11_VIEWPORT* pViewports) = 0;
        virtual void RSGetScissorRects(UINT* pNumRects, D3D11_RECT* pRects) = 0;
        virtual void HSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews) = 0;
        virtual void HSGetShader(gfx::ID3D11HullShader<ABI>** ppHullShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) = 0;
        virtual void HSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers) = 0;
        virtual void HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers) = 0;
        virtual void DSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews) = 0;
        virtual void DSGetShader(gfx::ID3D11DomainShader<ABI>** ppDomainShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) = 0;
        virtual void DSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers) = 0;
        virtual void DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers) = 0;
        virtual void CSGetShaderResources(UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI>** ppShaderResourceViews) = 0;
        virtual void CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI>** ppUnorderedAccessViews) = 0;
        virtual void CSGetShader(gfx::ID3D11ComputeShader<ABI>** ppComputeShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) = 0;
        virtual void CSGetSamplers(UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI>** ppSamplers) = 0;
        virtual void CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI>** ppConstantBuffers) = 0;
        virtual void ClearState() = 0;
        virtual void Flush() = 0;
        virtual D3D11_DEVICE_CONTEXT_TYPE GetType() = 0;
        virtual UINT GetContextFlags() = 0;
        virtual HRESULT FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList** ppCommandList) = 0;
    };
    
    template <abi_t ABI> struct ID3D11DeviceContextVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void (*VSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*PSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*PSSetShader)(void *, gfx::ID3D11PixelShader<ABI> *pPixelShader);
        void (*PSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*VSSetShader)(void *, gfx::ID3D11VertexShader<ABI> *pVertexShader);
        void (*DrawIndexed)(void *, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
        void (*Draw)(void *, UINT VertexCount, UINT StartVertexLocation);
        HRESULT (*Map)(void *, gfx::ID3D11Resource<ABI> *pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags,
                       D3D11_MAPPED_SUBRESOURCE *pMappedResource);
        void (*Unmap)(void *, gfx::ID3D11Resource<ABI> *pResource, UINT Subresource);
        void (*PSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*IASetInputLayout)(void *, ID3D11InputLayout *pInputLayout);
        void (*IASetVertexBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                   gfx::ID3D11Buffer<ABI> *const *ppVertexBuffers, UINT const *pStrides,
                                   UINT const *pOffsets);
        void (*IASetIndexBuffer)(void *, gfx::ID3D11Buffer<ABI> *pIndexBuffer, UINT HardwareIndexFormat, UINT Offset);
        void (*DrawIndexedInstanced)(void *, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation,
                                     INT BaseVertexLocation, UINT StartInstanceLocation);
        void (*DrawInstanced)(void *, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation,
                              UINT StartInstanceLocation);
        void (*GSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*GSSetShader)(void *, gfx::ID3D11GeometryShader<ABI> *pShader);
        void (*IASetPrimitiveTopology)(void *, D3D_PRIMITIVE_TOPOLOGY PrimitiveTopology);
        void (*VSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*VSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*Begin)(void *, ID3D11Asynchronous *pAsync);
        void (*End)(void *, ID3D11Asynchronous *pAsync);
        HRESULT (*GetData)(void *, ID3D11Asynchronous *pAsync, void *pData, UINT DataSize, UINT GetDataFlags);
        void (*SetPredication)(void *, ID3D11Predicate *pPredicate, BOOL PredicateValue);
        void (*GSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*GSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*OMSetRenderTargets)(void *, UINT NumViews, gfx::ID3D11RenderTargetView<ABI> *const *ppRTVs,
                                   gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView);
        void (*OMSetRenderTargetsAndUnorderedAccessViews)(
            void *, UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> *const *ppRTVs,
            gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs,
            gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews, UINT const *pUAVInitialCounts);
        void (*OMSetBlendState)(void *, gfx::ID3D11BlendState<ABI> *pBlendState, FLOAT const BlendFactor[4],
                                UINT SampleMask);
        void (*OMSetDepthStencilState)(void *, gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState, UINT StencilRef);
        void (*SOSetTargets)(void *, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppSOTargets, UINT const *pOffsets);
        void (*DrawAuto)(void *);
        void (*DrawIndexedInstancedIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                             UINT AlignedByteOffsetForArgs);
        void (*DrawInstancedIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
        void (*Dispatch)(void *, UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ);
        void (*DispatchIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
        void (*RSSetState)(void *, gfx::ID3D11RasterizerState<ABI> *pRasterizerState);
        void (*RSSetViewports)(void *, UINT NumViewports, D3D11_VIEWPORT const *pViewports);
        void (*RSSetScissorRects)(void *, UINT NumRects, D3D11_RECT const *pRects);
        void (*CopySubresourceRegion)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, UINT DstX,
                                      UINT DstY, UINT DstZ, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource,
                                      D3D11_BOX const *pSrcBox);
        void (*CopyResource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, gfx::ID3D11Resource<ABI> *pSrcResource);
        void (*UpdateSubresource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                  D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch);
        void (*CopyStructureCount)(void *, gfx::ID3D11Buffer<ABI> *pDstBuffer, UINT DstAlignedByteOffset,
                                   gfx::ID3D11UnorderedAccessView<ABI> *pSrcView);
        void (*ClearRenderTargetView)(void *, gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView,
                                      FLOAT const ColorRGBA[4]);
        void (*ClearUnorderedAccessViewUint)(void *, gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView,
                                             UINT const Values[4]);
        void (*ClearUnorderedAccessViewFloat)(void *, gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView,
                                              FLOAT const Values[4]);
        void (*ClearDepthStencilView)(void *, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT ClearFlags,
                                      FLOAT Depth, UINT8 Stencil);
        void (*GenerateMips)(void *, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void (*SetResourceMinLOD)(void *, gfx::ID3D11Resource<ABI> *pResource, FLOAT MinLOD);
        FLOAT (*GetResourceMinLOD)(void *, gfx::ID3D11Resource<ABI> *pResource);
        void (*ResolveSubresource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                   gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format);
        void (*ExecuteCommandList)(void *, ID3D11CommandList *pCommandList, BOOL RestoreContextState);
        void (*HSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*HSSetShader)(void *, gfx::ID3D11HullShader<ABI> *pHullShader);
        void (*HSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*HSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*DSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*DSSetShader)(void *, gfx::ID3D11DomainShader<ABI> *pDomainShader);
        void (*DSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*DSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*CSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*CSSetUnorderedAccessViews)(void *, UINT StartSlot, UINT NumUAVs,
                                          gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews,
                                          UINT const *pUAVInitialCounts);
        void (*CSSetShader)(void *, gfx::ID3D11ComputeShader<ABI> *pComputeShader);
        void (*CSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*CSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*VSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*PSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*PSGetShader)(void *, gfx::ID3D11PixelShader<ABI> **ppPixelShader, ID3D11ClassInstance **ppClassInstances,
                            UINT *pNumClassInstances);
        void (*PSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*VSGetShader)(void *, gfx::ID3D11VertexShader<ABI> **ppVertexShader,
                            ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void (*PSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*IAGetInputLayout)(void *, ID3D11InputLayout **ppInputLayout);
        void (*IAGetVertexBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppVertexBuffers,
                                   UINT *pStrides, UINT *pOffsets);
        void (*IAGetIndexBuffer)(void *, gfx::ID3D11Buffer<ABI> **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset);
        void (*GSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*GSGetShader)(void *, gfx::ID3D11GeometryShader<ABI> **ppGeometryShader,
                            ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void (*IAGetPrimitiveTopology)(void *, D3D11_PRIMITIVE_TOPOLOGY *pTopology);
        void (*VSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*VSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*GetPredication)(void *, ID3D11Predicate **ppPredicate, BOOL *pPredicateValue);
        void (*GSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*GSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*OMGetRenderTargets)(void *, UINT NumViews, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews,
                                   gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView);
        void (*OMGetRenderTargetsAndUnorderedAccessViews)(void *, UINT NumRTVs,
                                                          gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews,
                                                          gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView,
                                                          UINT UAVStartSlot, UINT NumUAVs,
                                                          gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews);
        void (*OMGetBlendState)(void *, gfx::ID3D11BlendState<ABI> **ppBlendState, FLOAT BlendFactor[4],
                                UINT *pSampleMask);
        void (*OMGetDepthStencilState)(void *, gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState,
                                       UINT *pStencilRef);
        void (*SOGetTargets)(void *, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppSOTargets);
        void (*RSGetState)(void *, gfx::ID3D11RasterizerState<ABI> **ppRasterizerState);
        void (*RSGetViewports)(void *, UINT *pNumViewports, D3D11_VIEWPORT *pViewports);
        void (*RSGetScissorRects)(void *, UINT *pNumRects, D3D11_RECT *pRects);
        void (*HSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*HSGetShader)(void *, gfx::ID3D11HullShader<ABI> **ppHullShader, ID3D11ClassInstance **ppClassInstances,
                            UINT *pNumClassInstances);
        void (*HSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*HSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*DSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*DSGetShader)(void *, gfx::ID3D11DomainShader<ABI> **ppDomainShader,
                            ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void (*DSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*DSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*CSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*CSGetUnorderedAccessViews)(void *, UINT StartSlot, UINT NumUAVs,
                                          gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews);
        void (*CSGetShader)(void *, gfx::ID3D11ComputeShader<ABI> **ppComputeShader,
                            ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void (*CSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*CSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*ClearState)(void *);
        void (*Flush)(void *);
        D3D11_DEVICE_CONTEXT_TYPE (*GetType)(void *);
        UINT (*GetContextFlags)(void *);
        HRESULT (*FinishCommandList)(void *, BOOL RestoreDeferredContextState,
                                     ID3D11CommandList **ppCommandList);
    };

    template <abi_t ABI>
        requires(ABI >= abi_t{6,2,11064,0} && ABI < abi_t{6,2,11294,0})
    struct ID3D11DeviceContextVtbl<ABI> : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void (*VSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*PSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*PSSetShader)(void *, gfx::ID3D11PixelShader<ABI> *pPixelShader);
        void (*PSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*VSSetShader)(void *, gfx::ID3D11VertexShader<ABI> *pVertexShader);
        void (*DrawIndexed)(void *, UINT64 StartIndexLocationAndIndexCount, INT BaseVertexLocation);
        void (*Draw)(void *, UINT VertexCount, UINT StartVertexLocation);
        HRESULT (*Map)(void *, gfx::ID3D11Resource<ABI> *pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags,
                       D3D11_MAPPED_SUBRESOURCE *pMappedResource);
        void (*Unmap)(void *, gfx::ID3D11Resource<ABI> *pResource, UINT Subresource);
        void (*PSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*IASetInputLayout)(void *, ID3D11InputLayout *pInputLayout);
        void (*IASetVertexBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                   gfx::ID3D11Buffer<ABI> *const *ppVertexBuffers, UINT const *pStrides,
                                   UINT const *pOffsets);
        void (*IASetIndexBuffer)(void *, gfx::ID3D11Buffer<ABI> *pIndexBuffer, UINT HardwareIndexFormat, UINT Offset);
        void (*DrawIndexedInstanced)(void *, UINT64 StartIndexLocationAndIndexCountPerInstance,
                                     UINT64 BaseVertexLocationAndStartInstanceLocation, UINT InstanceCount);
        void (*DrawInstanced)(void *, UINT VertexCountPerInstance, UINT64 StartVertexLocationAndStartInstanceLocation,
                              UINT InstanceCount);
        void (*GSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*GSSetShader)(void *, gfx::ID3D11GeometryShader<ABI> *pShader);
        void (*IASetPrimitiveTopology)(void *, D3D_PRIMITIVE_TOPOLOGY PrimitiveTopology);
        void (*VSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*VSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*Begin)(void *, ID3D11Asynchronous *pAsync);
        void (*End)(void *, ID3D11Asynchronous *pAsync);
        HRESULT (*GetData)(void *, ID3D11Asynchronous *pAsync, void *pData, UINT DataSize, UINT GetDataFlags);
        void (*SetPredication)(void *, ID3D11Predicate *pPredicate, BOOL PredicateValue);
        void (*GSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*GSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*OMSetRenderTargets)(void *, UINT NumViews, gfx::ID3D11RenderTargetView<ABI> *const *ppRTVs,
                                   gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView);
        void (*OMSetRenderTargetsAndUnorderedAccessViews)(
            void *, UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> *const *ppRTVs,
            gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs,
            gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews, UINT const *pUAVInitialCounts);
        void (*OMSetBlendState)(void *, gfx::ID3D11BlendState<ABI> *pBlendState, FLOAT const BlendFactor[4],
                                UINT SampleMask);
        void (*OMSetDepthStencilState)(void *, gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState, UINT StencilRef);
        void (*SOSetTargets)(void *, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppSOTargets, UINT const *pOffsets);
        void (*DrawAuto)(void *);
        void (*DrawIndexedInstancedIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs,
                                             UINT AlignedByteOffsetForArgs);
        void (*DrawInstancedIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
        void (*Dispatch)(void *, UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ);
        void (*DispatchIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
        void (*RSSetState)(void *, gfx::ID3D11RasterizerState<ABI> *pRasterizerState);
        void (*RSSetViewports)(void *, UINT NumViewports, D3D11_VIEWPORT const *pViewports);
        void (*RSSetScissorRects)(void *, UINT NumRects, D3D11_RECT const *pRects);
        void (*CopySubresourceRegion)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, UINT DstX,
                                      UINT DstY, UINT DstZ, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource,
                                      D3D11_BOX const *pSrcBox);
        void (*CopyResource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, gfx::ID3D11Resource<ABI> *pSrcResource);
        void (*UpdateSubresource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                  D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch);
        void (*CopyStructureCount)(void *, gfx::ID3D11Buffer<ABI> *pDstBuffer, UINT DstAlignedByteOffset,
                                   gfx::ID3D11UnorderedAccessView<ABI> *pSrcView);
        void (*ClearRenderTargetView)(void *, gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView,
                                      FLOAT const ColorRGBA[4]);
        void (*ClearUnorderedAccessViewUint)(void *, gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView,
                                             UINT const Values[4]);
        void (*ClearUnorderedAccessViewFloat)(void *, gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView,
                                              FLOAT const Values[4]);
        void (*ClearDepthStencilView)(void *, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT ClearFlags,
                                      FLOAT Depth, UINT8 Stencil);
        void (*GenerateMips)(void *, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void (*SetResourceMinLOD)(void *, gfx::ID3D11Resource<ABI> *pResource, FLOAT MinLOD);
        FLOAT (*GetResourceMinLOD)(void *, gfx::ID3D11Resource<ABI> *pResource);
        void (*ResolveSubresource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource,
                                   gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format);
        void (*ExecuteCommandList)(void *, ID3D11CommandList *pCommandList, BOOL RestoreContextState);
        void (*HSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*HSSetShader)(void *, gfx::ID3D11HullShader<ABI> *pHullShader);
        void (*HSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*HSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*DSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*DSSetShader)(void *, gfx::ID3D11DomainShader<ABI> *pDomainShader);
        void (*DSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*DSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*CSSetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void (*CSSetUnorderedAccessViews)(void *, UINT StartSlot, UINT NumUAVs,
                                          gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews,
                                          UINT const *pUAVInitialCounts);
        void (*CSSetShader)(void *, gfx::ID3D11ComputeShader<ABI> *pComputeShader);
        void (*CSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers,
                              gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void (*CSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void (*VSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*PSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*PSGetShader)(void *, gfx::ID3D11PixelShader<ABI> **ppPixelShader, ID3D11ClassInstance **ppClassInstances,
                            UINT *pNumClassInstances);
        void (*PSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*VSGetShader)(void *, gfx::ID3D11VertexShader<ABI> **ppVertexShader,
                            ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void (*PSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*IAGetInputLayout)(void *, ID3D11InputLayout **ppInputLayout);
        void (*IAGetVertexBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppVertexBuffers,
                                   UINT *pStrides, UINT *pOffsets);
        void (*IAGetIndexBuffer)(void *, gfx::ID3D11Buffer<ABI> **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset);
        void (*GSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*GSGetShader)(void *, gfx::ID3D11GeometryShader<ABI> **ppGeometryShader,
                            ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void (*IAGetPrimitiveTopology)(void *, D3D11_PRIMITIVE_TOPOLOGY *pTopology);
        void (*VSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*VSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*GetPredication)(void *, ID3D11Predicate **ppPredicate, BOOL *pPredicateValue);
        void (*GSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*GSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*OMGetRenderTargets)(void *, UINT NumViews, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews,
                                   gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView);
        void (*OMGetRenderTargetsAndUnorderedAccessViews)(void *, UINT NumRTVs,
                                                          gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews,
                                                          gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView,
                                                          UINT UAVStartSlot, UINT NumUAVs,
                                                          gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews);
        void (*OMGetBlendState)(void *, gfx::ID3D11BlendState<ABI> **ppBlendState, FLOAT BlendFactor[4],
                                UINT *pSampleMask);
        void (*OMGetDepthStencilState)(void *, gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState,
                                       UINT *pStencilRef);
        void (*SOGetTargets)(void *, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppSOTargets);
        void (*RSGetState)(void *, gfx::ID3D11RasterizerState<ABI> **ppRasterizerState);
        void (*RSGetViewports)(void *, UINT *pNumViewports, D3D11_VIEWPORT *pViewports);
        void (*RSGetScissorRects)(void *, UINT *pNumRects, D3D11_RECT *pRects);
        void (*HSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*HSGetShader)(void *, gfx::ID3D11HullShader<ABI> **ppHullShader, ID3D11ClassInstance **ppClassInstances,
                            UINT *pNumClassInstances);
        void (*HSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*HSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*DSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*DSGetShader)(void *, gfx::ID3D11DomainShader<ABI> **ppDomainShader,
                            ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void (*DSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*DSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*CSGetShaderResources)(void *, UINT StartSlot, UINT NumViews,
                                     gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void (*CSGetUnorderedAccessViews)(void *, UINT StartSlot, UINT NumUAVs,
                                          gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews);
        void (*CSGetShader)(void *, gfx::ID3D11ComputeShader<ABI> **ppComputeShader,
                            ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void (*CSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void (*CSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers,
                                     gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void (*ClearState)(void *);
        void (*Flush)(void *);
        D3D11_DEVICE_CONTEXT_TYPE (*GetType)(void *);
        UINT (*GetContextFlags)(void *);
        HRESULT (*FinishCommandList)(void *, BOOL RestoreDeferredContextState, ID3D11CommandList **ppCommandList);
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11294,0} && ABI < abi_t{ 6,2,13004,0 })
    struct ID3D11DeviceContextVtbl<ABI> : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void(*VSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*PSSetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void(*PSSetShader)(void *, gfx::ID3D11PixelShader<ABI> *pPixelShader);
        void(*PSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*VSSetShader)(void *, gfx::ID3D11VertexShader<ABI> *pVertexShader);
        void(*DrawIndexed)(void *, UINT64 StartIndexLocationAndIndexCount, INT BaseVertexLocation);
        void(*Draw)(void *, UINT VertexCount, UINT StartVertexLocation);
        HRESULT(*Map)(void *, gfx::ID3D11Resource<ABI> *pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE *pMappedResource);
        void(*Unmap)(void *, gfx::ID3D11Resource<ABI> *pResource, UINT Subresource);
        void(*PSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*IASetInputLayout)(void *, ID3D11InputLayout *pInputLayout);
        void(*IASetVertexBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppVertexBuffers, UINT const *pStrides, UINT const *pOffsets);
        void(*IASetIndexBuffer)(void *, UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer, UINT Offset);
        void(*DrawIndexedInstanced)(void *, UINT64 StartIndexLocationAndIndexCountPerInstance, UINT64 BaseVertexLocationAndStartInstanceLocation, UINT InstanceCount);
        void(*DrawInstanced)(void *, UINT VertexCountPerInstance, UINT64 StartVertexLocationAndStartInstanceLocation, UINT InstanceCount);
        void(*GSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*GSSetShader)(void *, gfx::ID3D11GeometryShader<ABI> *pShader);
        void(*VSSetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void(*VSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*Begin)(void *, ID3D11Asynchronous *pAsync);
        void(*End)(void *, ID3D11Asynchronous *pAsync);
        HRESULT(*GetData)(void *, ID3D11Asynchronous *pAsync, void *pData, UINT DataSize, UINT GetDataFlags);
        void(*SetPredication)(void *, ID3D11Predicate *pPredicate, BOOL PredicateValue);
        void(*GSSetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void(*GSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*OMSetRenderTargets)(void *, UINT NumViews, gfx::ID3D11RenderTargetView<ABI> *const *, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView);
        void(*OMSetRenderTargetsAndUnorderedAccessViews)(void *, UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> *const *ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews, UINT const *pUAVInitialCounts);
        void(*OMSetBlendState)(void *, gfx::ID3D11BlendState<ABI> *pBlendState, FLOAT const BlendFactor[4], UINT SampleMask);
        void(*OMSetDepthStencilState)(void *, gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState, UINT StencilRef);
        void(*SOSetTargets)(void *, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppSOTargets, UINT const *pOffsets);
        void(*DrawAuto)(void *);
        void(*DrawIndexedInstancedIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
        void(*DrawInstancedIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
        void(*Dispatch)(void *, UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ);
        void(*DispatchIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
        void(*RSSetState)(void *, gfx::ID3D11RasterizerState<ABI> *pRasterizerState);
        void(*RSSetViewports)(void *, UINT NumViewports, D3D11_VIEWPORT const *pViewports);
        void(*RSSetScissorRects)(void *, UINT NumRects, D3D11_RECT const *pRects);
        void(*CopySubresourceRegion)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, D3D11_BOX const *pSrcBox);
        void(*CopyResource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, gfx::ID3D11Resource<ABI> *pSrcResource);
        void(*UpdateSubresource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch);
        void(*CopyStructureCount)(void *, gfx::ID3D11Buffer<ABI> *pDstBuffer, UINT DstAlignedByteOffset, gfx::ID3D11UnorderedAccessView<ABI> *pSrcView);
        void(*ClearRenderTargetView)(void *, gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView, FLOAT const ColorRGBA[4]);
        void(*ClearUnorderedAccessViewUint)(void *, gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView, UINT const Values[4]);
        void(*ClearUnorderedAccessViewFloat)(void *, gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView, FLOAT const Values[4]);
        void(*ClearDepthStencilView)(void *, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil);
        void(*GenerateMips)(void *, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*SetResourceMinLOD)(void *, gfx::ID3D11Resource<ABI> *pResource, FLOAT MinLOD);
        FLOAT(*GetResourceMinLOD)(void *, gfx::ID3D11Resource<ABI> *pResource);
        void(*ResolveSubresource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format);
        void(*ExecuteCommandList)(void *, ID3D11CommandList *pCommandList, BOOL RestoreContextState);
        void(*HSSetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void(*HSSetShader)(void *, gfx::ID3D11HullShader<ABI> *pHullShader);
        void(*HSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*HSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*DSSetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void(*DSSetShader)(void *, gfx::ID3D11DomainShader<ABI> *pDomainShader);
        void(*DSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*DSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*CSSetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> *const *ppShaderResourceViews);
        void(*CSSetUnorderedAccessViews)(void *, UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews, UINT const *pUAVInitialCounts);
        void(*CSSetShader)(void *, gfx::ID3D11ComputeShader<ABI> *pComputeShader);
        void(*CSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*CSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*VSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*PSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*PSGetShader)(void *, gfx::ID3D11PixelShader<ABI> **ppPixelShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*PSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*VSGetShader)(void *, gfx::ID3D11VertexShader<ABI> **ppVertexShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*PSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*IAGetInputLayout)(void *, ID3D11InputLayout **ppInputLayout);
        void(*IAGetVertexBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppVertexBuffers, UINT *pStrides, UINT *pOffsets);
        void(*IAGetIndexBuffer)(void *, gfx::ID3D11Buffer<ABI> **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset);
        void(*GSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*GSGetShader)(void *, gfx::ID3D11GeometryShader<ABI> **ppGeometryShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*IAGetPrimitiveTopology)(void *, D3D11_PRIMITIVE_TOPOLOGY *pTopology);
        void(*VSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*VSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*GetPredication)(void *, ID3D11Predicate **ppPredicate, BOOL *pPredicateValue);
        void(*GSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*GSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*OMGetRenderTargets)(void *, UINT NumViews, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView);
        void(*OMGetRenderTargetsAndUnorderedAccessViews)(void *, UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews);
        void(*OMGetBlendState)(void *, gfx::ID3D11BlendState<ABI> **ppBlendState, FLOAT BlendFactor[4], UINT *pSampleMask);
        void(*OMGetDepthStencilState)(void *, gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState, UINT *pStencilRef);
        void(*SOGetTargets)(void *, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppSOTargets);
        void(*RSGetState)(void *, gfx::ID3D11RasterizerState<ABI> **ppRasterizerState);
        void(*RSGetViewports)(void *, UINT *pNumViewports, D3D11_VIEWPORT *pViewports);
        void(*RSGetScissorRects)(void *, UINT *pNumRects, D3D11_RECT *pRects);
        void(*HSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*HSGetShader)(void *, gfx::ID3D11HullShader<ABI> **ppHullShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*HSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*HSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*DSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*DSGetShader)(void *, gfx::ID3D11DomainShader<ABI> **ppDomainShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*DSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*DSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*CSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*CSGetUnorderedAccessViews)(void *, UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews);
        void(*CSGetShader)(void *, gfx::ID3D11ComputeShader<ABI> **ppComputeShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*CSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*CSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*ClearState)(void *);
        void(*Flush)(void *);
        D3D11_DEVICE_CONTEXT_TYPE(*GetType)(void *);
        UINT(*GetContextFlags)(void *);
        HRESULT(*FinishCommandList)(void *, BOOL RestoreDeferredContextState, ID3D11CommandList **ppCommandList);
    };

    template<abi_t ABI>
    requires (ABI >= abi_t{ 6,2,13004,0 })
    struct ID3D11DeviceContextVtbl<ABI> : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        void(*VSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*PSSetShaderResources)(void *, gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
        void(*PSSetShader)(void *, gfx::ID3D11PixelShader<ABI> *pPixelShader);
        void(*PSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*VSSetShader)(void *, gfx::ID3D11VertexShader<ABI> *pVertexShader);
        void(*DrawIndexed)(void *, UINT64 StartIndexLocationAndIndexCount, INT BaseVertexLocation);
        void(*Draw)(void *, UINT VertexCount, UINT StartVertexLocation);
        HRESULT(*Map)(void *, gfx::ID3D11Resource<ABI> *pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE *pMappedResource);
        void(*Unmap)(void *, gfx::ID3D11Resource<ABI> *pResource, UINT Subresource);
        void(*PSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*IASetInputLayout)(void *, ID3D11InputLayout *pInputLayout);
        void(*IASetVertexBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppVertexBuffers, UINT const *pStrides, UINT const *pOffsets);
        void(*IASetIndexBuffer)(void *, UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer, UINT Offset);
        void(*DrawIndexedInstanced)(void *, UINT64 StartIndexLocationAndIndexCountPerInstance, UINT64 BaseVertexLocationAndStartInstanceLocation, UINT InstanceCount);
        void(*DrawInstanced)(void *, UINT VertexCountPerInstance, UINT64 StartVertexLocationAndStartInstanceLocation, UINT InstanceCount);
        void(*GSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*GSSetShader)(void *, gfx::ID3D11GeometryShader<ABI> *pShader);
        void(*VSSetShaderResources)(void *, gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
        void(*VSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*Begin)(void *, ID3D11Asynchronous *pAsync);
        void(*End)(void *, ID3D11Asynchronous *pAsync);
        HRESULT(*GetData)(void *, ID3D11Asynchronous *pAsync, void *pData, UINT DataSize, UINT GetDataFlags);
        void(*SetPredication)(void *, ID3D11Predicate *pPredicate, BOOL PredicateValue);
        void(*GSSetShaderResources)(void *, gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
        void(*GSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*OMSetRenderTargets)(void *, UINT NumViews, gfx::ID3D11RenderTargetView<ABI> *const *, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView);
        void(*OMSetRenderTargetsAndUnorderedAccessViews)(void *, UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> *const *ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews, UINT const *pUAVInitialCounts);
        void(*OMSetBlendState)(void *, gfx::ID3D11BlendState<ABI> *pBlendState, FLOAT const BlendFactor[4], UINT SampleMask);
        void(*OMSetDepthStencilState)(void *, gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState, UINT StencilRef);
        void(*SOSetTargets)(void *, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppSOTargets, UINT const *pOffsets);
        void(*DrawAuto)(void *);
        void(*DrawIndexedInstancedIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
        void(*DrawInstancedIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
        void(*Dispatch)(void *, UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ);
        void(*DispatchIndirect)(void *, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs);
        void(*RSSetState)(void *, gfx::ID3D11RasterizerState<ABI> *pRasterizerState);
        void(*RSSetViewports)(void *, UINT NumViewports, D3D11_VIEWPORT const *pViewports);
        void(*RSSetScissorRects)(void *, UINT NumRects, D3D11_RECT const *pRects);
        void(*CopySubresourceRegion)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, D3D11_BOX const *pSrcBox);
        void(*CopyResource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, gfx::ID3D11Resource<ABI> *pSrcResource);
        void(*UpdateSubresource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch);
        void(*CopyStructureCount)(void *, gfx::ID3D11Buffer<ABI> *pDstBuffer, UINT DstAlignedByteOffset, gfx::ID3D11UnorderedAccessView<ABI> *pSrcView);
        void(*ClearRenderTargetView)(void *, gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView, FLOAT const ColorRGBA[4]);
        void(*ClearUnorderedAccessViewUint)(void *, gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView, UINT const Values[4]);
        void(*ClearUnorderedAccessViewFloat)(void *, gfx::ID3D11UnorderedAccessView<ABI> *pUnorderedAccessView, FLOAT const Values[4]);
        void(*ClearDepthStencilView)(void *, gfx::ID3D11DepthStencilView<ABI> *pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil);
        void(*GenerateMips)(void *, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*SetResourceMinLOD)(void *, gfx::ID3D11Resource<ABI> *pResource, FLOAT MinLOD);
        FLOAT(*GetResourceMinLOD)(void *, gfx::ID3D11Resource<ABI> *pResource);
        void(*ResolveSubresource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format);
        void(*ExecuteCommandList)(void *, ID3D11CommandList *pCommandList, BOOL RestoreContextState);
        void(*HSSetShaderResources)(void *, gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
        void(*HSSetShader)(void *, gfx::ID3D11HullShader<ABI> *pHullShader);
        void(*HSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*HSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*DSSetShaderResources)(void *, gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
        void(*DSSetShader)(void *, gfx::ID3D11DomainShader<ABI> *pDomainShader);
        void(*DSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*DSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*CSSetShaderResources)(void *, gfx::ID3D11ShaderResourceView<ABI>* const* ppShaderResourceViews, UINT StartSlot, UINT PacketHeader);
        void(*CSSetUnorderedAccessViews)(void *, UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> *const *ppUnorderedAccessViews, UINT const *pUAVInitialCounts);
        void(*CSSetShader)(void *, gfx::ID3D11ComputeShader<ABI> *pComputeShader);
        void(*CSSetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> *const *ppSamplers);
        void(*CSSetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers);
        void(*VSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*PSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*PSGetShader)(void *, gfx::ID3D11PixelShader<ABI> **ppPixelShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*PSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*VSGetShader)(void *, gfx::ID3D11VertexShader<ABI> **ppVertexShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*PSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*IAGetInputLayout)(void *, ID3D11InputLayout **ppInputLayout);
        void(*IAGetVertexBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppVertexBuffers, UINT *pStrides, UINT *pOffsets);
        void(*IAGetIndexBuffer)(void *, gfx::ID3D11Buffer<ABI> **pIndexBuffer, DXGI_FORMAT *Format, UINT *Offset);
        void(*GSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*GSGetShader)(void *, gfx::ID3D11GeometryShader<ABI> **ppGeometryShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*IAGetPrimitiveTopology)(void *, D3D11_PRIMITIVE_TOPOLOGY *pTopology);
        void(*VSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*VSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*GetPredication)(void *, ID3D11Predicate **ppPredicate, BOOL *pPredicateValue);
        void(*GSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*GSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*OMGetRenderTargets)(void *, UINT NumViews, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView);
        void(*OMGetRenderTargetsAndUnorderedAccessViews)(void *, UINT NumRTVs, gfx::ID3D11RenderTargetView<ABI> **ppRenderTargetViews, gfx::ID3D11DepthStencilView<ABI> **ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews);
        void(*OMGetBlendState)(void *, gfx::ID3D11BlendState<ABI> **ppBlendState, FLOAT BlendFactor[4], UINT *pSampleMask);
        void(*OMGetDepthStencilState)(void *, gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState, UINT *pStencilRef);
        void(*SOGetTargets)(void *, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppSOTargets);
        void(*RSGetState)(void *, gfx::ID3D11RasterizerState<ABI> **ppRasterizerState);
        void(*RSGetViewports)(void *, UINT *pNumViewports, D3D11_VIEWPORT *pViewports);
        void(*RSGetScissorRects)(void *, UINT *pNumRects, D3D11_RECT *pRects);
        void(*HSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*HSGetShader)(void *, gfx::ID3D11HullShader<ABI> **ppHullShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*HSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*HSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*DSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*DSGetShader)(void *, gfx::ID3D11DomainShader<ABI> **ppDomainShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*DSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*DSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*CSGetShaderResources)(void *, UINT StartSlot, UINT NumViews, gfx::ID3D11ShaderResourceView<ABI> **ppShaderResourceViews);
        void(*CSGetUnorderedAccessViews)(void *, UINT StartSlot, UINT NumUAVs, gfx::ID3D11UnorderedAccessView<ABI> **ppUnorderedAccessViews);
        void(*CSGetShader)(void *, gfx::ID3D11ComputeShader<ABI> **ppComputeShader, ID3D11ClassInstance **ppClassInstances, UINT *pNumClassInstances);
        void(*CSGetSamplers)(void *, UINT StartSlot, UINT NumSamplers, gfx::ID3D11SamplerState<ABI> **ppSamplers);
        void(*CSGetConstantBuffers)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers);
        void(*ClearState)(void *);
        void(*Flush)(void *);
        D3D11_DEVICE_CONTEXT_TYPE(*GetType)(void *);
        UINT(*GetContextFlags)(void *);
        HRESULT(*FinishCommandList)(void *, BOOL RestoreDeferredContextState, ID3D11CommandList **ppCommandList);
    };
    
    template<abi_t ABI>
    struct ID3D11DeviceContext1 : gfx::ID3D11DeviceContext<ABI>
    {
        virtual void CopySubresourceRegion1(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, D3D11_BOX const *pSrcBox, UINT CopyFlags) = 0;
        virtual void UpdateSubresource1(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch, UINT CopyFlags) = 0;
        virtual void DiscardResource(gfx::ID3D11Resource<ABI> *pResource) = 0;
        virtual void DiscardView(gfx::ID3D11View<ABI> *pResourceView) = 0;
        virtual void VSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants) = 0;
        virtual void HSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants) = 0;
        virtual void DSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants) = 0;
        virtual void GSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants) = 0;
        virtual void PSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants) = 0;
        virtual void CSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants) = 0;
        virtual void VSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants) = 0;
        virtual void HSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants) = 0;
        virtual void DSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants) = 0;
        virtual void GSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants) = 0;
        virtual void PSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants) = 0;
        virtual void CSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants) = 0;
        virtual void SwapDeviceContextState(ID3DDeviceContextState *pState, ID3DDeviceContextState **ppPreviousState) = 0;
        virtual void ClearView(gfx::ID3D11View<ABI> *pView, FLOAT const Color[4], D3D11_RECT const *pRect, UINT NumRects) = 0;
        virtual void DiscardView1(gfx::ID3D11View<ABI> *pResourceView, D3D11_RECT const *pRects, UINT NumRects) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11DeviceContext1Vtbl : gfx::ID3D11DeviceContextVtbl<ABI>
    {
        void(*CopySubresourceRegion1)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, D3D11_BOX const *pSrcBox, UINT CopyFlags);
        void(*UpdateSubresource1)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, D3D11_BOX const *pDstBox, void const *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch, UINT CopyFlags);
        void(*DiscardResource)(void *, gfx::ID3D11Resource<ABI> *pResource);
        void(*DiscardView)(void *, gfx::ID3D11View<ABI> *pResourceView);
        void(*VSSetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants);
        void(*HSSetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants);
        void(*DSSetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants);
        void(*GSSetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants);
        void(*PSSetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants);
        void(*CSSetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> *const *ppConstantBuffers, UINT const *pFirstConstant, UINT const *pNumConstants);
        void(*VSGetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants);
        void(*HSGetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants);
        void(*DSGetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants);
        void(*GSGetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants);
        void(*PSGetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants);
        void(*CSGetConstantBuffers1)(void *, UINT StartSlot, UINT NumBuffers, gfx::ID3D11Buffer<ABI> **ppConstantBuffers, UINT *pFirstConstant, UINT *pNumConstants);
        void(*SwapDeviceContextState)(void *, ID3DDeviceContextState *pState, ID3DDeviceContextState **ppPreviousState);
        void(*ClearView)(void *, gfx::ID3D11View<ABI> *pView, FLOAT const Color[4], D3D11_RECT const *pRect, UINT NumRects);
        void(*DiscardView1)(void *, gfx::ID3D11View<ABI> *pResourceView, D3D11_RECT const *pRects, UINT NumRects);
    };
    
    template<abi_t ABI>
    struct ID3D11DeviceContext2 : gfx::ID3D11DeviceContext1<ABI>
    {
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11DeviceContext2<ABI> : gfx::ID3D11DeviceContext1<ABI>
    {
        virtual HRESULT UpdateTileMappings(gfx::ID3D11Resource<ABI> *pTiledResource, UINT NumTiledResourceRegions, D3D11_TILED_RESOURCE_COORDINATE const *pTiledResourceRegionStartCoordinates, D3D11_TILE_REGION_SIZE const *pTiledResourceRegionSizes, gfx::ID3D11Buffer<ABI> *pTilePool, UINT NumRanges, UINT const *pRangeFlags, UINT const *pTilePoolStartOffsets, UINT const *pRangeTileCounts, UINT Flags) = 0;
        virtual HRESULT CopyTileMappings(gfx::ID3D11Resource<ABI> *pDestTiledResource, D3D11_TILED_RESOURCE_COORDINATE const *pDestRegionStartCoordinate, gfx::ID3D11Resource<ABI> *pSourceTiledResource, D3D11_TILED_RESOURCE_COORDINATE const *pSourceRegionStartCoordinate, D3D11_TILE_REGION_SIZE const *pTileRegionSize, UINT Flags) = 0;
        virtual void CopyTiles(gfx::ID3D11Resource<ABI> *pTiledResource, D3D11_TILED_RESOURCE_COORDINATE const *pTileRegionStartCoordinate, D3D11_TILE_REGION_SIZE const *pTileRegionSize, gfx::ID3D11Buffer<ABI> *pBuffer, UINT64 BufferStartOffsetInBytes, UINT Flags) = 0;
        virtual void UpdateTiles(gfx::ID3D11Resource<ABI> *pDestTiledResource, D3D11_TILED_RESOURCE_COORDINATE const *pDestTileRegionStartCoordinate, D3D11_TILE_REGION_SIZE const *pDestTileRegionSize, void const *pSourceTileData, UINT Flags) = 0;
        virtual HRESULT ResizeTilePool(gfx::ID3D11Buffer<ABI> *pTilePool, UINT64 NewSizeInBytes) = 0;
        virtual void TiledResourceBarrier(gfx::ID3D11DeviceChild<ABI> *pTiledResourceOrViewAccessBeforeBarrier, gfx::ID3D11DeviceChild<ABI> *pTiledResourceOrViewAccessAfterBarrier) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11DeviceContext2Vtbl : gfx::ID3D11DeviceContext1Vtbl<ABI>
    {
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11DeviceContext2Vtbl<ABI> : gfx::ID3D11DeviceContext1Vtbl<ABI>
    {
        HRESULT(*UpdateTileMappings)(void *, gfx::ID3D11Resource<ABI> *pTiledResource, UINT NumTiledResourceRegions, D3D11_TILED_RESOURCE_COORDINATE const *pTiledResourceRegionStartCoordinates, D3D11_TILE_REGION_SIZE const *pTiledResourceRegionSizes, gfx::ID3D11Buffer<ABI> *pTilePool, UINT NumRanges, UINT const *pRangeFlags, UINT const *pTilePoolStartOffsets, UINT const *pRangeTileCounts, UINT Flags);
        HRESULT(*CopyTileMappings)(void *, gfx::ID3D11Resource<ABI> *pDestTiledResource, D3D11_TILED_RESOURCE_COORDINATE const *pDestRegionStartCoordinate, gfx::ID3D11Resource<ABI> *pSourceTiledResource, D3D11_TILED_RESOURCE_COORDINATE const *pSourceRegionStartCoordinate, D3D11_TILE_REGION_SIZE const *pTileRegionSize, UINT Flags);
        void(*CopyTiles)(void *, gfx::ID3D11Resource<ABI> *pTiledResource, D3D11_TILED_RESOURCE_COORDINATE const *pTileRegionStartCoordinate, D3D11_TILE_REGION_SIZE const *pTileRegionSize, gfx::ID3D11Buffer<ABI> *pBuffer, UINT64 BufferStartOffsetInBytes, UINT Flags);
        void(*UpdateTiles)(void *, gfx::ID3D11Resource<ABI> *pDestTiledResource, D3D11_TILED_RESOURCE_COORDINATE const *pDestTileRegionStartCoordinate, D3D11_TILE_REGION_SIZE const *pDestTileRegionSize, void const *pSourceTileData, UINT Flags);
        HRESULT(*ResizeTilePool)(void *, gfx::ID3D11Buffer<ABI> *pTilePool, UINT64 NewSizeInBytes);
        void(*TiledResourceBarrier)(void *, gfx::ID3D11DeviceChild<ABI> *pTiledResourceOrViewAccessBeforeBarrier, gfx::ID3D11DeviceChild<ABI> *pTiledResourceOrViewAccessAfterBarrier);
    };
    
    template<abi_t ABI>
    struct ID3D11DeviceContextX : gfx::ID3D11DeviceContext2<ABI>
    {
        virtual INT PIXBeginEvent(LPCWSTR Name) = 0;
        virtual INT PIXEndEvent() = 0;
        virtual void PIXSetMarker(LPCWSTR Name) = 0;
        virtual BOOL PIXGetStatus() = 0;
        virtual HRESULT PIXGpuCaptureNextFrame(UINT Flags, LPCWSTR lpOutputFileName) = 0;
        virtual HRESULT PIXGpuBeginCapture(UINT Flags, LPCWSTR lpOutputFileName) = 0;
        virtual HRESULT PIXGpuEndCapture() = 0;
        virtual void StartCounters(ID3D11CounterSetX *pCounterSet) = 0;
        virtual void SampleCounters(ID3D11CounterSampleX *pCounterSample) = 0;
        virtual void StopCounters() = 0;
        virtual HRESULT GetCounterData(ID3D11CounterSampleX *pCounterSample, D3D11X_COUNTER_DATA *pData, UINT GetCounterDataFlags) = 0;
        virtual void FlushGpuCaches(gfx::ID3D11Resource<ABI> *pResource) = 0;
        virtual void FlushGpuCacheRange(UINT Flags, void *pBaseAddress, SIZE_T SizeInBytes) = 0;
        virtual void InsertWaitUntilIdle(UINT Flags) = 0;
        virtual UINT64 InsertFence(UINT Flags) = 0;
        virtual void InsertWaitOnFence(UINT Flags, UINT64 Fence) = 0;
        virtual void RemapConstantBufferInheritance(D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot) = 0;
        virtual void RemapShaderResourceInheritance(D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot) = 0;
        virtual void RemapSamplerInheritance(D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot) = 0;
        virtual void RemapVertexBufferInheritance(UINT Slot, UINT InheritSlot) = 0;
        virtual void PSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void PSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void PSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void VSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void VSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void VSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void GSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void GSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void GSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void CSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void CSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void CSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void HSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void HSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void HSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void DSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void DSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void DSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void IASetFastVertexBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, UINT Stride) = 0;
        virtual void IASetFastIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer) = 0;
        virtual void PSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void PSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void VSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void VSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void GSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void GSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void CSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void CSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void HSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void HSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void DSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void DSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void IASetPlacementVertexBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, void *pBaseAddress, UINT Stride) = 0;
        virtual void IASetPlacementIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer, void *pBaseAddress) = 0;
        virtual void HSSetTessellationParameters(D3D11X_TESSELLATION_PARAMETERS const *pTessellationParameters) = 0;
        virtual void HSGetLastUsedTessellationParameters(D3D11X_TESSELLATION_PARAMETERS *pTessellationParameters) = 0;
        virtual void CSEnableAutomaticGpuFlush(BOOL Enable) = 0;
        virtual void GpuSendPipelinedEvent(D3D11X_GPU_PIPELINED_EVENT Event) = 0;
        virtual HRESULT Suspend(UINT Flags) = 0;
        virtual HRESULT Resume() = 0;
        virtual void BeginCommandListExecution(UINT Flags) = 0;
        virtual void EndCommandListExecution() = 0;
        virtual void SetGraphicsShaderLimits(D3D11X_GRAPHICS_SHADER_LIMITS const *pShaderLimits) = 0;
        virtual void SetComputeShaderLimits(D3D11X_COMPUTE_SHADER_LIMITS const *pShaderLimits) = 0;
        virtual void SetPredicationBuffer(gfx::ID3D11Buffer<ABI> *pBuffer, UINT Offset, UINT Flags) = 0;
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11DeviceContextX<ABI> : gfx::ID3D11DeviceContext2<ABI>
    {
        virtual INT PIXBeginEvent(LPCWSTR Name) = 0;
        virtual INT PIXEndEvent() = 0;
        virtual void PIXSetMarker(LPCWSTR Name) = 0;
        virtual BOOL PIXGetStatus() = 0;
        virtual HRESULT PIXGpuCaptureNextFrame(UINT Flags, LPCWSTR lpOutputFileName) = 0;
        virtual HRESULT PIXGpuBeginCapture(UINT Flags, LPCWSTR lpOutputFileName) = 0;
        virtual HRESULT PIXGpuEndCapture() = 0;
        virtual void StartCounters(ID3D11CounterSetX *pCounterSet) = 0;
        virtual void SampleCounters(ID3D11CounterSampleX *pCounterSample) = 0;
        virtual void StopCounters() = 0;
        virtual HRESULT GetCounterData(ID3D11CounterSampleX *pCounterSample, D3D11X_COUNTER_DATA *pData, UINT GetCounterDataFlags) = 0;
        virtual void FlushGpuCaches(gfx::ID3D11Resource<ABI> *pResource) = 0;
        virtual void FlushGpuCacheRange(UINT Flags, void *pBaseAddress, SIZE_T SizeInBytes) = 0;
        virtual void InsertWaitUntilIdle(UINT Flags) = 0;
        virtual UINT64 InsertFence(UINT Flags) = 0;
        virtual void InsertWaitOnFence(UINT Flags, UINT64 Fence) = 0;
        virtual void RemapConstantBufferInheritance(D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot) = 0;
        virtual void RemapShaderResourceInheritance(D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot) = 0;
        virtual void RemapSamplerInheritance(D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot) = 0;
        virtual void RemapVertexBufferInheritance(UINT Slot, UINT InheritSlot) = 0;
        virtual void PSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void PSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void PSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void VSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void VSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void VSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void GSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void GSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void GSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void CSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void CSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void CSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void HSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void HSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void HSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void DSSetFastConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer) = 0;
        virtual void DSSetFastShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView) = 0;
        virtual void DSSetFastSampler(UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler) = 0;
        virtual void IASetFastVertexBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, UINT Stride) = 0;
        virtual void IASetFastIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer) = 0;
        virtual void PSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void PSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void VSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void VSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void GSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void GSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void CSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void CSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void HSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void HSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void DSSetPlacementConstantBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress) = 0;
        virtual void DSSetPlacementShaderResource(UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress) = 0;
        virtual void IASetPlacementVertexBuffer(UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, void *pBaseAddress, UINT Stride) = 0;
        virtual void IASetPlacementIndexBuffer(UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer, void *pBaseAddress) = 0;
        virtual void HSSetTessellationParameters(D3D11X_TESSELLATION_PARAMETERS const *pTessellationParameters) = 0;
        virtual void HSGetLastUsedTessellationParameters(D3D11X_TESSELLATION_PARAMETERS *pTessellationParameters) = 0;
        virtual void CSEnableAutomaticGpuFlush(BOOL Enable) = 0;
        virtual void GpuSendPipelinedEvent(D3D11X_GPU_PIPELINED_EVENT Event) = 0;
        virtual HRESULT Suspend(UINT Flags) = 0;
        virtual HRESULT Resume() = 0;
        virtual void BeginCommandListExecution(UINT Flags) = 0;
        virtual void EndCommandListExecution() = 0;
        virtual void SetGraphicsShaderLimits(D3D11X_GRAPHICS_SHADER_LIMITS const *pShaderLimits) = 0;
        virtual void SetComputeShaderLimits(D3D11X_COMPUTE_SHADER_LIMITS const *pShaderLimits) = 0;
        virtual void SetPredicationBuffer(gfx::ID3D11Buffer<ABI> *pBuffer, UINT Offset, UINT Flags) = 0;
        virtual void OMSetDepthBounds(FLOAT min, FLOAT max) = 0;
        virtual void OMSetDepthStencilStateX(gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState) = 0;
        virtual void OMSetSampleMask(UINT64 QuadSampleMask) = 0;
        virtual UINT32 *MakeCeSpace() = 0;
        virtual void SetFastResources_Debug(UINT *pTableStart, UINT *pTableEnd) = 0;
        virtual void BeginResourceBatch(void *pBuffer, UINT BufferSize) = 0;
        virtual UINT EndResourceBatch(UINT *pSizeNeeded) = 0;
        virtual void SetFastResourcesFromBatch_Debug(void *pBatch, UINT Size) = 0;
        virtual void CSPlaceUnorderedAccessView(UINT Slot, D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW *const pDescriptor, UINT64 Offset) = 0;
        virtual void WriteValueEndOfPipe(void *pDestination, UINT Value, UINT Flags) = 0;
        virtual void CopyMemoryToMemory(void *pDstAddress, void *pSrcAddress, SIZE_T SizeBytes) = 0;
        virtual void FillMemoryWithValue(void *pDstAddress, SIZE_T SizeBytes, UINT FillValue) = 0;
        virtual void BeginProcessVideoResource(gfx::ID3D11Resource<ABI> *pResource, UINT SubResource) = 0;
        virtual void EndProcessVideoResource(gfx::ID3D11Resource<ABI> *pResource, UINT SubResource) = 0;
        virtual HRESULT StartThreadTrace(D3D11X_THREAD_TRACE_DESC const *pDesc, void *pDstAddressShaderEngine0, void *pDstAddressShaderEngine1, SIZE_T BufferSizeBytes) = 0;
        virtual void StopThreadTrace(void *pDstAddressTraceSize) = 0;
        virtual void InsertThreadTraceMarker(UINT Marker) = 0;
        virtual void IASetPrimitiveResetIndex(UINT ResetIndex) = 0;
        virtual void SetShaderResourceViewMinLOD(gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, FLOAT MinLOD) = 0;
        virtual void InsertWaitOnPresent(UINT Flags, gfx::ID3D11Resource<ABI> *pBackBuffer) = 0;
        virtual void ClearRenderTargetViewX(gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView, UINT Flags, FLOAT const ColorRGBA[4]) = 0;
        virtual UINT GetResourceCompression(gfx::ID3D11Resource<ABI> *pResource) = 0;
        virtual UINT GetResourceCompressionX(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pResource) = 0;
        virtual void DecompressResource(gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, D3D11X_POINT const *pDstPoint, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, D3D11X_RECT const *pSrcRect, DXGI_FORMAT DecompressFormat, UINT DecompressFlags) = 0;
        virtual void DecompressResourceX(gfx::D3D11X_DESCRIPTOR_RESOURCE *pDstResource, UINT DstSubresource, D3D11X_POINT const *pDstPoint, gfx::D3D11X_DESCRIPTOR_RESOURCE *pSrcResource, UINT SrcSubresource, D3D11X_RECT const *pSrcRect, D3D11X_FORMAT DecompressFormat, UINT DecompressFlags) = 0;
        virtual void GSSetParameters(D3D11X_GS_PARAMETERS const *pGsParameters) = 0;
        virtual void GSGetLastUsedParameters(D3D11X_GS_PARAMETERS *pGsParameters) = 0;
        virtual void MultiDrawIndexedInstancedIndirect(UINT PrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags) = 0;
        virtual void MultiDrawInstancedIndirect(UINT PrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags) = 0;
        virtual void MultiDrawIndexedInstancedIndirectAuto(gfx::ID3D11Buffer<ABI> *pBufferForPrimitiveCount, UINT AlignedByteOffsetForPrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags) = 0;
        virtual void MultiDrawInstancedIndirectAuto(gfx::ID3D11Buffer<ABI> *pBufferForPrimitiveCount, UINT AlignedByteOffsetForPrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags) = 0;
        virtual HRESULT RSGetMSAASettingsForQuality(D3D11X_MSAA_SCAN_CONVERTER_SETTINGS *pMSAASCSettings, D3D11X_MSAA_EQAA_SETTINGS *pEQAASettings, D3D11X_MSAA_SAMPLE_PRIORITIES *pCentroidPriorities, D3D11X_MSAA_SAMPLE_POSITIONS *pSamplePositions, UINT LogSampleCount, UINT SampleQuality) = 0;
        virtual void RSSetScanConverterMSAASettings(D3D11X_MSAA_SCAN_CONVERTER_SETTINGS const *pMSAASCSettings) = 0;
        virtual void RSSetEQAASettings(D3D11X_MSAA_EQAA_SETTINGS const *pEQAASettings) = 0;
        virtual void RSSetSamplePositions(D3D11X_MSAA_SAMPLE_PRIORITIES const *pSamplesPriorities, D3D11X_MSAA_SAMPLE_POSITIONS const *pSamplePositions) = 0;
        virtual void SetResourceCompression(gfx::ID3D11Resource<ABI> *pResource, UINT Compression) = 0;
        virtual void SetResourceCompressionX(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pResource, UINT Compression) = 0;
        virtual void SetGDSRange(D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords) = 0;
        virtual void WriteGDS(D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords, UINT const *pCounterValues, UINT Flags) = 0;
        virtual void ReadGDS(D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords, UINT *pCounterValues, UINT Flags) = 0;
        virtual void VSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData) = 0;
        virtual void HSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData) = 0;
        virtual void DSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData) = 0;
        virtual void GSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData) = 0;
        virtual void PSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData) = 0;
        virtual void CSSetShaderUserData(UINT StartSlot, UINT NumRegisters, UINT const *pData) = 0;
        virtual void InsertWaitOnMemory(void const *pAddress, UINT Flags, D3D11_COMPARISON_FUNC ComparisonFunction, UINT ReferenceValue, UINT Mask) = 0;
        virtual void WriteTimestampToMemory(void *pDstAddress) = 0;
        virtual void WriteTimestampToBuffer(gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetBytes) = 0;
        virtual void StoreConstantRam(UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT BufferOffsetInBytes, UINT CeRamOffsetInBytes, UINT SizeInBytes) = 0;
        virtual void LoadConstantRam(UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT BufferOffsetInBytes, UINT CeRamOffsetInBytes, UINT SizeInBytes) = 0;
        virtual void WriteQuery(D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes, UINT StrideInBytes) = 0;
        virtual void ResetQuery(D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags) = 0;
        virtual void ConfigureQuery(D3D11_QUERY QueryType, void const *pConfiguration, UINT ConfigurationSize) = 0;
        virtual void SetShaderUserData(D3D11X_HW_STAGE ShaderStage, UINT StartSlot, UINT NumRegisters, UINT const *pData) = 0;
        virtual void SetPixelShaderDepthForceZOrder(BOOL ForceOrder) = 0;
        virtual void SetPredicationFromQuery(D3D11_QUERY QueryType, gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes, UINT Flags) = 0;
        virtual void SetBorderColorPalette(gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes, UINT Flags) = 0;
        virtual void WriteValueEndOfPipe64(void *pDestination, UINT64 Value, UINT Flags) = 0;
        virtual void InsertWaitOnMemory64(void const *pAddress, UINT Flags, D3D11_COMPARISON_FUNC ComparisonFunction, UINT64 ReferenceValue) = 0;
        virtual void LoadConstantRamImmediate(UINT Flags, void const *pBuffer, UINT CeRamOffsetInBytes, UINT SizeInBytes) = 0;
        virtual void SetScreenExtentsQuery(UINT Value) = 0;
        virtual void CollectScreenExtents(UINT Flags, UINT AddressCount, UINT64 const *pDestinationAddresses, USHORT ZMin, USHORT ZMax) = 0;
        virtual void FillResourceWithValue(gfx::ID3D11Resource<ABI> *pDstResource, UINT FillValue) = 0;
        virtual void SetDrawBalancing(UINT BalancingMode, UINT Flags) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11DeviceContextXVtbl : gfx::ID3D11DeviceContext2Vtbl<ABI>
    {
        INT(*PIXBeginEvent)(void *, LPCWSTR Name);
        INT(*PIXEndEvent)(void *);
        void(*PIXSetMarker)(void *, LPCWSTR Name);
        BOOL(*PIXGetStatus)(void *);
        HRESULT(*PIXGpuCaptureNextFrame)(void *, UINT Flags, LPCWSTR lpOutputFileName);
        HRESULT(*PIXGpuBeginCapture)(void *, UINT Flags, LPCWSTR lpOutputFileName);
        HRESULT(*PIXGpuEndCapture)(void *);
        void(*StartCounters)(void *, ID3D11CounterSetX *pCounterSet);
        void(*SampleCounters)(void *, ID3D11CounterSampleX *pCounterSample);
        void(*StopCounters)(void *);
        HRESULT(*GetCounterData)(void *, ID3D11CounterSampleX *pCounterSample, D3D11X_COUNTER_DATA *pData, UINT GetCounterDataFlags);
        void(*FlushGpuCaches)(void *, gfx::ID3D11Resource<ABI> *pResource);
        void(*FlushGpuCacheRange)(void *, UINT Flags, void *pBaseAddress, SIZE_T SizeInBytes);
        void(*InsertWaitUntilIdle)(void *, UINT Flags);
        UINT64(*InsertFence)(void *, UINT Flags);
        void(*InsertWaitOnFence)(void *, UINT Flags, UINT64 Fence);
        void(*RemapConstantBufferInheritance)(void *, D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot);
        void(*RemapShaderResourceInheritance)(void *, D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot);
        void(*RemapSamplerInheritance)(void *, D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot);
        void(*RemapVertexBufferInheritance)(void *, UINT Slot, UINT InheritSlot);
        void(*PSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*PSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*PSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*VSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*VSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*VSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*GSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*GSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*GSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*CSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*CSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*CSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*HSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*HSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*HSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*DSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*DSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*DSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*IASetFastVertexBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, UINT Stride);
        void(*IASetFastIndexBuffer)(void *, UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer);
        void(*PSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*PSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*VSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*VSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*GSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*GSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*CSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*CSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*HSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*HSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*DSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*DSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*IASetPlacementVertexBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, void *pBaseAddress, UINT Stride);
        void(*IASetPlacementIndexBuffer)(void *, UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer, void *pBaseAddress);
        void(*HSSetTessellationParameters)(void *, D3D11X_TESSELLATION_PARAMETERS const *pTessellationParameters);
        void(*HSGetLastUsedTessellationParameters)(void *, D3D11X_TESSELLATION_PARAMETERS *pTessellationParameters);
        void(*CSEnableAutomaticGpuFlush)(void *, BOOL Enable);
        void(*GpuSendPipelinedEvent)(void *, D3D11X_GPU_PIPELINED_EVENT Event);
        HRESULT(*Suspend)(void *, UINT Flags);
        HRESULT(*Resume)(void *);
        void(*BeginCommandListExecution)(void *, UINT Flags);
        void(*EndCommandListExecution)(void *);
        void(*SetGraphicsShaderLimits)(void *, D3D11X_GRAPHICS_SHADER_LIMITS const *pShaderLimits);
        void(*SetComputeShaderLimits)(void *, D3D11X_COMPUTE_SHADER_LIMITS const *pShaderLimits);
        void(*SetPredicationBuffer)(void *, gfx::ID3D11Buffer<ABI> *pBuffer, UINT Offset, UINT Flags);
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11DeviceContextXVtbl<ABI> : gfx::ID3D11DeviceContext2Vtbl<ABI>
    {
        INT(*PIXBeginEvent)(void *, LPCWSTR Name);
        INT(*PIXEndEvent)(void *);
        void(*PIXSetMarker)(void *, LPCWSTR Name);
        BOOL(*PIXGetStatus)(void *);
        HRESULT(*PIXGpuCaptureNextFrame)(void *, UINT Flags, LPCWSTR lpOutputFileName);
        HRESULT(*PIXGpuBeginCapture)(void *, UINT Flags, LPCWSTR lpOutputFileName);
        HRESULT(*PIXGpuEndCapture)(void *);
        void(*StartCounters)(void *, ID3D11CounterSetX *pCounterSet);
        void(*SampleCounters)(void *, ID3D11CounterSampleX *pCounterSample);
        void(*StopCounters)(void *);
        HRESULT(*GetCounterData)(void *, ID3D11CounterSampleX *pCounterSample, D3D11X_COUNTER_DATA *pData, UINT GetCounterDataFlags);
        void(*FlushGpuCaches)(void *, gfx::ID3D11Resource<ABI> *pResource);
        void(*FlushGpuCacheRange)(void *, UINT Flags, void *pBaseAddress, SIZE_T SizeInBytes);
        void(*InsertWaitUntilIdle)(void *, UINT Flags);
        UINT64(*InsertFence)(void *, UINT Flags);
        void(*InsertWaitOnFence)(void *, UINT Flags, UINT64 Fence);
        void(*RemapConstantBufferInheritance)(void *, D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot);
        void(*RemapShaderResourceInheritance)(void *, D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot);
        void(*RemapSamplerInheritance)(void *, D3D11_STAGE Stage, UINT Slot, D3D11_STAGE InheritStage, UINT InheritSlot);
        void(*RemapVertexBufferInheritance)(void *, UINT Slot, UINT InheritSlot);
        void(*PSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*PSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*PSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*VSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*VSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*VSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*GSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*GSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*GSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*CSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*CSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*CSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*HSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*HSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*HSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*DSSetFastConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer);
        void(*DSSetFastShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView);
        void(*DSSetFastSampler)(void *, UINT Slot, gfx::ID3D11SamplerState<ABI> *pSampler);
        void(*IASetFastVertexBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, UINT Stride);
        void(*IASetFastIndexBuffer)(void *, UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer);
        void(*PSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*PSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*VSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*VSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*GSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*GSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*CSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*CSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*HSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*HSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*DSSetPlacementConstantBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pConstantBuffer, void *pBaseAddress);
        void(*DSSetPlacementShaderResource)(void *, UINT Slot, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, void *pBaseAddress);
        void(*IASetPlacementVertexBuffer)(void *, UINT Slot, gfx::ID3D11Buffer<ABI> *pVertexBuffer, void *pBaseAddress, UINT Stride);
        void(*IASetPlacementIndexBuffer)(void *, UINT HardwareIndexFormat, gfx::ID3D11Buffer<ABI> *pIndexBuffer, void *pBaseAddress);
        void(*HSSetTessellationParameters)(void *, D3D11X_TESSELLATION_PARAMETERS const *pTessellationParameters);
        void(*HSGetLastUsedTessellationParameters)(void *, D3D11X_TESSELLATION_PARAMETERS *pTessellationParameters);
        void(*CSEnableAutomaticGpuFlush)(void *, BOOL Enable);
        void(*GpuSendPipelinedEvent)(void *, D3D11X_GPU_PIPELINED_EVENT Event);
        HRESULT(*Suspend)(void *, UINT Flags);
        HRESULT(*Resume)(void *);
        void(*BeginCommandListExecution)(void *, UINT Flags);
        void(*EndCommandListExecution)(void *);
        void(*SetGraphicsShaderLimits)(void *, D3D11X_GRAPHICS_SHADER_LIMITS const *pShaderLimits);
        void(*SetComputeShaderLimits)(void *, D3D11X_COMPUTE_SHADER_LIMITS const *pShaderLimits);
        void(*SetPredicationBuffer)(void *, gfx::ID3D11Buffer<ABI> *pBuffer, UINT Offset, UINT Flags);
        void(*OMSetDepthBounds)(void *, FLOAT min, FLOAT max);
        void(*OMSetDepthStencilStateX)(void *, gfx::ID3D11DepthStencilState<ABI> *pDepthStencilState);
        void(*OMSetSampleMask)(void *, UINT64 QuadSampleMask);
        UINT32 *(*MakeCeSpace)(void *);
        void(*SetFastResources_Debug)(void *, UINT *pTableStart, UINT *pTableEnd);
        void(*BeginResourceBatch)(void *, void *pBuffer, UINT BufferSize);
        UINT(*EndResourceBatch)(void *, UINT *pSizeNeeded);
        void(*SetFastResourcesFromBatch_Debug)(void *, void *pBatch, UINT Size);
        void(*CSPlaceUnorderedAccessView)(void *, UINT Slot, D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW *const pDescriptor, UINT64 Offset);
        void(*WriteValueEndOfPipe)(void *, void *pDestination, UINT Value, UINT Flags);
        void(*CopyMemoryToMemory)(void *, void *pDstAddress, void *pSrcAddress, SIZE_T SizeBytes);
        void(*FillMemoryWithValue)(void *, void *pDstAddress, SIZE_T SizeBytes, UINT FillValue);
        void(*BeginProcessVideoResource)(void *, gfx::ID3D11Resource<ABI> *pResource, UINT SubResource);
        void(*EndProcessVideoResource)(void *, gfx::ID3D11Resource<ABI> *pResource, UINT SubResource);
        HRESULT(*StartThreadTrace)(void *, D3D11X_THREAD_TRACE_DESC const *pDesc, void *pDstAddressShaderEngine0, void *pDstAddressShaderEngine1, SIZE_T BufferSizeBytes);
        void(*StopThreadTrace)(void *, void *pDstAddressTraceSize);
        void(*InsertThreadTraceMarker)(void *, UINT Marker);
        void(*IASetPrimitiveResetIndex)(void *, UINT ResetIndex);
        void(*SetShaderResourceViewMinLOD)(void *, gfx::ID3D11ShaderResourceView<ABI> *pShaderResourceView, FLOAT MinLOD);
        void(*InsertWaitOnPresent)(void *, UINT Flags, gfx::ID3D11Resource<ABI> *pBackBuffer);
        void(*ClearRenderTargetViewX)(void *, gfx::ID3D11RenderTargetView<ABI> *pRenderTargetView, UINT Flags, FLOAT const ColorRGBA[4]);
        UINT(*GetResourceCompression)(void *, gfx::ID3D11Resource<ABI> *pResource);
        UINT(*GetResourceCompressionX)(void *, gfx::D3D11X_DESCRIPTOR_RESOURCE const *pResource);
        void(*DecompressResource)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT DstSubresource, D3D11X_POINT const *pDstPoint, gfx::ID3D11Resource<ABI> *pSrcResource, UINT SrcSubresource, D3D11X_RECT const *pSrcRect, DXGI_FORMAT DecompressFormat, UINT DecompressFlags);
        void(*DecompressResourceX)(void *, gfx::D3D11X_DESCRIPTOR_RESOURCE *pDstResource, UINT DstSubresource, D3D11X_POINT const *pDstPoint, gfx::D3D11X_DESCRIPTOR_RESOURCE *pSrcResource, UINT SrcSubresource, D3D11X_RECT const *pSrcRect, D3D11X_FORMAT DecompressFormat, UINT DecompressFlags);
        void(*GSSetParameters)(void *, D3D11X_GS_PARAMETERS const *pGsParameters);
        void(*GSGetLastUsedParameters)(void *, D3D11X_GS_PARAMETERS *pGsParameters);
        void(*MultiDrawIndexedInstancedIndirect)(void *, UINT PrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags);
        void(*MultiDrawInstancedIndirect)(void *, UINT PrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags);
        void(*MultiDrawIndexedInstancedIndirectAuto)(void *, gfx::ID3D11Buffer<ABI> *pBufferForPrimitiveCount, UINT AlignedByteOffsetForPrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags);
        void(*MultiDrawInstancedIndirectAuto)(void *, gfx::ID3D11Buffer<ABI> *pBufferForPrimitiveCount, UINT AlignedByteOffsetForPrimitiveCount, gfx::ID3D11Buffer<ABI> *pBufferForArgs, UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags);
        HRESULT(*RSGetMSAASettingsForQuality)(void *, D3D11X_MSAA_SCAN_CONVERTER_SETTINGS *pMSAASCSettings, D3D11X_MSAA_EQAA_SETTINGS *pEQAASettings, D3D11X_MSAA_SAMPLE_PRIORITIES *pCentroidPriorities, D3D11X_MSAA_SAMPLE_POSITIONS *pSamplePositions, UINT LogSampleCount, UINT SampleQuality);
        void(*RSSetScanConverterMSAASettings)(void *, D3D11X_MSAA_SCAN_CONVERTER_SETTINGS const *pMSAASCSettings);
        void(*RSSetEQAASettings)(void *, D3D11X_MSAA_EQAA_SETTINGS const *pEQAASettings);
        void(*RSSetSamplePositions)(void *, D3D11X_MSAA_SAMPLE_PRIORITIES const *pSamplesPriorities, D3D11X_MSAA_SAMPLE_POSITIONS const *pSamplePositions);
        void(*SetResourceCompression)(void *, gfx::ID3D11Resource<ABI> *pResource, UINT Compression);
        void(*SetResourceCompressionX)(void *, gfx::D3D11X_DESCRIPTOR_RESOURCE const *pResource, UINT Compression);
        void(*SetGDSRange)(void *, D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords);
        void(*WriteGDS)(void *, D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords, UINT const *pCounterValues, UINT Flags);
        void(*ReadGDS)(void *, D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords, UINT *pCounterValues, UINT Flags);
        void(*VSSetShaderUserData)(void *, UINT StartSlot, UINT NumRegisters, UINT const *pData);
        void(*HSSetShaderUserData)(void *, UINT StartSlot, UINT NumRegisters, UINT const *pData);
        void(*DSSetShaderUserData)(void *, UINT StartSlot, UINT NumRegisters, UINT const *pData);
        void(*GSSetShaderUserData)(void *, UINT StartSlot, UINT NumRegisters, UINT const *pData);
        void(*PSSetShaderUserData)(void *, UINT StartSlot, UINT NumRegisters, UINT const *pData);
        void(*CSSetShaderUserData)(void *, UINT StartSlot, UINT NumRegisters, UINT const *pData);
        void(*InsertWaitOnMemory)(void *, void const *pAddress, UINT Flags, D3D11_COMPARISON_FUNC ComparisonFunction, UINT ReferenceValue, UINT Mask);
        void(*WriteTimestampToMemory)(void *, void *pDstAddress);
        void(*WriteTimestampToBuffer)(void *, gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetBytes);
        void(*StoreConstantRam)(void *, UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT BufferOffsetInBytes, UINT CeRamOffsetInBytes, UINT SizeInBytes);
        void(*LoadConstantRam)(void *, UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT BufferOffsetInBytes, UINT CeRamOffsetInBytes, UINT SizeInBytes);
        void(*WriteQuery)(void *, D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags, gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes, UINT StrideInBytes);
        void(*ResetQuery)(void *, D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags);
        void(*ConfigureQuery)(void *, D3D11_QUERY QueryType, void const *pConfiguration, UINT ConfigurationSize);
        void(*SetShaderUserData)(void *, D3D11X_HW_STAGE ShaderStage, UINT StartSlot, UINT NumRegisters, UINT const *pData);
        void(*SetPixelShaderDepthForceZOrder)(void *, BOOL ForceOrder);
        void(*SetPredicationFromQuery)(void *, D3D11_QUERY QueryType, gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes, UINT Flags);
        void(*SetBorderColorPalette)(void *, gfx::ID3D11Buffer<ABI> *pBuffer, UINT OffsetInBytes, UINT Flags);
        void(*WriteValueEndOfPipe64)(void *, void *pDestination, UINT64 Value, UINT Flags);
        void(*InsertWaitOnMemory64)(void *, void const *pAddress, UINT Flags, D3D11_COMPARISON_FUNC ComparisonFunction, UINT64 ReferenceValue);
        void(*LoadConstantRamImmediate)(void *, UINT Flags, void const *pBuffer, UINT CeRamOffsetInBytes, UINT SizeInBytes);
        void(*SetScreenExtentsQuery)(void *, UINT Value);
        void(*CollectScreenExtents)(void *, UINT Flags, UINT AddressCount, UINT64 const *pDestinationAddresses, USHORT ZMin, USHORT ZMax);
        void(*FillResourceWithValue)(void *, gfx::ID3D11Resource<ABI> *pDstResource, UINT FillValue);
        void(*SetDrawBalancing)(void *, UINT BalancingMode, UINT Flags);
    };
    
    template<abi_t ABI>
    struct ID3D11PerformanceContextX : gfx::ID3D11DeviceContextX<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11PerformanceContextXVtbl : gfx::ID3D11DeviceContextXVtbl<ABI>
    {
    };

    template <abi_t ABI>
    struct ID3D11UserDefinedAnnotationX : gfx::ID3D11DeviceContextX<ABI>
    {
    };

    template <abi_t ABI>
    struct ID3D11UserDefinedAnnotationXVtbl : gfx::ID3D11DeviceContextXVtbl<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11Device : xbox::IGraphicsUnknown<ABI>
    {
        virtual HRESULT CreateBuffer(D3D11_BUFFER_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData, gfx::ID3D11Buffer<ABI> **ppBuffer) = 0;
        virtual HRESULT CreateTexture1D(D3D11_TEXTURE1D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData, gfx::ID3D11Texture1D<ABI> **ppTexture1D) = 0;
        virtual HRESULT CreateTexture2D(D3D11_TEXTURE2D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData, gfx::ID3D11Texture2D<ABI> **ppTexture2D) = 0;
        virtual HRESULT CreateTexture3D(D3D11_TEXTURE3D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData, gfx::ID3D11Texture3D<ABI> **ppTexture3D) = 0;
        virtual HRESULT CreateShaderResourceView(gfx::ID3D11Resource<ABI> *pResource, D3D11_SHADER_RESOURCE_VIEW_DESC const *pDesc, gfx::ID3D11ShaderResourceView<ABI> **ppSRV) = 0;
        virtual HRESULT CreateUnorderedAccessView(gfx::ID3D11Resource<ABI> *pResource, D3D11_UNORDERED_ACCESS_VIEW_DESC const *pDesc, gfx::ID3D11UnorderedAccessView<ABI> **ppUAV) = 0;
        virtual HRESULT CreateRenderTargetView(gfx::ID3D11Resource<ABI> *pResource, D3D11_RENDER_TARGET_VIEW_DESC const *pDesc, gfx::ID3D11RenderTargetView<ABI> **ppRTV) = 0;
        virtual HRESULT CreateDepthStencilView(gfx::ID3D11Resource<ABI> *pResource, D3D11_DEPTH_STENCIL_VIEW_DESC const *pDesc, gfx::ID3D11DepthStencilView<ABI> **ppDSV) = 0;
        virtual HRESULT CreateInputLayout(D3D11_INPUT_ELEMENT_DESC const *pDesc, uint32_t NumElements, void const *pShaderBytecodeWithInputSignature, uint64_t BytecodeLength, ID3D11InputLayout **ppInputLayout) = 0;
        virtual HRESULT CreateVertexShader(void const *pBytecode, uint64_t BytecodeLength, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11VertexShader<ABI> **ppVS) = 0;
        virtual HRESULT CreateGeometryShader(void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11GeometryShader<ABI> **ppGS) = 0;
        virtual HRESULT CreateGeometryShaderWithStreamOutput(void const *pBytecode, uint64_t BytecodeLentgh, D3D11_SO_DECLARATION_ENTRY const *pSODeclaration, uint32_t NumEntries, uint32_t const *pStrides, uint32_t NumStides, uint32_t RasterizedStream, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11GeometryShader<ABI> **ppGS) = 0;
        virtual HRESULT CreatePixelShader(void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11PixelShader<ABI> **ppPS) = 0;
        virtual HRESULT CreateHullShader(void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11HullShader<ABI> **ppHS) = 0;
        virtual HRESULT CreateDomainShader(void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11DomainShader<ABI> **ppDS) = 0;
        virtual HRESULT CreateComputeShader(void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11ComputeShader<ABI> **ppCS) = 0;
        virtual HRESULT CreateClassLinkage(ID3D11ClassLinkage **ppClassLinkage) = 0;
        virtual HRESULT CreateBlendState(D3D11_BLEND_DESC const *pDesc, gfx::ID3D11BlendState<ABI> **ppBlendState) = 0;
        virtual HRESULT CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC const *pDesc, gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState) = 0;
        virtual HRESULT CreateRasterizerState(D3D11_RASTERIZER_DESC const *pDesc, gfx::ID3D11RasterizerState<ABI> **ppRasterizerState) = 0;
        virtual HRESULT CreateSamplerState(D3D11_SAMPLER_DESC const *pDesc, gfx::ID3D11SamplerState<ABI> **ppSamplerState) = 0;
        virtual HRESULT CreateQuery(D3D11_QUERY_DESC const *pDesc, ID3D11Query **ppQuery) = 0;
        virtual HRESULT CreatePredicate(D3D11_QUERY_DESC const *pDesc, ID3D11Predicate **ppPrediticate) = 0;
        virtual HRESULT CreateCounter(D3D11_COUNTER_DESC const *pDesc, ID3D11Counter **ppCounter) = 0;
        virtual HRESULT CreateDeferredContext(uint32_t Flags, gfx::ID3D11DeviceContext<ABI> **ppDeferredContext) = 0;
        virtual HRESULT OpenSharedResource(void *pResource, _GUID const &retInterface, void **ppResource) = 0;
        virtual HRESULT CheckFormatSupport(DXGI_FORMAT Format, uint32_t *pFormatSupport) = 0;
        virtual HRESULT CheckMultisampleQualityLevels(DXGI_FORMAT Format, uint32_t SampleCount, uint32_t *pNumQualityLevels) = 0;
        virtual void CheckCounterInfo(D3D11_COUNTER_INFO *pCounterInfo) = 0;
        virtual HRESULT CheckCounter(D3D11_COUNTER_DESC const *pDesc, D3D11_COUNTER_TYPE *pCounterType, uint32_t *pActiveCounters, char *szName, uint32_t *pNameLength, char *szUnits, uint32_t *pUnitsLength, char *szDescription, uint32_t *pDescriptionLength) = 0;
        virtual HRESULT CheckFeatureSupport(D3D11_FEATURE Feature, void *pFeatureSupportData, uint32_t FeatureSupportDataSize) = 0;
        virtual HRESULT GetPrivateData(_GUID const &guid, uint32_t *pDataSize, void *pData) = 0;
        virtual HRESULT SetPrivateData(_GUID const &guid, uint32_t DataSize, void const *pData) = 0;
        virtual HRESULT SetPrivateDataInterface(_GUID const &guid, IUnknown const *pData) = 0;
        virtual HRESULT SetPrivateDataInterfaceGraphics(_GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData) = 0;
        virtual D3D_FEATURE_LEVEL GetFeatureLevel() = 0;
        virtual uint32_t GetCreationFlags() = 0;
        virtual HRESULT GetDeviceRemovedReason() = 0;
        virtual void GetImmediateContext(gfx::ID3D11DeviceContext<ABI> **ppImmediateContext) = 0;
        virtual HRESULT SetExceptionMode(uint32_t ExceptionMode) = 0;
        virtual uint32_t GetExceptionMode() = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11DeviceVtbl : xbox::IGraphicsUnknownVtbl<ABI>
    {
        HRESULT(*CreateBuffer)(void *, D3D11_BUFFER_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData, gfx::ID3D11Buffer<ABI> **ppBuffer);
        HRESULT(*CreateTexture1D)(void *, D3D11_TEXTURE1D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData, gfx::ID3D11Texture1D<ABI> **ppTexture1D);
        HRESULT(*CreateTexture2D)(void *, D3D11_TEXTURE2D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData, gfx::ID3D11Texture2D<ABI> **ppTexture2D);
        HRESULT(*CreateTexture3D)(void *, D3D11_TEXTURE3D_DESC const *pDesc, D3D11_SUBRESOURCE_DATA const *pData, gfx::ID3D11Texture3D<ABI> **ppTexture3D);
        HRESULT(*CreateShaderResourceView)(void *, gfx::ID3D11Resource<ABI> *pResource, D3D11_SHADER_RESOURCE_VIEW_DESC const *pDesc, gfx::ID3D11ShaderResourceView<ABI> **ppSRV);
        HRESULT(*CreateUnorderedAccessView)(void *, gfx::ID3D11Resource<ABI> *pResource, D3D11_UNORDERED_ACCESS_VIEW_DESC const *pDesc, gfx::ID3D11UnorderedAccessView<ABI> **ppUAV);
        HRESULT(*CreateRenderTargetView)(void *, gfx::ID3D11Resource<ABI> *pResource, D3D11_RENDER_TARGET_VIEW_DESC const *pDesc, gfx::ID3D11RenderTargetView<ABI> **ppRTV);
        HRESULT(*CreateDepthStencilView)(void *, gfx::ID3D11Resource<ABI> *pResource, D3D11_DEPTH_STENCIL_VIEW_DESC const *pDesc, gfx::ID3D11DepthStencilView<ABI> **ppDSV);
        HRESULT(*CreateInputLayout)(void *, D3D11_INPUT_ELEMENT_DESC const *pDesc, uint32_t NumElements, void const *pShaderBytecodeWithInputSignature, uint64_t BytecodeLength, ID3D11InputLayout **ppInputLayout);
        HRESULT(*CreateVertexShader)(void *, void const *pBytecode, uint64_t BytecodeLength, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11VertexShader<ABI> **ppVS);
        HRESULT(*CreateGeometryShader)(void *, void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11GeometryShader<ABI> **ppGS);
        HRESULT(*CreateGeometryShaderWithStreamOutput)(void *, void const *pBytecode, uint64_t BytecodeLentgh, D3D11_SO_DECLARATION_ENTRY const *pSODeclaration, uint32_t NumEntries, uint32_t const *pStrides, uint32_t NumStides, uint32_t RasterizedStream, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11GeometryShader<ABI> **ppGS);
        HRESULT(*CreatePixelShader)(void *, void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11PixelShader<ABI> **ppPS);
        HRESULT(*CreateHullShader)(void *, void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11HullShader<ABI> **ppHS);
        HRESULT(*CreateDomainShader)(void *, void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11DomainShader<ABI> **ppDS);
        HRESULT(*CreateComputeShader)(void *, void const *pBytecode, uint64_t BytecodeLentgh, ID3D11ClassLinkage *pClassLinkage, gfx::ID3D11ComputeShader<ABI> **ppCS);
        HRESULT(*CreateClassLinkage)(void *, ID3D11ClassLinkage **ppClassLinkage);
        HRESULT(*CreateBlendState)(void *, D3D11_BLEND_DESC const *pDesc, gfx::ID3D11BlendState<ABI> **ppBlendState);
        HRESULT(*CreateDepthStencilState)(void *, D3D11_DEPTH_STENCIL_DESC const *pDesc, gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState);
        HRESULT(*CreateRasterizerState)(void *, D3D11_RASTERIZER_DESC const *pDesc, gfx::ID3D11RasterizerState<ABI> **ppRasterizerState);
        HRESULT(*CreateSamplerState)(void *, D3D11_SAMPLER_DESC const *pDesc, gfx::ID3D11SamplerState<ABI> **ppSamplerState);
        HRESULT(*CreateQuery)(void *, D3D11_QUERY_DESC const *pDesc, ID3D11Query **ppQuery);
        HRESULT(*CreatePredicate)(void *, D3D11_QUERY_DESC const *pDesc, ID3D11Predicate **ppPrediticate);
        HRESULT(*CreateCounter)(void *, D3D11_COUNTER_DESC const *pDesc, ID3D11Counter **ppCounter);
        HRESULT(*CreateDeferredContext)(void *, uint32_t Flags, gfx::ID3D11DeviceContext<ABI> **ppDeferredContext);
        HRESULT(*OpenSharedResource)(void *, void *pResource, _GUID const &retInterface, void **ppResource);
        HRESULT(*CheckFormatSupport)(void *, DXGI_FORMAT Format, uint32_t *pFormatSupport);
        HRESULT(*CheckMultisampleQualityLevels)(void *, DXGI_FORMAT Format, uint32_t SampleCount, uint32_t *pNumQualityLevels);
        void(*CheckCounterInfo)(void *, D3D11_COUNTER_INFO *pCounterInfo);
        HRESULT(*CheckCounter)(void *, D3D11_COUNTER_DESC const *pDesc, D3D11_COUNTER_TYPE *pCounterType, uint32_t *pActiveCounters, char *szName, uint32_t *pNameLength, char *szUnits, uint32_t *pUnitsLength, char *szDescription, uint32_t *pDescriptionLength);
        HRESULT(*CheckFeatureSupport)(void *, D3D11_FEATURE Feature, void *pFeatureSupportData, uint32_t FeatureSupportDataSize);
        HRESULT(*GetPrivateData)(void *, _GUID const &guid, uint32_t *pDataSize, void *pData);
        HRESULT(*SetPrivateData)(void *, _GUID const &guid, uint32_t DataSize, void const *pData);
        HRESULT(*SetPrivateDataInterface)(void *, _GUID const &guid, IUnknown const *pData);
        HRESULT(*SetPrivateDataInterfaceGraphics)(void *, _GUID const &guid, xbox::IGraphicsUnknown<ABI> const *pData);
        D3D_FEATURE_LEVEL(*GetFeatureLevel)(void *);
        uint32_t(*GetCreationFlags)(void *);
        HRESULT(*GetDeviceRemovedReason)(void *);
        void(*GetImmediateContext)(void *, gfx::ID3D11DeviceContext<ABI> **ppImmediateContext);
        HRESULT(*SetExceptionMode)(void *, uint32_t ExceptionMode);
        uint32_t(*GetExceptionMode)(void *);
    };
    
    template<abi_t ABI>
    struct ID3D11Device1 : gfx::ID3D11Device<ABI>
    {
        virtual void GetImmediateContext1(gfx::ID3D11DeviceContext1<ABI> **ppImmediateContext) = 0;
        virtual HRESULT CreateDeferredContext1(uint32_t Flags, gfx::ID3D11DeviceContext1<ABI> **ppDeferredContext1) = 0;
        virtual HRESULT CreateBlendState1(D3D11_BLEND_DESC1 const *pDesc, ID3D11BlendState1 **ppBlendState) = 0;
        virtual HRESULT CreateRasterizerState1(D3D11_RASTERIZER_DESC1 const *pDesc, ID3D11RasterizerState1 **ppRasterizerState) = 0;
        virtual HRESULT CreateDeviceContextState(uint32_t Flags, D3D_FEATURE_LEVEL const *pFeatureLevels, uint32_t FeatureLevels, uint32_t SDKVersion, _GUID const &EmulatedInterface, D3D_FEATURE_LEVEL *pChosenFeatureLevel, ID3DDeviceContextState **ppContextState) = 0;
        virtual HRESULT OpenSharedResource1(void *pResource, _GUID const &retInterface, void **ppResource) = 0;
        virtual HRESULT OpenSharedResourceByName(wchar_t const *pName, uint32_t dwDesiredAccess, _GUID const &retInterface, void **ppResource) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11Device1Vtbl : gfx::ID3D11DeviceVtbl<ABI>
    {
        void(*GetImmediateContext1)(void *, gfx::ID3D11DeviceContext1<ABI> **ppImmediateContext);
        HRESULT(*CreateDeferredContext1)(void *, uint32_t Flags, gfx::ID3D11DeviceContext1<ABI> **ppDeferredContext1);
        HRESULT(*CreateBlendState1)(void *, D3D11_BLEND_DESC1 const *pDesc, ID3D11BlendState1 **ppBlendState);
        HRESULT(*CreateRasterizerState1)(void *, D3D11_RASTERIZER_DESC1 const *pDesc, ID3D11RasterizerState1 **ppRasterizerState);
        HRESULT(*CreateDeviceContextState)(void *, uint32_t Flags, D3D_FEATURE_LEVEL const *pFeatureLevels, uint32_t FeatureLevels, uint32_t SDKVersion, _GUID const &EmulatedInterface, D3D_FEATURE_LEVEL *pChosenFeatureLevel, ID3DDeviceContextState **ppContextState);
        HRESULT(*OpenSharedResource1)(void *, void *pResource, _GUID const &retInterface, void **ppResource);
        HRESULT(*OpenSharedResourceByName)(void *, wchar_t const *pName, uint32_t dwDesiredAccess, _GUID const &retInterface, void **ppResource);
    };
    
    template<abi_t ABI>
    struct ID3D11Device2 : gfx::ID3D11Device1<ABI>
    {
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11Device2<ABI> : gfx::ID3D11Device1<ABI>
    {
        virtual void GetImmediateContext2(gfx::ID3D11DeviceContext2<ABI> **ppImmediateContext) = 0;
        virtual HRESULT CreateDeferredContext2(uint32_t Flags, gfx::ID3D11DeviceContext2<ABI> **ppDeferredContext) = 0;
        virtual void GetResourceTiling(gfx::ID3D11Resource<ABI> *pTiledResource, uint32_t *pNumTilesForEntireResource, D3D11_PACKED_MIP_DESC *pPackedMipDesc, D3D11_TILE_SHAPE *pStandardTileShapeForNonPackedMips, uint32_t *pNumSubresourceTilings, uint32_t FirstSubresourceTilingToGet, D3D11_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips) = 0;
        virtual HRESULT CheckMultisampleQualityLevels1(DXGI_FORMAT Format, uint32_t SampleCount, uint32_t Flags, uint32_t *pNumQualityLevels) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11Device2Vtbl : gfx::ID3D11Device1Vtbl<ABI>
    {
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11Device2Vtbl<ABI> : gfx::ID3D11Device1Vtbl<ABI>
    {
        void(*GetImmediateContext2)(void *, gfx::ID3D11DeviceContext2<ABI> **ppImmediateContext);
        HRESULT(*CreateDeferredContext2)(void *, uint32_t Flags, gfx::ID3D11DeviceContext2<ABI> **ppDeferredContext);
        void(*GetResourceTiling)(void *, gfx::ID3D11Resource<ABI> *pTiledResource, uint32_t *pNumTilesForEntireResource, D3D11_PACKED_MIP_DESC *pPackedMipDesc, D3D11_TILE_SHAPE *pStandardTileShapeForNonPackedMips, uint32_t *pNumSubresourceTilings, uint32_t FirstSubresourceTilingToGet, D3D11_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips);
        HRESULT(*CheckMultisampleQualityLevels1)(void *, DXGI_FORMAT Format, uint32_t SampleCount, uint32_t Flags, uint32_t *pNumQualityLevels);
    };
    
    template<abi_t ABI>
    struct ID3D11DMAEngineContextX : gfx::ID3D11DeviceChild<ABI>
    {
        virtual D3D11_DEVICE_CONTEXT_TYPE GetType() = 0;
        virtual void CopyResource(gfx::ID3D11Resource<ABI> *v1, gfx::ID3D11Resource<ABI> *v2, uint32_t v3) = 0;
        virtual void CopySubresourceRegion(gfx::ID3D11Resource<ABI> *v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, gfx::ID3D11Resource<ABI> *v6, uint32_t v7, D3D11_BOX const *v8, uint32_t v9) = 0;
        virtual HRESULT LZDecompressBuffer(gfx::ID3D11Buffer<ABI> *v1, uint32_t v2, gfx::ID3D11Buffer<ABI> *v3, uint32_t v4, uint32_t v5, uint32_t v6) = 0;
        virtual HRESULT LZDecompressTexture(gfx::ID3D11Resource<ABI> *v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, gfx::ID3D11Buffer<ABI> *v6, uint32_t v7) = 0;
        virtual HRESULT LZCompressBuffer(gfx::ID3D11Buffer<ABI> *v1, uint32_t v2, gfx::ID3D11Buffer<ABI> *v3, uint32_t v4, uint32_t v5, uint32_t v6) = 0;
        virtual HRESULT LZCompressTexture(gfx::ID3D11Buffer<ABI> *v1, gfx::ID3D11Resource<ABI> *v2, uint32_t v3, D3D11_BOX const *v4, uint32_t v5) = 0;
        virtual HRESULT JPEGDecode(gfx::ID3D11Resource<ABI> *v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, gfx::ID3D11Buffer<ABI> *v6, uint32_t v7) = 0;
        virtual uint64_t InsertFence(uint32_t v1) = 0;
        virtual void InsertWaitOnFence(uint32_t v1, uint64_t v2) = 0;
        virtual HRESULT Submit() = 0;
        virtual void CopyLastErrorCodeToMemory(void *v1) = 0;
        virtual void CopyLastErrorCodeToBuffer(gfx::ID3D11Buffer<ABI> *v1, uint32_t v2) = 0;
        virtual void CopyMemoryToMemory(void *v1, void *v2, uint64_t v3) = 0;
        virtual void FillMemoryWithValue(void *v1, uint64_t v2, uint32_t v3) = 0;
        virtual void FillResourceWithValue(gfx::ID3D11Resource<ABI> *v1, uint32_t v2) = 0;
        virtual HRESULT LZDecompressMemory(void *v1, void *v2, uint32_t v3, uint32_t v4) = 0;
        virtual HRESULT LZCompressMemory(void *v1, void *v2, uint32_t v3, uint32_t v4) = 0;
        virtual void WriteTimestampToMemory(void *v1) = 0;
        virtual void WriteTimestampToBuffer(gfx::ID3D11Buffer<ABI> *v1, uint32_t v2) = 0;
        virtual void WriteValueBottomOfPipe(void *v1, uint32_t v2) = 0;
        virtual void InsertWaitOnMemory(void const *v1, uint32_t v2, D3D11_COMPARISON_FUNC v3, uint32_t v4, uint32_t v5) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11DMAEngineContextXVtbl : gfx::ID3D11DeviceChildVtbl<ABI>
    {
        D3D11_DEVICE_CONTEXT_TYPE(*GetType)(void *);
        void(*CopyResource)(void *, gfx::ID3D11Resource<ABI> *v1, gfx::ID3D11Resource<ABI> *v2, uint32_t v3);
        void(*CopySubresourceRegion)(void *, gfx::ID3D11Resource<ABI> *v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, gfx::ID3D11Resource<ABI> *v6, uint32_t v7, D3D11_BOX const *v8, uint32_t v9);
        HRESULT(*LZDecompressBuffer)(void *, gfx::ID3D11Buffer<ABI> *v1, uint32_t v2, gfx::ID3D11Buffer<ABI> *v3, uint32_t v4, uint32_t v5, uint32_t v6);
        HRESULT(*LZDecompressTexture)(void *, gfx::ID3D11Resource<ABI> *v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, gfx::ID3D11Buffer<ABI> *v6, uint32_t v7);
        HRESULT(*LZCompressBuffer)(void *, gfx::ID3D11Buffer<ABI> *v1, uint32_t v2, gfx::ID3D11Buffer<ABI> *v3, uint32_t v4, uint32_t v5, uint32_t v6);
        HRESULT(*LZCompressTexture)(void *, gfx::ID3D11Buffer<ABI> *v1, gfx::ID3D11Resource<ABI> *v2, uint32_t v3, D3D11_BOX const *v4, uint32_t v5);
        HRESULT(*JPEGDecode)(void *, gfx::ID3D11Resource<ABI> *v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, gfx::ID3D11Buffer<ABI> *v6, uint32_t v7);
        uint64_t(*InsertFence)(void *, uint32_t v1);
        void(*InsertWaitOnFence)(void *, uint32_t v1, uint64_t v2);
        HRESULT(*Submit)(void *);
        void(*CopyLastErrorCodeToMemory)(void *, void *v1);
        void(*CopyLastErrorCodeToBuffer)(void *, gfx::ID3D11Buffer<ABI> *v1, uint32_t v2);
        void(*CopyMemoryToMemory)(void *, void *v1, void *v2, uint64_t v3);
        void(*FillMemoryWithValue)(void *, void *v1, uint64_t v2, uint32_t v3);
        void(*FillResourceWithValue)(void *, gfx::ID3D11Resource<ABI> *v1, uint32_t v2);
        HRESULT(*LZDecompressMemory)(void *, void *v1, void *v2, uint32_t v3, uint32_t v4);
        HRESULT(*LZCompressMemory)(void *, void *v1, void *v2, uint32_t v3, uint32_t v4);
        void(*WriteTimestampToMemory)(void *, void *v1);
        void(*WriteTimestampToBuffer)(void *, gfx::ID3D11Buffer<ABI> *v1, uint32_t v2);
        void(*WriteValueBottomOfPipe)(void *, void *v1, uint32_t v2);
        void(*InsertWaitOnMemory)(void *, void const *v1, uint32_t v2, D3D11_COMPARISON_FUNC v3, uint32_t v4, uint32_t v5);
    };
    
    template<abi_t ABI>
    struct ID3D11DeviceX : gfx::ID3D11Device2<ABI>
    {
        virtual void GetImmediateContextX(gfx::ID3D11DeviceContextX<ABI> **ppImmediateContextX) = 0;
        virtual HRESULT CreateCounterSet(D3D11X_COUNTER_SET_DESC const *pCounterSetDesc, ID3D11CounterSetX **ppCounterSet) = 0;
        virtual HRESULT CreateCounterSample(ID3D11CounterSampleX **ppCounterSample) = 0;
        virtual HRESULT SetDriverHint(UINT Feature, UINT Value) = 0;
        virtual HRESULT CreateDmaEngineContext(D3D11_DMA_ENGINE_CONTEXT_DESC const *pDmaEngineContextDesc,
                                               ID3D11DMAEngineContextX<ABI> **ppDmaDeviceContext) = 0;
        virtual BOOL IsFencePending(UINT64 Fence) = 0;
        virtual BOOL IsResourcePending(gfx::ID3D11Resource<ABI> *pResource) = 0;
        virtual HRESULT CreatePlacementBuffer(D3D11_BUFFER_DESC const *pDesc, void *pVirtualAddress, gfx::ID3D11Buffer<ABI> **ppBuffer) = 0;
        virtual HRESULT CreatePlacementTexture1D(D3D11_TEXTURE1D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture1D<ABI> **ppTexture1D) = 0;
        virtual HRESULT CreatePlacementTexture2D(D3D11_TEXTURE2D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture2D<ABI> **ppTexture2D) = 0;
        virtual HRESULT CreatePlacementTexture3D(D3D11_TEXTURE3D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture3D<ABI> **ppTexture3D) = 0;
        virtual void GetTimestamps(UINT64 *pGpuTimestamp, UINT64 *pCpuRdtscTimestamp) = 0;
        virtual HRESULT CreateComputeContextX(D3D11_COMPUTE_CONTEXT_DESC const *pComputeContextDesc, ID3D11ComputeContextX **ppComputeContext) = 0;
        virtual HRESULT CreateSamplerStateX(D3D11X_SAMPLER_DESC const *pSamplerDesc, gfx::ID3D11SamplerState<ABI> **ppSamplerState) = 0;
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11DeviceX<ABI> : gfx::ID3D11Device2<ABI>
    {
        virtual void GetImmediateContextX(gfx::ID3D11DeviceContextX<ABI> **ppImmediateContextX) = 0;
        virtual HRESULT CreateCounterSet(D3D11X_COUNTER_SET_DESC const *pCounterSetDesc, ID3D11CounterSetX **ppCounterSet) = 0;
        virtual HRESULT CreateCounterSample(ID3D11CounterSampleX **ppCounterSample) = 0;
        virtual HRESULT SetDriverHint(UINT Feature, UINT Value) = 0;
        virtual HRESULT CreateDmaEngineContext(D3D11_DMA_ENGINE_CONTEXT_DESC const *pDmaEngineContextDesc, ID3D11DMAEngineContextX<ABI> **ppDmaDeviceContext) = 0;
        virtual BOOL IsFencePending(UINT64 Fence) = 0;
        virtual BOOL IsResourcePending(gfx::ID3D11Resource<ABI> *pResource) = 0;
        virtual HRESULT CreatePlacementBuffer(D3D11_BUFFER_DESC const *pDesc, void *pVirtualAddress, gfx::ID3D11Buffer<ABI> **ppBuffer) = 0;
        virtual HRESULT CreatePlacementTexture1D(D3D11_TEXTURE1D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture1D<ABI> **ppTexture1D) = 0;
        virtual HRESULT CreatePlacementTexture2D(D3D11_TEXTURE2D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture2D<ABI> **ppTexture2D) = 0;
        virtual HRESULT CreatePlacementTexture3D(D3D11_TEXTURE3D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture3D<ABI> **ppTexture3D) = 0;
        virtual void GetTimestamps(UINT64 *pGpuTimestamp, UINT64 *pCpuRdtscTimestamp) = 0;
        virtual HRESULT CreateSamplerStateX(D3D11X_SAMPLER_DESC const *pSamplerDesc, gfx::ID3D11SamplerState<ABI> **ppSamplerState) = 0;
        virtual HRESULT CreateDeferredContextX(UINT Flags, gfx::ID3D11DeviceContextX<ABI> **ppDeferredContext) = 0;
        virtual void GarbageCollect(UINT Flags) = 0;
        virtual HRESULT CreateDepthStencilStateX(D3D11_DEPTH_STENCIL_DESC const *pDepthStencilStateDesc, gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState) = 0;
        virtual HRESULT CreatePlacementRenderableTexture2D(D3D11_TEXTURE2D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, D3D11X_RENDERABLE_TEXTURE_ADDRESSES const *pAddresses, gfx::ID3D11Texture2D<ABI> **ppTexture2D) = 0;
        virtual void GetDriverStatistics(UINT StructSize, D3D11X_DRIVER_STATISTICS *pStatistics) = 0;
        virtual HRESULT CreateComputeContextX(D3D11_COMPUTE_CONTEXT_DESC const *pComputeContextDesc, ID3D11ComputeContextX **ppComputeContext) = 0;
        virtual HRESULT GetDescriptorSize(D3D11X_DESCRIPTOR_TYPE DescriptorType) = 0;
        virtual void ComposeShaderResourceView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource, D3D11X_RESOURCE_VIEW_DESC const *pViewDesc, D3D11X_DESCRIPTOR_SHADER_RESOURCE_VIEW *pDescriptorSrv) = 0;
        virtual void ComposeUnorderedAccessView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource, D3D11X_RESOURCE_VIEW_DESC const *pViewDesc, D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW *pDescriptorUav) = 0;
        virtual void ComposeConstantBufferView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource, D3D11X_RESOURCE_VIEW_DESC const *pViewDesc, D3D11X_DESCRIPTOR_CONSTANT_BUFFER_VIEW *pDescriptorCb) = 0;
        virtual void ComposeVertexBufferView(gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource, D3D11X_RESOURCE_VIEW_DESC const *pViewDesc, D3D11X_DESCRIPTOR_VERTEX_BUFFER_VIEW *pDescriptorVb) = 0;
        virtual void ComposeSamplerState(D3D11X_SAMPLER_STATE_DESC const *pSamplerDesc, gfx::D3D11X_DESCRIPTOR_SAMPLER_STATE *pDescriptorSamplerState) = 0;
        virtual void PlaceSwapChainView(gfx::ID3D11Resource<ABI> *pSwapChainBuffer, gfx::ID3D11View<ABI> *pView) = 0;
        virtual void SetDebugFlags(UINT Flags) = 0;
        virtual uint32_t GetDebugFlags() = 0;
        virtual void SetHangCallbacks(D3D11XHANGBEGINCALLBACK pBeginCallback, D3D11XHANGPRINTCALLBACK pPrintCallback, D3D11XHANGDUMPCALLBACK pDumpCallback) = 0;
        virtual void ReportGpuHang(UINT Flags) = 0;
        virtual HRESULT SetGpuMemoryPriority(UINT Priority) = 0;
        virtual void GetGpuHardwareConfiguration(D3D11X_GPU_HARDWARE_CONFIGURATION *pGpuHardwareConfiguration) = 0;
    };
    
    template<abi_t ABI>
    struct ID3D11DeviceXVtbl : gfx::ID3D11Device2Vtbl<ABI>
    {
        void(*GetImmediateContextX)(void *, gfx::ID3D11DeviceContextX<ABI> **ppImmediateContextX);
        HRESULT(*CreateCounterSet)(void *, D3D11X_COUNTER_SET_DESC const *pCounterSetDesc, ID3D11CounterSetX **ppCounterSet);
        HRESULT(*CreateCounterSample)(void *, ID3D11CounterSampleX **ppCounterSample);
        HRESULT(*SetDriverHint)(void *, UINT Feature, UINT Value);
        HRESULT(*CreateDmaEngineContext)(void *, D3D11_DMA_ENGINE_CONTEXT_DESC const *pDmaEngineContextDesc, ID3D11DMAEngineContextX<ABI> **ppDmaDeviceContext);
        BOOL(*IsFencePending)(void *, UINT64 Fence);
        BOOL(*IsResourcePending)(void *, gfx::ID3D11Resource<ABI> *pResource);
        HRESULT(*CreatePlacementBuffer)(void *, D3D11_BUFFER_DESC const *pDesc, void *pVirtualAddress, gfx::ID3D11Buffer<ABI> **ppBuffer);
        HRESULT(*CreatePlacementTexture1D)(void *, D3D11_TEXTURE1D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture1D<ABI> **ppTexture1D);
        HRESULT(*CreatePlacementTexture2D)(void *, D3D11_TEXTURE2D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture2D<ABI> **ppTexture2D);
        HRESULT(*CreatePlacementTexture3D)(void *, D3D11_TEXTURE3D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture3D<ABI> **ppTexture3D);
        void(*GetTimestamps)(void *, UINT64 *pGpuTimestamp, UINT64 *pCpuRdtscTimestamp);
        HRESULT(*CreateComputeContextX)(void *, D3D11_COMPUTE_CONTEXT_DESC const *pComputeContextDesc, ID3D11ComputeContextX **ppComputeContext);
        HRESULT(*CreateSamplerStateX)(void *, D3D11X_SAMPLER_DESC const *pSamplerDesc, gfx::ID3D11SamplerState<ABI> **ppSamplerState);
    };
    
    template<abi_t ABI>
    requires (ABI >= abi_t{6,2,11274,0})
    struct ID3D11DeviceXVtbl<ABI> : gfx::ID3D11Device2Vtbl<ABI>
    {
        void(*GetImmediateContextX)(void *, gfx::ID3D11DeviceContextX<ABI> **ppImmediateContextX);
        HRESULT(*CreateCounterSet)(void *, D3D11X_COUNTER_SET_DESC const *pCounterSetDesc, ID3D11CounterSetX **ppCounterSet);
        HRESULT(*CreateCounterSample)(void *, ID3D11CounterSampleX **ppCounterSample);
        HRESULT(*SetDriverHint)(void *, UINT Feature, UINT Value);
        HRESULT (*CreateDmaEngineContext)(void *, D3D11_DMA_ENGINE_CONTEXT_DESC const *pDmaEngineContextDesc, ID3D11DMAEngineContextX<ABI> **ppDmaDeviceContext);
        BOOL(*IsFencePending)(void *, UINT64 Fence);
        BOOL(*IsResourcePending)(void *, gfx::ID3D11Resource<ABI> *pResource);
        HRESULT(*CreatePlacementBuffer)(void *, D3D11_BUFFER_DESC const *pDesc, void *pVirtualAddress, gfx::ID3D11Buffer<ABI> **ppBuffer);
        HRESULT(*CreatePlacementTexture1D)(void *, D3D11_TEXTURE1D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture1D<ABI> **ppTexture1D);
        HRESULT(*CreatePlacementTexture2D)(void *, D3D11_TEXTURE2D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture2D<ABI> **ppTexture2D);
        HRESULT(*CreatePlacementTexture3D)(void *, D3D11_TEXTURE3D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, void *pVirtualAddress, gfx::ID3D11Texture3D<ABI> **ppTexture3D);
        void(*GetTimestamps)(void *, UINT64 *pGpuTimestamp, UINT64 *pCpuRdtscTimestamp);
        HRESULT(*CreateSamplerStateX)(void *, D3D11X_SAMPLER_DESC const *pSamplerDesc, gfx::ID3D11SamplerState<ABI> **ppSamplerState);
        HRESULT(*CreateDeferredContextX)(void *, UINT Flags, gfx::ID3D11DeviceContextX<ABI> **ppDeferredContext);
        void(*GarbageCollect)(void *, UINT Flags);
        HRESULT(*CreateDepthStencilStateX)(void *, D3D11_DEPTH_STENCIL_DESC const *pDepthStencilStateDesc, gfx::ID3D11DepthStencilState<ABI> **ppDepthStencilState);
        HRESULT(*CreatePlacementRenderableTexture2D)(void *, D3D11_TEXTURE2D_DESC const *pDesc, UINT TileModeIndex, UINT Pitch, D3D11X_RENDERABLE_TEXTURE_ADDRESSES const *pAddresses, gfx::ID3D11Texture2D<ABI> **ppTexture2D);
        void(*GetDriverStatistics)(void *, UINT StructSize, D3D11X_DRIVER_STATISTICS *pStatistics);
        HRESULT(*CreateComputeContextX)(void *, D3D11_COMPUTE_CONTEXT_DESC const *pComputeContextDesc, ID3D11ComputeContextX **ppComputeContext);
        HRESULT(*GetDescriptorSize)(void *, D3D11X_DESCRIPTOR_TYPE DescriptorType);
        void(*ComposeShaderResourceView)(void *, gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource, D3D11X_RESOURCE_VIEW_DESC const *pViewDesc, D3D11X_DESCRIPTOR_SHADER_RESOURCE_VIEW *pDescriptorSrv);
        void(*ComposeUnorderedAccessView)(void *, gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource, D3D11X_RESOURCE_VIEW_DESC const *pViewDesc, D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW *pDescriptorUav);
        void(*ComposeConstantBufferView)(void *, gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource, D3D11X_RESOURCE_VIEW_DESC const *pViewDesc, D3D11X_DESCRIPTOR_CONSTANT_BUFFER_VIEW *pDescriptorCb);
        void(*ComposeVertexBufferView)(void *, gfx::D3D11X_DESCRIPTOR_RESOURCE const *pDescriptorResource, D3D11X_RESOURCE_VIEW_DESC const *pViewDesc, D3D11X_DESCRIPTOR_VERTEX_BUFFER_VIEW *pDescriptorVb);
        void(*ComposeSamplerState)(void *, D3D11X_SAMPLER_STATE_DESC const *pSamplerDesc, gfx::D3D11X_DESCRIPTOR_SAMPLER_STATE *pDescriptorSamplerState);
        void(*PlaceSwapChainView)(void *, gfx::ID3D11Resource<ABI> *pSwapChainBuffer, gfx::ID3D11View<ABI> *pView);
        void(*SetDebugFlags)(void *, UINT Flags);
        uint32_t(*GetDebugFlags)(void *);
        void(*SetHangCallbacks)(void *, D3D11XHANGBEGINCALLBACK pBeginCallback, D3D11XHANGPRINTCALLBACK pPrintCallback, D3D11XHANGDUMPCALLBACK pDumpCallback);
        void(*ReportGpuHang)(void *, UINT Flags);
        HRESULT(*SetGpuMemoryPriority)(void *, UINT Priority);
        void(*GetGpuHardwareConfiguration)(void *, D3D11X_GPU_HARDWARE_CONFIGURATION *pGpuHardwareConfiguration);
    };
    
    template<abi_t ABI>
    struct ID3D11PerformanceDeviceX : gfx::ID3D11DeviceX<ABI>
    {
    };
    
    template<abi_t ABI>
    struct ID3D11PerformanceDeviceXVtbl : gfx::ID3D11DeviceXVtbl<ABI>
    {
    };

    namespace details
    {
        template <abi_t ABI> struct IDXGIObjectData
        {
            void *m_pPrivateData;
        };
    }

    template <abi_t ABI> struct IDXGIObject : xbox::IGraphicsUnknown<ABI>, details::IDXGIObjectData<ABI>
    {
        virtual HRESULT SetPrivateData(GUID const &Name, uint32_t DataSize, void const *pData) = 0;
        virtual HRESULT SetPrivateDataInterface(GUID const &Name, IUnknown const *pUnknown) = 0;
        virtual HRESULT SetPrivateDataInterfaceGraphics(_GUID const &Name,
                                                        xbox::IGraphicsUnknown<ABI> const *pData) = 0;
        virtual HRESULT GetPrivateData(_GUID const &Name, UINT *pDataSize, void *pData) = 0;
        virtual HRESULT GetParent(_GUID const &riid, void **ppParent) = 0;
    };

    template <abi_t ABI> struct IDXGIObjectVtbl : xbox::IGraphicsUnknownVtbl<ABI>
    {
        HRESULT (*SetPrivateData)(void *, GUID const &Name, uint32_t DataSize, void const *pData);
        HRESULT (*SetPrivateDataInterface)(void *, GUID const &Name, IUnknown const *pUnknown);
        HRESULT (*SetPrivateDataInterfaceGraphics)(void *, _GUID const &Name, xbox::IGraphicsUnknown<ABI> const *pData);
        HRESULT (*GetPrivateData)(void *, _GUID const &Name, UINT *pDataSize, void *pData);
        HRESULT (*GetParent)(void *, _GUID const &riid, void **ppParent);
    };

    template <abi_t ABI>
        requires(ABI >= abi_t{6, 2, 1004, 0})
    struct IDXGIObject<ABI> : xbox::IGraphicsUnknown<ABI>, details::IDXGIObjectData<ABI>
    {
        virtual HRESULT SetPrivateData(GUID const &Name, uint32_t DataSize, void const *pData) = 0;
        virtual HRESULT SetPrivateDataInterface(GUID const &Name, IUnknown const *pUnknown) = 0;
        virtual HRESULT GetPrivateData(_GUID const &Name, UINT *pDataSize, void *pData) = 0;
        virtual HRESULT GetParent(_GUID const &riid, void **ppParent) = 0;
    };

    template <abi_t ABI>
        requires(ABI >= abi_t{6, 2, 13004, 0})
    struct IDXGIObjectVtbl<ABI> : xbox::IGraphicsUnknownVtbl<ABI>
    {
        HRESULT (*SetPrivateData)(void *, GUID const &Name, uint32_t DataSize, void const *pData);
        HRESULT (*SetPrivateDataInterface)(void *, GUID const &Name, IUnknown const *pUnknown);
        HRESULT (*GetPrivateData)(void *, _GUID const &Name, UINT *pDataSize, void *pData);
        HRESULT (*GetParent)(void *, _GUID const &riid, void **ppParent);
    };

    namespace details
    {
        template <abi_t ABI> struct IDXGIDeviceData
        {
            gfx::ID3D11Device<ABI> *m_pDevice;
        };
    }

    template <abi_t ABI> struct IDXGIDevice : gfx::IDXGIObject<ABI>, details::IDXGIDeviceData<ABI>
    {
        virtual HRESULT GetAdapter(gfx::IDXGIAdapter<ABI> **pAdapter) = 0;
        virtual HRESULT CreateSurface(DXGI_SURFACE_DESC const *pDesc, uint32_t NumSurfaces, DXGI_USAGE Usage,
                                      DXGI_SHARED_RESOURCE const *pSharedResource, IDXGISurface **ppSurface) = 0;
        virtual HRESULT QueryResourceResidency(xbox::IGraphicsUnknown<ABI> **ppResources,
                                               DXGI_RESIDENCY *pResidencyStatus, uint32_t NumResources) = 0;
        virtual HRESULT SetGPUThreadPriority(int Priority) = 0;
        virtual HRESULT GetGPUThreadPriority(int *pPriority) = 0;
    };

    template <abi_t ABI> struct IDXGIDeviceVtbl : gfx::IDXGIObjectVtbl<ABI>
    {
        HRESULT (*GetAdapter)(void *, gfx::IDXGIAdapter<ABI> **pAdapter);
        HRESULT (*CreateSurface)(void *, DXGI_SURFACE_DESC const *pDesc, uint32_t NumSurfaces, DXGI_USAGE Usage,
                                 DXGI_SHARED_RESOURCE const *pSharedResource, IDXGISurface **ppSurface);
        HRESULT (*QueryResourceResidency)(void *, xbox::IGraphicsUnknown<ABI> **ppResources,
                                          DXGI_RESIDENCY *pResidencyStatus, uint32_t NumResources);
        HRESULT (*SetGPUThreadPriority)(void *, int Priority);
        HRESULT (*GetGPUThreadPriority)(void *, int *pPriority);
    };

    template <abi_t ABI> struct IDXGIDevice1 : gfx::IDXGIDevice<ABI>
    {
        virtual HRESULT SetMaximumFrameLatency(uint32_t MaxLatency) = 0;
        virtual HRESULT GetMaximumFrameLatency(uint32_t *pMaxLatency) = 0;
    };

    template <abi_t ABI> struct IDXGIDevice1Vtbl : gfx::IDXGIDeviceVtbl<ABI>
    {
        HRESULT (*SetMaximumFrameLatency)(void *, uint32_t MaxLatency);
        HRESULT (*GetMaximumFrameLatency)(void *, uint32_t *pMaxLatency);
    };

    template <abi_t ABI> struct IDXGIDevice2 : gfx::IDXGIDevice1<ABI>
    {
        virtual HRESULT OfferResources(uint32_t NumResources, IDXGIResource *const *ppResources,
                                       DXGI_OFFER_RESOURCE_PRIORITY Priority) = 0;
        virtual HRESULT ReclaimResources(uint32_t NumResources, IDXGIResource *const *ppResources,
                                         bool *pDiscarded) = 0;
        virtual HRESULT EnqueueSetEvent(void *hEvent) = 0;
    };

    template <abi_t ABI> struct IDXGIDevice2Vtbl : gfx::IDXGIDevice1Vtbl<ABI>
    {
        HRESULT (*OfferResources)(void *, uint32_t NumResources, IDXGIResource *const *ppResources,
                                  DXGI_OFFER_RESOURCE_PRIORITY Priority);
        HRESULT (*ReclaimResources)(void *, uint32_t NumResources, IDXGIResource *const *ppResources, bool *pDiscarded);
        HRESULT (*EnqueueSetEvent)(void *, void *hEvent);
    };

    template <abi_t ABI> struct IDXGIAdapter : gfx::IDXGIObject<ABI>
    {
        virtual HRESULT EnumOutputs(UINT Output, IDXGIOutput **ppOutput) = 0;
        virtual HRESULT GetDesc(DXGI_ADAPTER_DESC *pDesc) = 0;
        virtual HRESULT CheckInterfaceSupport(_GUID const &InterfaceName, LARGE_INTEGER *pUMDVersion) = 0;
    };

    template <abi_t ABI> struct IDXGIAdapterVtbl : gfx::IDXGIObjectVtbl<ABI>
    {
        HRESULT (*EnumOutputs)(void *, UINT Output, IDXGIOutput **ppOutput);
        HRESULT (*GetDesc)(void *, DXGI_ADAPTER_DESC *pDesc);
        HRESULT (*CheckInterfaceSupport)(void *, _GUID const &InterfaceName, LARGE_INTEGER *pUMDVersion);
    };

    template <abi_t ABI> struct IDXGIAdapter1 : gfx::IDXGIAdapter<ABI>
    {
        virtual HRESULT GetDesc1(DXGI_ADAPTER_DESC1 *pDesc) = 0;
    };

    template <abi_t ABI> struct IDXGIAdapter1Vtbl : gfx::IDXGIAdapterVtbl<ABI>
    {
        HRESULT (*GetDesc1)(void *, DXGI_ADAPTER_DESC1 *pDesc);
    };

    template <abi_t ABI> struct IDXGIDeviceSubObject : gfx::IDXGIObject<ABI>
    {
        virtual HRESULT GetDevice(REFIID riid, void **ppDevice) = 0;
    };

    template <abi_t ABI> struct IDXGIDeviceSubObjectVtbl : gfx::IDXGIObjectVtbl<ABI>
    {
        HRESULT (*GetDevice)(void *, REFIID riid, void **ppDevice);
    };

    template <abi_t ABI> struct IDXGISwapChain : gfx::IDXGIDeviceSubObject<ABI>
    {
        virtual HRESULT Present(uint32_t SyncInterval, uint32_t Flags) = 0;
        virtual HRESULT GetBuffer(UINT Buffer, REFIID riid, void **ppSurface) = 0;
        virtual HRESULT SetFullscreenState(bool Fullscreen, IDXGIOutput *pTarget) = 0;
        virtual HRESULT GetFullscreenState(bool *pFullscreen, IDXGIOutput **ppTarget) = 0;
        virtual HRESULT GetDesc(DXGI_SWAP_CHAIN_DESC *pDesc) = 0;
        virtual HRESULT ResizeBuffers(uint32_t BufferCount, uint32_t Width, uint32_t Height, DXGI_FORMAT NewFormat,
                                      uint32_t SwapChainFlags) = 0;
        virtual HRESULT ResizeTarget(DXGI_MODE_DESC const *pNewTargetParameters) = 0;
        virtual HRESULT GetContainingOutput(IDXGIOutput **ppOutput) = 0;
        virtual HRESULT GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats) = 0;
        virtual HRESULT GetLastPresentCount(uint32_t *pLastPresentCount) = 0;
    };

    template <abi_t ABI> struct IDXGISwapChainVtbl : gfx::IDXGIDeviceSubObjectVtbl<ABI>
    {
        HRESULT (*Present)(void *, uint32_t SyncInterval, uint32_t Flags);
        HRESULT (*GetBuffer)(void *, UINT Buffer, REFIID riid, void **ppSurface);
        HRESULT (*SetFullscreenState)(void *, bool Fullscreen, IDXGIOutput *pTarget);
        HRESULT (*GetFullscreenState)(void *, bool *pFullscreen, IDXGIOutput **ppTarget);
        HRESULT (*GetDesc)(void *, DXGI_SWAP_CHAIN_DESC *pDesc);
        HRESULT (*ResizeBuffers)(void *, uint32_t BufferCount, uint32_t Width, uint32_t Height, DXGI_FORMAT NewFormat,
                                 uint32_t SwapChainFlags);
        HRESULT (*ResizeTarget)(void *, DXGI_MODE_DESC const *pNewTargetParameters);
        HRESULT (*GetContainingOutput)(void *, IDXGIOutput **ppOutput);
        HRESULT (*GetFrameStatistics)(void *, DXGI_FRAME_STATISTICS *pStats);
        HRESULT (*GetLastPresentCount)(void *, uint32_t *pLastPresentCount);
    };

    template <abi_t ABI> struct IDXGISwapChain1 : gfx::IDXGISwapChain<ABI>
    {
        virtual HRESULT GetDesc1(DXGI_SWAP_CHAIN_DESC1 *pDesc) = 0;
        virtual HRESULT GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc) = 0;
        virtual HRESULT GetHwnd(HWND *pHwnd) = 0;
        virtual HRESULT GetCoreWindow(REFIID refiid, void **ppUnk) = 0;
        virtual HRESULT Present1(uint32_t SyncInterval, uint32_t PresentFlags,
                                 DXGI_PRESENT_PARAMETERS const *pPresentParameters) = 0;
        virtual bool IsTemporaryMonoSupported() = 0;
        virtual HRESULT GetRestrictToOutput(IDXGIOutput **ppRestrictToOutput) = 0;
        virtual HRESULT SetBackgroundColor(DXGI_RGBA const *pColor) = 0;
        virtual HRESULT GetBackgroundColor(DXGI_RGBA *pColor) = 0;
        virtual HRESULT SetRotation(DXGI_MODE_ROTATION Rotation) = 0;
        virtual HRESULT GetRotation(DXGI_MODE_ROTATION *pRotation) = 0;
    };

    template <abi_t ABI> struct IDXGISwapChain1Vtbl : gfx::IDXGISwapChainVtbl<ABI>
    {
        HRESULT (*GetDesc1)(void *, DXGI_SWAP_CHAIN_DESC1 *pDesc);
        HRESULT (*GetFullscreenDesc)(void *, DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc);
        HRESULT (*GetHwnd)(void *, HWND *pHwnd);
        HRESULT (*GetCoreWindow)(void *, REFIID refiid, void **ppUnk);
        HRESULT (*Present1)(void *, uint32_t SyncInterval, uint32_t PresentFlags,
                            DXGI_PRESENT_PARAMETERS const *pPresentParameters);
        bool (*IsTemporaryMonoSupported)(void *);
        HRESULT (*GetRestrictToOutput)(void *, IDXGIOutput **ppRestrictToOutput);
        HRESULT (*SetBackgroundColor)(void *, DXGI_RGBA const *pColor);
        HRESULT (*GetBackgroundColor)(void *, DXGI_RGBA *pColor);
        HRESULT (*SetRotation)(void *, DXGI_MODE_ROTATION Rotation);
        HRESULT (*GetRotation)(void *, DXGI_MODE_ROTATION *pRotation);
    };

    namespace details
    {
        template <abi_t ABI> struct IDXGIFactoryData
        {
            IDXGIAdapter2 *m_pAdapter;
        };
    } // namespace details

    template <abi_t ABI> struct IDXGIFactory : gfx::IDXGIObject<ABI>, details::IDXGIFactoryData<ABI>
    {
        virtual HRESULT EnumAdapters(UINT Adapter, gfx::IDXGIAdapter<ABI> **ppAdapter) = 0;
        virtual HRESULT MakeWindowAssociation(HWND WindowHandle, UINT Flags) = 0;
        virtual HRESULT GetWindowAssociation(HWND *pWindowHandle) = 0;
        virtual HRESULT CreateSwapChain(xbox::IGraphicsUnknown<ABI> *pDevice, DXGI_SWAP_CHAIN_DESC *pDesc,
                                        gfx::IDXGISwapChain<ABI> **ppSwapChain) = 0;
        virtual HRESULT CreateSoftwareAdapter(HMODULE Module, gfx::IDXGIAdapter<ABI> **ppAdapter) = 0;
    };

    template <abi_t ABI> struct IDXGIFactoryVtbl : gfx::IDXGIObjectVtbl<ABI>
    {
        HRESULT (*EnumAdapters)(void *, UINT Adapter, gfx::IDXGIAdapter<ABI> **ppAdapter);
        HRESULT (*MakeWindowAssociation)(void *, HWND WindowHandle, UINT Flags);
        HRESULT (*GetWindowAssociation)(void *, HWND *pWindowHandle);
        HRESULT (*CreateSwapChain)(void *, xbox::IGraphicsUnknown<ABI> *pDevice, DXGI_SWAP_CHAIN_DESC *pDesc,
                                   gfx::IDXGISwapChain<ABI> **ppSwapChain);
        HRESULT (*CreateSoftwareAdapter)(void *, HMODULE Module, gfx::IDXGIAdapter<ABI> **ppAdapter);
    };

    template <abi_t ABI> struct IDXGIFactory1 : gfx::IDXGIFactory<ABI>
    {
        virtual HRESULT EnumAdapters1(UINT Adapter, gfx::IDXGIAdapter1<ABI> **ppAdapter) = 0;
        virtual bool IsCurrent() = 0;
    };

    template <abi_t ABI> struct IDXGIFactory1Vtbl : gfx::IDXGIFactoryVtbl<ABI>
    {
        HRESULT (*EnumAdapters1)(void *, UINT Adapter, gfx::IDXGIAdapter1<ABI> **ppAdapter);
        bool (*IsCurrent)(void *);
    };

    template <abi_t ABI> struct IDXGIFactory2 : gfx::IDXGIFactory1<ABI>
    {
        virtual bool IsWindowedStereoEnabled() = 0;
        virtual HRESULT CreateSwapChainForHwnd(xbox::IGraphicsUnknown<ABI> *pDevice, HWND hWnd,
                                               DXGI_SWAP_CHAIN_DESC1 const *pDesc,
                                               DXGI_SWAP_CHAIN_FULLSCREEN_DESC const *pFullscreenDesc,
                                               IDXGIOutput *pRestrictToOutput,
                                               gfx::IDXGISwapChain1<ABI> **ppSwapChain) = 0;
        virtual HRESULT CreateSwapChainForCoreWindow(xbox::IGraphicsUnknown<ABI> *pDevice, IUnknown *pWindow,
                                                     DXGI_SWAP_CHAIN_DESC1 *pDesc, IDXGIOutput *pRestrictToOutput,
                                                     gfx::IDXGISwapChain1<ABI> **ppSwapChain) = 0;
        virtual HRESULT GetSharedResourceAdapterLuid(void *hResource, _LUID *pLuid) = 0;
        virtual HRESULT RegisterStereoStatusWindow(HWND WindowHandle, uint32_t wMsg, uint32_t *pdwCookie) = 0;
        virtual HRESULT RegisterStereoStatusEvent(void *hEvent, uint32_t *pdwCookie) = 0;
        virtual void UnregisterStereoStatus(uint32_t dwCookie) = 0;
        virtual HRESULT RegisterOcclusionStatusWindow(HWND WindowHandle, uint32_t wMsg, uint32_t *pdwCookie) = 0;
        virtual HRESULT RegisterOcclusionStatusEvent(void *hEvent, uint32_t *pdwCookie) = 0;
        virtual void UnregisterOcclusionStatus(uint32_t dwCookie) = 0;
        virtual HRESULT CreateSwapChainForComposition(xbox::IGraphicsUnknown<ABI> *pDevice,
                                                      DXGI_SWAP_CHAIN_DESC1 const *pDesc,
                                                      IDXGIOutput *pRestrictToOutput,
                                                      gfx::IDXGISwapChain1<ABI> **ppSwapChain) = 0;
    };

    template <abi_t ABI> struct IDXGIFactory2Vtbl : gfx::IDXGIFactory1Vtbl<ABI>
    {
        bool (*IsWindowedStereoEnabled)(void *);
        HRESULT (*CreateSwapChainForHwnd)(void *, xbox::IGraphicsUnknown<ABI> *pDevice, HWND hWnd,
                                          DXGI_SWAP_CHAIN_DESC1 const *pDesc,
                                          DXGI_SWAP_CHAIN_FULLSCREEN_DESC const *pFullscreenDesc,
                                          IDXGIOutput *pRestrictToOutput, gfx::IDXGISwapChain1<ABI> **ppSwapChain);
        HRESULT (*CreateSwapChainForCoreWindow)(void *, xbox::IGraphicsUnknown<ABI> *pDevice, IUnknown *pWindow,
                                                DXGI_SWAP_CHAIN_DESC1 *pDesc, IDXGIOutput *pRestrictToOutput,
                                                gfx::IDXGISwapChain1<ABI> **ppSwapChain);
        HRESULT (*GetSharedResourceAdapterLuid)(void *, void *hResource, _LUID *pLuid);
        HRESULT (*RegisterStereoStatusWindow)(void *, HWND WindowHandle, uint32_t wMsg, uint32_t *pdwCookie);
        HRESULT (*RegisterStereoStatusEvent)(void *, void *hEvent, uint32_t *pdwCookie);
        void (*UnregisterStereoStatus)(void *, uint32_t dwCookie);
        HRESULT (*RegisterOcclusionStatusWindow)(void *, HWND WindowHandle, uint32_t wMsg, uint32_t *pdwCookie);
        HRESULT (*RegisterOcclusionStatusEvent)(void *, void *hEvent, uint32_t *pdwCookie);
        void (*UnregisterOcclusionStatus)(void *, uint32_t dwCookie);
        HRESULT (*CreateSwapChainForComposition)(void *, xbox::IGraphicsUnknown<ABI> *pDevice,
                                                 DXGI_SWAP_CHAIN_DESC1 const *pDesc, IDXGIOutput *pRestrictToOutput,
                                                 gfx::IDXGISwapChain1<ABI> **ppSwapChain);
    };
}

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11DeviceChild, 0x1841E5C8,0x16B0,0x489B,0xBC,0xC8,0x44,0xCF,0xB0,0xD5,0xDE,0xAE)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11Resource, 0xDC8E63F3,0xD12B,0x4952,0xB4,0x7B,0x5E,0x45,0x02,0x6A,0x86,0x2D)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11Texture1D, 0xF8FB5C27,0xC6B3,0x4F75,0xA4,0xC8,0x43,0x9A,0xF2,0xEF,0x56,0x4C)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11Texture2D, 0x6F15AAF2,0xD208,0x4E89,0x9A,0xB4,0x48,0x95,0x35,0xD3,0x4F,0x9C)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11Texture3D, 0x037E866E,0xF56D,0x4357,0xA8,0xAF,0x9D,0xAB,0xBE,0x6E,0x25,0x0E)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11Buffer, 0x48570B85,0xD1EE,0x4FCD,0xA2,0x50,0xEB,0x35,0x07,0x22,0xB0,0x37)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11VertexShader, 0x3B301D64,0xD678,0x4289,0x88,0x97,0x22,0xF8,0x92,0x8B,0x72,0xF3)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11PixelShader, 0xEA82E40D,0x51DC,0x4F33,0x93,0xD4,0xDB,0x7C,0x91,0x25,0xAE,0x8C)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11ComputeShader, 0x4F5B196E,0xC2BD,0x495E,0xBD,0x01,0x1F,0xDE,0xD3,0x8E,0x49,0x69)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11GeometryShader, 0x38325B96,0xEFFB,0x4022,0xBA,0x02,0x2E,0x79,0x5B,0x70,0x27,0x5C)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11HullShader, 0x8E5C6061,0x628A,0x4C8E,0x82,0x64,0xBB,0xE4,0x5C,0xB3,0xD5,0xDD)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11DomainShader, 0xF582C508,0x0F36,0x490C,0x99,0x77,0x31,0xEE,0xCE,0x26,0x8C,0xFA)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11SamplerState, 0xDA6FEA51,0x564C,0x4487,0x98,0x10,0xF0,0xD0,0xF9,0xB4,0xE3,0xA5)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11RasterizerState, 0x9BB4AB81,0xAB1A,0x4D8F,0xB5,0x06,0xFC,0x04,0x20,0x0B,0x6E,0xE7)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11BlendState, 0x75B68FAA,0x347D,0x4159,0x8F,0x45,0xA0,0x64,0x0F,0x01,0xCD,0x9A)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11DepthStencilState, 0x03823EFB,0x8D8F,0x4E1C,0x9A,0xA2,0xF6,0x4B,0xB2,0xCB,0xFD,0xF1)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11View, 0x839D1216,0xBB2E,0x412B,0xB7,0xF4,0xA9,0xDB,0xEB,0xE0,0x8E,0xD1)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11ShaderResourceView, 0xB0E06FE0,0x8192,0x4E1A,0xB1,0xCA,0x36,0xD7,0x41,0x47,0x10,0xB2)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11RenderTargetView, 0xDFDBA067,0x0B8D,0x4865,0x87,0x5B,0xD7,0xB4,0x51,0x6C,0xC1,0x64)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11DepthStencilView, 0x9FDAC92A,0x1876,0x48C3,0xAF,0xAD,0x25,0xB9,0x4F,0x84,0xA9,0xB6)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11UnorderedAccessView, 0xB0E06FE0,0x8192,0x4E1A,0xB1,0xCA,0x36,0xD7,0x41,0x47,0x10,0xB2)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11DeviceContext, 0xC0BFA96C,0xE089,0x44FB,0x8E,0xAF,0x26,0xF8,0x79,0x61,0x90,0xDA)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11DeviceContext1, 0xBB2C6FAA,0xB5FB,0x4082,0x8E,0x6B,0x38,0x8B,0x8C,0xFA,0x90,0xE1)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11DeviceContext2, 0x420D5B32,0xB90C,0x4DA4,0xBE,0xF0,0x35,0x9F,0x6A,0x24,0xA8,0x3A)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11DeviceContextX, 0x48800095,0x7134,0x4BE7,0x91,0x86,0xB8,0x6B,0xEC,0xB2,0x64,0x77)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11PerformanceContextX, 0x9458FE06,0xC78D,0x47F7,0x96,0xA0,0xEC,0x7B,0x72,0x7B,0xE1,0xE9)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11UserDefinedAnnotationX, 0xB2DAAD8B, 0x03D4, 0x4DBF, 0x95, 0xEB, 0x32, 0xAB, 0x4B, 0x63, 0xD0, 0xAB)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11Device, 0xDB6F6DDB,0xAC77,0x4E88,0x82,0x53,0x81,0x9D,0xF9,0xBB,0xF1,0x40)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11Device1, 0xA04BFB29,0x08EF,0x43D6,0xA4,0x9C,0xA9,0xBD,0xBD,0xCB,0xE6,0x86)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11Device2, 0xA04BFB29,0x08EF,0x43D6,0xA4,0x9C,0xA9,0xBD,0xBD,0xCB,0xE6,0x86)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11DMAEngineContextX, 0x1841E5C8,0x16B0,0x489B,0xBC,0xC8,0x44,0xCF,0xB0,0xD5,0xDE,0xAE)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11DeviceX, 0x177700F9,0x876A,0x4436,0xB3,0x68,0x36,0xA6,0x04,0xF8,0x2C,0xEF)

DECLARE_ABI_UUIDOF_HELPER(gfx::ID3D11PerformanceDeviceX, 0x88671610,0x712E,0x4F1E,0x84,0xAB,0x01,0xB5,0x94,0x8B,0xD3,0x73)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGIObject, 0xAEC22FB8, 0x76F3, 0x4639, 0x9B, 0xE0, 0x28, 0xEB, 0x43, 0xA6, 0x7A, 0x2E)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGIDevice, 0x54EC77FA, 0x1377, 0x44E6, 0x8C, 0x32, 0x88, 0xFD, 0x5F, 0x44, 0xC8, 0x4C)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGIDevice1, 0x77DB970F, 0x6276, 0x48BA, 0xBA, 0x28, 0x07, 0x01, 0x43, 0xB4, 0x39, 0x2C)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGIDevice2, 0x05008617, 0xFBFD, 0x4051, 0xA7, 0x90, 0x14, 0x48, 0x84, 0xB4, 0xF6, 0xA9)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGIAdapter, 0x2411E7E1, 0x12AC, 0x4CCF, 0xBD, 0x14, 0x97, 0x98, 0xE8, 0x53, 0x4D, 0xC0)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGIAdapter1, 0x29038F61, 0x3839, 0x4626, 0x91, 0xFD, 0x08, 0x68, 0x79, 0x01, 0x1A, 0x05)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGIDeviceSubObject, 0x3D3E0379, 0xF9DE, 0x4D58, 0xBB, 0x6C, 0x18, 0xD6, 0x29, 0x92, 0xF1, 0xA6)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGISwapChain, 0x310D36A0, 0xD2E7, 0x4C0A, 0xAA, 0x04, 0x6A, 0x9D, 0x23, 0xB8, 0x88, 0x6A)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGISwapChain1, 0x310D36A0, 0xD2E7, 0x4C0A, 0xAA, 0x04, 0x6A, 0x9D, 0x23, 0xB8, 0x88, 0x6A)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGIFactory, 0x7B7166EC, 0x21C7, 0x44AE, 0xB2, 0x1A, 0xC9, 0xAE, 0x32, 0x1A, 0xE3, 0x69)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGIFactory1, 0x29038F61, 0x3839, 0x4626, 0x91, 0xFD, 0x08, 0x68, 0x79, 0x01, 0x1A, 0x05)

DECLARE_ABI_UUIDOF_HELPER(gfx::IDXGIFactory2, 0x29038F61, 0x3839, 0x4626, 0x91, 0xFD, 0x08, 0x68, 0x79, 0x01, 0x1A, 0x05)

template<template<abi_t> typename T>
inline HRESULT d3d11CreateInstance(abi_t ABI, void **ppvObject)
{
    if (ppvObject == nullptr)
        return E_POINTER;
    
    if (ABI >= abi_t{10,0,19041,3453})
        *ppvObject = new T<abi_t{10,0,19041,3453}>();
    else if (ABI >= abi_t{10,0,14393,2152})
        *ppvObject = new T<abi_t{10,0,14393,2152}>();
    else if (ABI >= abi_t{10,0,10586,1225})
        *ppvObject = new T<abi_t{10,0,14393,2152}>();
    else if (ABI >= abi_t{6,2,13004,0})
        *ppvObject = new T<abi_t{6,2,13004,0}>();
    else if (ABI >= abi_t{6,2,11294,0})
        *ppvObject = new T<abi_t{6,2,11294,0}>();
    else if (ABI >= abi_t{6,2,11274,0})
        *ppvObject = new T<abi_t{6,2,11274,0}>();
    else if (ABI >= abi_t{6,2,10698,0})
        *ppvObject = new T<abi_t{6,2,10698,0}>();
    else if (ABI >= abi_t{6,2,11064,0})
        *ppvObject = new T<abi_t{6,2,11274,0}>();
    else
        *ppvObject = new T<abi_t{}>();
    
    return S_OK;
}

#define D3D11_DECLARE_ABI_TEMPLATES(prefix) \
    prefix template class ABI_INTERFACE((abi_t{0,0,0,0})); \
    prefix template class ABI_INTERFACE((abi_t{6,2,10698,0})); \
    prefix template class ABI_INTERFACE((abi_t{6,2,11064,0})); \
    prefix template class ABI_INTERFACE((abi_t{6,2,11274,0})); \
    prefix template class ABI_INTERFACE((abi_t{6,2,11294,0})); \
    prefix template class ABI_INTERFACE((abi_t{6,2,13004,0})); \
    prefix template class ABI_INTERFACE((abi_t{10,0,14393,2152})); \
    prefix template class ABI_INTERFACE((abi_t{10,0,19041,3453}))

#endif // __d3d11_x_g_h__

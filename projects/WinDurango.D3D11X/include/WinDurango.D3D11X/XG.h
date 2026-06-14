#include <Windows.h>
#include <d3d11.h>
#include "d3d11.x.h"

enum XG_USAGE
{
    XG_USAGE_DEFAULT = 0,
    XG_USAGE_IMMUTABLE = 1,
    XG_USAGE_DYNAMIC = 2,
    XG_USAGE_STAGING = 3
};

enum XG_BIND_FLAG
{
    XG_BIND_VERTEX_BUFFER = 0x1,
    XG_BIND_INDEX_BUFFER = 0x2,
    XG_BIND_CONSTANT_BUFFER = 0x4,
    XG_BIND_SHADER_RESOURCE = 0x8,
    XG_BIND_STREAM_OUTPUT = 0x10,
    XG_BIND_RENDER_TARGET = 0x20,
    XG_BIND_DEPTH_STENCIL = 0x40,
    XG_BIND_UNORDERED_ACCESS = 0x80,
    XG_BIND_DECODER = 0x200,
    XG_BIND_VIDEO_ENCODER = 0x400
};

enum XG_PLANE_USAGE
{
    XG_PLANE_USAGE_UNUSED = 0,
    XG_PLANE_USAGE_DEFAULT = 1,
    XG_PLANE_USAGE_COLOR_MASK = 2,
    XG_PLANE_USAGE_FRAGMENT_MASK = 3,
    XG_PLANE_USAGE_HTILE = 4,
    XG_PLANE_USAGE_LUMA = 5,
    XG_PLANE_USAGE_CHROMA = 6,
    XG_PLANE_USAGE_DEPTH = 7,
    XG_PLANE_USAGE_STENCIL = 8,
    XG_PLANE_USAGE_DELTA_COLOR_COMPRESSION = 9,
};

enum XG_TILE_MODE
{
    XG_TILE_MODE_INVALID = -1,
    XG_TILE_MODE_COMP_DEPTH_0 = 0,
    XG_TILE_MODE_COMP_DEPTH_1 = 1,
    XG_TILE_MODE_COMP_DEPTH_2 = 2,
    XG_TILE_MODE_COMP_DEPTH_3 = 3,
    XG_TILE_MODE_COMP_DEPTH_4 = 4,
    XG_TILE_MODE_UNC_DEPTH_5 = 5,
    XG_TILE_MODE_UNC_DEPTH_6 = 6,
    XG_TILE_MODE_UNC_DEPTH_7 = 7,
    XG_TILE_MODE_LINEAR = 8,
    XG_TILE_MODE_DISPLAY = 9,
    XG_TILE_MODE_2D_DISPLAY = 10,
    XG_TILE_MODE_TILED_DISPLAY = 11,
    XG_TILE_MODE_TILED_2D_DISPLAY = 12,
    XG_TILE_MODE_1D_THIN = 13,
    XG_TILE_MODE_2D_THIN = 14,
    XG_TILE_MODE_3D_THIN = 15,
    XG_TILE_MODE_TILED_1D_THIN = 16,
    XG_TILE_MODE_TILED_2D_THIN = 17,
    XG_TILE_MODE_TILED_3D_THIN = 18,
    XG_TILE_MODE_1D_THICK = 19,
    XG_TILE_MODE_2D_THICK = 20,
    XG_TILE_MODE_3D_THICK = 21,
    XG_TILE_MODE_TILED_1D_THICK = 22,
    XG_TILE_MODE_TILED_2D_THICK = 23,
    XG_TILE_MODE_TILED_3D_THICK = 24,
    XG_TILE_MODE_2D_XTHICK = 25,
    XG_TILE_MODE_3D_XTHICK = 26,
    XG_TILE_MODE_RESERVED_27 = 27,
    XG_TILE_MODE_RESERVED_28 = 28,
    XG_TILE_MODE_RESERVED_29 = 29,
    XG_TILE_MODE_RESERVED_30 = 30,
    XG_TILE_MODE_LINEAR_GENERAL = 31,
    XG_TILE_MODE_TILED_2D_DEPTH = XG_TILE_MODE_UNC_DEPTH_7,
};

enum XG_RESOURCE_DIMENSION
{
    XG_RESOURCE_DIMENSION_UNKNOWN = 0,
    XG_RESOURCE_DIMENSION_BUFFER = 1,
    XG_RESOURCE_DIMENSION_TEXTURE1D = 2,
    XG_RESOURCE_DIMENSION_TEXTURE2D = 3,
    XG_RESOURCE_DIMENSION_TEXTURE3D = 4
};

enum XG_FORMAT
{
    XG_FORMAT_UNKNOWN = 0,
    XG_FORMAT_R32G32B32A32_TYPELESS = 1,
    XG_FORMAT_R32G32B32A32_FLOAT = 2,
    XG_FORMAT_R32G32B32A32_UINT = 3,
    XG_FORMAT_R32G32B32A32_SINT = 4,
    XG_FORMAT_R32G32B32_TYPELESS = 5,
    XG_FORMAT_R32G32B32_FLOAT = 6,
    XG_FORMAT_R32G32B32_UINT = 7,
    XG_FORMAT_R32G32B32_SINT = 8,
    XG_FORMAT_R16G16B16A16_TYPELESS = 9,
    XG_FORMAT_R16G16B16A16_FLOAT = 10,
    XG_FORMAT_R16G16B16A16_UNORM = 11,
    XG_FORMAT_R16G16B16A16_UINT = 12,
    XG_FORMAT_R16G16B16A16_SNORM = 13,
    XG_FORMAT_R16G16B16A16_SINT = 14,
    XG_FORMAT_R32G32_TYPELESS = 15,
    XG_FORMAT_R32G32_FLOAT = 16,
    XG_FORMAT_R32G32_UINT = 17,
    XG_FORMAT_R32G32_SINT = 18,
    XG_FORMAT_R32G8X24_TYPELESS = 19,
    XG_FORMAT_D32_FLOAT_S8X24_UINT = 20,
    XG_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
    XG_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
    XG_FORMAT_R10G10B10A2_TYPELESS = 23,
    XG_FORMAT_R10G10B10A2_UNORM = 24,
    XG_FORMAT_R10G10B10A2_UINT = 25,
    XG_FORMAT_R11G11B10_FLOAT = 26,
    XG_FORMAT_R8G8B8A8_TYPELESS = 27,
    XG_FORMAT_R8G8B8A8_UNORM = 28,
    XG_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
    XG_FORMAT_R8G8B8A8_UINT = 30,
    XG_FORMAT_R8G8B8A8_SNORM = 31,
    XG_FORMAT_R8G8B8A8_SINT = 32,
    XG_FORMAT_R16G16_TYPELESS = 33,
    XG_FORMAT_R16G16_FLOAT = 34,
    XG_FORMAT_R16G16_UNORM = 35,
    XG_FORMAT_R16G16_UINT = 36,
    XG_FORMAT_R16G16_SNORM = 37,
    XG_FORMAT_R16G16_SINT = 38,
    XG_FORMAT_R32_TYPELESS = 39,
    XG_FORMAT_D32_FLOAT = 40,
    XG_FORMAT_R32_FLOAT = 41,
    XG_FORMAT_R32_UINT = 42,
    XG_FORMAT_R32_SINT = 43,
    XG_FORMAT_R24G8_TYPELESS = 44,
    XG_FORMAT_D24_UNORM_S8_UINT = 45,
    XG_FORMAT_R24_UNORM_X8_TYPELESS = 46,
    XG_FORMAT_X24_TYPELESS_G8_UINT = 47,
    XG_FORMAT_R8G8_TYPELESS = 48,
    XG_FORMAT_R8G8_UNORM = 49,
    XG_FORMAT_R8G8_UINT = 50,
    XG_FORMAT_R8G8_SNORM = 51,
    XG_FORMAT_R8G8_SINT = 52,
    XG_FORMAT_R16_TYPELESS = 53,
    XG_FORMAT_R16_FLOAT = 54,
    XG_FORMAT_D16_UNORM = 55,
    XG_FORMAT_R16_UNORM = 56,
    XG_FORMAT_R16_UINT = 57,
    XG_FORMAT_R16_SNORM = 58,
    XG_FORMAT_R16_SINT = 59,
    XG_FORMAT_R8_TYPELESS = 60,
    XG_FORMAT_R8_UNORM = 61,
    XG_FORMAT_R8_UINT = 62,
    XG_FORMAT_R8_SNORM = 63,
    XG_FORMAT_R8_SINT = 64,
    XG_FORMAT_A8_UNORM = 65,
    XG_FORMAT_R1_UNORM = 66,
    XG_FORMAT_R9G9B9E5_SHAREDEXP = 67,
    XG_FORMAT_R8G8_B8G8_UNORM = 68,
    XG_FORMAT_G8R8_G8B8_UNORM = 69,
    XG_FORMAT_BC1_TYPELESS = 70,
    XG_FORMAT_BC1_UNORM = 71,
    XG_FORMAT_BC1_UNORM_SRGB = 72,
    XG_FORMAT_BC2_TYPELESS = 73,
    XG_FORMAT_BC2_UNORM = 74,
    XG_FORMAT_BC2_UNORM_SRGB = 75,
    XG_FORMAT_BC3_TYPELESS = 76,
    XG_FORMAT_BC3_UNORM = 77,
    XG_FORMAT_BC3_UNORM_SRGB = 78,
    XG_FORMAT_BC4_TYPELESS = 79,
    XG_FORMAT_BC4_UNORM = 80,
    XG_FORMAT_BC4_SNORM = 81,
    XG_FORMAT_BC5_TYPELESS = 82,
    XG_FORMAT_BC5_UNORM = 83,
    XG_FORMAT_BC5_SNORM = 84,
    XG_FORMAT_B5G6R5_UNORM = 85,
    XG_FORMAT_B5G5R5A1_UNORM = 86,
    XG_FORMAT_B8G8R8A8_UNORM = 87,
    XG_FORMAT_B8G8R8X8_UNORM = 88,
    XG_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
    XG_FORMAT_B8G8R8A8_TYPELESS = 90,
    XG_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
    XG_FORMAT_B8G8R8X8_TYPELESS = 92,
    XG_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
    XG_FORMAT_BC6H_TYPELESS = 94,
    XG_FORMAT_BC6H_UF16 = 95,
    XG_FORMAT_BC6H_SF16 = 96,
    XG_FORMAT_BC7_TYPELESS = 97,
    XG_FORMAT_BC7_UNORM = 98,
    XG_FORMAT_BC7_UNORM_SRGB = 99,
    XG_FORMAT_AYUV = 100,
    XG_FORMAT_Y410 = 101,
    XG_FORMAT_Y416 = 102,
    XG_FORMAT_NV12 = 103,
    XG_FORMAT_P010 = 104,
    XG_FORMAT_P016 = 105,
    XG_FORMAT_420_OPAQUE = 106,
    XG_FORMAT_YUY2 = 107,
    XG_FORMAT_Y210 = 108,
    XG_FORMAT_Y216 = 109,
    XG_FORMAT_NV11 = 110,
    XG_FORMAT_AI44 = 111,
    XG_FORMAT_IA44 = 112,
    XG_FORMAT_P8 = 113,
    XG_FORMAT_A8P8 = 114,
    XG_FORMAT_B4G4R4A4_UNORM = 115,
    XG_FORMAT_R10G10B10_7E3_A2_FLOAT = 116,
    XG_FORMAT_R10G10B10_6E4_A2_FLOAT = 117,
    XG_FORMAT_D16_UNORM_S8_UINT = 118,
    XG_FORMAT_R16_UNORM_X8_TYPELESS = 119,
    XG_FORMAT_X16_TYPELESS_G8_UINT = 120,
    XG_FORMAT_FORCE_UINT = -1,
};

struct XG_SAMPLE_DESC
{
    UINT Count;
    UINT Quality;
};

struct XG_TEXTURE1D_DESC
{
    UINT Width;
    UINT MipLevels;
    UINT ArraySize;
    XG_FORMAT Format;
    XG_USAGE Usage;
    UINT BindFlags;
    UINT CPUAccessFlags;
    UINT MiscFlags;
    UINT ESRAMOffsetBytes;
    UINT ESRAMUsageBytes;
    XG_TILE_MODE TileMode;
    UINT Pitch;
};

struct XG_TEXTURE2D_DESC
{
    UINT Width;
    UINT Height;
    UINT MipLevels;
    UINT ArraySize;
    XG_FORMAT Format;
    XG_SAMPLE_DESC SampleDesc;
    XG_USAGE Usage;
    UINT BindFlags;
    UINT CPUAccessFlags;
    UINT MiscFlags;
    UINT ESRAMOffsetBytes;
    UINT ESRAMUsageBytes;
    XG_TILE_MODE TileMode;
    UINT Pitch;
};

struct XG_TEXTURE3D_DESC
{
    UINT Width;
    UINT Height;
    UINT Depth;
    UINT MipLevels;
    XG_FORMAT Format;
    XG_USAGE Usage;
    UINT BindFlags;
    UINT CPUAccessFlags;
    UINT MiscFlags;
    UINT ESRAMOffsetBytes;
    UINT ESRAMUsageBytes;
    XG_TILE_MODE TileMode;
    UINT Pitch;
};

struct XG_MIPLEVEL_LAYOUT
{
    ULONG SizeBytes;
    ULONG OffsetBytes;
    ULONG Slice2DSizeBytes;
    UINT PitchPixels;
    UINT PitchBytes;
    UINT AlignmentBytes;
    UINT PaddedWidthElements;
    UINT PaddedHeightElements;
    UINT PaddedDepthOrArraySize;
    UINT WidthElements;
    UINT HeightElements;
    UINT DepthOrArraySize;
    UINT SampleCount;
    XG_TILE_MODE TileMode;
    ULONG BankRotationAddressBitMask;
    ULONG BankRotationBytesPerSlice;
    UINT SliceDepthElements;
};

struct XG_PLANE_LAYOUT
{
    XG_PLANE_USAGE Usage;
    ULONG SizeBytes;
    ULONG BaseOffsetBytes;
    ULONG BaseAlignmentBytes;
    UINT BytesPerElement;
    XG_MIPLEVEL_LAYOUT* MipLayout;
};

struct XG_RESOURCE_LAYOUT
{
    ULONG SizeBytes;
    ULONG BaseAlignmentBytes;
    UINT MipLevels;
    UINT Planes;
    XG_PLANE_LAYOUT* Plane;

    XG_RESOURCE_DIMENSION Dimension;
};

struct XG_PACKED_MIP_DESC
{
    unsigned char NumStandardMips;
    unsigned char NumPackedMips;
    uint32_t NumTilesForPackedMips;
    uint32_t StartTileIndexInOverallResource;
};

struct XG_TILE_SHAPE
{
    uint32_t WidthInTexels;
    uint32_t HeightInTexels;
    uint32_t DepthInTexels;
};

struct XG_SUBRESOURCE_TILING
{
    uint32_t WidthInTiles;
    uint16_t HeightInTiles;
    uint16_t DepthInTiles;
    uint32_t StartTileIndexInOverallResource;
};
struct XGTextureAddressComputer_vtable;

struct XGTextureAddressComputer
{
    XGTextureAddressComputer_vtable* vt;
};

struct XGTextureAddressComputer_vtable
{
    uint32_t(*AddRef)(XGTextureAddressComputer*);
    uint32_t(*Release)(XGTextureAddressComputer*);
    int32_t(*GetResourceLayout)(XGTextureAddressComputer*, XG_RESOURCE_LAYOUT*);
    uint64_t(*GetMipLevelOffsetBytes)(XGTextureAddressComputer*, uint32_t, uint32_t);
    uint64_t(*GetTexelElementOffsetBytes)(XGTextureAddressComputer*, uint32_t, uint32_t, uint64_t, uint32_t, uint32_t, uint32_t);
    int32_t(*CopyIntoSubresource)(XGTextureAddressComputer*, void*, uint32_t, uint32_t, const void*, uint32_t, uint32_t);
    int32_t(*CopyFromSubresource)(XGTextureAddressComputer*, void*, uint32_t, uint32_t, const void*, uint32_t, uint32_t);
    int32_t(*GetResourceTiling)(XGTextureAddressComputer*, uint32_t*, XG_PACKED_MIP_DESC*, XG_TILE_SHAPE*, uint32_t*, uint32_t, XG_SUBRESOURCE_TILING*);
};

extern "C"
{
    typedef int (*XGCreateTexture1DComputer)(XG_TEXTURE1D_DESC* desc, XGTextureAddressComputer** computer);
    typedef int (*XGCreateTexture2DComputer)(XG_TEXTURE2D_DESC* desc, XGTextureAddressComputer** computer);
    typedef int (*XGCreateTexture3DComputer)(XG_TEXTURE3D_DESC* desc, XGTextureAddressComputer** computer);
}

HMODULE g_XboxGraphicsModule = nullptr;
XGCreateTexture2DComputer g_XGCreateTexture2DComputer = nullptr;

HRESULT CopyFromSubresourceChecked(XGTextureAddressComputer* Computer, UINT Subresource, void* pVirtualAddress, UINT RowPitch, UINT SlicePitch, BYTE** DetiledData)
{
    __try
    {
        Computer->vt->CopyFromSubresource(Computer, (*DetiledData), 0, Subresource, pVirtualAddress, RowPitch, SlicePitch);
        return S_OK;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return E_FAIL;
    }
}

HRESULT DetileTexture2D(UINT TileModeIndex, D3D11_TEXTURE2D_DESC* pDesc, void* pVirtualAddress, BYTE** DetiledData, UINT RowPitch, UINT SlicePitch)
{
    if (!pDesc)
        return E_FAIL;

    XG_TEXTURE2D_DESC desc{};
    desc.ArraySize = pDesc->ArraySize;
    desc.BindFlags = pDesc->BindFlags;
    desc.CPUAccessFlags = pDesc->CPUAccessFlags;
    desc.Format = (XG_FORMAT)pDesc->Format;
    desc.MipLevels = 1;
    desc.MiscFlags = pDesc->MiscFlags;
    desc.TileMode = (XG_TILE_MODE)TileModeIndex;
    desc.Height = pDesc->Height;
    desc.Width = pDesc->Width;
    desc.SampleDesc.Count = pDesc->SampleDesc.Count;
    desc.SampleDesc.Quality = pDesc->SampleDesc.Quality;
    desc.Pitch = 0;
    desc.ESRAMOffsetBytes = 0;
    desc.ESRAMUsageBytes = 0;
    desc.Usage = (XG_USAGE)pDesc->Usage;

    if (!g_XboxGraphicsModule)
    {
        g_XboxGraphicsModule = LoadLibraryW(L"xg_x.dll");
    }

    if (g_XboxGraphicsModule)
    {
        XGTextureAddressComputer* compWrapper = {};

        if (!g_XGCreateTexture2DComputer)
            g_XGCreateTexture2DComputer = (XGCreateTexture2DComputer)GetProcAddress(g_XboxGraphicsModule, "XGCreateTexture2DComputer");

        HRESULT hr = g_XGCreateTexture2DComputer(&desc, &compWrapper);
        if (FAILED(hr))
            return hr;

        BYTE *Detiled = new BYTE[SlicePitch];
        hr = CopyFromSubresourceChecked(compWrapper, 0, pVirtualAddress, RowPitch, SlicePitch, &Detiled);

        __try
        {
            memcpy((*DetiledData), Detiled, SlicePitch);
            delete[] Detiled;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            memcpy((*DetiledData), pVirtualAddress, SlicePitch);
            __try
            {
                delete[] Detiled;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {

            }
        }

        compWrapper->vt->Release(compWrapper);

        return hr;
    }

    MessageBoxA(nullptr, "xg_x.dll could not be found by DetileTexture2D! Make sure to copy it over to the executable folder.", "ERROR", MB_ICONERROR);
    return E_FAIL;
}

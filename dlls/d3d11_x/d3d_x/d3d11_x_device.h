#pragma once
#include <cstdio>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_2.h>

// thanks to Zombie for the idea
#define DX_MAJOR 2
#define DX_MINOR 18

#define MAKEINTVERSION(major, minor) (((0LL + (major)) << 48) | ((0LL + (minor)) << 32))
#define DX_VERSION (((0LL + (DX_MAJOR)) << 48) | ((0LL + (DX_MINOR)) << 32))

#define D3DDECL_UUID(Uuid) __declspec(uuid(#Uuid))
#define D3DINTERFACE(Name, Guid0, Guid1, Guid2, Guid3, Guid4, \
            Guid5, Guid6, Guid7, Guid8, Guid9, Guid10) \
            class D3DDECL_UUID(Guid0-Guid1-Guid2-Guid3##Guid4-Guid5##Guid6##Guid7##Guid8##Guid9##Guid10) Name

namespace d3d11x
{
	D3DINTERFACE(IGraphicsUnknown, aceeea63, e0a9, 4a1c, bb, ec, 71, b2, f4, 85, f7, 58)
	{
	public:

#if !defined(DX_VERSION) || DX_VERSION >= MAKEINTVERSION(2, 18)
		ULONG m_DeviceIndex : 3;
		ULONG m_PrivateDataPresent : 1;
		ULONG m_Reserved : 28;
#endif

#if !defined(DX_VERSION) || DX_VERSION >= MAKEINTVERSION(1, 1)
		ULONG m_RefCount;
#endif

		virtual HRESULT QueryInterface(REFIID riid, void** ppvObject) = 0;
		virtual ULONG AddRef( ) = 0;
		virtual ULONG Release( ) = 0;
	};

	class GraphicsUnknownWrapperX : public IGraphicsUnknown
	{
	public:
		GraphicsUnknownWrapperX(IUnknown* pUnknown)
		{
			m_RefCount = 1;
			m_pUnknown = pUnknown;
		}

		GraphicsUnknownWrapperX( )
		{
			m_RefCount = 1;
			m_pUnknown = nullptr;
		}

		HRESULT QueryInterface(REFIID riid, void** ppvObject) override
		{
			// note from unixian: for debugging purposes
			char iidstr[ sizeof("{AAAAAAAA-BBBB-CCCC-DDEE-FFGGHHIIJJKK}") ];
			OLECHAR iidwstr[ sizeof(iidstr) ];
			StringFromGUID2(riid, iidwstr, ARRAYSIZE(iidwstr));
			WideCharToMultiByte(CP_UTF8, 0, iidwstr, -1, iidstr, sizeof(iidstr), nullptr, nullptr);
			printf("[GraphicsUnknownWrapperX] QueryInterface: %s\n", iidstr);

			if (m_pUnknown)
				return m_pUnknown->QueryInterface(riid, ppvObject);

			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}

		ULONG AddRef( ) override
		{
			if (m_pUnknown)
				return m_pUnknown->AddRef( );

			return InterlockedIncrement(&m_RefCount);
		}

		ULONG Release( ) override
		{
			ULONG refCount = InterlockedDecrement(&m_RefCount);

			if (m_pUnknown)
				m_pUnknown->Release( );

			if (refCount == 0)
			{
				delete this;
			}
			return refCount;
		}

	private:
		IUnknown* m_pUnknown;
	};

	// Wrappers
	class ID3D11Buffer_X;
	class ID3D11BufferWrapper;
	class ID3D11RenderTargetView_X;
	class ID3D11UnorderedAccessView_X;
	class ID3D11ShaderResourceView_X;
	class ID3D11DepthStencilView_X;
	class ID3D11RenderTargetViewWrapper;
	class IDXGIDeviceWrapper;
	class ID3D11Texture2DWrapper;
	class ID3D11Texture1D_X;
	class ID3D11Texture2D_X;
	class ID3D11Texture3D_X;

	// D3D11.X forward declarations
	class IGraphicsUnknown;
	class ID3D11DeviceContext;
	class ID3D11DeviceContextX;
	class ID3D11CounterSetX;
	class ID3D11CounterSampleX;
	class ID3D11DmaEngineContextX;
	class ID3D11ComputeContextX;
	struct D3D11X_COUNTER_SET_DESC;
	struct D3D11X_DESCRIPTOR_RESOURCE;
	struct D3D11_DMA_ENGINE_CONTEXT_DESC;
	struct D3D11X_SAMPLER_DESC;
	struct D3D11X_RENDERABLE_TEXTURE_ADDRESSES;
	struct D3D11X_DRIVER_STATISTICS;
	struct D3D11_COMPUTE_CONTEXT_DESC;
	struct D3D11X_RESOURCE_VIEW_DESC;
	struct D3D11X_DESCRIPTOR_SHADER_RESOURCE_VIEW;
	struct D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW;
	struct D3D11X_DESCRIPTOR_CONSTANT_BUFFER_VIEW;
	struct D3D11X_DESCRIPTOR_VERTEX_BUFFER_VIEW;
	struct D3D11X_SAMPLER_STATE_DESC;
	struct D3D11X_DESCRIPTOR_SAMPLER_STATE;
	typedef enum D3D11X_HARDWARE_VERSION
	{
		D3D11X_HARDWARE_VERSION_XBOX_ONE = 0,
		D3D11X_HARDWARE_VERSION_XBOX_ONE_S = 1,
		D3D11X_HARDWARE_VERSION_XBOX_ONE_X = 2,
		D3D11X_HARDWARE_VERSION_XBOX_ONE_X_DEVKIT = 3
	} D3D11X_HARDWARE_VERSION;
	struct D3D11X_GPU_HARDWARE_CONFIGURATION {
		UINT64 GpuFrequency;
		D3D11X_HARDWARE_VERSION HardwareVersion;
		UINT32 GpuCuCount;
	};


	typedef UINT(*D3D11XHANGBEGINCALLBACK) (UINT64 Flags);
	typedef void (*D3D11XHANGPRINTCALLBACK) (const CHAR* strLine);
	typedef void (*D3D11XHANGDUMPCALLBACK) (const WCHAR* strFileName);

	D3DINTERFACE(ID3D11Device, db6f6ddb, ac77, 4e88, 82, 53, 81, 9d, f9, bb, f1, 40) : public IGraphicsUnknown
	{
	public:
		UINT m_CreationFlags;

		virtual HRESULT CreateBuffer(_In_ const D3D11_BUFFER_DESC* pDesc,
			_In_opt_ const D3D11_SUBRESOURCE_DATA* pInitialData,
			_Out_opt_ d3d11x::ID3D11Buffer_X** ppBuffer) = 0;

		virtual HRESULT CreateTexture1D(_In_ const D3D11_TEXTURE1D_DESC* pDesc,
			_In_reads_opt_(_Inexpressible_(pDesc->MipLevels* pDesc->ArraySize)) const D3D11_SUBRESOURCE_DATA* pInitialData,
			_Out_opt_ ID3D11Texture1D_X** ppTexture1D) = 0;

		virtual HRESULT CreateTexture2D(_In_ D3D11_TEXTURE2D_DESC* pDesc,
			_In_reads_opt_(_Inexpressible_(pDesc->MipLevels* pDesc->ArraySize)) const D3D11_SUBRESOURCE_DATA* pInitialData,
			_Out_opt_ ID3D11Texture2D_X** ppTexture2D) = 0;

		virtual HRESULT CreateTexture3D(_In_ const D3D11_TEXTURE3D_DESC* pDesc,
			_In_reads_opt_(_Inexpressible_(pDesc->MipLevels)) const D3D11_SUBRESOURCE_DATA* pInitialData,
			_Out_opt_ ID3D11Texture3D_X** ppTexture3D) = 0;

		virtual HRESULT CreateShaderResourceView(_In_ ID3D11Resource* pResource,
			_In_opt_ const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc,
			_Out_opt_ ID3D11ShaderResourceView_X** ppSRView) = 0;

		virtual HRESULT CreateUnorderedAccessView(_In_ ID3D11Resource* pResource,
			_In_opt_ const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc,
			_Out_opt_ ID3D11UnorderedAccessView_X** ppUAView) = 0;

		virtual HRESULT CreateRenderTargetView(_In_ ID3D11Resource* pResource,
			_In_opt_ const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
			_Out_opt_ ID3D11RenderTargetView_X** ppRTView) = 0;

		virtual HRESULT CreateDepthStencilView(
			_In_ ID3D11Resource* pResource,
			_In_opt_ const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
			_Out_opt_ ID3D11DepthStencilView_X** ppDepthStencilView) = 0;

		virtual HRESULT CreateInputLayout(
			_In_reads_(NumElements) const D3D11_INPUT_ELEMENT_DESC * pInputElementDescs,
			_In_range_(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT) UINT NumElements,
			_In_ const void* pShaderBytecodeWithInputSignature,
			_In_ SIZE_T BytecodeLength,
			_Out_opt_ ID3D11InputLayout * *ppInputLayout) = 0;

		virtual HRESULT CreateVertexShader(
			_In_ const void* pShaderBytecode,
			_In_ SIZE_T BytecodeLength,
			_In_opt_ ID3D11ClassLinkage* pClassLinkage,
			_Out_opt_ ID3D11VertexShader** ppVertexShader) = 0;

		virtual HRESULT CreateGeometryShader(
			_In_ const void* pShaderBytecode,
			_In_ SIZE_T BytecodeLength,
			_In_opt_ ID3D11ClassLinkage* pClassLinkage,
			_Out_opt_ ID3D11GeometryShader** ppGeometryShader) = 0;

		virtual HRESULT CreateGeometryShaderWithStreamOutput(
			_In_ const void* pShaderBytecode,
			_In_ SIZE_T BytecodeLength,
			_In_reads_opt_(NumEntries) const D3D11_SO_DECLARATION_ENTRY* pSODeclaration,
			_In_range_(0, D3D11_SO_STREAM_COUNT* D3D11_SO_OUTPUT_COMPONENT_COUNT) UINT NumEntries,
			_In_reads_opt_(NumStrides) const UINT* pBufferStrides,
			_In_range_(0, D3D11_SO_BUFFER_SLOT_COUNT) UINT NumStrides,
			_In_ UINT RasterizedStream,
			_In_opt_ ID3D11ClassLinkage* pClassLinkage,
			_Out_opt_ ID3D11GeometryShader** ppGeometryShader) = 0;

		virtual HRESULT CreatePixelShader(
			_In_ const void* pShaderBytecode,
			_In_ SIZE_T BytecodeLength,
			_In_opt_ ID3D11ClassLinkage* pClassLinkage,
			_Out_opt_ ID3D11PixelShader** ppPixelShader) = 0;

		virtual HRESULT CreateHullShader(
			_In_ const void* pShaderBytecode,
			_In_ SIZE_T BytecodeLength,
			_In_opt_ ID3D11ClassLinkage* pClassLinkage,
			_Out_opt_ ID3D11HullShader** ppHullShader) = 0;

		virtual HRESULT CreateDomainShader(
			_In_ const void* pShaderBytecode,
			_In_ SIZE_T BytecodeLength,
			_In_opt_ ID3D11ClassLinkage* pClassLinkage,
			_Out_opt_ ID3D11DomainShader** ppDomainShader) = 0;

		virtual HRESULT CreateComputeShader(
			_In_ const void* pShaderBytecode,
			_In_ SIZE_T BytecodeLength,
			_In_opt_ ID3D11ClassLinkage* pClassLinkage,
			_Out_opt_ ID3D11ComputeShader** ppComputeShader) = 0;

		virtual HRESULT CreateClassLinkage(
			_Out_ ID3D11ClassLinkage** ppLinkage) = 0;

		virtual HRESULT CreateBlendState(
			_In_ const D3D11_BLEND_DESC* pBlendStateDesc,
			_Out_opt_ ID3D11BlendState** ppBlendState) = 0;

		virtual HRESULT CreateDepthStencilState(
			_In_ const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc,
			_Out_opt_ ID3D11DepthStencilState** ppDepthStencilState) = 0;

		virtual HRESULT CreateRasterizerState(
			_In_ const D3D11_RASTERIZER_DESC* pRasterizerDesc,
			_Out_opt_ ID3D11RasterizerState** ppRasterizerState) = 0;

		virtual HRESULT CreateSamplerState(
			_In_ const D3D11_SAMPLER_DESC* pSamplerDesc,
			_Out_opt_ ID3D11SamplerState** ppSamplerState) = 0;

		virtual HRESULT CreateQuery(
			_In_ const D3D11_QUERY_DESC* pQueryDesc,
			_Out_opt_ ID3D11Query** ppQuery) = 0;

		virtual HRESULT CreatePredicate(
			_In_ const D3D11_QUERY_DESC* pPredicateDesc,
			_Out_opt_ ID3D11Predicate** ppPredicate) = 0;

		virtual HRESULT CreateCounter(
			_In_ const D3D11_COUNTER_DESC* pCounterDesc,
			_Out_opt_ ID3D11Counter** ppCounter) = 0;

		virtual HRESULT CreateDeferredContext(UINT ContextFlags, _Out_opt_ d3d11x::ID3D11DeviceContext** ppDeferredContext) = 0;

		virtual HRESULT OpenSharedResource(
			_In_ HANDLE hResource,
			_In_ REFIID ReturnedInterface,
			_Out_opt_ void** ppResource) = 0;

		virtual HRESULT CheckFormatSupport(
			_In_ DXGI_FORMAT Format,
			_Out_ UINT* pFormatSupport) = 0;

		virtual HRESULT CheckMultisampleQualityLevels(
			_In_ DXGI_FORMAT Format,
			_In_ UINT SampleCount,
			_Out_ UINT* pNumQualityLevels) = 0;

		virtual void CheckCounterInfo(_Out_ D3D11_COUNTER_INFO* pCounterInfo) = 0;

		virtual HRESULT CheckCounter(
			_In_ const D3D11_COUNTER_DESC* pDesc,
			_Out_ D3D11_COUNTER_TYPE* pType,
			_Out_ UINT* pActiveCounters,
			_Out_writes_opt_(*pNameLength) LPSTR szName,
			_Inout_opt_ UINT* pNameLength,
			_Out_writes_opt_(*pUnitsLength) LPSTR szUnits,
			_Inout_opt_ UINT* pUnitsLength,
			_Out_writes_opt_(*pDescriptionLength) LPSTR szDescription,
			_Inout_opt_ UINT* pDescriptionLength) = 0;

		virtual HRESULT CheckFeatureSupport(
			D3D11_FEATURE Feature,
			_Out_writes_bytes_(FeatureSupportDataSize) void* pFeatureSupportData,
			UINT FeatureSupportDataSize) = 0;

		virtual HRESULT GetPrivateData(
			_In_ REFGUID guid,
			_Inout_ UINT* pDataSize,
			_Out_writes_bytes_opt_(*pDataSize) void* pData) = 0;

		virtual HRESULT SetPrivateData(_In_ REFGUID guid, _In_ UINT DataSize, _In_reads_bytes_opt_(DataSize) const void* pData)= 0;

		virtual HRESULT SetPrivateDataInterface(_In_ REFGUID guid, _In_opt_ const IUnknown* pData) = 0;

		virtual HRESULT SetPrivateDataInterfaceGraphics(_In_ REFGUID guid, _In_opt_ const IGraphicsUnknown* pData) = 0;

		virtual D3D_FEATURE_LEVEL GetFeatureLevel( ) = 0;

		virtual UINT GetCreationFlags( ) = 0;

		virtual HRESULT GetDeviceRemovedReason( ) = 0;

		virtual void GetImmediateContext(ID3D11DeviceContext** ppImmediateContext) = 0;

		virtual HRESULT SetExceptionMode(UINT RaiseFlags) = 0;

		virtual UINT GetExceptionMode( ) = 0;
	};

	D3DINTERFACE(ID3D11Device1, a04bfb29, 08ef, 43d6, a4, 9c, a9, bd, bd, cb, e6, 86) : public ID3D11Device{
	public:
		virtual void GetImmediateContext1(_Out_ ::ID3D11DeviceContext1** ppImmediateContext) = 0;

		virtual HRESULT CreateDeferredContext1(
			UINT ContextFlags,
			_Out_ ::ID3D11DeviceContext1** ppDeferredContext) = 0;

		virtual HRESULT CreateBlendState1(
			_In_ const D3D11_BLEND_DESC1* pBlendStateDesc,
			_Out_opt_ ID3D11BlendState1** ppBlendState) = 0;

		virtual HRESULT CreateRasterizerState1(
			_In_ const D3D11_RASTERIZER_DESC1* pRasterizerDesc,
			_Out_opt_ ID3D11RasterizerState1** ppRasterizerState) = 0;

		virtual HRESULT CreateDeviceContextState(
			UINT Flags,
			_In_reads_(FeatureLevels) const D3D_FEATURE_LEVEL* pFeatureLevels,
			UINT FeatureLevels,
			UINT SDKVersion,
			REFIID EmulatedInterface,
			_Out_opt_ D3D_FEATURE_LEVEL* pChosenFeatureLevel,
			_Out_opt_ ID3DDeviceContextState** ppContextState) = 0;

		virtual HRESULT OpenSharedResource1(
			_In_ HANDLE hResource,
			_In_ REFIID ReturnedInterface,
			_Out_ void** ppResource) = 0;

		virtual HRESULT OpenSharedResourceByName(
			_In_ LPCWSTR lpName,
			_In_ DWORD dwDesiredAccess,
			_In_ REFIID ReturnedInterface,
			_Out_ void** ppResource) = 0;
	};

	D3DINTERFACE(ID3D11Device2, 9d06dffa, d1e5, 4d07, 83, a8, 1b, b1, 23, f2, f8, 41) : public ID3D11Device1 {

		virtual void GetImmediateContext2(
			_Out_ ::ID3D11DeviceContext2** ppImmediateContext) = 0;

		virtual HRESULT CreateDeferredContext2(
			UINT ContextFlags,
			_Out_ ::ID3D11DeviceContext2** ppDeferredContext) = 0;

		virtual void GetResourceTiling(
			_In_  ID3D11Resource* pTiledResource,
			_Out_opt_  UINT* pNumTilesForEntireResource,
			_Out_opt_  D3D11_PACKED_MIP_DESC* pPackedMipDesc,
			_Out_opt_  D3D11_TILE_SHAPE* pStandardTileShapeForNonPackedMips,
			_Inout_opt_  UINT* pNumSubresourceTilings,
			_In_  UINT FirstSubresourceTilingToGet,
			_Out_writes_(*pNumSubresourceTilings)  D3D11_SUBRESOURCE_TILING* pSubresourceTilingsForNonPackedMips) = 0;

		virtual HRESULT CheckMultisampleQualityLevels1(
			_In_  DXGI_FORMAT Format,
			_In_  UINT SampleCount,
			_In_  UINT Flags,
			_Out_  UINT* pNumQualityLevels) = 0;
	};

	D3DINTERFACE(ID3D11DeviceX, 177700f9, 876a, 4436, b3, 68, 36, a6, 04, f8, 2c, ef) : public ID3D11Device2
	{
	public:
		virtual void GetImmediateContextX(ID3D11DeviceContextX**) = 0;
		virtual HRESULT CreateCounterSet(const D3D11X_COUNTER_SET_DESC*, ID3D11CounterSetX**) = 0;
		virtual HRESULT CreateCounterSample(ID3D11CounterSampleX**) = 0;
		virtual HRESULT SetDriverHint(unsigned int, unsigned int) = 0;
		virtual HRESULT CreateDmaEngineContext(const D3D11_DMA_ENGINE_CONTEXT_DESC*, ID3D11DmaEngineContextX**) = 0;
		virtual int IsFencePending(unsigned __int64) = 0;
		virtual int IsResourcePending(ID3D11Resource*) = 0;
		virtual HRESULT CreatePlacementBuffer(const D3D11_BUFFER_DESC*, void*, ID3D11Buffer**) = 0;
		virtual HRESULT CreatePlacementTexture1D(const D3D11_TEXTURE1D_DESC*, unsigned int, unsigned int, void*, ID3D11Texture1D**) = 0;
		virtual HRESULT CreatePlacementTexture2D(const D3D11_TEXTURE2D_DESC*, unsigned int, unsigned int, void*, ID3D11Texture2D**) = 0;
		virtual HRESULT CreatePlacementTexture3D(const D3D11_TEXTURE3D_DESC*, unsigned int, unsigned int, void*, ID3D11Texture3D**) = 0;
		virtual void GetTimestamps(unsigned __int64*, unsigned __int64*) = 0;
		virtual HRESULT CreateSamplerStateX(const D3D11X_SAMPLER_DESC*, ID3D11SamplerState**) = 0;
		virtual HRESULT CreateDeferredContextX(unsigned int, ID3D11DeviceContextX**) = 0;
		virtual void GarbageCollect(unsigned int) = 0;
		virtual HRESULT CreateDepthStencilStateX(const D3D11_DEPTH_STENCIL_DESC*, ID3D11DepthStencilState**) = 0;
		virtual HRESULT CreatePlacementRenderableTexture2D(const D3D11_TEXTURE2D_DESC*, unsigned int, unsigned int, const D3D11X_RENDERABLE_TEXTURE_ADDRESSES*, ID3D11Texture2D**) = 0;
		virtual void GetDriverStatistics(unsigned int, D3D11X_DRIVER_STATISTICS*) = 0;
		virtual HRESULT CreateComputeContextX(const D3D11_COMPUTE_CONTEXT_DESC*, ID3D11ComputeContextX**) = 0;
		virtual void ComposeShaderResourceView(const D3D11X_DESCRIPTOR_RESOURCE*, const D3D11X_RESOURCE_VIEW_DESC*, D3D11X_DESCRIPTOR_SHADER_RESOURCE_VIEW*) = 0;
		virtual void ComposeUnorderedAccessView(const D3D11X_DESCRIPTOR_RESOURCE*, const D3D11X_RESOURCE_VIEW_DESC*, D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW*) = 0;
		virtual void ComposeConstantBufferView(const D3D11X_DESCRIPTOR_RESOURCE*, const D3D11X_RESOURCE_VIEW_DESC*, D3D11X_DESCRIPTOR_CONSTANT_BUFFER_VIEW*) = 0;
		virtual void ComposeVertexBufferView(const D3D11X_DESCRIPTOR_RESOURCE*, const D3D11X_RESOURCE_VIEW_DESC*, D3D11X_DESCRIPTOR_VERTEX_BUFFER_VIEW*) = 0;
		virtual void ComposeSamplerState(const D3D11X_SAMPLER_STATE_DESC*, D3D11X_DESCRIPTOR_SAMPLER_STATE*) = 0;
		virtual void PlaceSwapChainView(ID3D11Resource*, ID3D11View*) = 0;
		virtual void SetDebugFlags(unsigned int) = 0;
		virtual unsigned int GetDebugFlags( ) = 0;
		virtual void SetHangCallbacks(D3D11XHANGBEGINCALLBACK, D3D11XHANGPRINTCALLBACK, D3D11XHANGDUMPCALLBACK) = 0;
		virtual void ReportGpuHang(unsigned int) = 0;
		virtual HRESULT SetGpuMemoryPriority(unsigned int) = 0;
		virtual void GetGpuHardwareConfiguration(D3D11X_GPU_HARDWARE_CONFIGURATION*) = 0;
	};

	class D3D11DeviceXWrapperX : public ID3D11DeviceX
	{
	public:
		explicit D3D11DeviceXWrapperX(::ID3D11Device2* pDevice)
		{
			m_realDevice = pDevice;
			m_RefCount = 1;
		}

		HRESULT QueryInterface(REFIID riid, void** ppvObject) override;


		ULONG AddRef( ) override
		{
			printf("[D3D11DeviceXWrapperX] AddRef\n");
			InterlockedIncrement(&m_RefCount);
			return m_realDevice->AddRef( );
		}

		ULONG Release( ) override
		{
			ULONG refCount = InterlockedDecrement(&m_RefCount);
			m_realDevice->Release( );
			printf("[D3D11DeviceXWrapperX] Release\n");
			if (refCount == 0)
			{
				printf("[D3D11DeviceXWrapperX] Release | refCount == 0, class being deleted.\n");
				delete this;
			}
			return refCount;
		}

		// ID3D11Device

		HRESULT SetPrivateDataInterfaceGraphics(const GUID& guid, const IGraphicsUnknown* pData) override
		{
			return m_realDevice->SetPrivateDataInterface(guid, (IUnknown*)pData);
		}

		HRESULT CreateBuffer(
			   const D3D11_BUFFER_DESC* pDesc,
			   const D3D11_SUBRESOURCE_DATA* pInitialData,
			   d3d11x::ID3D11Buffer_X** ppBuffer) override;

		HRESULT CreateTexture1D(
			const D3D11_TEXTURE1D_DESC* pDesc,
			const D3D11_SUBRESOURCE_DATA* pInitialData,
			ID3D11Texture1D_X** ppTexture1D) override;

		HRESULT CreateTexture2D(
			D3D11_TEXTURE2D_DESC* pDesc,
			const D3D11_SUBRESOURCE_DATA* pInitialData,
			ID3D11Texture2D_X** ppTexture2D) override;

		HRESULT CreateTexture3D(
			const D3D11_TEXTURE3D_DESC* pDesc,
			const D3D11_SUBRESOURCE_DATA* pInitialData,
			ID3D11Texture3D_X** ppTexture3D) override;

		HRESULT CreateShaderResourceView(
			ID3D11Resource* pResource,
			const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc,
			ID3D11ShaderResourceView_X** ppSRView) override;

		HRESULT CreateUnorderedAccessView(
			ID3D11Resource* pResource,
			const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc,
			ID3D11UnorderedAccessView_X** ppUAView) override;

		HRESULT CreateRenderTargetView(ID3D11Resource* pResource,
			const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
			ID3D11RenderTargetView_X** ppRTView) override;

		HRESULT CreateDepthStencilView(
			ID3D11Resource* pResource,
			const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
			ID3D11DepthStencilView_X** ppDepthStencilView) override;

		HRESULT CreateInputLayout(
			const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
			UINT NumElements,
			const void* pShaderBytecodeWithInputSignature,
			SIZE_T BytecodeLength,
			ID3D11InputLayout** ppInputLayout) override {
			return m_realDevice->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
		}

		HRESULT CreateVertexShader(
			const void* pShaderBytecode,
			SIZE_T BytecodeLength,
			ID3D11ClassLinkage* pClassLinkage,
			ID3D11VertexShader** ppVertexShader) override {
			return m_realDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
		}

		HRESULT CreateGeometryShader(
			const void* pShaderBytecode,
			SIZE_T BytecodeLength,
			ID3D11ClassLinkage* pClassLinkage,
			ID3D11GeometryShader** ppGeometryShader) override {
			return m_realDevice->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
		}

		HRESULT CreateGeometryShaderWithStreamOutput(
			const void* pShaderBytecode,
			SIZE_T BytecodeLength,
			const D3D11_SO_DECLARATION_ENTRY* pSODeclaration,
			UINT NumEntries,
			const UINT* pBufferStrides,
			UINT NumStrides,
			UINT RasterizedStream,
			ID3D11ClassLinkage* pClassLinkage,
			ID3D11GeometryShader** ppGeometryShader) override {
			return m_realDevice->CreateGeometryShaderWithStreamOutput(pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);
		}

		HRESULT CreatePixelShader(
				const void* pShaderBytecode,
				SIZE_T BytecodeLength,
				ID3D11ClassLinkage* pClassLinkage,
				ID3D11PixelShader** ppPixelShader) override {
			return m_realDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
		}

		HRESULT CreateHullShader(
				const void* pShaderBytecode,
				SIZE_T BytecodeLength,
				ID3D11ClassLinkage* pClassLinkage,
				ID3D11HullShader** ppHullShader) override {
			return m_realDevice->CreateHullShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
		}

		HRESULT CreateDomainShader(
				const void* pShaderBytecode,
				SIZE_T BytecodeLength,
				ID3D11ClassLinkage* pClassLinkage,
				ID3D11DomainShader** ppDomainShader) override {
			return m_realDevice->CreateDomainShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
		}

		HRESULT CreateComputeShader(
				const void* pShaderBytecode,
				SIZE_T BytecodeLength,
				ID3D11ClassLinkage* pClassLinkage,
				ID3D11ComputeShader** ppComputeShader) override {
			return m_realDevice->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
		}

		HRESULT CreateClassLinkage(
				ID3D11ClassLinkage** ppLinkage) override {
			return m_realDevice->CreateClassLinkage(ppLinkage);
		}

		HRESULT CreateBlendState(
				const D3D11_BLEND_DESC* pBlendStateDesc,
				ID3D11BlendState** ppBlendState) override {
			return m_realDevice->CreateBlendState(pBlendStateDesc, ppBlendState);
		}

		HRESULT CreateDepthStencilState(
				const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc,
				ID3D11DepthStencilState** ppDepthStencilState) override {
			return m_realDevice->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState);
		}

		HRESULT CreateRasterizerState(
				const D3D11_RASTERIZER_DESC* pRasterizerDesc,
				ID3D11RasterizerState** ppRasterizerState) override {
			return m_realDevice->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
		}

		HRESULT CreateSamplerState(
				const D3D11_SAMPLER_DESC* pSamplerDesc,
				ID3D11SamplerState** ppSamplerState) override {
			return m_realDevice->CreateSamplerState(pSamplerDesc, ppSamplerState);
		}

		HRESULT CreateQuery(
				const D3D11_QUERY_DESC* pQueryDesc,
				ID3D11Query** ppQuery) override {
			return m_realDevice->CreateQuery(pQueryDesc, ppQuery);
		}

		HRESULT CreatePredicate(
				const D3D11_QUERY_DESC* pPredicateDesc,
				ID3D11Predicate** ppPredicate) override {
			return m_realDevice->CreatePredicate(pPredicateDesc, ppPredicate);
		}

		HRESULT CreateCounter(
				const D3D11_COUNTER_DESC* pCounterDesc,
				ID3D11Counter** ppCounter) override {
			return m_realDevice->CreateCounter(pCounterDesc, ppCounter);
		}

		// @Patoke todo: unwrap
		// @Aleblbl done, check cpp file
		HRESULT CreateDeferredContext(
			UINT ContextFlags, d3d11x::ID3D11DeviceContext** ppDeferredContext) override;

		HRESULT OpenSharedResource(
				HANDLE hResource,
				REFIID ReturnedInterface,
				void** ppResource) override {
			return m_realDevice->OpenSharedResource(hResource, ReturnedInterface, ppResource);
		}

		HRESULT CheckFormatSupport(
				DXGI_FORMAT Format,
				UINT* pFormatSupport) override {
			return m_realDevice->CheckFormatSupport(Format, pFormatSupport);
		}

		HRESULT CheckMultisampleQualityLevels(
				DXGI_FORMAT Format,
				UINT SampleCount,
				UINT* pNumQualityLevels) override {
			return m_realDevice->CheckMultisampleQualityLevels(Format, SampleCount, pNumQualityLevels);
		}

		void CheckCounterInfo(
				D3D11_COUNTER_INFO* pCounterInfo) override {
			m_realDevice->CheckCounterInfo(pCounterInfo);
		}

		HRESULT CheckCounter(
				const D3D11_COUNTER_DESC* pDesc,
				D3D11_COUNTER_TYPE* pType,
				UINT* pActiveCounters,
				LPSTR szName,
				UINT* pNameLength,
				LPSTR szUnits,
				UINT* pUnitsLength,
				LPSTR szDescription,
				UINT* pDescriptionLength) override {
			return m_realDevice->CheckCounter(pDesc, pType, pActiveCounters, szName, pNameLength, szUnits, pUnitsLength, szDescription, pDescriptionLength);
		}

		HRESULT CheckFeatureSupport(
			D3D11_FEATURE Feature,
				void* pFeatureSupportData,
			UINT FeatureSupportDataSize) override {
			return m_realDevice->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
		}

		HRESULT GetPrivateData(
				REFGUID guid,
				UINT* pDataSize,
				void* pData) override {
			return m_realDevice->GetPrivateData(guid, pDataSize, pData);
		}

		HRESULT SetPrivateData(
				REFGUID guid,
				UINT DataSize,
				const void* pData) override {
			return m_realDevice->SetPrivateData(guid, DataSize, pData);
		}

		HRESULT SetPrivateDataInterface(
				REFGUID guid,
				const IUnknown* pData) override {
			return m_realDevice->SetPrivateDataInterface(guid, pData);
		}

		D3D_FEATURE_LEVEL GetFeatureLevel(void) override {
			return m_realDevice->GetFeatureLevel( );
		}

		UINT GetCreationFlags(void) override {
			return m_realDevice->GetCreationFlags( );
		}

		HRESULT GetDeviceRemovedReason(void) override {
			return m_realDevice->GetDeviceRemovedReason( );
		}

		// @Patoke todo: unwrap
		// @Aleblbl don :} (check cpp file)
		void GetImmediateContext(ID3D11DeviceContext** ppImmediateContext) override;

		HRESULT SetExceptionMode(
			UINT RaiseFlags) override {
			return m_realDevice->SetExceptionMode(RaiseFlags);
		}

		UINT GetExceptionMode(void) override { return m_realDevice->GetExceptionMode( ); }


		// ID3D11Device1
		// @Patoke todo: unwrap
		void GetImmediateContext1(::ID3D11DeviceContext1** ppImmediateContext) override {
			m_realDevice->GetImmediateContext1(ppImmediateContext);
		}

		// @Patoke todo: unwrap
		HRESULT CreateDeferredContext1(UINT ContextFlags, ::ID3D11DeviceContext1** ppDeferredContext) override {
			return m_realDevice->CreateDeferredContext1(ContextFlags, ppDeferredContext);
		}

		HRESULT CreateBlendState1(const D3D11_BLEND_DESC1* pBlendStateDesc, ID3D11BlendState1** ppBlendState) override {
			return m_realDevice->CreateBlendState1(pBlendStateDesc, ppBlendState);
		}

		HRESULT CreateRasterizerState1(const D3D11_RASTERIZER_DESC1* pRasterizerDesc, ID3D11RasterizerState1** ppRasterizerState) override {
			return m_realDevice->CreateRasterizerState1(pRasterizerDesc, ppRasterizerState);
		}

		HRESULT CreateDeviceContextState(UINT Flags, const D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, REFIID EmulatedInterface, D3D_FEATURE_LEVEL* pChosenFeatureLevel, ID3DDeviceContextState** ppContextState) override {
			return m_realDevice->CreateDeviceContextState(Flags, pFeatureLevels, FeatureLevels, SDKVersion, EmulatedInterface, pChosenFeatureLevel, ppContextState);
		}

		HRESULT OpenSharedResource1(HANDLE hResource, REFIID returnedInterface, void** ppResource) override {
			return m_realDevice->OpenSharedResource1(hResource, returnedInterface, ppResource);
		}

		HRESULT OpenSharedResourceByName(LPCWSTR lpName, DWORD dwDesiredAccess, REFIID returnedInterface, void** ppResource) override {
			return m_realDevice->OpenSharedResourceByName(lpName, dwDesiredAccess, returnedInterface, ppResource);
		}

		// ID3D11Device2
		// @Patoke todo: unwrap
		void GetImmediateContext2(::ID3D11DeviceContext2** ppImmediateContext) override
		{
			m_realDevice->GetImmediateContext2(ppImmediateContext);
		}

		// @Patoke todo: unwrap
		HRESULT CreateDeferredContext2(UINT ContextFlags, ::ID3D11DeviceContext2** ppDeferredContext) override
		{
			return m_realDevice->CreateDeferredContext2(ContextFlags, ppDeferredContext);
		}

		void GetResourceTiling(ID3D11Resource* pTiledResource, UINT* pNumTilesForEntireResource,
			D3D11_PACKED_MIP_DESC* pPackedMipDesc, D3D11_TILE_SHAPE* pStandardTileShapeForNonPackedMips,
			UINT* pNumSubresourceTilings, UINT FirstSubresourceTilingToGet, D3D11_SUBRESOURCE_TILING* pSubresourceTilingsForNonPackedMips) override
		{
			m_realDevice->GetResourceTiling(pTiledResource, pNumTilesForEntireResource,
				pPackedMipDesc, pStandardTileShapeForNonPackedMips, pNumSubresourceTilings,
				FirstSubresourceTilingToGet, pSubresourceTilingsForNonPackedMips);
		}

		HRESULT CheckMultisampleQualityLevels1(DXGI_FORMAT Format, UINT SampleCount, UINT Flags, UINT* pNumQualityLevels) override
		{
			return m_realDevice->CheckMultisampleQualityLevels1(Format, SampleCount, Flags, pNumQualityLevels);
		}

		// ID3D11DeviceX
		void GetImmediateContextX(ID3D11DeviceContextX**) override;
		HRESULT CreateCounterSet(const D3D11X_COUNTER_SET_DESC*, ID3D11CounterSetX**) override;
		HRESULT CreateCounterSample(ID3D11CounterSampleX**) override;
		HRESULT SetDriverHint(UINT Feature, UINT Value) override;
		HRESULT CreateDmaEngineContext(const D3D11_DMA_ENGINE_CONTEXT_DESC*, ID3D11DmaEngineContextX**) override;
		int IsFencePending(UINT64) override;
		int IsResourcePending(ID3D11Resource*) override;
		HRESULT CreatePlacementBuffer(const D3D11_BUFFER_DESC*, void*, ID3D11Buffer**) override;
		HRESULT CreatePlacementTexture1D(const D3D11_TEXTURE1D_DESC*, UINT, UINT, void*, ID3D11Texture1D**) override;
		HRESULT CreatePlacementTexture2D(const D3D11_TEXTURE2D_DESC*, UINT, UINT, void*, ID3D11Texture2D**) override;
		HRESULT CreatePlacementTexture3D(const D3D11_TEXTURE3D_DESC*, UINT, UINT, void*, ID3D11Texture3D**) override;
		void GetTimestamps(UINT64*, UINT64*) override;
		HRESULT CreateSamplerStateX(const D3D11X_SAMPLER_DESC*, ID3D11SamplerState**) override;
		HRESULT CreateDeferredContextX(UINT, ID3D11DeviceContextX**) override;
		void GarbageCollect(UINT) override;
		HRESULT CreateDepthStencilStateX(const D3D11_DEPTH_STENCIL_DESC*, ID3D11DepthStencilState**) override;
		HRESULT CreatePlacementRenderableTexture2D(const D3D11_TEXTURE2D_DESC*, UINT, UINT, const D3D11X_RENDERABLE_TEXTURE_ADDRESSES*, ID3D11Texture2D**) override;
		void GetDriverStatistics(UINT, D3D11X_DRIVER_STATISTICS*) override;
		HRESULT CreateComputeContextX(const D3D11_COMPUTE_CONTEXT_DESC*, ID3D11ComputeContextX**) override;
		void ComposeShaderResourceView(const D3D11X_DESCRIPTOR_RESOURCE*, const D3D11X_RESOURCE_VIEW_DESC*, D3D11X_DESCRIPTOR_SHADER_RESOURCE_VIEW*) override;
		void ComposeUnorderedAccessView(const D3D11X_DESCRIPTOR_RESOURCE*, const D3D11X_RESOURCE_VIEW_DESC*, D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW*) override;
		void ComposeConstantBufferView(const D3D11X_DESCRIPTOR_RESOURCE*, const D3D11X_RESOURCE_VIEW_DESC*, D3D11X_DESCRIPTOR_CONSTANT_BUFFER_VIEW*) override;
		void ComposeVertexBufferView(const D3D11X_DESCRIPTOR_RESOURCE*, const D3D11X_RESOURCE_VIEW_DESC*, D3D11X_DESCRIPTOR_VERTEX_BUFFER_VIEW*) override;
		void ComposeSamplerState(const D3D11X_SAMPLER_STATE_DESC*, D3D11X_DESCRIPTOR_SAMPLER_STATE*) override;
		void PlaceSwapChainView(ID3D11Resource*, ID3D11View*) override;
		void SetDebugFlags(UINT) override;
		unsigned int GetDebugFlags( ) override;
		void SetHangCallbacks(D3D11XHANGBEGINCALLBACK, D3D11XHANGPRINTCALLBACK, D3D11XHANGDUMPCALLBACK) override;
		void ReportGpuHang(UINT) override;
		HRESULT SetGpuMemoryPriority(UINT) override;
		void GetGpuHardwareConfiguration(D3D11X_GPU_HARDWARE_CONFIGURATION*) override;

	public:
		::ID3D11Device2* m_realDevice;
	};


	MIDL_INTERFACE("88671610-712E-4F1E-84AB-01B5948BD373")
		ID3D11PerformanceDeviceX : ID3D11DeviceX
	{
		// yea this is just empty lol
	};
}
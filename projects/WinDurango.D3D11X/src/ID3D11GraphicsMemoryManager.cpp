#include "ID3D11GraphicsMemoryManager.h"
#include "ID3D11Resource.h"
#include "ID3D11DeviceContext.h"
#include "ID3D11View.h"
#include "d3d11.x.h"

template<abi_t ABI>
LONG D3D11GraphicsMemoryManager<ABI>::VectoredExceptionHandler(_EXCEPTION_POINTERS* pExceptionPointers)
{
    if (pExceptionPointers->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
    {
        if (pExceptionPointers->ExceptionRecord->ExceptionInformation[0] == 1)
        {
            MEMORY_BASIC_INFORMATION mbi{};
            SIZE_T Result = VirtualQuery((void*)pExceptionPointers->ExceptionRecord->ExceptionInformation[1], &mbi, sizeof(mbi));
            if (mbi.AllocationBase && Result == sizeof(mbi))
            {
                if (g_ResourceMap.size() > 0)
                {
                    std::lock_guard<std::mutex> lock(g_ResourceMapMutex);
                    auto Range = g_ResourceMap.equal_range(mbi.AllocationBase);
                    for (auto it = Range.first; it != Range.second; ++it)
                    {
                        D3D11_RESOURCE_DIMENSION Type{};
                        reinterpret_cast<gfx::ID3D11Resource<ABI>*>(it->second)->GetType(&Type);
                        if (Type == D3D11_RESOURCE_DIMENSION_BUFFER) reinterpret_cast<D3D11Buffer<ABI>*>(it->second)->m_IsDirty = true;
                        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D) reinterpret_cast<D3D11Texture1D<ABI>*>(it->second)->m_IsDirty = true;
                        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D) reinterpret_cast<D3D11Texture2D<ABI>*>(it->second)->m_IsDirty = true;
                        else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D) reinterpret_cast<D3D11Texture3D<ABI>*>(it->second)->m_IsDirty = true;
                    }
                }

                DWORD LastFlProtect = 0;
                VirtualProtect((void*)pExceptionPointers->ExceptionRecord->ExceptionInformation[1], 1, PAGE_READWRITE, &LastFlProtect);
                return EXCEPTION_CONTINUE_EXECUTION;
            }

            return EXCEPTION_CONTINUE_SEARCH;
        }

        return EXCEPTION_CONTINUE_SEARCH;
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11GraphicsMemoryManager<ABI>
D3D11_DECLARE_ABI_TEMPLATES();
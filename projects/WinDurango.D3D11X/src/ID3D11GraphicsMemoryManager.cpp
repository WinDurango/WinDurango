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
            VirtualQuery((void*)pExceptionPointers->ExceptionRecord->ExceptionInformation[1], &mbi, sizeof(mbi));
            if (mbi.AllocationBase)
            {
                if (g_ResourceMap.size() > 0)
                {
                    std::lock_guard<std::mutex> lock(g_ResourceMapMutex);
                    for (const auto& pair : g_ResourceMap)
                    {
                        if (pair.first == mbi.AllocationBase)
                        {
                            D3D11_RESOURCE_DIMENSION Type{};
                            reinterpret_cast<gfx::ID3D11Resource<ABI>*>(pair.second)->GetType(&Type);
                            if (Type == D3D11_RESOURCE_DIMENSION_BUFFER) reinterpret_cast<D3D11Buffer<ABI>*>(pair.second)->m_IsDirty = true;
                            else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE1D) reinterpret_cast<D3D11Texture1D<ABI>*>(pair.second)->m_IsDirty = true;
                            else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE2D) reinterpret_cast<D3D11Texture2D<ABI>*>(pair.second)->m_IsDirty = true;
                            else if (Type == D3D11_RESOURCE_DIMENSION_TEXTURE3D) reinterpret_cast<D3D11Texture3D<ABI>*>(pair.second)->m_IsDirty = true;
                            DWORD LastFlProtect = 0;
                            VirtualProtect((void*)pair.first, 1, PAGE_READWRITE, &LastFlProtect);
                        }
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
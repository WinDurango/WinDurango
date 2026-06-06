#pragma once
#pragma comment(lib, "kernel32.lib")
#include <Windows.h>
#include <errhandlingapi.h>
#include "d3d11_x.g.h"

class ID3D11GraphicsMemoryManager
{
public:
    virtual void RegisterVEH() = 0;
};

template <abi_t ABI>
class D3D11GraphicsMemoryManager : public ID3D11GraphicsMemoryManager
{
private:
      static LONG VectoredExceptionHandler(_EXCEPTION_POINTERS* pExceptionPointers);
public:
    void RegisterVEH() override
    {
        AddVectoredExceptionHandler(1, VectoredExceptionHandler);
    }
};

#undef ABI_INTERFACE
#define ABI_INTERFACE(ABI) D3D11GraphicsMemoryManager<ABI>
D3D11_DECLARE_ABI_TEMPLATES(extern);
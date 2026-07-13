cmake_minimum_required(VERSION 4.0)
project(WinDurango.D3D11X VERSION 1.0.0)

set(VERSION_SUFFIX "-dev.1") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 20)

find_package(directxtex CONFIG REQUIRED HINTS "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/share/directxtex")
find_package(ZLIB REQUIRED)

set(FILES
    src/d3d11.x.cpp
    src/IGraphicsUnknown.cpp
    src/IIDExports.cpp
    include/WinDurango.D3D11X/d3d11.x.h
    include/WinDurango.D3D11X/d3d11_x.g.h
    include/WinDurango.D3D11X/unknown.g.h
    include/WinDurango.D3D11X/IGraphicsUnknown.h
    include/WinDurango.D3D11X/IIDExports.h
    Exports.def
)

add_library(WinDurango.D3D11X SHARED ${FILES} "include/WinDurango.D3D11X/ID3D11DeviceChild.h" "src/ID3D11DeviceChild.cpp" "include/WinDurango.D3D11X/ID3D11Resource.h" "src/ID3D11Resource.cpp" "include/WinDurango.D3D11X/ID3D11Shader.h" "src/ID3D11Shader.cpp" "include/WinDurango.D3D11X/ID3D11State.h" "src/ID3D11State.cpp" "include/WinDurango.D3D11X/ID3D11View.h" "src/ID3D11View.cpp" "include/WinDurango.D3D11X/ID3D11DeviceContext.h" "src/ID3D11DeviceContext.cpp" "include/WinDurango.D3D11X/ID3D11DMAEngineContext.h" "src/ID3D11DMAEngineContext.cpp" "include/WinDurango.D3D11X/ID3D11Device.h" "src/ID3D11Device.cpp" "include/WinDurango.D3D11X/ID3D11Runtime.h" "src/dllmain.cpp" "include/WinDurango.D3D11X/IDXGIAdapter.h" "include/WinDurango.D3D11X/IDXGIDevice.h" "include/WinDurango.D3D11X/IDXGIFactory.h" "include/WinDurango.D3D11X/IDXGISwapChain.h" "src/IDXGIAdapter.cpp" "src/IDXGIDevice.cpp" "src/IDXGIFactory.cpp" "src/IDXGISwapChain.cpp"  "include/WinDurango.D3D11X/ID3D11GraphicsMemoryManager.h" "src/ID3D11GraphicsMemoryManager.cpp" "include/WinDurango.D3D11X/XG.h" "include/WinDurango.D3D11X/ID3D11CommandList.h" "src/ID3D11CommandList.cpp" "include/WinDurango.D3D11X/ID3D11DrawBundlesContext.h" "src/ID3D11DrawBundlesContext.cpp" "include/WinDurango.D3D11X/ID3D11ComputeContext.h" "src/ID3D11ComputeContext.cpp")

target_link_libraries(WinDurango.D3D11X PRIVATE WinDurango.Common)
target_link_libraries(WinDurango.D3D11X PRIVATE WinDurango.KernelX)
target_link_libraries(WinDurango.D3D11X PRIVATE Microsoft::DirectXTex)
target_link_libraries(WinDurango.D3D11X PRIVATE ZLIB::ZLIB)

target_include_directories(WinDurango.D3D11X PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.D3D11X/
    ../WinDurango.Common/include/
    ../WinDurango.KernelX/include/WinDurango.KernelX/
)

target_link_options(WinDurango.D3D11X
    PUBLIC 
    $<$<CXX_COMPILER_ID:MSVC>:/FORCE:MULTIPLE>
)

set_target_properties(WinDurango.D3D11X PROPERTIES
    OUTPUT_NAME "d3d11_x"
)

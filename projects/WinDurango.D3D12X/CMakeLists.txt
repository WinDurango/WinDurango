cmake_minimum_required(VERSION 4.0)
project(WinDurango.D3D12X VERSION 1.0.0)

set(VERSION_SUFFIX "-dev.1") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 20)

find_package(directxtex CONFIG REQUIRED HINTS "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/share/directxtex")

set(FILES
    Exports.def
)

add_library(WinDurango.D3D12X SHARED ${FILES} "WinDurango.D3D12X.cpp" "WinDurango.D3D12X.h")

target_link_libraries(WinDurango.D3D12X PRIVATE WinDurango.Common)
target_link_libraries(WinDurango.D3D12X PRIVATE WinDurango.KernelX)
target_link_libraries(WinDurango.D3D12X PRIVATE Microsoft::DirectXTex)

target_include_directories(WinDurango.D3D12X PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.D3D12X/
    ../WinDurango.Common/include/
    ../WinDurango.KernelX/include/WinDurango.KernelX/
    ${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/include
)

target_link_options(WinDurango.D3D12X
    PUBLIC 
    $<$<CXX_COMPILER_ID:MSVC>:/FORCE:MULTIPLE>
)

set_target_properties(WinDurango.D3D12X PROPERTIES
    OUTPUT_NAME "d3d12_x"
)

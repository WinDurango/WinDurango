cmake_minimum_required(VERSION 4.0)
project(WinDurango.KernelX VERSION 1.0.0)

set(VERSION_SUFFIX "-dev.1") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 20)

find_path(DETOURS_INCLUDE_DIRS "detours/detours.h" REQUIRED HINTS "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/include")
find_library(DETOURS_LIBRARY detours REQUIRED HINTS "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/lib")

set(FILES
    src/kernelx.cpp
    src/dllmain.cpp
    src/Hooks.cpp
    src/CurrentApp.cpp
    include/WinDurango.KernelX/CurrentApp.h
    include/WinDurango.KernelX/kernelx.h
    include/WinDurango.KernelX/Logan.h
    include/WinDurango.KernelX/Hooks.h
)

add_library(WinDurango.KernelX SHARED ${FILES} "include/WinDurango.KernelX/EraCoreApplication.h" "src/EraCoreApplication.cpp" "include/WinDurango.KernelX/EraCoreWindow.h" "src/EraCoreWindow.cpp" "include/WinDurango.KernelX/MMDeviceEnumerator.h" "src/MMDeviceEnumerator.cpp" "include/WinDurango.KernelX/ForzaThreadHook.h" "include/WinDurango.KernelX/D3D11Peggle2Hook.h")

target_link_libraries(WinDurango.KernelX PRIVATE 
    WinDurango.Common 
    WinDurango.Implementation.WinRT 
    ${DETOURS_LIBRARY}
)

target_link_options(WinDurango.KernelX
    PUBLIC 
    $<$<CXX_COMPILER_ID:MSVC>:/FORCE:MULTIPLE>
)

target_include_directories(WinDurango.KernelX PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.KernelX/
    ${CMAKE_SOURCE_DIR}/projects/WinDurango.Common/include
    ${CMAKE_SOURCE_DIR}/projects/WinDurango.Implementation.WinRT/include
    ${DETOURS_INCLUDE_DIRS}
)

set_target_properties(WinDurango.KernelX PROPERTIES
    OUTPUT_NAME "kernelx"
)
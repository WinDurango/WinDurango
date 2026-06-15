cmake_minimum_required(VERSION 3.30)
project(WinDurango)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_subdirectory(projects/WinDurango.Common)
add_subdirectory(projects/WinDurango.Implementation.WinRT)
#add_subdirectory(projects/WinDurango.Implementation.Native)
add_subdirectory(projects/WinDurango.WinRT)
add_subdirectory(projects/WinDurango.Kinect)
add_subdirectory(projects/WinDurango.etwplus)
add_subdirectory(projects/WinDurango.KernelX)
add_subdirectory(projects/WinDurango.D3D11X)
add_subdirectory(projects/WinDurango.D3D12X)
add_subdirectory(projects/WinDurango.MMDevAPI)
add_subdirectory(projects/WinDurango.MFPlat)
add_subdirectory(projects/WinDurango.Watchdog)

add_custom_target(WinDurango ALL DEPENDS
    WinDurango.Common
    WinDurango.Implementation.WinRT
    #WinDurango.Implementation.Native
    WinDurango.WinRT
    WinDurango.Kinect
    WinDurango.etwplus
    WinDurango.KernelX
    WinDurango.D3D11X
    WinDurango.D3D12X
    WinDurango.MMDevAPI
    WinDurango.MFPlat
    WinDurango.Watchdog
)

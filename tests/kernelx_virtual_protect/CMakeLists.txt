cmake_minimum_required(VERSION 3.21)
project(KernelXVirtualProtectTests LANGUAGES CXX)

if(NOT WIN32 OR NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "These tests require Windows x64 and the Windows SDK")
endif()

set(kernelx_root "${CMAKE_CURRENT_SOURCE_DIR}/../../projects/WinDurango.KernelX")
set(KERNELX_SOURCE_FILE "${kernelx_root}/src/kernelx.cpp" CACHE FILEPATH
    "Production source to test; can point at a saved pre-fix copy")
set(kernelx_header "${kernelx_root}/include/WinDurango.KernelX/kernelx.h")
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    "${KERNELX_SOURCE_FILE}" "${kernelx_header}")

# Compile the actual production functions and mappable-allocation registry,
# without loading KernelX's game-specific startup hooks or other dependencies.
function(extract_section path begin_marker end_marker output)
    file(READ "${path}" contents)
    string(FIND "${contents}" "${begin_marker}" begin_offset)
    string(FIND "${contents}" "${end_marker}" end_offset)
    if(begin_offset LESS 0 OR end_offset LESS_EQUAL begin_offset)
        message(FATAL_ERROR "Cannot find the expected production section in ${path}")
    endif()
    math(EXPR section_length "${end_offset} - ${begin_offset}")
    string(SUBSTRING "${contents}" ${begin_offset} ${section_length} section)
    set(${output} "${section}" PARENT_SCOPE)
endfunction()

extract_section("${kernelx_header}" "typedef struct _MAPPABLE_MEM"
    "static DWORD WIN32_FROM_HRESULT" registry)
extract_section("${KERNELX_SOURCE_FILE}" "EXTERN_C BOOL __stdcall EraVirtualProtectEx("
    "EXTERN_C PVOID __stdcall MapTitlePhysicalPages(" protect_functions)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/production_virtual_protect.h"
    "// Generated from the production KernelX source; do not edit.\n${registry}\n${protect_functions}")

add_executable(kernelx_virtual_protect_tests virtual_protect_tests.cpp)
target_include_directories(kernelx_virtual_protect_tests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_compile_features(kernelx_virtual_protect_tests PRIVATE cxx_std_20)
target_link_libraries(kernelx_virtual_protect_tests PRIVATE onecore)
target_compile_definitions(kernelx_virtual_protect_tests PRIVATE
    UNICODE _UNICODE NOMINMAX WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0A00)
if(MSVC)
    target_compile_options(kernelx_virtual_protect_tests PRIVATE /W4 /WX /permissive- /EHsc /utf-8)
endif()

enable_testing()
add_test(NAME kernelx_virtual_protect_contract COMMAND kernelx_virtual_protect_tests)
set_tests_properties(kernelx_virtual_protect_contract PROPERTIES TIMEOUT 30)

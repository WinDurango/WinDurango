cmake_minimum_required(VERSION 3.30)
project(WinDurango.WinRT VERSION 1.0.0)

set(VERSION_SUFFIX "-dev.1") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(_AMD64_)

make_directory(${CMAKE_BINARY_DIR}/WinMetadata)
file(GLOB IDL_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/idl/*.idl")
cmake_path(CONVERT "${IDL_FILES}" TO_NATIVE_PATH_LIST IDL_FILES)

foreach(IDL_FILE ${IDL_FILES})
    execute_process(
        COMMAND midl
            /winrt /h nul /nomidl /x64
            /I "${CMAKE_SOURCE_DIR}/idl"
            /metadata_dir "$ENV{WindowsSdkDir}References\\$ENV{WindowsSdkVersion}Windows.Foundation.FoundationContract\\4.0.0.0"
            /reference "$ENV{WindowsSdkDir}References\\$ENV{WindowsSdkVersion}Windows.Foundation.FoundationContract\\4.0.0.0\\Windows.Foundation.FoundationContract.winmd"
            /reference "$ENV{WindowsSdkDir}References\\$ENV{WindowsSdkVersion}Windows.Foundation.UniversalApiContract\\20.0.0.0\\Windows.Foundation.UniversalApiContract.winmd"
            /out "${CMAKE_BINARY_DIR}\\WinMetadata"
            ${IDL_FILE}
        RESULT_VARIABLE MIDL_RESULT
        ERROR_VARIABLE MIDL_ERROR)
    
    if(NOT MIDL_RESULT EQUAL 0)
        message(FATAL_ERROR "${MIDL_ERROR}")
    endif()
endforeach()

execute_process(
    COMMAND cppwinrt
        -prefix
        -pch .
        -input "${CMAKE_BINARY_DIR}\\WinMetadata"
        -reference sdk
        -component "${CMAKE_CURRENT_SOURCE_DIR}\\Generated Files\\sources"
        -out "${CMAKE_CURRENT_SOURCE_DIR}\\Generated Files")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB WINRT_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/Generated Files/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Generated Files/winrt/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Generated Files/winrt/impl/*.cpp" 
)

add_library(WinDurango.WinRT SHARED ${SOURCES} ${WINRT_FILES} WinDurango.WinRT.def)
target_include_directories(WinDurango.WinRT PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/Achievements"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/Media"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/System"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/Input"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/Management/Deployment"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/ApplicationModel"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/ApplicationModel/Core"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/ApplicationModel/Store"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/ApplicationModel/State"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/Multiplayer"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/Storage"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/Services"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/Networking"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/Chat"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/Speech/Recognition"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.WinRT/Windows/Xbox/UI"
    "${CMAKE_CURRENT_SOURCE_DIR}/Generated Files"
    "${CMAKE_SOURCE_DIR}/projects/WinDurango.Common/include"
)

target_link_libraries(WinDurango.WinRT PRIVATE WinDurango.Common windowsapp runtimeobject)

target_compile_definitions(WinDurango.WinRT PUBLIC
    WINDURANGO_WINRT_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
    WINDURANGO_WINRT_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
    WINDURANGO_WINRT_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
    WINDURANGO_WINRT_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
    WINDURANGO_WINRT_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

set_target_properties(WinDurango.WinRT PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(WinDurango.WinRT PRIVATE WINRT_DLL WIN32_LEAN_AND_MEAN WINRT_LEAN_AND_MEAN)

if (WINRT_USE_CROSS_PLATFORM STREQUAL ON)
    target_link_libraries(WinDurango.WinRT PUBLIC WinDurango.Implementation.Native)
    target_compile_definitions(WinDurango.WinRT PUBLIC WINRT_CROSS_PLATFORM)
else()
    target_link_libraries(WinDurango.WinRT PUBLIC WinDurango.Implementation.WinRT)
endif()

set_target_properties(WinDurango.WinRT PROPERTIES
    OUTPUT_NAME "winrt_x"
)
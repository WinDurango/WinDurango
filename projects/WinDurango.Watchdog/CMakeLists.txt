cmake_minimum_required(VERSION 4.0)
project(WinDurango.Watchdog VERSION 1.0.0)

include(FetchContent)

set(VERSION_SUFFIX "-dev.1") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG docking
)

FetchContent_MakeAvailable(imgui)

set(FILES
    src/main.cpp
    src/Watchdog.cpp
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
)

FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/Cherrytree56567/spdlog.git GIT_TAG v1.x)
FetchContent_MakeAvailable(spdlog)

add_executable(WinDurango.Watchdog ${FILES})
target_include_directories(WinDurango.Watchdog PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    ${imgui_SOURCE_DIR}
)

target_link_libraries(WinDurango.Watchdog PUBLIC spdlog::spdlog)

target_compile_definitions(WinDurango.Watchdog PUBLIC
    WINDURANGO_WATCHDOG_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
    WINDURANGO_WATCHDOG_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
    WINDURANGO_WATCHDOG_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
    WINDURANGO_WATCHDOG_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
    WINDURANGO_WATCHDOG_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

set_target_properties(WinDurango.Watchdog PROPERTIES LINKER_LANGUAGE CXX)
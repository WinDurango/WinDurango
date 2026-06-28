add_library(WinDurango.ToolHelpX SHARED "src/WinDurango.ToolHelpX.cpp" "include/WinDurango.ToolHelpX/WinDurango.ToolHelpX.h")

target_include_directories(WinDurango.ToolHelpX PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.ToolHelpX"
)

set_target_properties(WinDurango.ToolHelpX PROPERTIES
    OUTPUT_NAME "toolhelpx"
)
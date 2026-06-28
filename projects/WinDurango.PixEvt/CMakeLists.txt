add_library(WinDurango.PixEvt SHARED ${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.PixEvt/WinDurango.PixEvt.h ${CMAKE_CURRENT_SOURCE_DIR}/src/WinDurango.PixEvt.cpp)

target_include_directories(WinDurango.PixEvt PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/WinDurango.PixEvt"
)

set_target_properties(WinDurango.PixEvt PROPERTIES
    OUTPUT_NAME "pixEvt"
)
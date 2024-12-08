cmake_minimum_required(VERSION 3.13.1)

# Print current directory
message("Current directory: ${CMAKE_CURRENT_SOURCE_DIR}")

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(BOARD chessboard)
set(DTS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(mcuboot_CONFIG_BOOT_SIGNATURE_KEY_FILE \"${CMAKE_CURRENT_SOURCE_DIR}/../keys/root-rsa-2048.pem\")

set_property(GLOBAL PROPERTY CSTD c11)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app)
target_sources(app PRIVATE src/main.cpp src/highlights.cpp src/timer.cpp)
add_subdirectory(src/tiles)
add_subdirectory(src/display)
add_subdirectory(src/screens)
add_subdirectory(src/buttons)

# Include directories
zephyr_include_directories(include)
target_include_directories(app PUBLIC include)

# Link chess_logic_lib to app
#add_subdirectory(../lib/chess_logic ${CMAKE_BINARY_DIR}/lib/chess_logic)
#target_link_libraries(app PUBLIC chess_logic_lib)

cmake_minimum_required(VERSION 3.13.1)

# Print current directory
message("Current directory: ${CMAKE_CURRENT_SOURCE_DIR}")

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(BOARD chessboard)
set(mcuboot_CONFIG_BOOT_SIGNATURE_KEY_FILE \"${CMAKE_CURRENT_SOURCE_DIR}/../keys/root-rsa-2048.pem\")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app)

# Link chess_logic_lib to app
add_subdirectory(../lib/chess_logic ${CMAKE_BINARY_DIR}/lib/chess_logic)
target_link_libraries(app PUBLIC chess_logic_lib)

target_sources(app PRIVATE src/main.cpp)

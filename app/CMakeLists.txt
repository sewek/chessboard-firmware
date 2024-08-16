cmake_minimum_required(VERSION 3.13.1)

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(BOARD chessboard)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app)

# Link chess_logic_lib to app
add_subdirectory(../lib/chess_logic ${CMAKE_BINARY_DIR}/lib/chess_logic)
target_link_libraries(app PUBLIC chess_logic_lib)

target_sources(app PRIVATE src/main.cpp)

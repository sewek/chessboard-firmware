project(chess_logic LANGUAGES CXX)

if (POLICY CMP0025)
   cmake_policy(SET CMP0025 NEW)
endif ()

if(BUILD_UNIT_TESTS)
   set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror -g -fprofile-arcs -ftest-coverage --coverage -O0")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
endif(BUILD_UNIT_TESTS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES
   src/chess.cpp
   src/chess_board.cpp
   src/chess_position.cpp
   src/chess_events.cpp
   src/chess_game.cpp
)

include_directories(include)
add_library(chess_logic_lib ${SOURCES})
target_include_directories(chess_logic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(BUILD_UNIT_TESTS)
   message("Building unit tests")

   # Tests
   set(TESTS
   test/board.cpp
   test/game.cpp
   test/events.cpp
   test/position.cpp
   )

   enable_testing()
   Include(FetchContent)
   FetchContent_Declare(
   Catch2
   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
   GIT_TAG        v3.7.0
   )
   FetchContent_MakeAvailable(Catch2)

   list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

   add_executable(tests ${TESTS} ${SOURCES})

   target_link_libraries(tests PRIVATE chess_logic_lib Catch2::Catch2WithMain)
   include(CTest)
   include(Catch)
   catch_discover_tests(tests)

   if(BUILD_COVERAGE)
      message("Building coverage")

      # Coverage
      set(GCOVR_ADDITIONAL_ARGS "--gcov-ignore-parse-errors")
      include(../../cmake/CodeCoverage.cmake)
      APPEND_COVERAGE_COMPILER_FLAGS()
      setup_target_for_coverage_gcovr_xml(
         NAME coverage
         EXECUTABLE tests
         DEPENDENCIES tests chess_logic_lib
      )
   endif(BUILD_COVERAGE)
endif(BUILD_UNIT_TESTS)


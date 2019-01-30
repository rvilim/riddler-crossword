cmake_minimum_required(VERSION 3.13)
project(riddler_crossword)

set(CMAKE_CXX_STANDARD 11)

add_executable(riddler_crossword src/main.cpp src/params.h src/rows.cpp src/rows.h src/masks.cpp src/masks.h)
add_executable(tests test/catchmain.cpp src/params.h src/rows.cpp src/rows.h src/masks.cpp src/masks.h test/testrows.cpp test/testmasks.cpp)

target_compile_definitions(tests PUBLIC TESTING=1)

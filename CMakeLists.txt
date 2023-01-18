cmake_minimum_required(VERSION 3.20)
project(test)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCES "src/*.cpp")
set(SRC_FILES ${SOURCES})


enable_testing()

add_subdirectory(tests)



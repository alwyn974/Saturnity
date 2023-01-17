cmake_minimum_required(VERSION 3.20)
project(test)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCES "src/*.cpp")
set(SRC_FILES ${SOURCES})

#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#)

# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(tests)

#add_executable(mainTest tests/main_test.cpp)
#
#target_link_libraries(
#  mainTest
#  GTest::gtest_main
#)
#
#include(GoogleTest)
#gtest_discover_tests(mainTest)


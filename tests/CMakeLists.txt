cmake_minimum_required(VERSION 3.17)
project(UnitTest)

set(CMAKE_CXX_STANDARD 20)
set(BINARY_NAME "unit_test")

include(FetchContent) # Add FetchContent

# Fetch google test from github
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest) # Make google test available

add_library(GTest::GTest INTERFACE IMPORTED) # Create a library for google test
target_link_libraries(GTest::GTest INTERFACE gtest_main) # Link the library to gtest_main

# FILE(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.cpp) # Get all the files with .cpp extensions
get_target_property(library_includes Saturnity INCLUDE_DIRECTORIES) # Get the include directories of Saturnity
include_directories(${library_includes}) # Include the project include directories
# Create an executable for the tests, link it to the sources files
add_executable(${BINARY_NAME} ${SOURCES_FILES} MainTest.cpp
        binary/TestEncoding.cpp
)

get_target_property(linked_targets Saturnity INTERFACE_LINK_LIBRARIES) # Get the linked libraries of Saturnity
message(STATUS "Tests linked library: ${linked_targets}")
target_link_libraries(${BINARY_NAME} PRIVATE GTest::GTest ${linked_targets}) # Link the executable to the google test library
add_test(main_gtests ${BINARY_NAME}) # Add the test to the test suite

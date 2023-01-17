cmake_minimum_required(VERSION 3.17)
project(Saturnity)

set(CMAKE_CXX_STANDARD 20)
set(BINARY_NAME "saturnity")
set(PROJECT_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")

#[[if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG) # TODO: replace this with cmake options
endif ()]]

add_executable(${BINARY_NAME} main.cpp # TODO: replace this with add_library
        src/Saturnity.cpp
        )
target_include_directories(${BINARY_NAME} PUBLIC ${PROJECT_INCLUDE_DIRECTORIES}) # Include all headers directories
target_link_libraries(${BINARY_NAME} ) # Link all libraries

# Enable warnings, will not work on header only libraries
target_compile_options(${BINARY_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra>
        $<$<CXX_COMPILER_ID:MSVC>: /W4>
)

# Set the startup project in Visual Studio
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${BINARY_NAME})
    message(STATUS "Setting startup project to ${BINARY_NAME}")
endif (MSVC)

# Enable Tests
enable_testing()
add_subdirectory(tests)

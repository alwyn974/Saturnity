cmake_minimum_required(VERSION 3.17)
project(
        Saturnity
        VERSION 0.0.1.0
        DESCRIPTION "Saturnity is a library to handle networking"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
# Make project-provided Find modules available
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_DEBUG_POSTFIX "-debug")
set(PROJECT_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC src/Saturnity.cpp)
# Include all headers directories
target_include_directories(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

find_package(spdlog 1.11.1 REQUIRED)
# Link all libraries
target_link_libraries(${PROJECT_NAME}
        PUBLIC
            spdlog
)

# Enable warnings, will not work on header only libraries
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra>
        $<$<CXX_COMPILER_ID:MSVC>: /W4>
)

# Add install target
#install(TARGETS ${PROJECT_NAME} EXPORT SaturnityTargets
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib
#        RUNTIME DESTINATION bin
#        INCLUDES DESTINATION include
#)
#install(EXPORT SaturnityTargets
#        FILE SaturnityTargets.cmake
#        NAMESPACE Saturnity::
#        DESTINATION lib/cmake/Saturnity
#)
#
#include(CMakePackageConfigHelpers)
#write_basic_package_version_file(
#        SaturnityConfigVersion.cmake
#        VERSION ${PROJECT_VERSION}
#        COMPATIBILITY SameMajorVersion
#)
#install(FILES SaturnityConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/SaturnityConfigVersion.cmake
#        DESTINATION lib/cmake/Saturnity
#)
#include(CPack)

# Set the startup project in Visual Studio
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    message(STATUS "Setting startup project to ${PROJECT_NAME}")
endif (MSVC)

# Enable Tests
enable_testing() # TODO: add an option to disable tests
add_subdirectory(tests)

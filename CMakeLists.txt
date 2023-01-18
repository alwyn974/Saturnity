cmake_minimum_required(VERSION 3.17)
project(
        Saturnity
        VERSION 0.0.1.0
        DESCRIPTION "Saturnity is a library to handle networking"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
# Make project-provided Find modules available
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(SATURNITY_BUILD_TESTS "Build tests" OFF)
option(SATURNITY_INSTALL "Install Saturnity" ON)

#add_executable(${PROJECT_NAME} main.cpp)
add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC src/Saturnity.cpp)
# Include all headers directories
target_include_directories(${PROJECT_NAME}
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/src"
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

find_package(spdlog 1.11.1 REQUIRED)
find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics audio system window)
# Link all libraries
target_link_libraries(${PROJECT_NAME}
        PUBLIC
            spdlog::spdlog
            sfml-graphics sfml-audio sfml-system sfml-window
)

# Enable warnings, will not work on header only libraries
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra>
        $<$<CXX_COMPILER_ID:MSVC>: /W4>
)

# Set some properties
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "-debug")

# Set the startup project in Visual Studio
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    message(STATUS "Setting startup project to ${PROJECT_NAME}")
endif (MSVC)

if (SATURNITY_BUILD_TESTS)
    message(STATUS "Generating tests")
    enable_testing()
    add_subdirectory(tests)
endif ()

if (SATURNITY_INSTALL)
    # Specify the files to be installed
    message(STATUS "Installing Saturnity")
    install(TARGETS ${PROJECT_NAME}
            EXPORT ${PROJECT_NAME}-targets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    #[[install(EXPORT ${PROJECT_NAME}-targets
            FILE ${PROJECT_NAME}-config.cmake
            NAMESPACE ${PROJECT_NAME}::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )]]
endif ()

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

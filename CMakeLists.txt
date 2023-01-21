cmake_minimum_required(VERSION 3.17)
project(
        Saturnity
        VERSION 0.0.1.0
        DESCRIPTION "Saturnity is a library to handle networking"
        HOMEPAGE_URL "https://github.com/alwyn974/Saturnity"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
# Make project-provided Find modules available
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(SATURNITY_BUILD_TESTS "Build tests" OFF)
option(SATURNITY_INSTALL "Install Saturnity" ON)
option(SATURNITY_CPACK "Create the installer" ON)
option(USE_CLANG_TIDY "Use clang-tidy" OFF)
option(USE_CLANG_FORMAT "Use clang-format" OFF)

#add_executable(${PROJECT_NAME} main.cpp)
add_library(${PROJECT_NAME} src/Saturnity.cpp)
# Include all headers directories
target_include_directories(${PROJECT_NAME}
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/src"
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

find_package(spdlog 1.11.1 REQUIRED)
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window)
find_package(Boost 1.81.0 REQUIRED COMPONENTS asio json iostreams)

# Link all libraries
target_link_libraries(${PROJECT_NAME}
        PUBLIC
            spdlog
            sfml-graphics sfml-audio sfml-system sfml-window
            Boost::asio Boost::json Boost::iostreams
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
    include(GoogleTest)
    enable_testing()
    add_subdirectory(tests)
endif ()

if (USE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if (NOT CLANG_TIDY_EXE)
        message(WARNING "clang-tidy not found.")
    else ()
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    endif ()
endif ()

if (USE_CLANG_FORMAT)

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
    # Setup the version file
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            ${PROJECT_NAME}ConfigVersion.cmake
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY AnyNewerVersion
    )

    # TODO: config more for the install & do cpack
    # TODO: remove this don't thinks is usefull, add real cpack & clang-{format,tidy}
endif ()

if (SATURNITY_CPACK)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPackConfig.cmake)
endif ()

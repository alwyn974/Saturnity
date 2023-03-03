cmake_minimum_required(VERSION 3.17)
project(
        Saturnity
        VERSION 1.0.1.7
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
option(SATURNITY_CPACK "Create the installer" OFF)
option(USE_CLANG_TIDY "Use clang-tidy" OFF) # Used by the CI
option(USE_CLANG_TIDY_WITH_ERRORS "Use clang tidy but all warnings are errors" OFF) # Used by the CI
option(USE_CLANG_TIDY_WITH_FIX "Use clang-tidy with fix" OFF) # Used by the CI
option(BUILD_SHARED_LIBS "Build shared libraries" OFF) # Fix dll issues on Windows

if(WIN32)
    set(${PROJECT_NAME}_ICON ${CMAKE_CURRENT_SOURCE_DIR}/assets/app.rc)
endif()

add_library(${PROJECT_NAME}
        src/core/ByteBuffer.cpp
        src/core/PacketRegistry.cpp
        src/core/network/ConnectionToServer.cpp
        src/core/network/ConnectionToClient.cpp
        src/core/asio/tcp/TCPServer.cpp
        src/core/asio/tcp/TCPClient.cpp
        src/core/asio/tcp/TCPConnectionToClient.cpp
        src/core/asio/udp/UDPServer.cpp
        src/core/asio/udp/UDPClient.cpp
        src/core/asio/udp/UDPConnectionToClient.cpp
)

# Include all headers directories
target_include_directories(${PROJECT_NAME}
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/src"
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

find_package(spdlog 1.11.1 REQUIRED)
find_package(Boost 1.81.0 REQUIRED COMPONENTS asio
    algorithm align array assert bind chrono concept_check config container container_hash context conversion
    core coroutine date_time describe detail exception function function_types functional fusion integer intrusive
    io iterator lexical_cast move mp11 mpl numeric/conversion optional pool predef preprocessor range ratio rational
    regex smart_ptr static_assert system throw_exception tokenizer tuple type_index type_traits typeof unordered
    utility variant2 winapi
)

# Link all libraries
target_link_libraries(${PROJECT_NAME}
        PUBLIC
            spdlog
            boost_asio # Dependencies of boost asio T_T
                boost_algorithm boost_align boost_array boost_assert boost_bind boost_chrono boost_concept_check
                boost_config boost_container boost_container_hash boost_context boost_conversion boost_core
                boost_coroutine boost_date_time boost_describe boost_detail boost_exception boost_function
                boost_function_types boost_functional boost_fusion boost_integer boost_intrusive boost_io
                boost_iterator boost_lexical_cast boost_move boost_mp11 boost_mpl boost_numeric_conversion
                boost_optional boost_pool boost_predef boost_preprocessor boost_range boost_ratio boost_rational
                boost_regex boost_smart_ptr boost_static_assert boost_system boost_throw_exception boost_tokenizer
                boost_tuple boost_type_index boost_type_traits boost_typeof boost_unordered boost_utility
                boost_variant2 boost_winapi
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

if (USE_CLANG_TIDY OR USE_CLANG_TIDY_WITH_ERRORS OR USE_CLANG_TIDY_WITH_FIX)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy-16")
    if (NOT CLANG_TIDY_EXE)
        message(WARNING "clang-tidy not found.")
    else ()
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        if (USE_CLANG_TIDY_WITH_FIX)
            set(CLANG_TIDY_COMMMAND "${CLANG_TIDY_EXE}" "--fix" "--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
        elseif (USE_CLANG_TIDY_WITH_ERRORS)
            set(CLANG_TIDY_COMMMAND "${CLANG_TIDY_EXE}" "--warnings-as-errors=*" "--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
        else ()
            set(CLANG_TIDY_COMMMAND "${CLANG_TIDY_EXE}" "--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
        endif ()
        set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMMAND}")
    endif ()
endif ()

if (SATURNITY_INSTALL OR SATURNITY_CPACK)
    # Specify the files to be installed
    message(STATUS "Installing ${PROJECT_NAME}")
    get_target_property(${PROJECT_NAME}_deps ${PROJECT_NAME} INTERFACE_LINK_LIBRARIES)

    install(TARGETS ${PROJECT_NAME} ${${PROJECT_NAME}_deps}
            EXPORT ${PROJECT_NAME}Targets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT archive
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtime
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT headers
    )

    install(DIRECTORY include
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/../ # Remove the extra include directory
            COMPONENT headers
    )

    install(EXPORT ${PROJECT_NAME}Targets
            FILE ${PROJECT_NAME}Targets.cmake
            NAMESPACE ${PROJECT_NAME}::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} COMPONENT cmake
    )

    # Setup the version file
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            ${PROJECT_NAME}ConfigVersion.cmake
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY AnyNewerVersion
    )

    # generate the config file that is includes the exports
    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
            NO_SET_AND_CHECK_MACRO
            NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )

    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} COMPONENT cmake
    )

    export(EXPORT ${PROJECT_NAME}Targets FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

endif ()

if (SATURNITY_CPACK)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPackConfig.cmake)
endif ()

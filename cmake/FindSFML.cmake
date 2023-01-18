cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME SFML)

if (NOT ${LIBRARY_NAME}_FOUND)
    Include(FetchContent)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Declare(
            ${LIBRARY_NAME}
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x
    )
    FetchContent_MakeAvailable(${LIBRARY_NAME})
    set(${LIBRARY_NAME}_FOUND TRUE)
    message(STATUS "${LIBRARY_NAME} is available now")
    # Add the SFML components that you want to use in your project
    # For example, to use the graphics, window and system modules
    FetchContent_GetProperties(sfml)
    if(NOT sfml_POPULATED)
        message(FATAL_ERROR "sfml not found")
    endif()

    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "")
    set(SFML_BUILD_DOC OFF CACHE BOOL "")
    set(SFML_BUILD_AUDIO ON CACHE BOOL "")
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "")
    set(SFML_BUILD_GRAPHICS ON CACHE BOOL "")
    set(SFML_BUILD_WINDOW ON CACHE BOOL "")
    set(SFML_BUILD_SYSTEM ON CACHE BOOL "")
endif ()


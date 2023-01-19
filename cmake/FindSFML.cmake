cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME SFML)

Include(FetchContent)
if (NOT ${LIBRARY_NAME}_FIND_QUIETLY)
    set(FETCHCONTENT_QUIET OFF)
endif ()
FetchContent_Declare(
        ${LIBRARY_NAME}
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW 1 # Only fetch the head commit
)
FetchContent_MakeAvailable(${LIBRARY_NAME})

# Add the SFML components that you want to use in your project
# For example, to use the graphics, window and system modules
FetchContent_GetProperties(sfml)
message(STATUS "${LIBRARY_NAME} is available now ${${LIBRARY_NAME}_FIND_COMPONENTS}")

set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "")
set(SFML_BUILD_DOC OFF CACHE BOOL "")
set(SFML_BUILD_AUDIO OFF CACHE BOOL "")
set(SFML_BUILD_NETWORK OFF CACHE BOOL "")
set(SFML_BUILD_GRAPHICS OFF CACHE BOOL "")
set(SFML_BUILD_WINDOW OFF CACHE BOOL "")
set(SFML_BUILD_SYSTEM OFF CACHE BOOL "")

foreach(component ${${LIBRARY_NAME}_FIND_COMPONENTS})
    string(TOUPPER ${component} component)
    message(STATUS "Enabling ${component} for ${LIBRARY_NAME}")
    set(SFML_BUILD_${component} ON CACHE BOOL "" FORCE)
endforeach()

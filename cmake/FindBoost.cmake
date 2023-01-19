cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME Boost)

Include(FetchContent)
if (NOT ${LIBRARY_NAME}_FIND_QUIETLY)
    set(FETCHCONTENT_QUIET OFF)
endif ()

set(BOOST_SUBMODULES "tools/cmake;tools/boostdep;tools/boost_install" CACHE STRING "Boost submodules to fetch" FORCE)
set(boost_libraries_required "" CACHE STRING "Required Boost libraries" FORCE)
message(STATUS "Boost Components: ${${LIBRARY_NAME}_FIND_COMPONENTS}")
foreach(submodule ${${LIBRARY_NAME}_FIND_COMPONENTS})
    string(SUBSTRING "${submodule}" 0 8 prefix)
    list(FIND BOOST_SUBMODULES "libs/${submodule}" index)
    if (index EQUAL -1)
        if (prefix STREQUAL "numeric_") # Fix for numeric_*
            string(REPLACE "numeric_" "numeric/" submodule ${submodule})
        endif ()
        message(STATUS "Adding submodule ${submodule}")
        list(APPEND BOOST_SUBMODULES "libs/${submodule}")
    endif ()
endforeach()
message(STATUS "Submodules: ${BOOST_SUBMODULES}")

set(BOOST_INCLUDE_LIBRARIES ${${LIBRARY_NAME}_FIND_COMPONENTS}) # enabled libraries
set(BOOST_ENABLE_CMAKE ON) # CMake support
message(STATUS "Fetching Boost")
FetchContent_Declare(
        ${LIBRARY_NAME}
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.81.0
        GIT_SHALLOW 1 # Only fetch the head commit
        GIT_SUBMODULES ${BOOST_SUBMODULES}
        GIT_PROGRESS TRUE
        CACHE
)
FetchContent_MakeAvailable(${LIBRARY_NAME})
FetchContent_GetProperties(${LIBRARY_NAME})

foreach(component ${${LIBRARY_NAME}_FIND_COMPONENTS})
    message(STATUS "Adding component ${component}")
    get_target_property(linked_targets Boost::${component} INTERFACE_LINK_LIBRARIES) # Get the linked libraries of Saturnity

    if (NOT linked_targets)
        message(STATUS "No linked targets for ${component}")
        continue()
    endif ()

    # Creating a list of all the boost library required by the component
    foreach(required_lib ${linked_targets})
        string(REGEX REPLACE "Boost::" "" required_lib ${required_lib})
        list(FIND boost_libraries_required "${required_lib}" index)
        if (index EQUAL -1)
            list(APPEND boost_libraries_required "${required_lib}")
        endif ()
    endforeach()

    message(STATUS "Boost::${component} require: ${boost_libraries_required}")

    #[[message(STATUS "Finding missing boost libraries")
    set(Boost_FOUND FALSE CACHE BOOL "Boost found" FORCE)
    find_package(Boost REQUIRED COMPONENTS ${boost_libraries_required})]]
endforeach()

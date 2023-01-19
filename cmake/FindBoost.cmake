cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME Boost)

Include(FetchContent)
if (NOT ${LIBRARY_NAME}_FIND_QUIETLY)
    set(FETCHCONTENT_QUIET OFF)
endif ()

# set the timestamps of extracted contents to the time of extraction
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

#[[set(BOOST_SUBMODULES "tools/cmake;tools/boostdep;tools/boost_install" CACHE STRING "Boost submodules to fetch" FORCE)
message(STATUS "Boost Components: ${${LIBRARY_NAME}_FIND_COMPONENTS}")
foreach (submodule ${${LIBRARY_NAME}_FIND_COMPONENTS})
    string(SUBSTRING "${submodule}" 0 8 prefix)
    list(FIND BOOST_SUBMODULES "libs/${submodule}" index)
    if (index EQUAL -1)
        if (prefix STREQUAL "numeric_") # Fix for numeric_*
            string(REPLACE "numeric_" "numeric/" submodule ${submodule})
        endif ()
        message(STATUS "Adding submodule ${submodule}")
        list(APPEND BOOST_SUBMODULES "libs/${submodule}")
    endif ()
endforeach ()
message(STATUS "Submodules: ${BOOST_SUBMODULES}")]]

set(BOOST_INCLUDE_LIBRARIES ${${LIBRARY_NAME}_FIND_COMPONENTS}) # enabled libraries
set(BOOST_ENABLE_CMAKE ON) # CMake support
message(STATUS "Fetching Boost")
FetchContent_Declare(
        ${LIBRARY_NAME}
        URL https://github.com/boostorg/boost/releases/download/boost-1.81.0/boost-1.81.0.tar.xz
        #[[GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.81.0
        GIT_SHALLOW 1 # Only fetch the head commit
        GIT_SUBMODULES ${BOOST_SUBMODULES}
        GIT_PROGRESS TRUE
        CACHE]]
)
FetchContent_MakeAvailable(${LIBRARY_NAME})
FetchContent_GetProperties(${LIBRARY_NAME})

#[[Include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost.utils.cmake)

foreach (component ${${LIBRARY_NAME}_FIND_COMPONENTS})
    message(STATUS "Adding Boost component ${component}")
    create_boost_dependency(Boost::${component})
endforeach ()]]

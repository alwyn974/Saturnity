cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME Boost)

Include(FetchContent)
if (NOT ${LIBRARY_NAME}_FIND_QUIETLY)
    set(FETCHCONTENT_QUIET OFF)
endif ()
set(BOOST_INCLUDE_LIBRARIES asio) # enabled libraries
set(BOOST_ENABLE_CMAKE ON) # CMake support
message(STATUS "Fetching Boost ${Boost_FIND_REQUIRED}")
FetchContent_Declare(
        ${LIBRARY_NAME}
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.81.0
        GIT_SHALLOW 1 # Only fetch the head commit
)
FetchContent_MakeAvailable(${LIBRARY_NAME})

#TODO: rework this, taking too much time
#TODO: get the version required from the CMakeLists.txt file

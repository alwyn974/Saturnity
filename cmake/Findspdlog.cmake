cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME spdlog)

Include(FetchContent)
if (NOT ${LIBRARY_NAME}_FIND_QUIETLY)
    set(FETCHCONTENT_QUIET OFF)
endif ()
FetchContent_Declare(
        ${LIBRARY_NAME}
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.11.0
        GIT_SHALLOW 1 # Only fetch the head commit
)
FetchContent_MakeAvailable(${LIBRARY_NAME})
message(STATUS "${LIBRARY_NAME} is available now")

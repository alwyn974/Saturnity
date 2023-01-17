cmake_minimum_required(VERSION 3.17)

set(LIBRARY_NAME spdlog)

if (NOT ${LIBRARY_NAME}_FOUND)
    Include(FetchContent)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Declare(
            ${LIBRARY_NAME}
            GIT_REPOSITORY https://github.com/gabime/spdlog.git
            GIT_TAG v1.11.0
    )
    FetchContent_MakeAvailable(${LIBRARY_NAME})
    set(${LIBRARY_NAME}_FOUND TRUE)
    message(STATUS "${LIBRARY_NAME} is available now")
    list(APPEND PROJECT_DEPENDENCIES "${LIBRARY_NAME}")
endif ()


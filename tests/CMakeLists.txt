include(FetchContent)
#set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

#FetchContent_Declare(
#        SFML
#        GIT_REPOSITORY https://github.com/SFML/SFML.git
#        GIT_TAG 2.5.1
#)

FetchContent_MakeAvailable(googletest)
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED true)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(main_test main_test.cpp ${SRC_FILES})

target_link_libraries(main_test
        PRIVATE
        GTest::GTest
        sfml-graphics
        )

add_test(main_gtests main_test)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(main_test main_test.cpp ${SRC_FILES})

target_link_libraries(main_test
 PRIVATE
  GTest::GTest)

add_test(main_gtests main_test)
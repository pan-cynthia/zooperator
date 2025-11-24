include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)

set(TEST_SOURCES test_animal.cpp test_penguin.cpp test_bear.cpp test_rabbit.cpp)

add_executable(zooperator_tests ${TEST_SOURCES})

target_link_libraries(zooperator_tests PRIVATE GTest::gtest_main zooperator_lib)

target_include_directories(zooperator_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(zooperator_tests)

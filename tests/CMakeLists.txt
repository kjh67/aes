#
# GOOGLETEST SETUP
#

# Min C++ Standard requirement for GoogleTest
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()


#
# TEST FILE SETUP
#

add_executable(
    aes_tests
    state.test.cc
    key.test.cc
    aes.test.cc
    aes_mathfuncs.test.cc
)

target_link_libraries(
    aes_tests
    GTest::gtest_main
    aes
)

include(GoogleTest)
gtest_discover_tests(aes_tests)

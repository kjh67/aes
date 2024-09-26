cmake_minimum_required(VERSION 3.14)
project(
    aes
    VERSION 0.1.0
    LANGUAGES CXX
)


#
# MAIN PROJECT SETUP
#

add_library(aes src/aes.cpp src/key.cpp src/state.cpp)
target_include_directories(aes PUBLIC include)


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
    tests/state.test.cc
    tests/key.test.cc
    tests/aes.test.cc
)

target_link_libraries(
    aes_tests
    GTest::gtest_main
    aes
)

include(GoogleTest)
gtest_discover_tests(aes_tests)

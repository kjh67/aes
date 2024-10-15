cmake_minimum_required(VERSION 3.14)
project(
    aes
    VERSION 0.1.0
    LANGUAGES CXX
)


#
# MAIN PROJECT SETUP
#

add_library(aes src/aes.cpp src/key.cpp src/state.cpp src/aes_mathfuncs.cpp)
target_include_directories(aes PUBLIC include)

enable_testing()
add_subdirectory(tests)

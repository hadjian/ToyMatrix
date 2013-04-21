cmake_minimum_required (VERSION 2.8)
project (ToyMatrixUnitTests)

# The version number.
set (ToyMatrix_VERSION_MAJOR 0)
set (ToyMatrix_VERSION_MINOR 1)
 
# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/ToyMatrixConfig.h.in"
#  "${PROJECT_BINARY_DIR}/ToyMatrixConfig.h"
#)

add_library(gtest_main STATIC IMPORTED)
set_property(TARGET gtest_main PROPERTY IMPORTED_LOCATION ../../gtest-1.6.0/libgtest_main.a)

add_library(gtest STATIC IMPORTED)
set_property(TARGET gtest PROPERTY IMPORTED_LOCATION ../../gtest-1.6.0/libgtest.a)
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}" "../../gtest-1.6.0/include")
 
# add the executable
add_executable(TestToyMatrix TestToyMatrix.cpp)
target_link_libraries(TestToyMatrix gtest_main gtest)

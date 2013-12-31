cmake_minimum_required(VERSION 2.8)
project(ToyMatrix_UnitTests)

option(ArithmeticExceptions "Check Include/arithmeticex.h for a list of exceptions. 
                             Turn on to help you hunt bugs (but run less efficiently)." OFF)

if (ArithmeticExceptions)
  add_definitions( -DARITHMETIC_EXCEPTIONS )
endif(ArithmeticExceptions)

add_library(gtest_main STATIC IMPORTED)
set_property(TARGET gtest_main PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../gtest-1.6.0/libgtest_main.a)

add_library(gtest STATIC IMPORTED)
set_property(TARGET gtest PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../gtest-1.6.0/libgtest.a)

include_directories("${CMAKE_SOURCE_DIR}/../gtest-1.6.0/include" "${CMAKE_SOURCE_DIR}/")

# add the executable. The .h file are added to make
# the target depend on the .h file and to rebuild the
# target when the .h file changes.
add_executable(testtoymatrix testtoymatrix.cpp ${CMAKE_SOURCE_DIR}/Src/toymatrix.h ${CMAKE_SOURCE_DIR}/Include/arithmeticex.cpp)
target_link_libraries(testtoymatrix gtest_main gtest)

add_executable(testexceptions testexceptions.cpp ${CMAKE_SOURCE_DIR}/Include/arithmeticex.cpp)
target_link_libraries(testexceptions gtest_main gtest)

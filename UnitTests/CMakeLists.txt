cmake_minimum_required(VERSION 2.8)
project(ToyMatrix_UnitTests)

option(ArithmeticExceptions "Check Include/arithmeticex.h for a list of exceptions. 
                             Turn on to help you hunt bugs (but run less efficiently)." OFF)

if (ArithmeticExceptions)
  add_definitions( -DARITHMETIC_EXCEPTIONS )
endif(ArithmeticExceptions)

# add the executable. The .h file are added to make
# the target depend on the .h file and to rebuild the
# target when the .h file changes.
add_executable(testtoymatrix testtoymatrix.cpp ${CMAKE_SOURCE_DIR}/Include/toymatrix.h ${CMAKE_SOURCE_DIR}/Include/arithmeticex.cpp)
target_link_libraries(testtoymatrix ${GTEST_MAIN_LIBRARIES})
set_target_properties(testtoymatrix PROPERTIES
                       COMPILE_FLAGS ${GTEST_CXX_FLAGS})

add_executable(testtoyvector testtoyvector.cpp ${CMAKE_SOURCE_DIR}/Include/toyvector.h ${CMAKE_SOURCE_DIR}/Include/arithmeticex.cpp)
target_link_libraries(testtoyvector ${GTEST_MAIN_LIBRARIES})
set_target_properties(testtoyvector PROPERTIES
                       COMPILE_FLAGS ${GTEST_CXX_FLAGS})

add_executable(testexceptions testexceptions.cpp ${CMAKE_SOURCE_DIR}/Include/arithmeticex.cpp)
target_link_libraries(testexceptions ${GTEST_MAIN_LIBRARIES})
set_target_properties(testexceptions PROPERTIES 
                       COMPILE_FLAGS ${GTEST_CXX_FLAGS})

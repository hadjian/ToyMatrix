cmake_minimum_required (VERSION 2.8)
project (ToyMatrix)

# The version number.
set(ToyMatrix_VERSION_MAJOR 0)
set(ToyMatrix_VERSION_MINOR 1)
set(ToyMatrix_VERSION_PATCH 0)
set(ToyMatrix_VERSION ${ToyMatrix_VERSION_MAJOR}.${ToyMatrix_VERSION_MINOR}.${ToyMatrix_VERSION_PATCH})

find_package(GTest 1.6.0 EXACT REQUIRED)

include_directories(${PROJECT_SOURCE_DIR} ${GTEST_INCLUDE_DIRS})

add_subdirectory(UnitTests EXCLUDE_FROM_ALL)
add_custom_target(UnitTests
  COMMAND ${CMAKE_BUILD_TOOL}
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/UnitTests")

add_custom_target(NoLibraryWarning
  ALL
  COMMENT "This project consists of C++ templates, only. 
  As such, there is no library to build.
  Run \"make UnitTests\" to build the tests for the templates.")

set(CONF_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR})
configure_file(ToyMatrixConfig.cmake.in ToyMatrixConfig.cmake @ONLY)
configure_file(ToyMatrixConfigVersion.cmake.in ToyMatrixConfigVersion.cmake @ONLY)

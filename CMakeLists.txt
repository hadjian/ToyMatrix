cmake_minimum_required (VERSION 2.8)
project (ToyMatrix)

# The version number.
set (ToyMatrix_VERSION_MAJOR 0)
set (ToyMatrix_VERSION_MINOR 1)

add_subdirectory(UnitTests EXCLUDE_FROM_ALL)
add_custom_target(UnitTests
  COMMAND ${CMAKE_BUILD_TOOL}
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/UnitTests")

add_custom_target(NoLibraryWarning
  ALL
  COMMENT "This project consists of C++ templates, only. 
  As such, there is no library to build.
  Run \"make UnitTests\" to build the tests for the templates.")


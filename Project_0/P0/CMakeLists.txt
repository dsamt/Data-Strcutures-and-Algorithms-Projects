cmake_minimum_required(VERSION 3.5)
project(P0 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VECTOR_SOURCE
  Vector.hpp Vector.cpp)

set(TEST_SOURCE
  student_tests.cpp)

set(SOURCE ${VECTOR_SOURCE})

# create unittests
add_executable(student-tests catch.hpp ${SOURCE} ${TEST_SOURCE})

# some simple tests
enable_testing()
add_test(student-tests student-tests)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
  Vector.cpp student_tests.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

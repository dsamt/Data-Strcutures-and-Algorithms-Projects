cmake_minimum_required(VERSION 3.5)
project(P2_1 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(STACK_SOURCE
  Stack.hpp Stack.txx)

set(TEST_SOURCE
  student_tests.cpp)

set(SOURCE ${STACK_SOURCE})

# create unittests
add_executable(student-tests catch.hpp student_catch.cpp ${SOURCE} ${TEST_SOURCE})

# some simple tests
enable_testing()
add_test(student-tests student-tests)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
  Stack.txx student_tests.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

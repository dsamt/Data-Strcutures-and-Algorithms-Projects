cmake_minimum_required(VERSION 3.5)
project(dlinkedlist CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE student_tests.cpp dLinkedList.hpp dNode.hpp)

# create unittests
add_executable(student_tests catch.hpp ${SOURCE})
set_target_properties(student_tests PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()

# unit tests
add_test(unittest student_tests)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
  dNode.txx dLinkedList.txx student_tests.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
     

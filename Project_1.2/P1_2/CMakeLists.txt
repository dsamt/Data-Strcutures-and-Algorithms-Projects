cmake_minimum_required(VERSION 3.5)
project(turing_machine CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE student_tests.cpp TuringMachine.hpp)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# create unittests
add_executable(student-tests catch.hpp ${SOURCE})
set_target_properties(student-tests PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()

# unit tests
add_test(unittest student-tests)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
  TuringMachine.hpp TuringMachine.cpp Tape.hpp Tape.cpp student_tests.cpp dNode.txx dLinkedList.txx
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
     

cmake_minimum_required(VERSION 3.5)
project(route_finder CXX)

set(CMAKE_CXX STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE student_tests.cpp RouteFinder.hpp dNode.hpp dLinkedList.hpp)

add_executable(student_tests catch.hpp student_catch.cpp ${SOURCE})
set_target_properties(student_tests PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()

add_test(unittest student_tests)

add_custom_target(submission COMMAND
	${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
	RouteFinder.hpp RouteFinder.cpp student_tests.cpp dNode.txx dLinkedList.txx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
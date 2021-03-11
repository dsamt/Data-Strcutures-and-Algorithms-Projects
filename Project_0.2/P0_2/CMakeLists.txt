cmake_minimum_required(VERSION 3.5)
project(P0 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# build the image library
ADD_SUBDIRECTORY(lib)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

# build the compare program
ADD_EXECUTABLE(compare compare.cpp)
TARGET_LINK_LIBRARIES(compare image)

set(VECTOR_SOURCE
  Vector.hpp Vector.cpp)

set(SPHERE_SOURCE
  Sphere.hpp Sphere.cpp)

set(RAYTRACER_SOURCE
  RayTracer.hpp RayTracer.cpp)
  
set(TEST_SOURCE
  student_tests.cpp)

set(SOURCE ${VECTOR_SOURCE} ${SPHERE_SOURCE} ${RAYTRACER_SOURCE})

# create unittests
add_executable(student-tests catch.hpp ${SOURCE} ${TEST_SOURCE})
TARGET_LINK_LIBRARIES(student-tests image)

# some simple tests
enable_testing()
add_test(student-tests student-tests)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
  Vector.cpp Sphere.cpp RayTracer.cpp student_tests.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

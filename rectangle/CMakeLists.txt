cmake_minimum_required(VERSION 3.6)
project(openMPI)
set(CMAKE_CXX_COMPILER mpicxx)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}")

add_executable(rectanglePatternDetection main.cpp testRectangles.h MatrixBuilder.cpp MatrixBuilder.h)


cmake_minimum_required(VERSION 3.0)
project(openMPI)
set(CMAKE_CXX_COMPILER mpicxx)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}")

add_executable(rectanglePatternDetection main.cpp matrixCreation/MatrixBuilder.cpp matrixCreation/MatrixBuilder.h matrixCreation/CoordValidator.cpp matrixCreation/CoordValidator.h matrixCreation/VectorParser.cpp matrixCreation/VectorParser.h search/RectangleValidator.cpp search/RectangleValidator.h RectangleDetector.cpp RectangleDetector.h)
add_executable(tests ./testConfigs/TestSearch.cpp matrixCreation/MatrixBuilder.cpp matrixCreation/MatrixBuilder.h matrixCreation/CoordValidator.cpp matrixCreation/CoordValidator.h matrixCreation/VectorParser.cpp matrixCreation/VectorParser.h search/RectangleValidator.cpp search/RectangleValidator.h RectangleDetector.cpp RectangleDetector.h)
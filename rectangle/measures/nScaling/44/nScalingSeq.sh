#!/bin/bash

cd ../../../../
cmake CMakeLists.txt -DCMAKE_BUILD_TYPE=RELEASE
make
cd rectangle/RELEASE/

pathToConfig="../measures/nScaling/44/"

echo "Starting rectanglePatternDetection:......."
echo "------------------------------------------"
echo "0"
mpirun rectanglePatternDetection $pathToConfig/40000/0
mpirun rectanglePatternDetection $pathToConfig/36000/0
mpirun rectanglePatternDetection $pathToConfig/32000/0
mpirun rectanglePatternDetection $pathToConfig/28000/0
mpirun rectanglePatternDetection $pathToConfig/24000/0
mpirun rectanglePatternDetection $pathToConfig/20000/0
mpirun rectanglePatternDetection $pathToConfig/16000/0
mpirun rectanglePatternDetection $pathToConfig/12000/0
mpirun rectanglePatternDetection $pathToConfig/8000/0
mpirun rectanglePatternDetection $pathToConfig/4000/0
mpirun rectanglePatternDetection $pathToConfig/100/0
echo "------------------------------------------"
echo "1"
mpirun rectanglePatternDetection $pathToConfig/40000/1
mpirun rectanglePatternDetection $pathToConfig/36000/1
mpirun rectanglePatternDetection $pathToConfig/32000/1
mpirun rectanglePatternDetection $pathToConfig/28000/1
mpirun rectanglePatternDetection $pathToConfig/24000/1
mpirun rectanglePatternDetection $pathToConfig/20000/1
mpirun rectanglePatternDetection $pathToConfig/16000/1
mpirun rectanglePatternDetection $pathToConfig/12000/1
mpirun rectanglePatternDetection $pathToConfig/8000/1
mpirun rectanglePatternDetection $pathToConfig/4000/1
mpirun rectanglePatternDetection $pathToConfig/100/1
echo "------------------------------------------"
echo "2"
mpirun rectanglePatternDetection $pathToConfig/40000/2
mpirun rectanglePatternDetection $pathToConfig/36000/2
mpirun rectanglePatternDetection $pathToConfig/32000/2
mpirun rectanglePatternDetection $pathToConfig/28000/2
mpirun rectanglePatternDetection $pathToConfig/24000/2
mpirun rectanglePatternDetection $pathToConfig/20000/2
mpirun rectanglePatternDetection $pathToConfig/16000/2
mpirun rectanglePatternDetection $pathToConfig/12000/2
mpirun rectanglePatternDetection $pathToConfig/8000/2
mpirun rectanglePatternDetection $pathToConfig/4000/2
mpirun rectanglePatternDetection $pathToConfig/100/2

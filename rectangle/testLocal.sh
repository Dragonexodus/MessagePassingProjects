#!/bin/bash

cd ../
cmake CMakeLists.txt -DCMAKE_BUILD_TYPE=RELEASE
make
cd rectangle/RELEASE/

echo "Starting rectanglePatternDetection:......."
echo "------------------------------------------"

pathToConfig="../testConfigs/"

mpirun -npernode 2 rectanglePatternDetection ../config
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/nothingFound1
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/rectFound1
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/rectFound2
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/rectFound3
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/rectFound4
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/rectFound5
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/rectFound6
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/somethingElseFound1
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/somethingElseFound2
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/somethingElseFound3
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/somethingElseFound4
mpirun -npernode 2 rectanglePatternDetection $pathToConfig/somethingElseFound5

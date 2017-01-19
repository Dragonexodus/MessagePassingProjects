#!/bin/bash

cd ../
cmake CMakeLists.txt -DCMAKE_BUILD_TYPE=RELEASE
make
cd rectangle/RELEASE/

echo "Starting rectanglePatternDetection:......."
echo "------------------------------------------"

pathToConfig="../testConfigs/"
hostFileDir="../hosts"

mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection ../config

mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/nothingFound1
mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/rectFound1
mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/rectFound2
mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/rectFound3
mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/rectFound4
mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/rectFound5
mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/rectFound6
mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/somethingElseFound1
mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/somethingElseFound2
mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/somethingElseFound3
mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/somethingElseFound4
mpirun -np 2 -hostfile $hostFileDir rectanglePatternDetection $pathToConfig/somethingElseFound5

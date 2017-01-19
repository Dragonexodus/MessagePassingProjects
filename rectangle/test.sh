#!/bin/bash

cd ../
cmake CMakeLists.txt -DCMAKE_BUILD_TYPE=RELEASE
make
cd rectangle/RELEASE/

echo "Starting rectanglePatternDetection:......."
echo "------------------------------------------"

mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../config

mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/nothingFound1
mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/rectFound1
mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/rectFound2
mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/rectFound3
mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/rectFound4
mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/rectFound5
mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/rectFound6
mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/somethingElseFound1
mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/somethingElseFound2
mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/somethingElseFound3
mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/somethingElseFound4
mpirun -np 2 -hostfile ../hosts rectanglePatternDetection ../testConfigs/somethingElseFound5

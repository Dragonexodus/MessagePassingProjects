#!/bin/bash

cd ../
cmake CMakeLists.txt
make
cd rectangle/

echo "Starting rectanglePatternDetection:......."
echo "------------------------------------------"
mpirun -np 4 -hostfile hosts rectanglePatternDetection
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/nothingFound1
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/rectFound1
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/rectFound2
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/rectFound3
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/rectFound4
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/rectFound5
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/rectFound6
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/somethingElseFound1
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/somethingElseFound2
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/somethingElseFound3
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/somethingElseFound4
mpirun -np 4 -hostfile hosts rectanglePatternDetection testConfigs/somethingElseFound5

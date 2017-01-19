#!/bin/bash

cd ../
cmake CMakeLists.txt -DCMAKE_BUILD_TYPE=RELEASE
make
cd rectangle/RELEASE/

echo "Starting rectanglePatternDetection:......."
echo "------------------------------------------"
# measures TODO: one runMPI call for all measures -> use 14 host files
# mpirun -np 1 rectanglePatternDetection ../2
# mpirun -np 1 rectanglePatternDetection ../1
# mpirun -np 1 rectanglePatternDetection ../0

mpirun -np 1 rectanglePatternDetection ../config

# mpirun -np 2 -hostfile hosts rectanglePatternDetection 1
# mpirun -np 2 -hostfile hosts rectanglePatternDetection 0


# tests
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/nothingFound1
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/rectFound1
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/rectFound2
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/rectFound3
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/rectFound4
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/rectFound5
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/rectFound6
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/somethingElseFound1
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/somethingElseFound2
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/somethingElseFound3
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/somethingElseFound4
# mpirun -np 2 -hostfile hosts rectanglePatternDetection testConfigs/somethingElseFound5

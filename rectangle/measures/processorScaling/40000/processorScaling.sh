#!/bin/bash

cd ../
cmake CMakeLists.txt -DCMAKE_BUILD_TYPE=RELEASE
make
cd rectangle/RELEASE/

pathToConfig="../measures/processorScaling/40000/"

echo "Starting rectanglePatternDetection:......."
echo "------------------------------------------"

mpirun -np 2 -hostfile ../hostfiles/22 rectanglePatternDetection $pathToConfig/2
mpirun -np 2 -hostfile ../hostfiles/22 rectanglePatternDetection $pathToConfig/1
mpirun -np 2 -hostfile ../hostfiles/22 rectanglePatternDetection $pathToConfig/0

mpirun -np 2 -hostfile ../hostfiles/20 rectanglePatternDetection $pathToConfig/2
mpirun -np 2 -hostfile ../hostfiles/20 rectanglePatternDetection $pathToConfig/1
mpirun -np 2 -hostfile ../hostfiles/20 rectanglePatternDetection $pathToConfig/0

mpirun -np 2 -hostfile ../hostfiles/18 rectanglePatternDetection $pathToConfig/2
mpirun -np 2 -hostfile ../hostfiles/18 rectanglePatternDetection $pathToConfig/1
mpirun -np 2 -hostfile ../hostfiles/18 rectanglePatternDetection $pathToConfig/0

mpirun -np 2 -hostfile ../hostfiles/16 rectanglePatternDetection $pathToConfig/2
mpirun -np 2 -hostfile ../hostfiles/16 rectanglePatternDetection $pathToConfig/1
mpirun -np 2 -hostfile ../hostfiles/16 rectanglePatternDetection $pathToConfig/0

mpirun -np 2 -hostfile ../hostfiles/14 rectanglePatternDetection $pathToConfig/2
mpirun -np 2 -hostfile ../hostfiles/14 rectanglePatternDetection $pathToConfig/1
mpirun -np 2 -hostfile ../hostfiles/14 rectanglePatternDetection $pathToConfig/0

mpirun -np 2 -hostfile ../hostfiles/12 rectanglePatternDetection $pathToConfig/2
mpirun -np 2 -hostfile ../hostfiles/12 rectanglePatternDetection $pathToConfig/1
mpirun -np 2 -hostfile ../hostfiles/12 rectanglePatternDetection $pathToConfig/0

mpirun -np 2 -hostfile ../hostfiles/10 rectanglePatternDetection $pathToConfig/2
mpirun -np 2 -hostfile ../hostfiles/10 rectanglePatternDetection $pathToConfig/1
mpirun -np 2 -hostfile ../hostfiles/10 rectanglePatternDetection $pathToConfig/0

mpirun -np 2 -hostfile ../hostfiles/8 rectanglePatternDetection $pathToConfig/2
mpirun -np 2 -hostfile ../hostfiles/8 rectanglePatternDetection $pathToConfig/1
mpirun -np 2 -hostfile ../hostfiles/8 rectanglePatternDetection $pathToConfig/0

mpirun -np 2 -hostfile ../hostfiles/6 rectanglePatternDetection $pathToConfig/2
mpirun -np 2 -hostfile ../hostfiles/6 rectanglePatternDetection $pathToConfig/1
mpirun -np 2 -hostfile ../hostfiles/6 rectanglePatternDetection $pathToConfig/0

mpirun -np 2 -hostfile ../hostfiles/4 rectanglePatternDetection $pathToConfig/2
mpirun -np 2 -hostfile ../hostfiles/4 rectanglePatternDetection $pathToConfig/1
mpirun -np 2 -hostfile ../hostfiles/4 rectanglePatternDetection $pathToConfig/0

mpirun -np 2 -hostfile ../hostfiles/2 rectanglePatternDetection $pathToConfig/2
mpirun -np 2 -hostfile ../hostfiles/2 rectanglePatternDetection $pathToConfig/1
mpirun -np 2 -hostfile ../hostfiles/2 rectanglePatternDetection $pathToConfig/0

mpirun -np 1 -hostfile ../hostfiles/1 rectanglePatternDetection $pathToConfig/2
mpirun -np 1 -hostfile ../hostfiles/1 rectanglePatternDetection $pathToConfig/1
mpirun -np 1 -hostfile ../hostfiles/1 rectanglePatternDetection $pathToConfig/0

# mpirun -np 2 -hostfile hosts rectanglePatternDetection 1
# mpirun -np 2 -hostfile hosts rectanglePatternDetection 0


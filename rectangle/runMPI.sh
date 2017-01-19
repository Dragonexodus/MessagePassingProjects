#!/bin/bash

cd ../
cmake CMakeLists.txt -DCMAKE_BUILD_TYPE=RELEASE
make
cd rectangle/RELEASE/

echo "Starting rectanglePatternDetection:......."
echo "------------------------------------------"
# measures TODO: one runMPI call for all measures -> use 14 host files

mpirun -np 2 -hostfile ../hostfiles/22 rectanglePatternDetection ../2
mpirun -np 2 -hostfile ../hostfiles/22 rectanglePatternDetection ../1
mpirun -np 2 -hostfile ../hostfiles/22 rectanglePatternDetection ../0

mpirun -np 2 -hostfile ../hostfiles/20 rectanglePatternDetection ../2
mpirun -np 2 -hostfile ../hostfiles/20 rectanglePatternDetection ../1
mpirun -np 2 -hostfile ../hostfiles/20 rectanglePatternDetection ../0

mpirun -np 2 -hostfile ../hostfiles/18 rectanglePatternDetection ../2
mpirun -np 2 -hostfile ../hostfiles/18 rectanglePatternDetection ../1
mpirun -np 2 -hostfile ../hostfiles/18 rectanglePatternDetection ../0

mpirun -np 2 -hostfile ../hostfiles/16 rectanglePatternDetection ../2
mpirun -np 2 -hostfile ../hostfiles/16 rectanglePatternDetection ../1
mpirun -np 2 -hostfile ../hostfiles/16 rectanglePatternDetection ../0

mpirun -np 2 -hostfile ../hostfiles/14 rectanglePatternDetection ../2
mpirun -np 2 -hostfile ../hostfiles/14 rectanglePatternDetection ../1
mpirun -np 2 -hostfile ../hostfiles/14 rectanglePatternDetection ../0

mpirun -np 2 -hostfile ../hostfiles/12 rectanglePatternDetection ../2
mpirun -np 2 -hostfile ../hostfiles/12 rectanglePatternDetection ../1
mpirun -np 2 -hostfile ../hostfiles/12 rectanglePatternDetection ../0

mpirun -np 2 -hostfile ../hostfiles/10 rectanglePatternDetection ../2
mpirun -np 2 -hostfile ../hostfiles/10 rectanglePatternDetection ../1
mpirun -np 2 -hostfile ../hostfiles/10 rectanglePatternDetection ../0

mpirun -np 2 -hostfile ../hostfiles/8 rectanglePatternDetection ../2
mpirun -np 2 -hostfile ../hostfiles/8 rectanglePatternDetection ../1
mpirun -np 2 -hostfile ../hostfiles/8 rectanglePatternDetection ../0

mpirun -np 2 -hostfile ../hostfiles/6 rectanglePatternDetection ../2
mpirun -np 2 -hostfile ../hostfiles/6 rectanglePatternDetection ../1
mpirun -np 2 -hostfile ../hostfiles/6 rectanglePatternDetection ../0

mpirun -np 2 -hostfile ../hostfiles/4 rectanglePatternDetection ../2
mpirun -np 2 -hostfile ../hostfiles/4 rectanglePatternDetection ../1
mpirun -np 2 -hostfile ../hostfiles/4 rectanglePatternDetection ../0

mpirun -np 2 -hostfile ../hostfiles/2 rectanglePatternDetection ../2
mpirun -np 2 -hostfile ../hostfiles/2 rectanglePatternDetection ../1
mpirun -np 2 -hostfile ../hostfiles/2 rectanglePatternDetection ../0

mpirun -np 1 -hostfile ../hostfiles/1 rectanglePatternDetection ../2
mpirun -np 1 -hostfile ../hostfiles/1 rectanglePatternDetection ../1
mpirun -np 1 -hostfile ../hostfiles/1 rectanglePatternDetection ../0

# mpirun -np 2 -hostfile hosts rectanglePatternDetection 1
# mpirun -np 2 -hostfile hosts rectanglePatternDetection 0


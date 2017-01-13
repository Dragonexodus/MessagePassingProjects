#!/bin/bash
echo "Starting rectanglePatternDetection:......."

mpirun -np 4 -hostfile hosts rectanglePatternDetection

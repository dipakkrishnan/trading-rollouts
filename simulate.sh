#!/bin/bash
mpirun -np 4 ./rollouts
# Get number of processes from command line argument, default to 4 if not provided
NUM_PROCS=${1:-4}

mpirun -np $NUM_PROCS ./rollouts

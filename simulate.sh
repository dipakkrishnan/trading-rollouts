#!/bin/bash
# Get number of processes from command line argument, default to 4 if not provided
NUM_PROCS=${1:-4}

mpirun --mca btl ^sm -np 4 ./rollouts

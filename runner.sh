#!/bin/sh

# Output the number of processors
#echo "Got &NSLOTS processor(s)"

# Setting OpenMP Threading parameter
echo "Running with 4 threads.."
export OMP_NUM_THREADS=6
./build/main input/input_4096.txt output_on
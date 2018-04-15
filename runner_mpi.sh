#!/bin/sh

# Output the number of processors
#echo "Got &NSLOTS processor(s)"

# Setting OpenMP Threading parameter
echo "Got $NSLOTS processors(s)."

export OMP_NUM_THREADS=4
./build/main input/input_1024.txt output_on

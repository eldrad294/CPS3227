#!/bin/sh

# Output the number of processors
#echo "Got &NSLOTS processor(s)"

# Output the number of processors
echo "Got $NSLOTS processor(s)"

export OMP_NUM_THREADS=1
./build/main input/input_1024.txt output_on

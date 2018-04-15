#!/bin/sh

# Output the number of processors
#echo "Got &NSLOTS processor(s)"

# Setting OpenMP Threading parameter
echo "Got $NSLOTS processor(s)."

# File Body Count: (64)
export OMP_NUM_THREADS=2
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
export OMP_NUM_THREADS=3
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
export OMP_NUM_THREADS=4
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
export OMP_NUM_THREADS=5
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
export OMP_NUM_THREADS=6
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
export OMP_NUM_THREADS=7
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
export OMP_NUM_THREADS=8
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
export OMP_NUM_THREADS=9
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
export OMP_NUM_THREADS=10
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
export OMP_NUM_THREADS=11
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
export OMP_NUM_THREADS=12
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off
./build/main input/input_64.txt output_off

# File Body Count: (1024)
export OMP_NUM_THREADS=2
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
export OMP_NUM_THREADS=3
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
export OMP_NUM_THREADS=4
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
export OMP_NUM_THREADS=5
./build/main input/input_1024.txt output_off
export OMP_NUM_THREADS=6
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
export OMP_NUM_THREADS=7
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
export OMP_NUM_THREADS=8
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
export OMP_NUM_THREADS=9
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
export OMP_NUM_THREADS=10
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
export OMP_NUM_THREADS=11
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
export OMP_NUM_THREADS=12
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off
./build/main input/input_1024.txt output_off

# File Body Count: (4096)
export OMP_NUM_THREADS=2
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
export OMP_NUM_THREADS=3
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
export OMP_NUM_THREADS=4
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
export OMP_NUM_THREADS=5
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
export OMP_NUM_THREADS=6
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
export OMP_NUM_THREADS=7
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
export OMP_NUM_THREADS=8
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
export OMP_NUM_THREADS=9
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
export OMP_NUM_THREADS=10
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
export OMP_NUM_THREADS=11
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
export OMP_NUM_THREADS=12
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off
./build/main input/input_4096.txt output_off

# File Body Count: (16384)
export OMP_NUM_THREADS=2
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
export OMP_NUM_THREADS=3
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
export OMP_NUM_THREADS=4
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
export OMP_NUM_THREADS=5
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
export OMP_NUM_THREADS=6
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
export OMP_NUM_THREADS=7
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
export OMP_NUM_THREADS=8
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
export OMP_NUM_THREADS=9
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
export OMP_NUM_THREADS=10
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
export OMP_NUM_THREADS=11
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
export OMP_NUM_THREADS=12
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off
./build/main input/input_16384.txt output_off

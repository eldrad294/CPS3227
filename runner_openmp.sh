#!/bin/sh
#
# Parallel environment request. Set the number of processors here.
#$ -N openmp_run
#$ -cwd
#$ -S /bin/bash
#$ -pe smp 12

# If modules are needed, source modules environment
. /etc/profile.d/modules.sh

# Add any required modules:
module load sge shared

# Setting OpenMP Threading parameter
echo "Got $NSLOTS processor(s)."

# File Body Count: (64)
export OMP_NUM_THREADS=1
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
export OMP_NUM_THREADS=2
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
export OMP_NUM_THREADS=4
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
export OMP_NUM_THREADS=8
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
export OMP_NUM_THREADS=12
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt output_off

# File Body Count: (1024)
export OMP_NUM_THREADS=1
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
export OMP_NUM_THREADS=2
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
export OMP_NUM_THREADS=4
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
export OMP_NUM_THREADS=8
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
export OMP_NUM_THREADS=12
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt output_off

# File Body Count: (4096)
export OMP_NUM_THREADS=1
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
export OMP_NUM_THREADS=2
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
export OMP_NUM_THREADS=4
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
export OMP_NUM_THREADS=8
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
export OMP_NUM_THREADS=12
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt output_off

# File Body Count: (16384)
export OMP_NUM_THREADS=1
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
export OMP_NUM_THREADS=2
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
export OMP_NUM_THREADS=4
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
export OMP_NUM_THREADS=8
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
export OMP_NUM_THREADS=12
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off
./CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt output_off

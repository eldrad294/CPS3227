#!/bin/sh
#
# The job name
#$ -N OPENMPIx3
#$ -cwd
#$ -S /bin/bash
#$ -pe openmpi_4x1 12

# If modules are needed, source modules environment:
. /etc/profile.d/modules.sh

# Add any required modules
module load sge shared
module load gcc/4.9.4
module load openmpi/gcc/64/1.8.8

# Output the number of processors
echo "Got $NSLOTS processors(s)."

# Setting Run to single thread
export OMP_NUM_THREADS=1

# Num of Nodes(3)
# File Body Count: (64)
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt 64 output_off OPENMPIx3
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt 64 output_off OPENMPIx3
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt 64 output_off OPENMPIx3

# File Body Count: (1024)
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt 1024 output_off OPENMPIx3
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt 1024 output_off OPENMPIx3
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_1024.txt 1024 output_off OPENMPIx3

# File Body Count: (4096)
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt 4096 output_off OPENMPIx3
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt 4096 output_off OPENMPIx3
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_4096.txt 4096 output_off OPENMPIx3

# File Body Count: (16384)
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt 16384 output_off OPENMPIx3
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt 16384 output_off OPENMPIx3
mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_16384.txt 16384 output_off OPENMPIx3
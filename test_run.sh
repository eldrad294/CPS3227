#!/bin/sh
#
# The job name
#$ -N mpi_run
#$ -cwd
#$ -S /bin/bash
#$ -pe openmpi_4x1 8

. /etc/profile.d/modules.sh

module load sge shared
module load gcc/4.9.4
module load openmpi/gcc/64/1.8.8

echo "Got $NSLOTS processors(s)."

export OMP_NUM_THREADS=1

mpirun -npernode 1 CPS3227_Assignment/build/main CPS3227_Assignment/input/input_64.txt 64 output_on test_run

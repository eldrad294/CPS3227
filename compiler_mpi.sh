#! /bin/sh

# Add Modules
module add shared openmpi/gcc/64

# Compile program
mpic++ -Wall -fopenmp -std=c++11 src/*main.cpp -o build/main

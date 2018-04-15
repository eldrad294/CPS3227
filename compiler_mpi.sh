#!/bin/sh

# Compile program
mpiCC -fopenmp src/*main.cpp -o build/main

#!/bin/sh

# Compile program
mpicxx -fopenmp src/*main.cpp -o build/main

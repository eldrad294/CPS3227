/*
Main class, which contains all the logic and respective references
*/
// Library Imports
#include <omp.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "file_handler.cpp"
#include "particle.cpp"
/*
Constant Declarations
*/
#define maxIteration 1000
#define deltaT 0.01f
#define gTerm 20.f
/*
Method Definitions
*/
void PersistPositions(const std::string, std::vector<Particle>, bool);
std::vector<Particle> read_from_file(std::string);
void reportInfo(std::string, double);
void reportInfoToFile(std::string, double);
double captureTimestamp(void);
/*
Main Routine
*/
int main(int argc, char **argv)
{
    /*
    Variable Declarations
    */
    double start_time_stamp = .0;
    double end_time_stamp = .0;
    std::string enable_output = "output_off";
    FileHandler fh;
    Particle p;
    std::stringstream fileOutput;
    std::vector<Particle> bodies;
    std::string input_file_path = "../CPS3227_Assignment/input/input_64.txt";    
    std::string output_file_name = "../CPS3227_Assignment/output/nbody_";
    
    /*
    Initialize the MPI environment
    */
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD), &world_size); //Get the number of processes
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); //Get the rank of the process

    /*
    Main Logic
    */
    // Check if input file has been specified. Otherwise default to input_64.txt
    if(argc > 1)
    {
        enable_output = argv[2];
    }
    if(argc > 0)
    {
        input_file_path = argv[1];
    }

    // Opening Input File
    bodies = fh.read_from_file(input_file_path);

    // Take Initial Time Measurement
    start_time_stamp = captureTimestamp();

    for (int iteration = 0; iteration < maxIteration; ++iteration)
	{
		p.ComputeForces(bodies, gTerm);
		p.MoveBodies(bodies, deltaT);
		
        fileOutput.str(std::string());
        fileOutput << output_file_name << iteration << ".txt";
        fh.PersistPositions(fileOutput.str(), bodies, enable_output);
	}

    // Take Final Time Measurement
    end_time_stamp = captureTimestamp();
    fh.reportInfo(input_file_path, end_time_stamp - start_time_stamp); //Logs increment run.
    fh.reportInfoToFile(input_file_path, end_time_stamp - start_time_stamp); //Logs increment run. Saves to File.
    
    /*
    Destruct MPI environment
    */
    MPI_Finalize(); //Finalize the MPI Environment
    return 0;
}

double captureTimestamp(void)
{
    return omp_get_wtime();
}
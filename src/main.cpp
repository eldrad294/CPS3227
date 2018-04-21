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
std::vector<Particle> read_from_file(std::string, std::string enable_output);
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
    std::vector<Particle> local_bodies;
    std::string input_file_path = "CPS3227_Assignment/input/input_64.txt";    
    std::string output_file_name = "CPS3227_Assignment/output/nbody_";
    
    /*
    Initialize the MPI environment
    */
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); //Get the number of processes
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

    // Read input files and start recording time from master node only
    if (world_rank == 0)
    {
        // Opening Input File
        bodies = fh.read_from_file(input_file_path, enable_output);

        // Take Initial Time Measurement
        start_time_stamp = captureTimestamp();
    }

    /*
    Defining MPI datatype - *TO BE REVISED*
    */
    // Defining (self-defined) MPI position and velocity vectors
    MPI_Datatype position_obj;
    MPI_Type_vector(2, MPI_FLOAT, &position_obj);
    MPI_Type_commit(&position_obj);
    MPI_Datatype velocity_obj;
    MPI_Type_vector(2, MPI_FLOAT, &velocity_obj);
    MPI_Type_commit(&velocity_obj);

    // Defining (self-defined) MPI particle datatype
    int num_members = 3;
    int lengths[num_members] = {2,2,1};
    MPI_Aint offsets[num_members] = {offsetof(Particle,Position),offsetof(Particle,Velocity),offsetof(Particle,Mass)};
    MPI_Datatype types[num_members] = {position_obj, velocity_obj, MPI_FLOAT};
    MPI_Datatype particle_type;
    MPI_Type_struct(num_members,lengths,offsets,types,&particle_type);
    MPI_Type_commit(&particle_type);

    // Defining (self-defined) MPI body vector list of particles
    MPI_Datatype vector_obj;
    MPI_Type_vector(bodies.size(), particle, &vector_obj);
    MPI_Type_commit(&vector_obj);

    for (int iteration = 0; iteration < maxIteration; ++iteration)
	{
        //Broadcast bodies for Particle Force Computation
        MPI_Bcast(bodies,bodies.size(),vector_obj,0,MPI_COMM_WORLD);
		//Return sub vector of particles
        local_bodies = p.ComputeForces(bodies, gTerm, world_rank, world_size);
        //Gather all bodies into head node
        MPI_Gather(local_bodies, local_bodies.size(), vector_obj, &bodies, bodies.size(), vector_obj, 0, MPI_COMM_WORLD);

        //Broadcast bodies for Particle Force Computation
        MPI_Bcast(bodies,bodies.size(),vector_obj,0,MPI_COMM_WORLD);
        //Return sub vector of particles
		local_bodies = p.MoveBodies(bodies, deltaT, world_rank, world_size);
		//Gather all bodies into head node
        MPI_Gather(local_bodies, local_bodies.size(), vector_obj, &bodies, bodies.size(), vector_obj, 0, MPI_COMM_WORLD);
           
        if (world_rank == 0)
        {
            fileOutput.str(std::string());
            fileOutput << output_file_name << iteration << ".txt";
            fh.PersistPositions(fileOutput.str(), bodies, enable_output);
        }
	}

    // Finish recording time from master node only
    if (world_rank == 0)
    {
        // Take Final Time Measurement
        end_time_stamp = captureTimestamp();

        fh.reportInfo(input_file_path, end_time_stamp - start_time_stamp); //Logs increment run.
        //fh.reportInfoToFile(input_file_path, end_time_stamp - start_time_stamp); //Logs increment run. Saves to File.
    }
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

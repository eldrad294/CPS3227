/*
Main class, which contains all the logic and respective references
*/
// Library Imports
#include <omp.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "file_handler.cpp"
#include "particle.cpp"
#include <mpi.h>
#include <stdio.h>
/*
Constant Declarations
*/
#define maxIteration 1000
#define deltaT 0.01f
#define gTerm 20.f
/*
Method Prototypes
*/
void PersistPositions(const std::string, std::vector<Particle>, bool);
void read_from_file(std::string, std::string enable_output, std::vector<Particle>);
void reportInfo(std::string, double);
void reportInfoToFile(std::string, double);
double captureTimestamp(void);
/*
Main Routine
*/
int main(int argc, char **argv)
{    
    std::cout << "Initializing MPI_Environment..\n";
    /*
    Initialize the MPI environment
    */
    MPI_Init(&argc, &argv);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); //Get the number of processes
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); //Get the rank of the process
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
    std::string execution_identifier = "test_run";
    int body_size = 0;
    /*
    Defining MPI datatype
    */
    //GS begin
    MPI_Datatype particle_type;
    MPI_Type_contiguous(5,MPI_FLOAT,&particle_type);
    MPI_Type_commit(&particle_type);
    //GS else
    // int block_count = 2;
    // int block_length = 1;
    // int stride = 1;
    // MPI_Datatype position_obj;
    // MPI_Type_vector(block_count,block_length,stride,MPI_FLOAT, &position_obj);
    // MPI_Type_commit(&position_obj);
    // MPI_Datatype velocity_obj;
    // MPI_Type_vector(block_count,block_length,stride,MPI_FLOAT, &velocity_obj);
    // MPI_Type_commit(&velocity_obj);
    // // Defining (self-defined) MPI Particle datatype
    // int num_members = 3;
    // int lengths[] = {1,1,1};
    // MPI_Aint lb;
    // MPI_Aint extentFloat;
    // MPI_Type_get_extent(MPI_FLOAT, &lb, &extentFloat);
    // MPI_Aint offsets[] = {0, 2*extentFloat, 4*extentFloat};
    // MPI_Datatype types[] = {position_obj, velocity_obj, MPI_FLOAT};
    // MPI_Datatype particle_type;
    // MPI_Type_create_struct(num_members,lengths,offsets,types,&particle_type);
    // MPI_Type_commit(&particle_type);
    //GS end
    /*
    Main Logic
    */
    if (world_rank == 0)
    {
        // Check if input file has been specified. Otherwise default to input_64.txt
        if(argc > 3)
        {
            execution_identifier = argv[3]; //Denotes the type of execution - useful to interpret the type of run
        }
        if(argc > 2)
        {
            enable_output = argv[2]; //Parameter which disables/enables script output
        }
        if(argc > 1)
        {
            input_file_path = argv[1]; //Input file-path
        }

        // Opening Input File
        fh.read_from_file(input_file_path, enable_output, bodies);

        // Take Initial Time Measurement
        start_time_stamp = captureTimestamp();

        // Assign variable with total body size so as to inform all slave nodes
        body_size = bodies.size();
    }

    // Broadcast body size
    MPI_Bcast(&body_size,1,MPI_INT,0,MPI_COMM_WORLD);

    //Synchronize step
    MPI_Barrier(MPI_COMM_WORLD);

    // Reserve memory for bodies on slave nodes
    if (world_rank != 0)
    {
        bodies.resize(body_size);
    }

    for (int iteration = 0; iteration < maxIteration; ++iteration)
    {   
        //Synchronize step
        MPI_Barrier(MPI_COMM_WORLD);
        
        //Broadcast bodies for Particle Force Computation
        MPI_Bcast(&bodies.front(),bodies.size(),particle_type,0,MPI_COMM_WORLD);
        
        //Return sub vector of particles
        p.ComputeForces(bodies, local_bodies, gTerm, world_rank, world_size);

        //Gather all bodies into head node
        MPI_Gather(&local_bodies.front(), local_bodies.size(), particle_type, &bodies.front(), bodies.size(), particle_type, 0, MPI_COMM_WORLD);
        
        //Synchronize step
        MPI_Barrier(MPI_COMM_WORLD);
        
        //Broadcast bodies for Particle Force Computation
        MPI_Bcast(&bodies.front(),bodies.size(),particle_type,0,MPI_COMM_WORLD);

        //Return sub vector of particles
	    p.MoveBodies(bodies, local_bodies, deltaT, world_rank, world_size);	

        //Gather all bodies into head node
        MPI_Gather(&local_bodies.front(), local_bodies.size(), particle_type, &bodies.front(), bodies.size(),  particle_type, 0, MPI_COMM_WORLD);

        //Synchronize step
        MPI_Barrier(MPI_COMM_WORLD);

        //Master node persist file output
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

        fh.reportInfo(input_file_path, end_time_stamp - start_time_stamp, execution_identifier); //Logs increment run.
        //fh.reportInfoToFile(input_file_path, end_time_stamp - start_time_stamp, execution_identifier); //Logs increment run. Saves to File.
    }
    /*
    Destruct MPI environment
    */
    //MPI_Type_free(&position_obj);
    //MPI_Type_free(&velocity_obj);
    MPI_Type_free(&particle_type);
    MPI_Finalize(); //Finalize the MPI Environment
    //std::cout << "Debug 8 Rank: " << world_rank << "\n";    
    return 0;
}

double captureTimestamp(void)
{
    return omp_get_wtime();
}

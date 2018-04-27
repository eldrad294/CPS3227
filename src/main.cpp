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
    int body_size = 0;
        
    /*
    Initialize the MPI environment
    */
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); //Get the number of processes
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); //Get the rank of the process

    /*
    Defining MPI datatype
    */
    // MPI_Datatype particle_type;
    // MPI_Type_contiguous(10,MPI_FLOAT,&particle_type);
    // MPI_Type_commit(&particle_type);
    // Defining (self-defined) MPI Position/Velocity datatypes
    MPI_Datatype position_obj;
    MPI_Type_vector(2,1,1,MPI_FLOAT, &position_obj);
    MPI_Type_commit(&position_obj);
    MPI_Datatype velocity_obj;
    MPI_Type_vector(2,1,1,MPI_FLOAT, &velocity_obj);
    MPI_Type_commit(&velocity_obj);

    // Defining (self-defined) MPI particle datatype
    int num_members = 3;
    int lengths[] = {1,1,1};
    MPI_Aint lb;
    MPI_Aint extentFloat;
    MPI_Type_get_extent(MPI_FLOAT, &lb, &extentFloat);
    //MPI_Aint offsets[] = {2,2,2};
    MPI_Aint offsets[] = {0, 2*extentFloat, 4*extentFloat};
    MPI_Datatype types[] = {position_obj, velocity_obj, MPI_FLOAT};
    MPI_Datatype particle_type;
    MPI_Type_create_struct(num_members,lengths,offsets,types,&particle_type);
    MPI_Type_commit(&particle_type);
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
        fh.read_from_file(input_file_path, enable_output, bodies);

        // Take Initial Time Measurement
        start_time_stamp = captureTimestamp();

        // Assign variable with total body size so as to inform all slave nodes
        body_size = bodies.size();
    }

    // Broadcast body size
    MPI_Bcast(&body_size,1,MPI_INT,0,MPI_COMM_WORLD);

    // Reserve memory for bodies on slave nodes
    if (world_rank != 0)
    {
        bodies.resize(body_size);
    }

    std::cout << "Debug 1 Rank: " << world_rank << "\n";
    for (int iteration = 0; iteration < maxIteration; ++iteration)
    {   
        //Synchronize step
        MPI_Barrier(MPI_COMM_WORLD);
        std::cout << "Debug 2 Rank: " << world_rank << " Position: " << bodies[0].Position[0] << " Iteration: " << iteration << "\n";
        
        //Broadcast bodies for Particle Force Computation
        MPI_Bcast(&bodies.front(),bodies.size(),particle_type,0,MPI_COMM_WORLD);
        std::cout << "Debug 3 Rank: " << world_rank << " Position: " << bodies[0].Position[0] << " Iteration: " << iteration << "\n";
        
        //Return sub vector of particles
        p.ComputeForces(bodies, local_bodies, gTerm, world_rank, world_size);

        std::cout << "Debug 4 Rank: " << world_rank << " Bodies Size: " << bodies.size() << " Local Bodies Size: " << local_bodies.size() << " \n";
        //Gather all bodies into head node
        MPI_Gather(&local_bodies.front(), local_bodies.size(), particle_type, &bodies.front(), bodies.size(), particle_type, 0, MPI_COMM_WORLD);
        
        std::cout << "Debug 5 Rank: " << world_rank << "\n";
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

        fh.reportInfo(input_file_path, end_time_stamp - start_time_stamp); //Logs increment run.
        //fh.reportInfoToFile(input_file_path, end_time_stamp - start_time_stamp); //Logs increment run. Saves to File.
    }
    /*
    Destruct MPI environment
    */
    std::cout << "Debug 6 Rank: " << world_rank << "\n";
    MPI_Type_free(&position_obj);
    MPI_Type_free(&velocity_obj);
    MPI_Type_free(&particle_type);
    std::cout << "Debug 7 Rank: " << world_rank << "\n";
    MPI_Finalize(); //Finalize the MPI Environment
    std::cout << "Debug 8 Rank: " << world_rank << "\n";
    
    return 0;
}

double captureTimestamp(void)
{
    return omp_get_wtime();
}

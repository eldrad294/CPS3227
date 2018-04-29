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
// void PersistPositions(const std::string, int, float, float, float, float);
// void read_from_file(std::string, std::string, float, float, float);
// void reportInfo(std::string, double);
// void reportInfoToFile(std::string, double);
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
    std::string input_file_path = "CPS3227_Assignment/input/input_64.txt";    
    std::string output_file_name = "CPS3227_Assignment/output/nbody_";
    std::string execution_identifier = "test_run";
    int body_count = 64;

    /*
    Accept Input CMD Line Parameters
    */
    if(argc > 4)
    {
        execution_identifier = argv[4]; //Denotes the type of execution - useful to interpret the type of run
    }
    if(argc > 3)
    {
        enable_output = argv[3]; //Parameter which disables/enables script output
    }
    if(argc > 2)
    {
        body_count = std::atoi(argv[2]); //Parameter which dictates body count
    }
    if(argc > 1)
    {
        input_file_path = argv[1]; //Check if input file has been specified. Otherwise default to input_64.txt
    }

    // Memory allocation for mass, velocity, particle structures
    float *mass = new float[body_count];
    float *velocity_0 = new float[body_count];
    float *velocity_1 = new float[body_count];
    float *position_0 = new float[body_count];
    float *position_1 = new float[body_count];
    float local_velocity_0[body_count/world_size];
    float local_velocity_1[body_count/world_size];
    float local_position_0[body_count/world_size];
    float local_position_1[body_count/world_size];
    // Initialize local structures
    for (int i=0;i<body_count/world_size;i++){
        velocity_0[i] = 0;
        velocity_1[i] = 0;
        position_0[i] = 0;
        position_1[i] = 0;
        local_velocity_0[i] = 0;
        local_velocity_1[i] = 0;
        local_position_0[i] = 0;
        local_position_1[i] = 0;
    }

    if (world_rank == 0)
    {
        // Opening Input File
        fh.read_from_file(input_file_path, enable_output, mass, position_0, position_1);
    }

    /*
    Main Logic
    */
    //Broadcast particle (unchanging) masses to all slaves - Done once at the beginning for efficiency
    MPI_Bcast(mass,body_count,MPI_FLOAT,0,MPI_COMM_WORLD);

    //std::cout << "World_Rank: " << world_rank << " Mass10: " << mass[10] << "\n";

    if (world_rank == 0)
    {
        // Take Initial Time Measurement
        start_time_stamp = captureTimestamp();
    }

    for (short iteration = 0; iteration < maxIteration; ++iteration)
    {   
        //Synchronize step
        MPI_Barrier(MPI_COMM_WORLD);
        
        //Broadcast Particle Positions
        MPI_Bcast(position_0,body_count,MPI_FLOAT,0,MPI_COMM_WORLD);
        MPI_Bcast(position_1,body_count,MPI_FLOAT,0,MPI_COMM_WORLD);
        //std::cout << "World_Rank: " << world_rank << " position_1(63): " << position_1[63] << "\n";

        //Compute Particle Velocities
        p.ComputeForces(body_count, mass, velocity_0, velocity_1, position_0, position_1, local_velocity_0, local_velocity_1, gTerm, world_rank, world_size);
        
        //Synchronize step
        MPI_Barrier(MPI_COMM_WORLD);
        //std::cout <<"world_rank:"<<world_rank<< " local_velocity_0:"<<local_velocity_0[0]<<"\n";        
        
        //Gather all updated velocities into head node
        MPI_Gather(&local_velocity_0, body_count / world_size, MPI_FLOAT, velocity_0, body_count / world_size, MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Gather(&local_velocity_1, body_count / world_size, MPI_FLOAT, velocity_1, body_count / world_size, MPI_FLOAT, 0, MPI_COMM_WORLD);
        
        //Synchronize step
        MPI_Barrier(MPI_COMM_WORLD);
        std::cout  << "World_Rank: " << world_rank << " Velocity_0: " << position_0[36] << "\n";
        //std::cout  << "World_Rank: " << world_rank << " local_velocity_0: " << local_velocity_0[0] << "\n";
        
        //Broadcast Particle Velocity
        MPI_Bcast(velocity_0,body_count,MPI_FLOAT,0,MPI_COMM_WORLD);
        MPI_Bcast(velocity_1,body_count,MPI_FLOAT,0,MPI_COMM_WORLD);

        //Compute Particle Positions
	    p.MoveBodies(body_count, mass, velocity_0, velocity_1, local_position_0, local_position_1, deltaT, world_rank, world_size);	

        //Synchronize step
        MPI_Barrier(MPI_COMM_WORLD);

        //Gather all updated positions into head node
        MPI_Gather(&local_position_0, body_count / world_size, MPI_FLOAT, position_0, body_count / world_size, MPI_FLOAT, 0, MPI_COMM_WORLD);
        MPI_Gather(&local_position_1, body_count / world_size, MPI_FLOAT, position_1, body_count / world_size, MPI_FLOAT, 0, MPI_COMM_WORLD);

        //Synchronize step
        MPI_Barrier(MPI_COMM_WORLD);
        //std::cout << "Rank:" << world_rank << " position_0:" << position_0[0] << "\n";
        //Master node persist file output
        if (world_rank == 0)
        {
	        fileOutput.str(std::string());
            fileOutput << output_file_name << iteration << ".txt";
            fh.PersistPositions(fileOutput.str(), body_count, mass, position_0, position_1, enable_output);
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

    // Memory Cleanup
    delete[] mass;
    delete[] velocity_0;
    delete[] velocity_1;
    delete[] position_0;
    delete[] position_1;

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

/*
Main class, which contains all the logic
*/
// Library Imports
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "file_handler.cpp"
#include "particle.cpp"
/*
Constant Declarations
*/
const int maxIteration = 1000;
const float deltaT = 0.01f;
const float gTerm = 20.f;
/*
Method Definitions
*/
void PersistPositions(const std::string &p_strFilename, std::vector<Particle> &p_bodies);
std::vector<Particle> read_from_file(std::string);
void getInfo(void);
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
    FileHandler fh;
    Particle p;
    std::stringstream fileOutput;
    std::vector<Particle> bodies;
    std::string input_file_path = "../CPS3227_Assignment/input/input_64.txt";    
    std::string output_file_name = "../CPS3227_Assignment/output/nbody_";
    /*
    Main Logic
    */
    getInfo(); //RLogs particular data for this specific run, concerning the system

    // Check if input file has been specified. Otherwise default to input_64.txt
    if(argc > 1)
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
		fh.PersistPositions(fileOutput.str(), bodies);
	}

    // Take Final Time Measurement
    end_time_stamp = captureTimestamp();
    std::cout << "Total Elapsed Time: " << end_time_stamp - start_time_stamp << " seconds\n";
    return 0;
}

double captureTimestamp(void)
{
    return omp_get_wtime();
}

void getInfo(void)
{
    std::cout << "Clock Frequency\n";
    std::cout << "wtime = " << omp_get_wtime() << "\n";
    std::cout << "Number of processors = " << omp_get_num_procs() << "\n";
    std::cout << "wtick(Clock Frequency) = " << omp_get_wtick() << "\n";
    std::cout << "1/wtick = " << 1.0/omp_get_wtick() << "\n\n";
}
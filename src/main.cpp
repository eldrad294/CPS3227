/*
Main class, which contains all the logic
*/
// Library Imports
#include <iostream>
#include <sstream>
#include "file_handler.cpp"
#include "particle.cpp"
/*
Constant Declarations
*/
const std::string input_file_path = "/home/gabriel/HighPerformanceComputing/CPS3227_Assignment/input/input_64.txt";    
const int maxIteration = 1000;
const float deltaT = 0.01f;
const float gTerm = 20.f;
/*
Method Definitions
*/
void PersistPositions(const std::string &p_strFilename, std::vector<Particle> &p_bodies);
std::vector<Particle> read_from_file(std::string);
/*
Main Routine
*/
int main(int argc, char **argv)
{
    /*
    Variable Declarations
    */
    FileHandler fh;
    Particle p;
    std::stringstream fileOutput;
    std::vector<Particle> bodies;
    std::string output_file_name = "../CPS3227_Assignment/output/nbody_";
    /*
    Main Logic
    */
    // Opening Input File
    bodies = fh.read_from_file(input_file_path);

    for (int iteration = 0; iteration < maxIteration; ++iteration)
	{
		p.ComputeForces(bodies, gTerm);
		p.MoveBodies(bodies, deltaT);
		
		fileOutput.str(std::string());
		fileOutput << output_file_name << iteration << ".txt";
		fh.PersistPositions(fileOutput.str(), bodies);
	}
    return 0;
}
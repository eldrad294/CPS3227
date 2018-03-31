/*
Main class, which contains all the logic
*/
// Library Imports
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "file_handler.cpp"
#include "vector2.h"
/*
Constant Declarations
*/
const std::string input_file_path = "/home/gabriel/HighPerformanceComputing/CPS3227_Assignment/input/input_64.txt";    
const int fieldWidth = 1000;
const int fieldHalfWidth = fieldWidth >> 1;
const int fieldHeight = 1000;
const int fieldHalfHeight = fieldHeight >> 1;
const float minBodyMass = 2.5f;
const float maxBodyMassVariance = 5.f;
/*
 * Particle structure
 */
struct Particle
{
	Vector2 Position;
	Vector2 Velocity;
	float	Mass;
	
	Particle(void) 
		: Position( ((float)rand()) / RAND_MAX * fieldWidth - fieldHalfWidth,
					((float)rand()) / RAND_MAX * fieldHeight - fieldHalfHeight)
		, Velocity( 0.f, 0.f )
		, Mass ( ((float)rand()) / RAND_MAX * maxBodyMassVariance + minBodyMass )
	{ }
};
/*
Method Definitions
*/
int save_to_file(std::string);
int read_from_file(std::string);
/*
Main Routine
*/
int main(int argc, char **argv)
{
    /*
    Variable Declarations
    */
    /*
    Object Declarations
    */
    FileHandler fh;

    /*
    Main Logic
    */
    // Opening Input File
    if(fh.read_from_file(input_file_path) != 0)
    {
        std::cout << "A problem occurred during opening of the input file!";
        return 1;
    }
    return 0;
}
/*
Main class, which contains all the logic
*/
// Library Imports
#include <iostream>
#include "file_handler.cpp"
/*
Constant Declarations
*/
const std::string input_file_path = "/home/gabriel/HighPerformanceComputing/CPS3227_Assignment/input/input_64.txt";    
/*
Method Definitions
*/
short save_to_file(std::string);
short read_from_file(std::string);
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
/*
Main class, which contains all the logic
*/
// Library Imports
#include <iostream>
// External File Imports
#include "file_handler.cpp"
#include "constants.cpp"
using namespace std;

int main(int argc, char **argv)
{
    /*
    Variable Declarations
    */
    Constants c;
    FileHandler fh;

    /*
    Main Logic
    */
    // Opening Input File
    if(fh.read_from_file(c.input_file_path) != 0)
    {
        cout << "A problem occurred during opening of the input file!";
        return 1;
    }
    return 0;
}
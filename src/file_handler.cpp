// Library Imports
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "particle.cpp"

class FileHandler{
    public:
        short save_to_file(std::string file_path)
        {
            return 0;
        }

        /*
        Reads from files with name:

        "input_n.txt"

        File format eg:

        M,X,Y
        6.27803, -368.462, -499.992
        3.5948, 32.7673, -41.3501
        5.89648, 178.865, -452.955

        Returns 0 on successfull open, otherwise returns 1
        */
        short read_from_file(std::string file_path)
        {
            std::string line;
            std::string temp_line;
            std::ifstream myfile;
            std::string temp_mass;
            std::string temp_X;
            std::string temp_Y;
            char delimeter = ',';
            short comma_counter;
            float mass;
            float X;
            float Y;

            /*
            Opens input file at specified path 
            (Note: C++11 file.open() requires an input parameter of type char) 
            */
            myfile.open(file_path.c_str());
            if(myfile.is_open())
            {
                //Fetches content from the file line by line
                while(getline(myfile,line))
                {
                    temp_mass = "";
                    temp_X = "";
                    temp_Y = "";
                    comma_counter = 0;
                    
                    // Parse each line by stripping away whitespace, and splitting values by comma delimeter
                    for (unsigned i=0;i<line.length();i++)
                    {
                        if (line[i] == delimeter)
                            comma_counter += 1;
                        else if(line[i] != ' ' and comma_counter == 0)
                            temp_mass += line[i];
                        else if (line[i] != ' ' and comma_counter == 1)
                            temp_X += line[i];
                        else if (line[i] != ' ' and comma_counter == 2)
                            temp_Y += line[i];
                    }

                    // Type Conversion from string to float values
                    mass = atof(temp_mass.c_str());
                    X = atof(temp_X.c_str());
                    Y = atof(temp_Y.c_str());
                    // std::cout << mass << "\n";
                    // std::cout << X << "\n";
                    // std::cout << Y << "\n";
                    // std::cout << "--------------\n";
                }
                myfile.close();
            }else
            {
                std::cout << "Unable to open file at location: [" << file_path << "]";
                return 1;   
            }
            
            return 0;
        }
};
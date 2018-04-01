// Library Imports
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "particle.cpp"

class FileHandler{
    public:
        /*
        * Commit particle masses and positions to file in CSV format
        */
        void PersistPositions(const std::string &p_strFilename, std::vector<Particle> &p_bodies)
        {
            std::cout << "Writing to file: " << p_strFilename << std::endl;
            
            std::ofstream output(p_strFilename.c_str());
            
            if (output.is_open())
            {	
                for (unsigned j = 0; j < p_bodies.size(); j++)
                {
                    output << 	p_bodies[j].Mass << ", " <<
                        p_bodies[j].Position.Element[0] << ", " <<
                        p_bodies[j].Position.Element[1] << std::endl;
                }
                
                output.close();
            }
            else
                std::cerr << "Unable to persist data to file:" << p_strFilename << std::endl;

        }

        /*
        Reads from files with name:

        "input_n.txt"

        File format eg:

        M,X,Y
        6.27803, -368.462, -499.992
        3.5948, 32.7673, -41.3501
        5.89648, 178.865, -452.955

        Returns a vector list with all loaded particles from file
        */
        std::vector<Particle> read_from_file(std::string file_path)
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
            std::vector<Particle> bodies;

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
                    bodies.push_back(Particle(mass, X, Y));
                    // std::cout << mass << "\n";
                    // std::cout << X << "\n";
                    // std::cout << Y << "\n";
                    // std::cout << "--------------\n";
                }
                myfile.close();
                std::cout << "Files Loaded Successfully\n";
            }else
            {
                std::cerr << "Unable to open file at location: [" << file_path << "]\n";
                exit(1);   
            }
            
            return bodies;
        }
};
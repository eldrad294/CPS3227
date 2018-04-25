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
        void PersistPositions(const std::string &p_strFilename, std::vector<Particle> &p_bodies, std::string enable_output)
        {
            if (enable_output == "output_on")
            {
                std::cout << "Writing to file: " << p_strFilename << std::endl;
            }
                        
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
        void read_from_file(std::string file_path, std::string enable_output, std::vector<Particle> &p_bodies)
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
                    p_bodies.push_back(Particle(mass, X, Y));
                    // std::cout << mass << "\n";
                    // std::cout << X << "\n";
                    // std::cout << Y << "\n";
                    // std::cout << "--------------\n";
                }
                myfile.close();
                if (enable_output == "output_on")
                {
                    std::cout << "Files Loaded Successfully\n";
                }
            }else
            {
                std::cerr << "Unable to open file at location: [" << file_path << "]\n";
                exit(1);   
            }
        }

        /*
        * Writes run details to console out
        */
        void reportInfo(std::string input_file_path, double tot_time)
        {
            std::cout << "Input File: " << input_file_path << "\n";
            std::cout << "wtime = " << omp_get_wtime() << "\n";
            std::cout << "Number of processors = " << omp_get_num_procs() << "\n";
            std::cout << "Number of threads = " << omp_get_max_threads() << "\n";
            std::cout << "Clock Frequency = " << omp_get_wtick() << "\n";
            std::cout << "1/wtick = " << 1.0/omp_get_wtick() << "\n\n";
            std::cout << "Total Elapsed Time: " << tot_time << " seconds\n--------------------------------------\n";
        }

        /*
        * Write run details to file
        */
        void reportInfoToFile(std::string input_file_path, double tot_time)
        {
            /*
            Opens input file at specified path 
            (Note: C++11 file.open() requires an input parameter of type char) 
            */
            std::string strFilename = "../CPS3227_Assignment/report/report.txt";
            std::ofstream output(strFilename.c_str(), std::ios_base::app); //Open File in Append mode
            if (output.is_open())
            {	
                output << "Input File: " << input_file_path << "\n";
                output << "wtime = " << omp_get_wtime() << "\n";
                output << "Number of processors = " << omp_get_num_procs() << "\n";
                output << "Number of threads = " << omp_get_max_threads() << "\n";
                output << "Clock Frequency = " << omp_get_wtick() << "\n";
                output << "1/wtick = " << 1.0/omp_get_wtick() << "\n\n";
                output << "Total Elapsed Time: " << tot_time << " seconds\n--------------------------------------\n";
                
                output.close();
            }
            else
                std::cerr << "Unable to persist data to file:" << strFilename << std::endl;
        }
};

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
        void PersistPositions(const std::string &p_strFilename, int body_count, float *mass, float *p_position_0, float *p_position_1, std::string enable_output)
        {
            if (enable_output == "output_on")
            {
                std::cout << "Writing to file: " << p_strFilename << std::endl;
            }           
            std::ofstream output(p_strFilename.c_str());
            if (output.is_open())
            {	
                for (int j = 0; j < body_count; j++)
                {
                    output << 	mass[j] << ", " <<
                        p_position_0[j] << ", " <<
                        p_position_1[j] << std::endl;
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
        void read_from_file(std::string file_path, std::string enable_output, float *p_mass, float *p_position_0, float *p_position_1)
        {
            std::string line;
            std::string temp_line;
            std::ifstream myfile;
            std::string temp_mass;
            std::string temp_X;
            std::string temp_Y;
            char delimeter = ',';
            short comma_counter;
            int iteration_counter = 0;

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
                    p_mass[iteration_counter] = atof(temp_mass.c_str());
                    p_position_0[iteration_counter] = atof(temp_X.c_str());
                    p_position_1[iteration_counter] = atof(temp_Y.c_str());

                    iteration_counter++;
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
        void reportInfo(std::string input_file_path, double tot_time, std::string execution_identifier)
        {
            std::cout << "Execution Type: " << execution_identifier << "\n";
            std::cout << "Input File: " << input_file_path << "\n";
            std::cout << "wtime = " << omp_get_wtime() << "\n";
            std::cout << "Number of processors = " << omp_get_num_procs() << "\n";
            std::cout << "Number of threads = " << omp_get_max_threads() << "\n";
            std::cout << "Clock Frequency = " << omp_get_wtick() << "\n";
            std::cout << "1/wtick = " << 1.0/omp_get_wtick() << "\n";
            std::cout << "Total Elapsed Time: " << tot_time << " seconds\n--------------------------------------\n";
        }

        /*
        * Write run details to file
        */
        void reportInfoToFile(std::string input_file_path, double tot_time, std::string execution_identifier)
        {
            /*
            Opens input file at specified path 
            (Note: C++11 file.open() requires an input parameter of type char) 
            */
            std::string strFilename = "../CPS3227_Assignment/report/report.txt";
            std::ofstream output(strFilename.c_str(), std::ios_base::app); //Open File in Append mode
            if (output.is_open())
            {	
                output << "Execution Type: " << execution_identifier << "\n";
                output << "Input File: " << input_file_path << "\n";
                output << "wtime = " << omp_get_wtime() << "\n";
                output << "Number of processors = " << omp_get_num_procs() << "\n";
                output << "Number of threads = " << omp_get_max_threads() << "\n";
                output << "Clock Frequency = " << omp_get_wtick() << "\n";
                output << "1/wtick = " << 1.0/omp_get_wtick() << "\n";
                output << "Total Elapsed Time: " << tot_time << " seconds\n--------------------------------------\n";
                
                output.close();
            }
            else
                std::cerr << "Unable to persist data to file:" << strFilename << std::endl;
        }
};

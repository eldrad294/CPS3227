#include <string>
#include <fstream>
#include <iostream>

class FileHandler{
    public:
        int save_to_file(std::string file_path)
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
        int read_from_file(std::string file_path)
        {
            std::string line;
            std::ifstream myfile;
            char delimeter = ',';

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
                    std::cout << line << "\n";
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
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class FileHandler{
    public:
        int save_to_file(string);
        int read_from_file(string);
};

int save_to_file(string file_path)
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
int read_from_file(string file_path)
{
    string line;
    ifstream myfile (file_path);
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            cout << line << "\n";
        }
        myfile.close();
    }else
    {
        cout << "Unable to open file at location: [" << file_path << "]";
        return 1;   
    }
    
    return 0;
}
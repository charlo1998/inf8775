#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <chrono>
#include <unordered_map>
#include "algo.hpp"
using namespace std;

int main(int argc, char **argv)
{

    int n_circ;
    string filename;
    bool P_flag = false;
    // command line arguments
    for (int i = 0; i < argc - 1; i++)
    {

        if (string(argv[i]) == "-e")
        {
            filename = string(argv[i + 1]);
        }
        if (string(argv[i]) == "-c")
        {
			n_circ = int(argv[i + 1]);
        }
        if (string(argv[i]) == "-P")
        {
            P_flag = true;
        }
    }

    if (!p_flag)
    {
        cout << "lecture du fichier '" << filename << '\'' << endl;
    }
    // lecture du fichier
    ifstream input;
    input.open(filename);
    if (!input)
    {
        cout << "Can't find source file" << endl;
        return -1;
    }
	//todo

   
    int64_t temps;
    
    if (p_flag)
    {
        // to do
    }

    cout << "temps ecoulé : "<<temps << " ns" << endl;

}

#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <chrono>
#include <unordered_map>
#include "algo.hpp"
#include "utils.hpp"
#include "circonscription.hpp"
using namespace std;
int main(int argc, char **argv)
{

    int n_circ;
    string filename;
    bool p_flag = false;
    // command line arguments
    for (int i = 0; i < argc - 1; i++)
    {

        if (string(argv[i]) == "-e")
        {
            filename = string(argv[i + 1]);
        }
        if (string(argv[i]) == "-c")
        {
			n_circ = stoi(argv[i + 1]);
        }
        if (string(argv[i]) == "-P")
        {
            p_flag = true;
        }
    }

    if (!p_flag)
    {
        cout << "lecture du fichier '" << filename << '\'' << endl;
    }
    // lecture du fichier

    auto municipalities = read_input_data(filename);
	//todo

    // for (auto& mun : municipalities){
    //  cout << mun <<endl;
    // }


    std::vector<Circonscription> Solution;
    for(int i = 0; i<3; i++){
        Circonscription circ;

        for(int j =0; j<5; j++){
            cout << 5*i+j;
            cout << mun << endl;
            circ.addMunicipalite(municipalities[5*i+j],5);   
        }
        Solution.push_back(circ);
        
    }
    
    printSolution(Solution);

    if (p_flag)
    {
        cout << "not implemented yet..."<<endl;
        // to do
    }
}

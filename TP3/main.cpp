#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <chrono>
#include <unordered_map>
#include "circonscription.hpp"
#include "heuristique.hpp"
#include "municipalite.hpp"
using namespace std;
vector<Municipalite> read_input_data(const std::string& filename);
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


    std::vector<Circonscription> solution;
    for(int i = 0; i<3; i++){
        Circonscription circ;

        for(int j =0; j<5; j++){
            circ.addMunicipalite(municipalities[5*i+j], 5);
        }
        solution.push_back(circ);
        
    }


    

    if (p_flag)
    {
        //print the solution in the good format
        cout << endl;
        for(int i = 0; i<solution.size(); i++)
        {
            solution[i].print();
        }
    }
    else 
    {
        int count = 0;
        for(int i = 0; i<solution.size(); i++)
        {
            cout << solution[i].getVotes();
            cout << endl;
            count += solution[i].isWinning();
        }
        cout << count << endl;
    }

    
}
std::vector<Municipalite> read_input_data(const std::string& filename){
    std::vector<Municipalite> municipalities;
    std::ifstream input;
    input.open(filename);
    if (!input)
    {
        std::cout << "Can't find source file: \'" << filename << "'" << std::endl;
        return municipalities;
    }
    int width, height;
    input >> width >> height;
    for(int y =0; y<height;y++){
        for(int x=0; x<width ; ++x){
            int pop;
            input >> pop;
            Municipalite mun ={x,y,pop};
            municipalities.push_back(mun);
        }
    }
    return municipalities;
}
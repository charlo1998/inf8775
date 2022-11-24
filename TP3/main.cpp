#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>
#include <chrono>
#include <unordered_map>
#include "circonscription.hpp"
#include "heuristique.hpp"
#include "municipalite.hpp"
#include "dpr.hpp"
using namespace std;
vector<Municipalite> read_input_data(const std::string& filename);
int main(int argc, char **argv)
{

    int n_circ;
    int width, height;
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
        std::cout << "lecture du fichier '" << filename << '\'' << endl;
    }
    // lecture du fichier

    auto municipalities = read_input_data(filename);
    int nb_circ =5;

    std::vector<Circonscription> solution = brute(municipalities, nb_circ);

    
}
std::vector<Municipalite> read_input_data(const std::string& filename){
    std::vector<Municipalite> municipalities;
    std::ifstream input;
    input.open(filename);
    int width,height;
    if (!input)
    {
        std::cout << "Can't find source file: \'" << filename << "'" << std::endl;
        return municipalities;
    }
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
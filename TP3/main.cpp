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
using namespace std;
vector<Municipalite> read_input_data(const std::string& filename, int &width, int &height);
int main(int argc, char **argv)
{

    int n_circ;
    int width, height;
    string filename;
    bool p_flag = false;
    // command line arguments
    for (int i = 0; i < argc; i++)
    {

        if (string(argv[i]) == "-e")
        {
            filename = string(argv[i + 1]);
        }
        if (string(argv[i]) == "-c")
        {
			n_circ = stoi(argv[i + 1]);
        }
        if (string(argv[i]) == "-p")
        {
            p_flag = true;
        }
    }


    auto municipalities = read_input_data(filename, width, height);
    int dist_max = ceil(municipalities.size()/(2.0f*float(n_circ)));

    //cout << "width: " << width << " height: " << height << " dist_max: " << dist_max << endl;

    auto start = chrono::high_resolution_clock::now();

    std::vector<Circonscription> solution;
    solution = generate_initial_solution(municipalities,  n_circ, dist_max, width, height);

    int i =0;
    while(i<10000){
        heuristique(municipalities, solution, n_circ, dist_max, p_flag,  width, height);
        i++;
    }

    auto finish = chrono::high_resolution_clock::now();
    int64_t t= chrono::duration_cast<chrono::nanoseconds>(finish-start).count();

    //cout << "program took: " << t/1000000.0f << " ms" << endl;
    

    

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
            //cout << solution[i].getVotes();
            //cout << endl;
            count += solution[i].isWinning();
        }
        cout << count << endl;
    }

    
}
std::vector<Municipalite> read_input_data(const std::string& filename, int &width, int &height){
    std::vector<Municipalite> municipalities;
    std::ifstream input;
    input.open(filename);
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
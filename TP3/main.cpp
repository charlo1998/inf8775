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
vector<Municipalite> read_input_data(const std::string &filename, int &width, int &height);
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
    int dist_max = ceil(municipalities.size() / (2.0f * float(n_circ)));
if(!p_flag)
    {cout << "width: " << width << " height: " << height << " dist_max: " << dist_max << endl;}

    // auto startinitial = chrono::high_resolution_clock::now();

    std::vector<Circonscription> solution;
    solution = generate_initial_solution(municipalities, n_circ, dist_max, width, height);
    if (p_flag){
        for(auto &circ : solution){
            circ.print();
        }
    }
    // auto finishinitial = chrono::high_resolution_clock::now();
    // int64_t t= chrono::duration_cast<chrono::nanoseconds>(finishinitial-startinitial).count();

    int i = 0;
    int max_iterations = 10'000'000;
    float temperature = 100.0f;
    while (i<max_iterations)
    {
        heuristique(municipalities, solution, n_circ, dist_max, p_flag, width, height, temperature);
        i++;
    }

    // auto finishiterations = chrono::high_resolution_clock::now();
    // int64_t t2= chrono::duration_cast<chrono::nanoseconds>(finishiterations-finishinitial).count();

    // cout << "generating initial solution took: " << t/1000000000.0f << " s" << endl;
    // cout << "iterating took: " << t2/1000000.0f/max_iterations << " ms per iteration for a total of " << t2/1000000.0f << endl;
}
std::vector<Municipalite> read_input_data(const std::string &filename, int &width, int &height)
{
    std::vector<Municipalite> municipalities;
    std::ifstream input;
    input.open(filename);
    if (!input)
    {
        std::cout << "Can't find source file: \'" << filename << "'" << std::endl;
        return municipalities;
    }
    input >> width >> height;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; ++x)
        {
            int pop;
            input >> pop;
            Municipalite mun = {x, y, pop};
            municipalities.push_back(mun);
        }
    }
    return municipalities;
}
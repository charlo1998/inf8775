#include "glouton.hpp"
#include "progdyn.hpp"
#include "restaurant.hpp"
#include "heuristic.hpp"
#include "chronometre.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <chrono>
#include <unordered_map>
using namespace std;


int main(int argc, char **argv)
{
    unordered_map<string,timed_algos> algorithms = 
    {
        {"local",chrono_local }, 
        {"glouton",chrono_greedy} ,
        {"progdyn", chrono_progdyn}
    };
    string algo;
    string filename;
    bool i_flag = false;
    bool t_flag = false;
    // command line arguments 
    for (int i = 0; i < argc - 1; i++)
    {
        if (string(argv[i]) == "-a")
        {
            algo = string(argv[i + 1]);
        }

        if (string(argv[i]) == "-e")
        {
            filename = string(argv[i + 1]);
        }
        if (string(argv[i]) == "-i")
        {
            i_flag = true;
        }
        if (string(argv[i]) == "-t")
        {
            t_flag = true;
        }
    }
    if (algorithms.find(algo) == algorithms.end()) {
        cout << "algorithme inconnue!"<<endl;
        return -1;
    }

    cout << "utilisation de l'algorithme "<< algo << endl;
    cout << "lecture du fichier '"<<filename << '\''<<endl;
    //lecture du fichier
    vector<Restaurant> restos;
    ifstream input;
    input.open(filename);
    if (!input)
    {
        cout << "Can't find source file" << endl;
        return -1;
    }
    int n_resto = 0;
    int id, qtty, revenue, capacity;
    input >> n_resto;
    for (int i = 0; i < n_resto; ++i)
    {
        input >> id >> revenue >> qtty;
        restos.push_back(Restaurant(id, qtty, revenue));
    }
    input >> capacity;

    int64_t temps;
    auto solution = algorithms[algo](restos,capacity, temps);
    if (i_flag) {
        for (auto resto : solution)
            cout<<resto.id<< ' '<<endl;
        return 0;
    }
    if (t_flag) {
        cout << temps/1000 <<endl;
    }
    cout << temps << " ns"<<endl;

}


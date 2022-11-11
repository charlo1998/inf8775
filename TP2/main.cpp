#include "glouton.hpp"
#include "progdyn.hpp"
#include "restaurant.hpp"
#include "heuristic.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int main(int argc, char** argv) {
    string algo;
    string filename;
    for(int i =0; i< argc-1; i++){
        if(string(argv[i]) == "-a"){
            algo = string(argv[i+1]);
             
        }

        if(string(argv[i]) == "-e"){
            filename = string(argv[i+1]);
        }
    }

    cout << algo << endl; 
    cout << filename <<endl;
    vector<Restaurant> restos;
    ifstream input;
    input.open(filename);
    if(!input)
	{
		cout<< "Can't find source file"<<endl;
		return -1;
	}
    int n_resto =0;
    int id, qtty, revenue, capacity;
    input >> n_resto;
    cout << n_resto << endl;
    for(int i =0; i< n_resto; ++i) {
        input >> id >> revenue >> qtty;
        restos.push_back(Restaurant(id,qtty,revenue));
    }
    input >> capacity;
    if (algo == "glouton")
    {
        vector<Restaurant> solution = greedy10(restos, capacity);
        for(auto& resto : solution) resto.display();
    } else if (algo == "progdyn")
    {
        vector<Restaurant> solution = progdyn(restos, capacity);
        for(auto& resto : solution) resto.display();
    } else if (algo == "local")
    {
        vector<Restaurant> solution = start_heuristic(restos, capacity);
        for(auto& resto : solution) resto.display();
    } else {
        test_swap();
    }
    
    
    
    


    


}
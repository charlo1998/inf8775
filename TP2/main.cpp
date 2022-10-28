#include "glouton.hpp"
#include "dynamique.hpp"
#include "restaurant.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char** argv) {
    string filename;
    for(int i =0; i< argc-1; i++){
        if(string(argv[1]) == "-e"){
            filename = string(argv[i+1]);
        }
    }

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
    cout << n_resto;
    for(int i =0; i< n_resto; ++i) {
        input >> id >> revenue >> qtty;
        cout << id << " " << revenue << " " <<qtty << endl;
        restos.push_back(Restaurant(id,qtty,revenue));
    }
    input >> capacity;
    vector<Restaurant> solution = greedy10(restos, capacity);
    for(auto& resto : solution) resto.display();


}
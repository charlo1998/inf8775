#include "heuristique.hpp"
std::vector<Circonscription> generate_initial_solution(std::vector<Municipalite> &munis, int n_circ, int dist_max, int x_size, int y_size){
    
    std::vector<Circonscription> solution;
    for(int i = 0; i<3; i++){
        Circonscription circ(i);

        for(int j =0; j<5; j++){
            circ.addMunicipalite(munis[5*i+j], 5);
        }
        solution.push_back(circ);
        
    }

    return solution;
}

void heuristique(std::vector<Municipalite> &munis){

}
#include "heuristique.hpp"
std::vector<Circonscription> generate_initial_solution(std::vector<Municipalite> &munis, int n_circ, int dist_max, int x_size, int y_size){
    
    std::vector<Circonscription> solution;
    std::vector<Municipalite> muniRestantes = munis;


    //create starting points for all the circ, alternating along the largest side
    float freq = std::max(x_size, y_size)/float(n_circ);
    std::cout << "spacing: " << freq << endl;
    int shortSide = std::min(x_size, y_size);
    float freqCounter = 0;
    int idx;
    if (shortSide == x_size) { // vertical rectangle
        for(int i = 0; i<n_circ; i++){
            Circonscription circ(i);
            if (i%2) {  //even, place on the left
                idx = round(freqCounter)*x_size;
                circ.addMunicipalite(munis[idx], dist_max);
                freqCounter += freq;
            } else { //odd, place on the right
                idx = round(freqCounter)*x_size + x_size-1;
                circ.addMunicipalite(munis[idx], dist_max);
                freqCounter += freq;
            }
            muniRestantes[idx] = muniRestantes.back();
            muniRestantes.pop_back();
            solution.push_back(circ);
        }
    } else { // horizontal rectangle
        for(int i = 0; i<n_circ; i++){
            Circonscription circ(i);
            if (i%2) {  //even, place on the top
                idx = round(freqCounter);
                circ.addMunicipalite(munis[idx], dist_max);
                freqCounter += freq;
            } else { //odd, place on the bottom
                idx = round(freqCounter) + x_size*(y_size-1);
                circ.addMunicipalite(munis[idx], dist_max);
                freqCounter += freq;
            }
            muniRestantes[idx] = muniRestantes.back();
            muniRestantes.pop_back();
            solution.push_back(circ);
        }
    }
    
    
    // for(int i = 0; i<3; i++){
    //     Circonscription circ(i);

    //     for(int j =0; j<5; j++){
    //         circ.addMunicipalite(munis[5*i+j], 5);
    //     }
    //     solution.push_back(circ);
        
    // }

    return solution;
}

void heuristique(std::vector<Municipalite> &munis){

}
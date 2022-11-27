#include "heuristique.hpp"
std::vector<Circonscription> generate_initial_solution(std::vector<Municipalite> &munis, int n_circ, int dist_max, int x_size, int y_size){
    
    std::vector<Circonscription> solution;
    std::vector<Municipalite> muniStart;
    std::vector<Municipalite> muniRestantes = munis;
    int max_size = ceil(munis.size()/float(n_circ));
    int min_size = floor(munis.size()/float(n_circ));
    std::cout << max_size << endl;


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
            muniStart.push_back(munis[idx]);
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
            muniStart.push_back(munis[idx]);
            muniRestantes[idx] = muniRestantes.back();
            muniRestantes.pop_back();
            solution.push_back(circ);
        }
    }

    //now that we have starting points fill the space by assigning munis to closest circ.
    bool full_circs = false;
    for (auto &municipalite : muniRestantes){
        int dist_min = dist_max + 1;
        int closest_circ = 0;
        // first fill circ to minimal size, then add remaining munis up to max size
        if (!full_circs){
            for (int i = 0; i<muniStart.size(); i++){
                if(solution[i].getCount() < min_size){
                    full_circs = false;
                    int dist = solution[i].distance(municipalite, muniStart[i]);
                    if (dist < dist_min) { //found a closer circ
                        dist_min = dist;
                        closest_circ = i;
                    } else if (dist == dist_min) { // same distance, prioritize smaller circs
                        if (solution[i].getCount() < solution[closest_circ].getCount()){
                            dist_min = dist;
                            closest_circ = i;
                        }
                    }
                }
            }
        } else { // didn't find a circ with less than min_size munis
            for (int i = 0; i<muniStart.size(); i++){
                if(solution[i].getCount() < max_size){
                    full_circs = false;
                    int dist = solution[i].distance(municipalite, muniStart[i]);
                    if ( dist < dist_min) {
                        dist_min = dist;
                        closest_circ = i;
                    }
                }
            }
        } 

        if (dist_min <= dist_max){
            solution[closest_circ].addMunicipalite(municipalite, dist_max);
        } else {
            std::cout << "no available circonscription found for municipality: " << municipalite << endl;
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
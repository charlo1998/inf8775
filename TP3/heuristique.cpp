#include "heuristique.hpp"
std::vector<Circonscription> generate_initial_solution(std::vector<Municipalite> &munis, int n_circ, int dist_max, int x_size, int y_size){
    
    std::vector<Circonscription> solution;
    std::vector<Municipalite> muniStart;
    int max_size = ceil(munis.size()/float(n_circ));
    int min_size = floor(munis.size()/float(n_circ));
    std::cout << "min_size: "<< min_size << " max_size: " << max_size << endl;


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
            solution.push_back(circ);
        }
    }

    std::vector<Municipalite> muniOrphelines;
    //now that we have starting points fill the space by assigning munis to closest circ.
    bool full_circs = false;
    for (auto &municipalite : munis){
        if (municipalite.i_circ == -1){ //make sure muni is un-assigned
            int dist_min = dist_max + 1;
            int closest_circ = 0;
            // first fill circ to minimal size, then add remaining munis up to max size
            if (!full_circs){
                for (int i = 0; i<n_circ; i++){
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
            } else { // didn't find a circ with less than min_size munis now add to max size
                for (int i = 0; i<n_circ; i++){
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
                bool success = solution[closest_circ].addMunicipalite(municipalite, dist_max);
                if(!success){
                    std::cout << "failed to add muni " << municipalite << endl;
                    muniOrphelines.push_back(municipalite);
                }
            } else {
                muniOrphelines.push_back(municipalite);
                std::cout << "no available circonscription found for municipality: " << municipalite << endl;
            }
        } else {
            std::cout << municipalite << " is already assigned" << endl;
        }
        
    }
    
    // monte carlo pour assigner les munis orphelines aux circonscriptions non-complètes
    while (muniOrphelines.size() >= 1){
        int smallest_idx;
        int smallest_size = max_size;
        //find smallest circ to add a muni to it
        for(int i = 0; i<n_circ; i++){
            int size = solution[i].getCount();
            if (size < smallest_size){
                smallest_size = size;
                smallest_idx = i;
            }
        }
        //first check if we can add one of the remaining munis
        bool success = false;
        for (int i = 0; i<muniOrphelines.size(); i++){
            //we need to assign from the real set, so find whichs muni this correpsonds to in munis
            int x = muniOrphelines[i].x;
            int y = muniOrphelines[i].y;
            success = solution[smallest_idx].addMunicipalite(munis[x_size*y + x], dist_max);
            if (success){
                std::cout << "assigned orphan muni! " << muniOrphelines[i]  << " to: " << smallest_idx << endl;
                muniOrphelines[i] = muniOrphelines.back();
                muniOrphelines.pop_back();
                break;
            }
        }
        //if not, then steal a random muni from the neighbors
        if (!success){
            //solution[smallest_idx].print();
            solution[smallest_idx].stealNeighbor(solution, munis, x_size, y_size, dist_max);
        }
    }

    return solution;
}

void heuristique(std::vector<Municipalite> &munis){

}
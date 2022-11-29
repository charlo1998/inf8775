#include "heuristique.hpp"
std::vector<Circonscription> generate_initial_solution(std::vector<Municipalite> &munis, int n_circ, int dist_max, int x_size, int y_size){
    
    std::vector<Circonscription> solution;
    std::vector<Municipalite> muniStart;
    float freq = munis.size()/float(n_circ);
    int max_size = ceil(freq);
    int min_size = floor(freq);
    std::cout << "min_size: "<< min_size << " max_size: " << max_size << endl;


    //create starting points for all the circ
    int idx = 0;
    float counter=0;

    //rectangular tessellation TODO
    float x = sqrt(x_size/float(y_size)*float(n_circ));
    float y = floor(n_circ/x);
    x = floor(x);
    //std::cout << "x: " << x << " y: " << y << endl;
    float aspectRatio = y_size/float(x_size);
    while(x*y < n_circ){
        adjustAspectRatio(x,y,n_circ,aspectRatio);
    }
    std::cout << "tesselation in a " << x << " x " << y << " rectangle" << endl;

    float x_jump = (x_size-1)/(x-1);
    float y_jump = (y_size-1)/(y-1);
    std::cout << "x jump: " << x_jump << " y_jump: " << y_jump << endl;
    int m = 0;
    while(m < n_circ){
        //initialize backwards so that the filling routine starts with the farthest munis
        for(int i = y-1; i >= 0; i--) {
            for(int j = x-1; j >= 0; j--) {
                if (m < n_circ){
                    int idx = round(x_jump*j) + round(y_jump*i)*x_size;
                    //std::cout << "idx: " << idx << endl;
                    Circonscription circ(m);
                    circ.addMunicipalite(munis[idx], dist_max);
                    muniStart.push_back(munis[idx]);
                    solution.push_back(circ);
                    m++;
                }
                
            }
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
                full_circs = true;
                for (int i = 0; i<n_circ; i++){
                    if(solution[i].getCount() < min_size){
                        full_circs = false;
                        int dist = solution[i].distance(municipalite, muniStart[i]);
                        //std::cout << "i: " << i  << " muni: " << municipalite << "circ start: " << muniStart[i] << " dist: " << dist << endl;
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
                    //std::cout << "failed to add muni " << municipalite << " to circ " << closest_circ << endl;
                    muniOrphelines.push_back(municipalite);
                }
            } else {
                muniOrphelines.push_back(municipalite);
                //std::cout << "no available circonscription found for municipality: " << municipalite << endl;
            }
        } else {
            //std::cout << municipalite << " is already assigned" << endl;
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
                //std::cout << "assigned orphan muni! " << muniOrphelines[i]  << " to: " << smallest_idx << endl;
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

    std::cout << "Creation du graphe des circonscriptions" << endl;
    
    //creation du graphe des circonscriptions  n*m
    for(int i = 0; i < y_size; i++) {
        for(int j = 0; j < floor(x_size/2.0f)+x_size%2; j++) {
            int idx = (2*j) + (i)*x_size + (1-i%2);
            //generation voisinage de munis[idx]
            for(int dx=-1; dx<2;dx++) {
                for(int dy=-1; dy<2;dy++) {
                    int newX = munis[idx].x + dx;
                    int newY = munis[idx].y + dy;
                     //make sure we are still within bounds
                    if (newX >= 0 && newX < x_size && newY >= 0 && newY < y_size) {
                        int neighbour_circ = munis[x_size*newY + newX].i_circ;
                        int current_circ = munis[idx].i_circ;
                         //if either muni is unassigned, skip
                        if (current_circ != -1 && neighbour_circ != -1){
                            if (neighbour_circ != current_circ){ //found a connection!
                                 // if not already there, add it to the neighbours
                                if(!solution[current_circ].isNeighbour(neighbour_circ)) { //opération baromètre linéaire en m
                                    solution[current_circ].voisins.push_back(neighbour_circ);
                                    solution[neighbour_circ].voisins.push_back(current_circ);
                                }
                            }
                        }
                        
                    }
                }
            }
        }
    }

    // for(auto &circ : solution){
    //     std::cout << "Circ: " << circ.id << " Neighbours: ";
    //     for(int &voisin: circ.voisins){
    //         std::cout << voisin << " ";
    //     }
    //     std::cout << endl;
    // }

    //assignation des municipalites orphelines
    //parcours en profondeur pour trouver un chemin entre la municipalite orpheline et la plus petite circonscription

    return solution;
}

void heuristique(std::vector<Municipalite> &munis){

}

void adjustAspectRatio(float &x, float &y, int n_circ, float globalAspectRatio){
    
    
    if((x+1)*y < n_circ){ // if adding to x is not enough
        y =y+1;
        return;
    } else if((y+1)*x < n_circ){ // if adding to y is not enough
        x =x+1;
        return;
    }
    
    float aspectRatio_x = y/(x+1.0f);
    float aspectRatio_y = (y+1.0f)/x;
    float dx = abs(globalAspectRatio - aspectRatio_x);
    float dy = abs(globalAspectRatio - aspectRatio_y);
    //std::cout << "dx: " << dx << " dy: " << dy << endl;
    if (dx < dy){
        x = x+1;
    } else {
        y = y+1;
    }
}
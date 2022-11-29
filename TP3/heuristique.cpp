#include "heuristique.hpp"
std::vector<Circonscription> generate_initial_solution(std::vector<Municipalite> &munis, int n_circ, int dist_max, int x_size, int y_size){
    
    std::vector<Circonscription> solution;
    std::vector<Municipalite> muniStart;
    int total = 0;
    for(int i=0; i<static_cast<int>(munis.size()); i++){
        total += munis[i].votes;
    }
    std::cout << "total amount of votes: " << total << endl;
    float freq = munis.size()/float(n_circ);
    int max_size = ceil(freq);
    int min_size = floor(freq);
    std::cout << "min_size: "<< min_size << " max_size: " << max_size << endl;


    //create starting points for all the circ
    int idx = 0;

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

    float x_jump;
    float y_jump;
    if(x==1){
        x_jump = 0;
    } else {
        x_jump = (x_size-1)/(x-1);
    }
    if(y==1){
        y_jump = 0;
    } else {
        y_jump = (y_size-1)/(y-1);
    }
    std::cout << "x jump: " << x_jump << " y_jump: " << y_jump << endl;
    int m = 0;
    while(m < n_circ){
        //initialize backwards so that the filling routine starts with the farthest munis
        for(int i = y-1; i >= 0; i--) {
            for(int j = x-1; j >= 0; j--) {
                if (m < n_circ){
                    idx = round(x_jump*j) + round(y_jump*i)*x_size;
                    //std::cout << "idx: " << idx << endl;
                    Circonscription circ(m);
                    circ.addMunicipalite(munis[idx], dist_max, max_size);
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
            std::vector<int> closest_circs;
            int closest_circ = 0;
            // first fill circ to minimal size, then add remaining munis up to max size
            if (!full_circs){
                full_circs = true;
                for (int i = 0; i<n_circ; i++){
                    if(static_cast<int>(solution[i].getCount()) < min_size){
                        full_circs = false;
                        int dist = solution[i].distance(municipalite, muniStart[i]);
                        //std::cout << "i: " << i  << " muni: " << municipalite << "circ start: " << muniStart[i] << " dist: " << dist << endl;
                        if (dist < dist_min) { //found a closer circ
                            dist_min = dist;
                            closest_circ = i;
                            closest_circs.push_back(i);
                        } else if (dist == dist_min) { // same distance, prioritize smaller circs
                            if (solution[i].getCount() < solution[closest_circ].getCount()){
                                dist_min = dist;
                                closest_circ = i;
                                closest_circs.push_back(i);
                            }
                        }
                    }
                }
            } else { // didn't find a circ with less than min_size munis now add to max size
                for (int i = 0; i<n_circ; i++){
                    if(static_cast<int>(solution[i].getCount()) < max_size){
                        int dist = solution[i].distance(municipalite, muniStart[i]);
                        if ( dist < dist_min) {
                            dist_min = dist;
                            closest_circ = i;
                            closest_circs.push_back(i);
                        }
                    }
                }
            } 

            if (dist_min <= dist_max){
                bool success = false;
                for(int i = closest_circs.size()-1; i >=0; i--){ // try to add to closest, if not to 2nd closest etc.
                    int i_circ = closest_circs[i];
                    success = solution[i_circ].addMunicipalite(municipalite, dist_max, max_size);
                    if(success){
                        break;
                    } else {
                        //std::cout << "failed to add muni " << municipalite << " to circ " << closest_circ << endl;
                    }
                }
                if(!success){
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

    std::cout << "Starting monte carlo to fill solution" << endl;
    
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
        for (int i = 0; i<static_cast<int>(muniOrphelines.size()); i++){
            //we need to assign from the real set, so find whichs muni this correpsonds to in munis
            int x = muniOrphelines[i].x;
            int y = muniOrphelines[i].y;
            success = solution[smallest_idx].addMunicipalite(munis[x_size*y + x], dist_max, max_size);
            if (success){
                //std::cout << "assigned orphan muni! " << muniOrphelines[i]  << " to: " << smallest_idx << endl;
                muniOrphelines[i] = muniOrphelines.back();
                muniOrphelines.pop_back();
                break; // we found an orphan, restart the process with updated values
            }
        }
        //if not, then steal a random muni from the neighbors
        if (!success){
            //solution[smallest_idx].print();
            Municipalite stolen = solution[smallest_idx].stealNeighbor(solution, munis, x_size, y_size, dist_max, max_size);
            if(stolen.i_circ == -1){
                for(int i = 0; i < static_cast<int>(muniOrphelines.size()); i++){
                    if(stolen == muniOrphelines[i]) {
                        muniOrphelines[i] = muniOrphelines.back();
                        muniOrphelines.pop_back();
                    }
                }
            }

        }
    }


    std::cout << "creating circonscription graph" << endl;    
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

bool heuristique(std::vector<Municipalite> &munis, std::vector<Circonscription> &circs, int n_circ, int dist_max, bool p_flag, int x_size, int y_size){

    std::vector<Municipalite> dummy_munis = munis;
    std::vector<Circonscription> dummy_circs = circs;
    float freq = munis.size()/float(n_circ);
    int max_size = ceil(freq);


    //randomly choose a muni
    int i_muni = std::rand()%munis.size();
    int i_circ = munis[i_muni].i_circ;


    //randomly choose one of her neighbours
    int delta_x = (std::rand()%3) - 1;
    int delta_y = (std::rand()%3) - 1;
    int newX = munis[i_muni].x + delta_x;
    int newY = munis[i_muni].y + delta_y;


    //if you can and it improves, swap them
    if (newX >= 0 && newX < x_size && newY >= 0 && newY < y_size){
        int new_circ = munis[x_size*newY + newX].i_circ;
        if (new_circ != i_circ){
            int before = dummy_circs[i_circ].isWinning() + dummy_circs[new_circ].isWinning();
            dummy_circs[i_circ].removeMunicipalite(dummy_munis[i_muni]);
            dummy_circs[new_circ].removeMunicipalite(dummy_munis[x_size*newY + newX]);

            bool success1 = dummy_circs[i_circ].addMunicipalite(dummy_munis[x_size*newY + newX], dist_max, max_size);
            bool success2 = dummy_circs[new_circ].addMunicipalite(dummy_munis[i_muni], dist_max, max_size);
            if(success1 && success2){
                int after = dummy_circs[i_circ].isWinning() + dummy_circs[new_circ].isWinning();
                if(after>before){
                    circs[i_circ].removeMunicipalite(munis[i_muni]);
                    circs[new_circ].removeMunicipalite(munis[x_size*newY + newX]);
                    circs[i_circ].addMunicipalite(munis[x_size*newY + newX], dist_max, max_size);
                    circs[new_circ].addMunicipalite(munis[i_muni], dist_max, max_size);
                    //std::cout << "improved!" << endl;

                    if (p_flag)
                    {
                        //print the solution in the good format
                        cout << endl;
                        for(int i = 0; i<circs.size(); i++)
                        {
                            circs[i].print();
                        }
                    }
                    else 
                    {
                        int count = 0;
                        for(int i = 0; i<circs.size(); i++)
                        {
                            //cout << solution[i].getVotes();
                            //cout << endl;
                            count += circs[i].isWinning();
                        }
                        cout << count << endl;
                    }
                    return true;
                }
            }

        }
    }

    //std::cout << "failed to improve" << endl;
    return false;
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
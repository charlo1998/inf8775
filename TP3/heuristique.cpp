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
    std::cout << "x: " << x << " y: " << y << endl;
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
    // while (muniOrphelines.size() > 0){
    //     int smallest_idx;
    //     int smallest_size = max_size;
    //     //find smallest circ to add a muni to it
    //     for(int i = 0; i<n_circ; i++){
    //         int size = solution[i].getCount();
    //         if (size < smallest_size){
    //             smallest_size = size;
    //             smallest_idx = i;
    //         }
    //     }
    //     //first check if we can add one of the remaining munis
    //     bool success = false;
    //     for (int i = 0; i<static_cast<int>(muniOrphelines.size()); i++){
    //         //we need to assign from the real set, so find whichs muni this correpsonds to in munis
    //         int x = muniOrphelines[i].x;
    //         int y = muniOrphelines[i].y;
    //         success = solution[smallest_idx].addMunicipalite(munis[x_size*y + x], dist_max, max_size);
    //         if (success){
    //             //std::cout << "assigned orphan muni! " << muniOrphelines[i]  << " to: " << smallest_idx << endl;
    //             muniOrphelines[i] = muniOrphelines.back();
    //             muniOrphelines.pop_back();
    //             break; // we found an orphan, restart the process with updated values
    //         }
    //     }
    //     //if not, then steal a random muni from the neighbors
    //     if (!success){
    //         //solution[smallest_idx].print();
    //         Municipalite stolen = solution[smallest_idx].stealNeighbor(solution, munis, x_size, y_size, dist_max, max_size);
    //         if(stolen.i_circ == -1){
    //             for(int i = 0; i < static_cast<int>(muniOrphelines.size()); i++){
    //                 if(stolen == muniOrphelines[i]) {
    //                     muniOrphelines[i] = muniOrphelines.back();
    //                     muniOrphelines.pop_back();
    //                 }
    //             }
    //         }

    //     }
    // }


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
    for(auto &circ : solution){
        std::cout << "Circ: " << circ.id << " Neighbours: ";
        for(int &voisin: circ.voisins){
            std::cout << voisin << " ";
        }
        std::cout << endl;
    }
    visualize(munis,  x_size, y_size);

    //assignation des municipalites orphelines
    //parcours en largeur pour trouver un chemin entre la municipalite orpheline et la plus petite circonscription
    for(int i =0; i < muniOrphelines.size(); i++){//muniOrphelines.size()
        std::cout << "orpheline: " << muniOrphelines[i] << endl;
        int x = muniOrphelines[i].x;
        int y = muniOrphelines[i].y;
        int start;
        for(int dx=-1; dx<2;dx++) {
            for(int dy=-1; dy<2;dy++) {
                int newX = muniOrphelines[i].x + dx;
                int newY = muniOrphelines[i].y + dy;
                //make sure we are still within bounds
                if (newX >= 0 && newX < x_size && newY >= 0 && newY < y_size){
                    if(munis[x_size*newY + newX].i_circ != -1){
                        start = munis[x_size*newY + newX].i_circ;
                        break;
                    }
                }
            }
        }
        std::vector<bool> visited(munis.size(),false);
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
        int target = smallest_idx;

        if(start == target){
            bool success = solution[start].addMunicipalite(munis[x_size*y + x], dist_max, max_size);
            if(success){
                std::cout << "added orphan " << munis[x_size*y + x] << endl;
            } else {
            std::cout << "failed to add orphan " << munis[x_size*y + x] << endl;
            }
        } else {
            std::cout << "Find path from circ " << start << " to " << target << endl;
            int pred[solution.size()], dist[solution.size()];
            if (!BFS(solution, start, target, solution.size(),pred, dist)){
                std::cout << "didn't find any path from " << start << " to " << target << endl;
                continue;
            }
            vector<int> path;
            int crawl = target;
            path.push_back(crawl);
            while (pred[crawl] != -1) {
                path.push_back(pred[crawl]);
                crawl = pred[crawl];
            }
            for(int i = path.size() - 1; i >= 0; i--){
                std::cout << path[i] << " ";
            }
            std::cout << endl;

            //solution[start].stealNeighborFromCirc(solution, munis, x_size, y_size, dist_max, max_size,  path[0]);
            for(int i =0; i <path.size()-1; i++){
                int i_circ = path[i];
                int target = path[i+1];
                std::cout << i_circ << " steals from " << target << endl;
                solution[i_circ].stealNeighborFromCirc(solution, munis, x_size, y_size, dist_max, max_size, target);
            }
            std::cout << path.back() << " tries to add " << munis[x_size*y + x] << endl;
            bool success = solution[path.back()].addMunicipalite(munis[x_size*y + x], dist_max, max_size);
            if(success){
                std::cout << "added orphan " << munis[x_size*y + x] << endl;
            } else {
            std::cout << "failed to add orphan " << munis[x_size*y + x] << endl;
            }
        }
        
        visualize(munis,  x_size, y_size);

    }

    
    cout << endl;
    for(int i = 0; i<solution.size(); i++)
    {
        solution[i].print();
    }

    return solution;
}

bool BFS(std::vector<Circonscription> &solution, int src, int dest, int v,
         int pred[], int dist[])
{
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // DFS algorithm
    std::list<int> queue;
 
    // boolean array visited[] which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    bool visited[v];
 
    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = 99999;
        pred[i] = -1;
    }
 
    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    // standard BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < solution[u].voisins.size(); i++) {
            if (visited[solution[u].voisins[i]] == false) {
                visited[solution[u].voisins[i]] = true;
                dist[solution[u].voisins[i]] = dist[u] + 1;
                pred[solution[u].voisins[i]] = u;
                queue.push_back(solution[u].voisins[i]);
 
                // We stop BFS when we find
                // destination.
                if (solution[u].voisins[i] == dest)
                    return true;
            }
        }
    }
    return false;
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

void visualize(std::vector<Municipalite> &munis, int x_size, int y_size){
    for(int i =  0; i < y_size; i++){
        for(int j = 0; j < x_size; j++){
            if(munis[x_size*i+j].i_circ==-1){
                std::cout << munis[x_size*i+j].i_circ << " ";
            } else{
                std::cout << munis[x_size*i+j].i_circ << "  ";
            }
            
        }
        std::cout << endl;
    }
}
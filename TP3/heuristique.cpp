#include "heuristique.hpp"
std::vector<Circonscription> generate_initial_solution(std::vector<Municipalite> &munis, int n_circ, int dist_max, int x_size, int y_size){
    bool verbose = true;
    std::vector<Circonscription> solution;
    std::vector<Municipalite> muniStart;
    int total = 0;
    for(int i=0; i<static_cast<int>(munis.size()); i++){
        total += munis[i].votes;
    }
    
    float freq = munis.size()/float(n_circ);
    int max_size = ceil(freq);
    int min_size = floor(freq);
    if(verbose){
        std::cout << "total amount of votes: " << total << endl;
        std::cout << "min_size: "<< min_size << " max_size: " << max_size << endl;
    }
    


    //create starting points for all the circ
    int idx = 0;

    //rectangular tessellation TODO
    float x = sqrt(x_size/float(y_size)*float(n_circ));
    float y = floor(n_circ/x);
    x = floor(x);
    //std::cout << "x: " << x << " y: " << y << endl;
    float aspectRatio = y_size/float(x_size);
    while(x*y < n_circ){ // find rough rectangle able to fit all circs, in a similar shape of the map
        adjustAspectRatio(x,y,n_circ,aspectRatio);
    }
    if(x*y > n_circ) {//if rectangle is too big, try to reduce it to fit better
        adjustAspectRatio(x,y,n_circ,aspectRatio);
    }
    

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
    if(verbose){
        std::cout << "tesselation in a " << x << " x " << y << " rectangle" << endl;
        std::cout << "x jump: " << x_jump << " y_jump: " << y_jump << endl;
    }
    int m = 0;
    while(m < n_circ){
        //initialize backwards so that the filling routine starts with the farthest munis
        for(int i = y-1; i >= 0; i--) {
            for(int j = x-1; j >= 0; j--) {
                if (m < n_circ){
                    idx = round(x_jump*j) + round(y_jump*i)*x_size;
                    //std::cout << "idx: " << idx << endl;
                    Circonscription circ(m,max_size, dist_max);
                    circ.addMunicipalite(munis[idx]);
                    muniStart.push_back(munis[idx]);
                    solution.push_back(circ);
                    m++;
                }
                
            }
        }
        
    }
    


    std::vector<Municipalite> muniOrphelines;
    //now that we have starting points fill the space by assigning munis to closest circ, one circ at a time
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
                    success = solution[i_circ].addMunicipalite(municipalite);
                    if(success){
                        break;
                    } 
                    // else {
                    //     //std::cout << "failed to add muni " << municipalite << " to circ " << closest_circ << endl;
                    // }
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


    if(verbose){
        std::cout << "number of orphan munis: " << muniOrphelines.size() << endl;
        std::cout << "Starting monte carlo to fill solution" << endl;
    }
    
    //visualize(munis,  x_size, y_size);
    // monte carlo pour assigner les munis orphelines aux circonscriptions non-complètes
    while (muniOrphelines.size() > 0){
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

        //int smallest_size = sizes[0][0];
        //int smallest_idx = sizes[0][1];

        //first check if we can add one of the remaining munis
        bool success = false;
        for (size_t i = 0; i<muniOrphelines.size(); i++){
            //we need to assign from the real set, so find whichs muni this correpsonds to in munis
            int x = muniOrphelines[i].x;
            int y = muniOrphelines[i].y;
            success = solution[smallest_idx].addMunicipalite(munis[x_size*y + x]);
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
            Municipalite stolen = solution[smallest_idx].stealNeighbor(solution, munis, x_size, y_size);
            if(stolen.i_circ == -1){
                std::cout << "test" << endl;
                for(int i = 0; i < static_cast<int>(muniOrphelines.size()); i++){
                    if(stolen == muniOrphelines[i]) {
                        muniOrphelines[i] = muniOrphelines.back();
                        muniOrphelines.pop_back();
                    }
                }
            }

        }
    }




    return solution;
}

void generateConnectivity(std::vector<Municipalite> &munis, std::vector<Circonscription> &solution,  int x_size, int y_size){
    //std::cout << "creating circonscription graph" << endl;    
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


bool heuristique(std::vector<Municipalite> &munis, std::vector<Circonscription> &circs, int n_circ, int dist_max, bool p_flag, int x_size, int y_size, float &temperature){

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
            Circonscription dummy_icirc = circs[i_circ];
            Circonscription dummy_newcirc = circs[new_circ];
            Municipalite dummy_imuni = munis[i_muni];
            Municipalite dummy_newmuni = munis[x_size*newY + newX];

            int before = dummy_icirc.isWinning() + dummy_newcirc.isWinning();
            dummy_icirc.removeMunicipalite(dummy_imuni);
            dummy_newcirc.removeMunicipalite(dummy_newmuni);
            bool success1 = dummy_icirc.addMunicipalite(dummy_newmuni);
            bool success2 = dummy_newcirc.addMunicipalite(dummy_imuni);
            int after = dummy_icirc.isWinning() + dummy_newcirc.isWinning();
            
            if(success1 && success2){
                if(after>=before){
                    circs[i_circ].removeMunicipalite(munis[i_muni]);
                    circs[new_circ].removeMunicipalite(munis[x_size*newY + newX]);
                    circs[i_circ].addMunicipalite(munis[x_size*newY + newX]);
                    circs[new_circ].addMunicipalite(munis[i_muni]);
                    //std::cout << "improved!" << endl;
                    if(after>before){
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
                    }
                    temperature *= 0.999;
                    return true;
                } else { // use the temperature to determine if we switch
                    float random = (std::rand()%100000000)/1000000.0f;
                    if(after == before -1){
                        if(random < temperature/2.0f){
                            //std::cout<< "used temp for -1! " << temperature << endl;
                            circs[i_circ].removeMunicipalite(munis[i_muni]);
                            circs[new_circ].removeMunicipalite(munis[x_size*newY + newX]);
                            circs[i_circ].addMunicipalite(munis[x_size*newY + newX]);
                            circs[new_circ].addMunicipalite(munis[i_muni]);
                        }
                    } else if(after == before -2){
                        if(random < temperature/16.0f){
                            //std::cout<< "used temp for -2!" << endl;
                            circs[i_circ].removeMunicipalite(munis[i_muni]);
                            circs[new_circ].removeMunicipalite(munis[x_size*newY + newX]);
                            circs[i_circ].addMunicipalite(munis[x_size*newY + newX]);
                            circs[new_circ].addMunicipalite(munis[i_muni]);
                        }
                    }
                }
            }

        }
    }

    //std::cout << "failed to improve" << endl;
    //temperature *= 1.001;
    return false;
}

void adjustAspectRatio(float &x, float &y, int n_circ, float globalAspectRatio){
    

    //if rectangle is too small, increase it
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

    // if to big, reduce it
    if ((x-1)*y < n_circ) { // if reducing x is too much
        while(x*y > n_circ){
            y = y-x;
        }
        y = y+x; //go back to last valid size
    } else if((y-1*x) < n_circ){
        while(x*y > n_circ){
            x = x-y;
        }
        x = y+x; //go back to last valid size
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

void mergeSort(std::vector<std::vector<int>> &arr, int n)
{
   int curr_size;  // For current size of subarrays to be merged
                   // curr_size varies from 1 to n/2
   int left_start; // For picking starting index of left subarray
                   // to be merged
 
   // Merge subarrays in bottom up manner.  First merge subarrays of
   // size 1 to create sorted subarrays of size 2, then merge subarrays
   // of size 2 to create sorted subarrays of size 4, and so on.
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
   {
       // Pick starting point of different subarrays of current size
       for (left_start=0; left_start<n-1; left_start += 2*curr_size)
       {
           // Find ending point of left subarray. mid+1 is starting
           // point of right
           int mid = min(left_start + curr_size - 1, n-1);
 
           int right_end = min(left_start + 2*curr_size - 1, n-1);
 
           // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
           merge(arr, left_start, mid, right_end);
       }
   }
}
 
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(std::vector<std::vector<int>> &arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
    int Lids[n1], Rids[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        L[i] = arr[l + i][0];
        Lids[i] = arr[l + i][1];
    }
    for (j = 0; j < n2; j++){
                R[j] = arr[m + 1+ j][0];
        Rids[j] = arr[m + 1+ j][1];
    }

 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k][0] = L[i];
            arr[k][1] = Lids[i];
            i++;
        }
        else
        {
            arr[k][0] = R[j];
            arr[k][1] = Rids[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k][0] = L[i];
        arr[k][1] = Lids[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k][0] = R[j];
        arr[k][1] = Rids[j];
        j++;
        k++;
    }
}
#include "circonscription.hpp"
Circonscription::Circonscription(int id) {
    votes = 0;
    this->id = id;
}
Circonscription::Circonscription(const Circonscription& other){
    votes = other.votes;
    municipalites = other.municipalites;
    id = other.id;
    voisins = other.voisins;
}

size_t Circonscription::getCount()
{
    return municipalites.size();
}

bool Circonscription::isNeighbour(int i) {
    for(int &voisin : voisins){
        if (voisin == i) {
            return true;
        }
    }
    return false;
}

bool Circonscription::isWinning()
{
    return votes > municipalites.size() * 50;
}

int Circonscription::getVotes(){ return votes;}

bool Circonscription::addMunicipalite(Municipalite &mun, int distance_max, int max_size)
{
    if(this->getCount() >= max_size){
        //std::cout << "max capacity reached of circ " << this->id << endl;
        return false;
    }
    for (auto &municipalite : municipalites)
    {
        if (distance(mun, municipalite) > distance_max)
        {
            //std::cout << mun << municipalite << "distance: " << distance(mun, municipalite) << endl;
            return false;
        }
    }
    municipalites.push_back(mun);
    mun.i_circ = id;
    votes +=mun.votes;
    return true;
}

void Circonscription::removeMunicipalite(Municipalite& target){
    votes -= target.votes;
    if(target.i_circ == id){ //if we own it, set circ to unassigned. otherwise, addmunicipality already updated its assignment
        target.i_circ = -1;
    }
    
    municipalites.erase(std::remove_if( municipalites.begin(), municipalites.end(),
            [this,&target](Municipalite mun) { 
                return mun == target; 
                }), municipalites.end());
}

void Circonscription::print(){
    for (auto &municipalite : municipalites){
        std::cout << municipalite;
    }
    cout << endl;
}

Municipalite Circonscription::stealNeighbor(std::vector<Circonscription> &circs, std::vector<Municipalite> &munis, int x_size, int y_size, int dist_max, int max_size){
        // cout << endl;
        // for(int i = 0; i<circs.size(); i++)
        // {
        //     circs[i].print();
        // }
        //std::cout << "trying to steal a neighbour for circ " << id << endl;
        
        bool foundNeighbor  = false;
        while(!foundNeighbor){
            int i_muni = std::rand()%municipalites.size();
            int delta_x = (std::rand()%3) - 1;
            int delta_y = (std::rand()%3) - 1;
            int newX = municipalites[i_muni].x + delta_x;
            int newY = municipalites[i_muni].y + delta_y;
            if (newX >= 0 && newX < x_size && newY >= 0 && newY < y_size) {
                //std::cout << "X: " << newX << " Y: " << newY << "  " << munis[x_size*newY + newX] << endl;
                int previous_circ = munis[x_size*newY + newX].i_circ;
                if (previous_circ != this->id){
                    //std::cout << previous_circ << endl;
                    Municipalite candidat = munis[x_size*newY + newX];
                    bool success = this->addMunicipalite(munis[x_size*newY + newX], dist_max, max_size);
                    if(success){
                        foundNeighbor = true;
                        if (previous_circ != -1){
                            circs[previous_circ].removeMunicipalite(munis[x_size*newY + newX]);
                            //std::cout<< "Found neighbor!: " << munis[x_size*newY + newX] << "belonged to: " << previous_circ << " added to " << this->id  << endl;
                        } else {
                            //std::cout << "neighbour is an orphan! assigned " << munis[x_size*newY + newX] << endl;
                        }
                        return candidat;
                        
                    }
                }
            }
        }
    }

bool Circonscription::stealNeighborFromCirc(std::vector<Circonscription> &circs, std::vector<Municipalite> &munis, int x_size, int y_size, int dist_max, int max_size, int circ){
        // cout << endl;
        // for(int i = 0; i<circs.size(); i++)
        // {
        //     circs[i].print();
        // }
        //std::cout << "trying to steal a neighbour for circ " << id << endl;
     
        bool foundNeighbor  = false;
        int iteration = 0;
        while(!foundNeighbor && iteration < 1000){
            int i_muni = std::rand()%municipalites.size();
            int delta_x = (std::rand()%3) - 1;
            int delta_y = (std::rand()%3) - 1;
            int newX = municipalites[i_muni].x + delta_x;
            int newY = municipalites[i_muni].y + delta_y;
            if (newX >= 0 && newX < x_size && newY >= 0 && newY < y_size) {
                //std::cout << "X: " << newX << " Y: " << newY << "  " << munis[x_size*newY + newX] << endl;
                int previous_circ = munis[x_size*newY + newX].i_circ;
                if (previous_circ == circ){
                    //std::cout << previous_circ << endl;
                    bool success = this->addMunicipalite(munis[x_size*newY + newX], dist_max, max_size);
                    if(success){
                        foundNeighbor = true;
                        if (previous_circ != -1){
                            circs[previous_circ].removeMunicipalite(munis[x_size*newY + newX]);
                            //std::cout << "neighbour is an orphan! assigned " << munis[x_size*newY + newX] << endl;
                        }
                        return true;
                        //std::cout<< "Found neighbor!: " << munis[x_size*newY + newX] << "belonged to: " << previous_circ << endl;
                     
                    }
                }
            }
            iteration++;
        }
        return false;
    }
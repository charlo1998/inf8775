#include "circonscription.hpp"
Circonscription::Circonscription(int id) {
    votes = 0;
    this->id = id;
}

size_t Circonscription::getCount()
{
    return municipalites.size();
}

bool Circonscription::isWinning()
{
    return votes > municipalites.size() * 50;
}

int Circonscription::getVotes(){ return votes;}

bool Circonscription::addMunicipalite(Municipalite &mun, int distance_max)
{
    for (auto &municipalite : municipalites)
    {
        if (distance(mun, municipalite) > distance_max)
        {
            return false;
        }
    }
    municipalites.push_back(mun);
    mun.i_circ = id;
    votes +=mun.votes;
    return true;
}

void Circonscription::removeMunicipalite(Municipalite& target){
        municipalites.erase(std::remove_if( municipalites.begin(), municipalites.end(),
            [this,&target](Municipalite mun) { 
                this->votes -= mun.votes;
                mun.i_circ = -1;
                return mun == target; 
                }), municipalites.end());
}

void Circonscription::print(){
    for (auto &municipalite : municipalites){
        std::cout << municipalite;
    }
    cout << endl;
}

void Circonscription::stealNeighbor(std::vector<Circonscription> &circs, std::vector<Municipalite> &munis, int x_size, int y_size, int dist_max){
        // for (auto &municipalite : munis){
        //     std::cout << municipalite.i_circ << endl;
        // }
        
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
                    bool success = this->addMunicipalite(munis[x_size*newY + newX], dist_max);
                    if(success){
                        foundNeighbor = true;
                        circs[previous_circ].removeMunicipalite(munis[x_size*newY + newX]);
                        //std::cout<< "Found neighbor!: " << munis[x_size*newY + newX] << "belonged to: " << previous_circ << endl;
                        
                    }
                }
                
            }
        }
    }
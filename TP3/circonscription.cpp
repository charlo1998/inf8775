#include "circonscription.hpp"
Circonscription::Circonscription(const Circonscription& other){
    votes = other.votes;
    municipalites = other.municipalites;
}
Circonscription::Circonscription() {
    votes=0;
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

bool Circonscription::addMunicipalite(const Municipalite &mun, int distance_max)
{
    for (auto &municipalite : municipalites)
    {
        if (distance(mun, municipalite) > distance_max)
        {
            return false;
        }
    }
    municipalites.push_back(mun);
    votes +=mun.votes;
    return true;
}

void Circonscription::removeMunicipalite(Municipalite& target){
        municipalites.erase(remove_if( municipalites.begin(), municipalites.end(),
            [this,&target](Municipalite mun) { 
                this->votes -= mun.votes;
                return mun == target; 
                }), municipalites.end());
}

void Circonscription::print(){
    for (auto &municipalite : municipalites){
        cout << municipalite;
    }
    std:cout << endl;
}

int Circonscription::distance(const Municipalite&m1 , const Municipalite& m2){
    return abs(m1.x - m2.x) + abs(m1.y - m2.y);
}

bool Circonscription::addCirconscription( Circonscription other, int distance_max){
    for (auto& mun : municipalites){
        if(!other.addMunicipalite(mun, distance_max)) {
            return false;
        }
    }
    municipalites = other.municipalites;
    votes = other.votes;
    return true;
}
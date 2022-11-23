#include "circonscription.hpp"
Circonscription::Circonscription() {}
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
        municipalites.erase(std::remove_if( municipalites.begin(), municipalites.end(),
            [this,&target](Municipalite mun) { 
                this->votes -= mun.votes;
                return mun == target; 
                }), municipalites.end());
}
#include "Circonscription.hpp"
Cirsconscription::Cirsconscription(){}
size_t Cirsconscription::getCount(){
return municipalites.size();
}
bool Cirsconscription::isWinning(){
    int count = countVotes();
    return count > municipalites.size() *50;
}
int Cirsconscription::countVotes(){
    int count =0;
    for (auto& municipalite : municipalites){
        count += municipalite.voteCount;
    }
}
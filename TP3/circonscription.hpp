#pragma once
#include <vector>
#include <algorithm>
#include "municipalite.hpp"
using namespace std;

class Circonscription {
    vector<Municipalite> municipalites;
    int votes;
    public:
    Circonscription(int id);
    size_t getCount();
    bool isWinning();
    int getVotes();
    int id;

    bool addMunicipalite(const Municipalite& mun, int distance_max);
    void removeMunicipalite(Municipalite& target);
    void print();
    int distance(const Municipalite& m1, const Municipalite &m2){
    return abs(m1.x - m2.x) + abs(m1.y - m2.y);
}
};
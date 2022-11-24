#pragma once
#include <vector>
#include <algorithm>
#include "municipalite.hpp"
using namespace std;

class Circonscription {
    vector<Municipalite> municipalites;
    int votes;
    public:
    Circonscription();
    Circonscription( const Circonscription& other);
    size_t getCount();
    bool isWinning();
    int getVotes();

    bool addMunicipalite(const Municipalite& mun, int distance_max);
    void removeMunicipalite(Municipalite& target);
    void print();
    int distance(const Municipalite& m1, const Municipalite &m2);
    bool addCirconscription(Circonscription other, int distance_max);
};
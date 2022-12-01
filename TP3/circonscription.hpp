#pragma once
#include <vector>
#include <algorithm>
#include "municipalite.hpp"
using namespace std;

class Circonscription
{
private:
    vector<Municipalite> municipalites;
    int votes;
    int max_size;
    int max_dist;

public:
    int id;
    std::vector<int> voisins;
    Circonscription(int id, int size_max, int dist_max);
    Circonscription(const Circonscription &other);
    size_t getCount() const;
    bool isNeighbour(int i);
    bool isWinning();
    int getVotes();

    bool addMunicipalite(Municipalite &mun);
    void removeMunicipalite(Municipalite &target);
    void print();
    bool canBeAdded(const Municipalite &m);
    Municipalite stealNeighbor(std::vector<Circonscription> &circs, std::vector<Municipalite> &munis, int x_size, int y_size);
    bool stealNeighborFromCirc(std::vector<Circonscription> &circs, std::vector<Municipalite> &munis, int x_size, int y_size, int circ);
    int distance(const Municipalite &m1, const Municipalite &m2);
};

// functor class for min heap definition
class CirconscriptionComparator{
    public:
    bool operator() (const Circonscription& c1, const Circonscription& c2){
        return c1.getCount() > c2.getCount();
    }
};
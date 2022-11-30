#pragma once
#include <vector>
#include <algorithm>
#include "municipalite.hpp"
using namespace std;

class Circonscription {
    int votes;
    vector<Municipalite> municipalites;
    public:
    Circonscription(int id);
    size_t getCount();
    bool isNeighbour(int i);
    bool isWinning();
    int getVotes();
    int id;
    std::vector<int> voisins;

    bool addMunicipalite(Municipalite& mun, int distance_max, int max_size);
    void removeMunicipalite(Municipalite& target);
    void print();
    Municipalite stealNeighbor(std::vector<Circonscription> &circs, std::vector<Municipalite> &munis, int x_size, int y_size, int dist_max, int max_size);
    bool stealNeighborFromCirc(std::vector<Circonscription> &circs, std::vector<Municipalite> &munis, int x_size, int y_size, int dist_max, int max_size, int circ);
    int distance(const Municipalite& m1, const Municipalite &m2){
    return abs(m1.x - m2.x) + abs(m1.y - m2.y);
}
};
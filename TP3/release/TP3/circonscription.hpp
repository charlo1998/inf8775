#pragma once
#include <vector>
#include <algorithm>
#include "municipalite.hpp"
using namespace std;

class Circonscription
{

public:
    unsigned votes;
    vector<Municipalite> municipalites;
    int id;
    std::vector<int> voisins;
    Circonscription(int id);
    Circonscription(const Circonscription &other);
    size_t getCount();
    bool isNeighbour(int i);
    bool isWinning();
    int getVotes();

    bool addMunicipalite(Municipalite &mun, int distance_max, size_t max_size);
    void removeMunicipalite(Municipalite &target);
    void print();
    Municipalite stealNeighbor(std::vector<Circonscription> &circs, std::vector<Municipalite> &munis, int x_size, int y_size, int dist_max, size_t max_size);
    bool stealNeighborFromCirc(std::vector<Circonscription> &circs, std::vector<Municipalite> &munis, int x_size, int y_size, int dist_max, size_t max_size, int circ);
    int distance(const Municipalite &m1, const Municipalite &m2)
    {
        return abs(m1.x - m2.x) + abs(m1.y - m2.y);
    }
};
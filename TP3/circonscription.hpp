#include <vector>
#include <algorithm>
#include "utils.hpp"
using namespace std;

class Circonscription {
    vector<Municipalite> municipalites;
    int votes;
    public:
    Circonscription();
    size_t getCount();
    bool isWinning();
    int getVotes();

    bool addMunicipalite(const Municipalite& mun, int distance_max);
    void removeMunicipalite(Municipalite& target);
};
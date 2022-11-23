#include <vector>
#include "utils.hpp"
using namespace std;

class Cirsconscription {
    vector<Municipalite> municipalites;
    public:
    Cirsconscription();
    size_t getCount();
    bool isWinning();
    int countVotes();
};
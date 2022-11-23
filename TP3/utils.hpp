#include <stdint.h>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


typedef struct {
    int x,y;
    uint8_t voteCount;
} Municipalite;

typedef struct {
    int m_count;
    Municipalite** municipalities;
    bool isVotingGreen;
} Circonscription;

int distance(const Municipalite& m1, const Municipalite &m2);

std::vector<Municipalite> read_input_data(const std::string& filename);

std::ostream& operator<<(std::ostream& out, const Municipalite &mun);
std::ostream& operator<<(std::ostream& out, const Circonscription &circ);
void printSolution(const std::vector<Circonscription> &Solution);
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

int distance(const Municipalite& m1, const Municipalite &m2);

std::vector<Municipalite> read_input_data(const std::string& filename);

std::ostream& operator<<(std::ostream& out, const Municipalite &mun);

bool operator==( Municipalite& m1 ,    Municipalite & m2 ){
    return m1.x == m2.x && m1.y == m2.y;
}
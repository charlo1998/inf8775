#include "municipalite.hpp"

    Municipalite::Municipalite(int _x, int _y, int _votes ){
        x=_x;
        y=_y;
        votes=_votes;
    }
    Municipalite::Municipalite(const Municipalite& other){
        x = other.x;
        y=other.y;
        votes=other.votes;
    }
    bool Municipalite::operator==(const Municipalite& other)const {
        return other.x == x && other.y == y;
    }
#include "municipalite.hpp"

Municipalite::Municipalite(int _x, int _y, int _votes)
{
    x = _x;
    y = _y;
    votes = _votes;
    i_circ = -1;
}
Municipalite::Municipalite(const Municipalite &other)
{
    x = other.x;
    y = other.y;
    votes = other.votes;
    i_circ = other.i_circ;
}
bool Municipalite::operator==(const Municipalite &other) const
{
    return other.x == x && other.y == y;
}
#pragma once
#include <stdint.h>
#include <iostream>
class Municipalite {
    public:
    int x,y;
    uint8_t votes;
    int i_circ; //id of the circonscription it belongs to

    Municipalite(int _x, int _y, int _votes );
    Municipalite(const Municipalite& other);
    bool operator==(const Municipalite& other)const;
    friend std::ostream& operator<<(std::ostream& out , Municipalite mun){
        return out  << mun.x<<" "<<mun.y << " ";
    }

};
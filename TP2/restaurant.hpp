#pragma once
#include <iostream>
using namespace std;
class Restaurant {
public:
    Restaurant(int id, int qtty, int revenue);
    int id;
    int qtty;
    int revenue;
    double   probabilite;
    double   rentabilite;
    void display();
    bool operator==(const Restaurant& other) const;
};
#include "restaurant.hpp"
Restaurant::Restaurant(const Restaurant& resto){
    this->id            = resto.id;
    this->qtty          = resto.qtty;
    this->revenue       = resto.revenue;
    this->probabilite   = resto.probabilite;
    this->rentabilite   = (double) revenue/(double)qtty;
}
Restaurant::Restaurant(int id, int qtty, int revenue){
    this->id = id;
    this->qtty = qtty;
    this->revenue = revenue;
    this->probabilite =0;
    this->rentabilite = (double) revenue/(double)qtty;
}

void Restaurant::display(){
    cout << "restaurant #"<<id <<" q="<<qtty<<" r = "<<revenue <<endl;
}

bool Restaurant::operator==(const Restaurant& other) const {
    return other.id == id;
}
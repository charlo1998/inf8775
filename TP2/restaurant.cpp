#include "restaurant.hpp"

Restaurant::Restaurant(int id, int qtty, int revenue){
    this->id = id;
    this->qtty = qtty;
    this->revenue = revenue;
    this->probabilite =0;
    this->rentabilite = (double) revenue/(double)qtty;
}

void Restaurant::display(){
    cout << "restraunt #"<<id <<" q="<<qtty<<" r = "<<rentabilite <<endl;
}
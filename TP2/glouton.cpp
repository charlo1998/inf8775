#include "glouton.hpp"

double rentabilite_total(vector<Restaurant> restos){
    double rentabilite_total  =0;
    for(auto& resto : restos){
        rentabilite_total += resto.rentabilite;
    }
    return rentabilite_total;
}

Restaurant pige_aleatoire(vector<Restaurant>& restos, int& N, double rentabilite_total){
    // calcule de la probabilite
    for (int i = 0; i < restos.size(); i++) {
        Restaurant resto = restos[i];
        //  delete restaurant with bigger needs than we can provide
        if (resto.qtty > N ) restos.erase(restos.begin()+i);
        // calcule proba
        resto.probabilite = resto.rentabilite/rentabilite_total;
    }
    // generate random numnber
    srand( (unsigned)time( NULL ) );
    double random = (double) rand()/RAND_MAX ;

    double lower_bound =0;

    for (unsigned i = 0; i < restos.size(); i++){
        Restaurant resto = restos[i];

        if (resto.probabilite +lower_bound> random ){
            // remove the chosen one and update the remaining capacity
            restos.erase(restos.begin() + i);
            N -= resto.qtty;
            return resto;
        }
        // check next
        lower_bound += resto.probabilite;
    }
    return Restaurant(0,0,0);
}

vector<Restaurant> greedy(vector<Restaurant> restos, int N, int& revenue){
    vector<Restaurant> chosens;
    revenue =0;
    while(restos.size() >0){
        Restaurant chosen_one = pige_aleatoire(restos, N, rentabilite_total(restos));
        chosens.push_back(chosen_one);
        revenue  += chosen_one.revenue;
    }
    return chosens;
}

vector<Restaurant> greedy10 (vector<Restaurant> restos, int N){
    vector<Restaurant> max;
    int max_rev = 0;
    for(int i =0; i< 10; i++){
        int revenue;
        vector<Restaurant> current = greedy(restos, N, revenue);
        if(max_rev < revenue){
            max_rev = revenue;
            max = current;
        }
    }
}
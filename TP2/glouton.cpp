#include "glouton.hpp"

double calcule_rentability(const vector<Restaurant>& restos){
    double rentabilite_total  =0;
    for(auto& resto : restos){
        rentabilite_total += resto.rentabilite;
    }
    return rentabilite_total;
}

Restaurant pige_aleatoire(vector<Restaurant>& restos, int& N){
    // generate random numnber
    srand( (unsigned)time( NULL ) );
    double random = (double) rand()/RAND_MAX ;
    double lower_bound =0.0;
    double rentabilite_total = calcule_rentability(restos);
    // calcule de la probabilite
    for (int i = 0; i< (int)  restos.size(); i++) {
        Restaurant resto = restos[i];
        // calcule proba
        restos[i].probabilite = resto.rentabilite/rentabilite_total;
    }

    for (unsigned i = 0; i < restos.size(); i++){
        Restaurant resto = restos[i];
        lower_bound += resto.probabilite;
        if (resto.probabilite +lower_bound> random ){
            N -= resto.qtty;
            return resto;
        }
        // check next
    }
    return Restaurant(-1,0,0);
}

vector<Restaurant> greedy(vector<Restaurant> restos, int N, float& revenue){
    vector<Restaurant> chosens;
    revenue =0;
    while(restos.size() >0 && N > 0){
        if(N == 1 && 1==restos.size()) {
            restos[0].display();
        }
        Restaurant chosen_one = pige_aleatoire(restos, N);
        if (chosen_one.id == -1)
            continue;  
        chosens.push_back(chosen_one);
        restos.erase(remove_if( restos.begin(), restos.end(),
            [&N,&chosen_one](Restaurant i_resto) { 
                return i_resto.qtty > N || i_resto == chosen_one ; 
                }), restos.end());
        cout<<"restaurant chosen : " <<endl;
        chosen_one.display();
        cout << "N remaining " << N<<endl;
        revenue  += chosen_one.revenue;
    }
    return chosens;
}

vector<Restaurant> greedy10 (vector<Restaurant> restos, int N){
    vector<Restaurant> max;
    int max_rev = 0;
    for(int i =0; i< 10; i++){
        float revenue = 0;
        vector<Restaurant> current = greedy(restos, N, revenue);
        if(max_rev < revenue){
            max_rev = revenue;
            max = current;
        }
        cout<<"Run #"<<i<<endl <<"Revenue : "<<revenue <<endl<<endl;
    }
    return max;
}
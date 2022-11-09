#include "heuristic.hpp"
int calculer_qtty_disponible(vector<Restaurant> restos, int N){
    int qtty =0;
    for(auto& resto : restos){
        qtty += resto.qtty;
    }
    return N- qtty;
}
bool is_in(const Restaurant resto, const vector<Restaurant> restos){
    for (auto & obj : restos){
        if(resto == obj){
            return true;
        }
    }
    return false;
}
vector<Restaurant> start_heuristic(vector<Restaurant> restos, int N){
    float revenu;
    vector<Restaurant> greed = greedy(restos, N, revenu);
    cout <<"greed"<<endl<<"******************"<<endl;
    for(auto& resto : greed) resto.display();
    cout <<"******************"<<endl;
    return heuristic_local(greed, restos, N);
}
vector<Restaurant> heuristic_local(vector<Restaurant> solution, vector<Restaurant> restos, int N){
    vector<vector<Restaurant>> combinaison_solution;
    vector<vector<Restaurant>> combinaison_resto;
    for (auto i_sol = solution.begin(); i_sol != solution.end(); ++i_sol){
        // calculer N restant si i_sol est enlever:
        int N_restant = calculer_qtty_disponible(solution,N);
        N_restant += i_sol->qtty;

        // trouver le meilleur candidat
        Restaurant candidat = *i_sol;
        for(auto& resto : restos){
            // considerer le restaurant uniquement 
            if  (resto.qtty <= N_restant && !is_in(resto, solution)){
                if(resto.revenue > candidat.revenue){
                    candidat = resto;
                    cout<<"swapped!"<<endl;
                }
            }
        }
        *i_sol = Restaurant(candidat);
    }
    return solution;
}
// current is better then old when we return >0
int compare(vector<Restaurant> old, vector<Restaurant> current){
    int revenue_old =0;
    int revenue_current = 0;
    for (auto& resto : old ){
        revenue_old += resto.revenue;
    }
    for (auto& resto : current ){
        revenue_current += resto.revenue;
    }
    return revenue_current - revenue_old;
}
// trouver touteles combinaisons possibles
vector<vector<Restaurant>> combinaison(int n, vector<Restaurant> restos){
    vector<vector<Restaurant>> combinaisons;
    for (auto& resto: restos){
        vector<Restaurant> vec;
        vec.push_back( Restaurant(resto));
        combinaisons.push_back(vec);
    }

    while(restos.size() >1){
        Restaurant resto = *restos.end();
        restos.pop_back();
        for (int i = restos.size() -1 ; i >= 0; i--){
            vector<Restaurant> vec;
            vec.push_back(resto);
            vec.push_back(restos[i]);
            combinaisons.push_back(vec);
        }
    }
    return combinaisons;
}


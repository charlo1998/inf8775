#include "heuristic.hpp"

/**
 * @
*/
vector<Restaurant> start_heuristic(vector<Restaurant> restos, int N)
{
    float revenu;
    vector<Restaurant> solution = greedy(restos, N, revenu);
    int swap_count;
    int i =0;
    do
    {
        swap_count = heuristic_local(solution, restos, N);
        cout<<swap_count<<endl;
    } while (swap_count > 0);
    // swap_count = heuristic_local(solution, restos, N);
    int rev_tot = 0;
    for (auto &resto : solution)
        rev_tot += resto.revenue;
    return solution;
}

void test_swap(){
    vector<Restaurant> restos;
    for(int i =1; i<6; i++){
        restos.push_back(Restaurant(i,i,i));
    }
    for (auto &resto : restos)
        resto.display();
    cout<<"************************"<<endl;
    vector<Restaurant> to_remove;
    for(int i =1; i<3; i++){
        to_remove.push_back(Restaurant(i,i,i));
    }
    cout<< "to_remove" <<endl;
    for (auto &resto : to_remove)
        resto.display();
    cout<<"************************"<<endl;
    vector<Restaurant> to_add;
    for(int i =3; i<5; i++){
        to_add.push_back(Restaurant(i,i,i));
    }
    cout<< "to_add" <<endl;
    for (auto &resto : to_add)
        resto.display();
    cout<<"************************"<<endl;
    swap_vectors(restos, to_remove, to_add);
    for (auto &resto : restos)
        resto.display();
}

int heuristic_local(vector<Restaurant> &solution, vector<Restaurant> restos, int N)
{
    // combien de modification on etait apporté
    int swap_count = 0;
    int gain_global = 0;
    vector<Restaurant> nouveau;
    vector<Restaurant> ancien;
    // booleen qui est vrai si un candidat apporte une amelioration a la solution et donc doit etre swapped
    bool isBetter = false;

    vector<vector<Restaurant>> combinaison_solution = combinaison(solution);
    // minimiser le nbr de resto
    vector<Restaurant> restos_valides;
    for (auto &resto : restos)
    {
        if (!is_in(resto, solution))
        {
            restos_valides.push_back(resto);
        }
    }
    vector<vector<Restaurant>> combinaison_resto = combinaison( restos_valides);
    // calculer N restant parmi solution existante:
    int N_restant = calculer_qtty_disponible(solution, N);
    // évaluer toutes les solutions voisines
    cout <<"Resto taille:" <<combinaison_resto.size();
    for (auto i_sol = combinaison_solution.begin(); i_sol != combinaison_solution.end(); ++i_sol)
    {
        // trouver le meilleur candidat
        for (auto &candidat : combinaison_resto)
        {
            int N_candidat = N_restant - compare_qtty( *i_sol, candidat);

            
            if (N_candidat >= 0)
            {
                int revenue_diff = compare_revenue(*i_sol, candidat);
                if (revenue_diff > gain_global)
                {
                    gain_global = revenue_diff;
                    nouveau = candidat;
                    ancien = *i_sol;
                    isBetter = true;
                }
            }
        }
    }
    // swap 2 if there is a gain
    if (isBetter)
    {
        swap_vectors(solution, ancien, nouveau);
        swap_count++;
    }
    
    return swap_count;
}
void swap_vectors(vector<Restaurant> &container, vector<Restaurant> old, vector<Restaurant> current)
{
    // cout << "avant: " << endl;
    // for(int i = 0; i < container.size(); i++)
    // {
    //     container[i].display();
    // }
    container.erase(remove_if( container.begin(), container.end(),
            [&old](Restaurant i_resto) { 
                return is_in(i_resto, old); 
                }), container.end());

    for (auto &resto : current)
    {
        container.push_back(resto);
    }
    // cout << "après: " << endl;
    // for(int i = 0; i < container.size(); i++)
    // {
    //     container[i].display();
    // }
}
// current is bigger then old when we return >0
int compare_qtty(vector<Restaurant> old, vector<Restaurant> current)
{
    int qtty_old = 0;
    int qtty_current = 0;
    for (auto &resto : old)
    {
        qtty_old += resto.qtty;
    }
    for (auto &resto : current)
    {
        qtty_current += resto.qtty;
    }
    return qtty_current - qtty_old;
}
// current is better then old when we return >0
int compare_revenue(vector<Restaurant> old, vector<Restaurant> current)
{
    int revenue_old = 0;
    int revenue_current = 0;
    for (auto &resto : old)
    {
        revenue_old += resto.revenue;
    }
    for (auto &resto : current)
    {
        revenue_current += resto.revenue;
    }
    return revenue_current - revenue_old;
}
// trouver touteles combinaisons possibles
vector<vector<Restaurant>> combinaison( vector<Restaurant> restos)
{
    vector<vector<Restaurant>> combinaisons;
    for (auto &resto : restos)
    {
        vector<Restaurant> vec;
        vec.push_back(Restaurant(resto));
        combinaisons.push_back(vec);
    }

    while (restos.size() > 1)
    {
        Restaurant resto = *(restos.end()-1);
        restos.pop_back();
        for (int i = restos.size()-1; i >= 0; i--)
        {
            vector<Restaurant> vec;
            vec.push_back(resto);
            vec.push_back(restos[i]);
            combinaisons.push_back(vec);
        }
    }

    // for(int i = 0; i < combinaisons.size(); i++)
    // {
    //     for(int j = 0; j < combinaisons[i].size(); j++)
    //     {
    //         cout << "#" << combinaisons[i][j].id << " ";
    //     }
    //     cout << endl;
    // }
    return combinaisons;
}
int calculer_qtty_disponible(vector<Restaurant> restos, int N)
{
    int qtty = 0;
    for (auto &resto : restos)
    {
        qtty += resto.qtty;
    }
    return N - qtty;
}
bool is_in(const Restaurant resto, const vector<Restaurant> restos)
{
    for (auto &obj : restos)
    {
        if (resto == obj)
        {
            return true;
        }
    }
    return false;
}

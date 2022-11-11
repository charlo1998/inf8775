#include "heuristic.hpp"

/**
 * @
*/
vector<Restaurant> start_heuristic(vector<Restaurant> restos, int N)
{
    float revenu;
    vector<Restaurant> solution = greedy(restos, N, revenu);
    cout << "solution avec greed" << endl
         << "******************" << endl;
    for (auto &resto : solution)
        resto.display();
    cout << "******************" << endl;
    int swap_count;
    int i =0;
    do
    {
        swap_count = heuristic_local(solution, restos, N);
        cout << "essai #" << endl << ++i << "swap count: " << swap_count<<endl;
    } while (swap_count > 0);
    // swap_count = heuristic_local(solution, restos, N);
    return solution;
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
    cout << "combinaisonS de solution: " << combinaison_solution.size() << endl;
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
    cout << "combinaisons de candidats: " << combinaison_resto.size() << endl;

    // calculer N restant parmi solution existante:
    int N_restant = calculer_qtty_disponible(solution, N);
    cout << "N restant: " << N_restant << endl;

    // évaluer toutes les solutions voisines
    for (auto i_sol = combinaison_solution.begin(); i_sol != combinaison_solution.end(); ++i_sol)
    {
        int N_candidat = 0;
        // cout << "restos à changer: " << endl;
        //     for (auto &resto : *i_sol)
        //     {
        //         resto.display();
        //     }

        // trouver le meilleur candidat
        for (auto &candidat : combinaison_resto)
        {
            N_candidat = N_restant +  compare_qtty(candidat, *i_sol);
            // cout << "nouvelle quantité: " << N_candidat << ", ";
            // cout << "candidats: ";
            // for (auto &resto : candidat)
            // {
            //     cout << "#" << resto.id << "   ";
            // }
            // cout << endl;
            
            if (N_candidat >= 0)
            {
                int revenue_diff = compare_revenue(*i_sol, candidat);
                if (revenue_diff > gain_global)
                {
                    cout << "amélioration de: " << revenue_diff << endl;
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
    
    container.erase(container.begin(),container.begin()+old.size());

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

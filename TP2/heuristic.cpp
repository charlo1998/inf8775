#include "heuristic.hpp"
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
vector<Restaurant> start_heuristic(vector<Restaurant> restos, int N)
{
    float revenu;
    vector<Restaurant> greed = greedy(restos, N, revenu);
    cout << "greed" << endl
         << "******************" << endl;
    for (auto &resto : greed)
        resto.display();
    cout << "******************" << endl;
    return heuristic_local(greed, restos, N);
}
vector<Restaurant> heuristic_local(vector<Restaurant> solution, vector<Restaurant> restos, int N)
{
    vector<vector<Restaurant>> combinaison_solution = combinaison(2, solution);
    // minimiser le nbr de resto
    vector<Restaurant> restos_valides;
    for (auto &resto : restos)
    {
        if (!is_in(resto, solution))
        {
            restos_valides.push_back(resto);
        }
    }
    vector<vector<Restaurant>> combinaison_resto = combinaison(2, restos_valides);
    for (auto i_sol = combinaison_solution.begin(); i_sol != combinaison_solution.end(); ++i_sol)
    {
        // calculer N restant si i_sol est enlever:
        int N_restant = calculer_qtty_disponible(solution, N);
        // trouver le meilleur candidat
        int delta_revenue = 0;
        vector<Restaurant> candidat = *i_sol;
        for (auto &combinaison : combinaison_resto)
        {
            N_restant += compare_qtty(combinaison, *i_sol);
            if (N_restant >= 0)
            {
                int revenue_diff = compare_revenue(candidat, combinaison);
                if (revenue_diff > delta_revenue)
                {
                    delta_revenue = revenue_diff;
                    candidat = combinaison;
                }
            }
        }
        // swap 2 combinaison
    }
    return solution;
}
void swap(vector<Restaurant> container, vector<Restaurant> old, vector<Restaurant> current)
{
    for (auto &it = container.begin(); it != container.end(); ++it)
    {
        if(is_in(*it, old)){
            remove(begin(container), end(container), it);
        }
    }
    for(auto& resto : current){
        container.push_back(resto);
    }
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
vector<vector<Restaurant>> combinaison(int n, vector<Restaurant> restos)
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
        Restaurant resto = *restos.end();
        restos.pop_back();
        for (int i = restos.size() - 1; i >= 0; i--)
        {
            vector<Restaurant> vec;
            vec.push_back(resto);
            vec.push_back(restos[i]);
            combinaisons.push_back(vec);
        }
    }
    return combinaisons;
}

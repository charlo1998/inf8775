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
    // do
    // {
    //     swap_count = heuristic_local(solution, restos, N);
    //     cout << "essai #" << ++i << "swap count: " << swap_count<<endl;
    // } while (swap_count > 0);
    swap_count = heuristic_local(solution, restos, N);
    return solution;
}


int heuristic_local(vector<Restaurant> &solution, vector<Restaurant> restos, int N)
{
    // combien de modification on etait apporté
    int swap_count = 0;
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
    for (auto i_sol = combinaison_solution.begin(); i_sol != combinaison_solution.end(); ++i_sol)
    {
        // booleen qui est vrai si un candidat apporte une amelioration a la solution et donc doit etre swapped
        bool isBetter = false;
        // calculer N restant si i_sol est enlever:
        int N_restant = calculer_qtty_disponible(solution, N);
        // trouver le meilleur candidat
        vector<Restaurant> candidat = *i_sol;
        for (auto &combinaison : combinaison_resto)
        {
            N_restant += compare_qtty(combinaison, *i_sol);
            if (N_restant >= 0)
            {
                int revenue_diff = compare_revenue(candidat, combinaison);
                if (revenue_diff > 0)
                {
                    isBetter = true;
                    candidat = combinaison;
                }
            }
        }
        // swap 2 if there is a gain
        if (isBetter)
        {
            swap_vectors(solution, *i_sol, candidat);
            swap_count++;
        }
    }
    return swap_count;
}
void swap_vectors(vector<Restaurant> container, vector<Restaurant> old, vector<Restaurant> current)
{
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        if (is_in(*it, old))
        {
            remove(begin(container), end(container), *it);
        }
    }
    for (auto &resto : current)
    {
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

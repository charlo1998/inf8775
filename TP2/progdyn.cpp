#include "progdyn.hpp"

vector<Restaurant> progdyn (vector<Restaurant> restos, int N){
    //creating the table for optimal revenue given i restos and j capacity
    vector<vector<int>> revenu_optimal(restos.size()+1);
    for (size_t i = 0; i < revenu_optimal.size(); i++)
    {
        revenu_optimal[i].resize(N+1);
    }

    //intitializing boundary values of the table
    for (size_t i = 0; i < revenu_optimal.size(); i++)
    {
        revenu_optimal[i][0] = 0; //no capacity left
        revenu_optimal[0][i] = 0; //no restos left
    }

    //filling the table with the recursion equation
    for (size_t i = 1; i < revenu_optimal.size(); i++)
    {
        for (size_t j = 1; j < revenu_optimal[i].size(); j++)
        {
            int r_i = restos[i].revenue;
            int q_i = restos[i].qtty;
            revenu_optimal[i][j] = max(r_i + revenu_optimal[i-1][j-q_i], revenu_optimal[i-1][j]);
        }
        
    }
    


    //finding the answer
    vector<Restaurant> solution;
    int i = revenu_optimal.size();
    int j = revenu_optimal[0].size();
    cout << "Revenue: " << revenu_optimal[i][j] << endl;

    while (i > 0 && j > 0)
    {
        int r_i = restos[i].revenue;
        int q_i = restos[i].qtty;
        if (r_i + revenu_optimal[i-1][j-q_i] > revenu_optimal[i-1][j]) //we take the resto
        {
            solution.push_back(restos[i]);
            j = j - q_i;
        }
        i--;
        
    }
    
    return solution;

}
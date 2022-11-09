#include "progdyn.hpp"

vector<Restaurant> progdyn (vector<Restaurant> restos, int N){
    //creating the table for optimal revenue given i restos and j capacity
    // vector<vector<int>> revenu_optimal(restos.size()+1);
	int n_restos = restos.size();
    int revenu_optimal[n_restos + 1][N+1]  ={0};

    cout << "initializing done" << endl;


    //filling the table with the recursion equation
    for (int i = 1; i < n_restos+1; i++)
    {
        for (int j = 1; j < N+1; j++)
        {
            int r_i = restos[i-1].revenue;
            int q_i = restos[i-1].qtty;
            if (q_i <= int(j)) // there is place for this resto
            {
                revenu_optimal[i][j] = max(r_i + revenu_optimal[i-1][j-q_i], revenu_optimal[i-1][j]);
            } else {
                revenu_optimal[i][j] = revenu_optimal[i-1][j];
            }
        }
    }


    //finding the answer
    vector<Restaurant> solution;
    int i = n_restos;
    int j = N;
    cout << "Revenue: " << revenu_optimal[i][j] << endl;

    while (i > 0 && j > 0)
    {
        int r_i = restos[i-1].revenue;
        int q_i = restos[i-1].qtty;

        if (q_i <= j) //there is place for this resto
        {
            if (r_i + revenu_optimal[i-1][j-q_i] > revenu_optimal[i-1][j]) //we take the resto
            {
                solution.push_back(restos[i-1]);
                j = j - q_i;
                
            }
            
        }
        i--;        
    }

    return solution;

}
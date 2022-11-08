#include "progdyn.hpp"

vector<Restaurant> progdyn (vector<Restaurant> restos, int N){
    //creating the table for optimal revenue given i restos and j capacity
    // vector<vector<int>> revenu_optimal(restos.size()+1);
	int n_restos = restos.size();
    int revenu_optimal[n_restos + 1][N+1]  ={0};
    // for (size_t i = 0; i <= N; i++)
    // {
    //     revenu_optimal[i].resize(N+1);
    // }

    

    //intitializing boundary values of the table
	// for (size_t i = 0; i <= n_restos+1; i++)
	// {
	// 	//cout << "i :" << i << endl;
	// 	revenu_optimal[i][0] = 0; //no capacity left
	// }
    // for (size_t j = 0; j <= N+1; j++)
    // {   
    //     //cout << "j :"<<j<<endl;
	// 	revenu_optimal[0][j] = 0; //no restos left
    // }
    cout << "initializing done" << endl;

    //printing result for debug purposes
    //  for (int i = 0; i < n_restos+1; i++)
    //  {
    //      for (int j = 0; j < N+1; j++)
    //      {
    //          cout << revenu_optimal[i][j] << " ";
    //      }
    //      cout << endl;
    //  }

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
    //cout << "filling table done" << endl;

    //printing result for debug purposes
    //  for (int i = 0; i < n_restos+1; i++)
    //  {
    //      for (int j = 0; j < N+1; j++)
    //      {
    //          cout << revenu_optimal[i][j] << " ";
    //      }
    //      cout << endl;
    //  }
    

    //finding the answer
    vector<Restaurant> solution;
    int i = n_restos;
    int j = N;
    cout << "Revenue: " << revenu_optimal[i][j] << endl;

    while (i > 0 && j > 0)
    {
        int r_i = restos[i-1].revenue;
        int q_i = restos[i-1].qtty;
        //cout << "r_i: " << r_i << " q_i: " << q_i;
        //cout << "   i: " << i << " j: " << j << endl;
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
#include "chronometre.hpp"
vector<Restaurant> chrono_local  (vector<Restaurant>& restos, int N, int64_t& t){
    auto start = chrono::high_resolution_clock::now();

    vector<Restaurant> solution = start_heuristic(restos, N);

    auto finish = chrono::high_resolution_clock::now();
    t= chrono::duration_cast<chrono::nanoseconds>(finish-start).count() ;
    return solution;

}
vector<Restaurant> chrono_greedy (vector<Restaurant>& restos, int N, int64_t& t){

    auto start = chrono::high_resolution_clock::now();

    vector<Restaurant> solution = greedy10(restos, N);

    auto finish = chrono::high_resolution_clock::now();
    t= chrono::duration_cast<chrono::nanoseconds>(finish-start).count() ;
    return solution;
}
vector<Restaurant> chrono_progdyn(vector<Restaurant>& restos, int N, int64_t& t){
    auto start = chrono::high_resolution_clock::now();

    vector<Restaurant> solution = progdyn(restos, N);

    auto finish = chrono::high_resolution_clock::now();
    t= chrono::duration_cast<chrono::nanoseconds>(finish-start).count() ;
    return solution;
}
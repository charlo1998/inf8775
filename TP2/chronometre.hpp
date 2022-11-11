#include "restaurant.hpp"
#include "glouton.hpp"
#include "progdyn.hpp"
#include "heuristic.hpp"
#include <vector>
#include <chrono>
typedef  vector<Restaurant> (*timed_algos) (vector<Restaurant>&,int, int64_t&) ;


vector<Restaurant> chrono_local  (vector<Restaurant>& restos, int N, int64_t& t );
vector<Restaurant> chrono_greedy (vector<Restaurant>& restos, int N, int64_t& t );
vector<Restaurant> chrono_progdyn(vector<Restaurant>& restos, int N, int64_t& t );
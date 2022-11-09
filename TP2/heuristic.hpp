#include "restaurant.hpp"
#include "glouton.hpp"

vector<Restaurant> start_heuristic(vector<Restaurant> restos, int N);
vector<Restaurant> heuristic_local(vector<Restaurant> solution, vector<Restaurant> restos, int N);
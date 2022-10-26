#pragma once
#include <vector>
#include <time.h>
#include "restaurant.hpp"
using namespace std;

vector<double> calcule_rentability(vector<int> revenus, vector<int> qtty, int& N);

Restaurant pige_aleatoire(vector<Restaurant> restos, int& N, double& rentabilite_total);

vector<Restaurant> greedy(vector<Restaurant> restos, int N, int& revenue);
vector<Restaurant> greedy10 (vector<Restaurant> restos, int N);
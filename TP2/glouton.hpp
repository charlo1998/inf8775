#pragma once
#include <vector>
#include <time.h>
#include <algorithm> 
#include "restaurant.hpp"
using namespace std;

double calcule_rentability(const vector<Restaurant>& restos);

Restaurant pige_aleatoire(vector<Restaurant>& restos, int& N);

vector<Restaurant> greedy(vector<Restaurant> restos, int N, float& revenue);
vector<Restaurant> greedy10 (vector<Restaurant> restos, int N);
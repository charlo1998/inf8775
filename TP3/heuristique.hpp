#pragma once
#include <vector>
#include "municipalite.hpp"
#include "circonscription.hpp"
#include <math.h>

std::vector<Circonscription> generate_initial_solution(std::vector<Municipalite> &munis, int n_circ, int dist_max, int x_size, int y_size);
void heuristique(std::vector<Municipalite> &munis);
void adjustAspectRatio(float &x, float &y, int n_circ, float globalAspectRatio);

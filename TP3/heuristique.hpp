#pragma once
#include <vector>
#include "utils.hpp"

void generate_initial_solution(std::vector<municipalite> &munis, int n_circ, int dist_max, int x_size, int y_size);
void heuristique(std::vector<municipalite> &munis);

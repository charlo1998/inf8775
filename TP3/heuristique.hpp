#pragma once
#include <vector>
#include "municipalite.hpp"
#include "circonscription.hpp"
#include <math.h>
#include<list> 

std::vector<Circonscription> generate_initial_solution(std::vector<Municipalite> &munis, int n_circ, int dist_max, int x_size, int y_size);
bool heuristique(std::vector<Municipalite> &munis, std::vector<Circonscription> &circs, int n_circ, int dist_max, bool p_flag, int x_size, int y_size, float &temperature);
bool BFS(std::vector<Circonscription> &solution, int src, int dest, int v,
         int pred[], int dist[]);
void visualize(std::vector<Municipalite> &munis, int x_size, int y_size);
void generateConnectivity(std::vector<Municipalite> &munis, std::vector<Circonscription> &solution,  int x_size, int y_size);
void adjustAspectRatio(float &x, float &y, int n_circ, float globalAspectRatio);
void merge(std::vector<std::vector<int>> &arr, int l, int m, int r);
void mergeSort(std::vector<std::vector<int>> &arr, int n);



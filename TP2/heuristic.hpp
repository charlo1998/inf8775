#include "restaurant.hpp"
#include "glouton.hpp"
void test_swap();
/**
 * fonction qui execute l'algorithm heuristic local
 * @param restos vecteur contenant tout les restaurant
 * @param N quantite maximal
 * @return vecteurs contenant la solution
*/
vector<Restaurant> start_heuristic(vector<Restaurant> restos, int N);
/**
 * fonction qui execute une iteration.
 * @param solution la solution actuel (sera modifier)
 * @param restos vecteur contenant les restos
 * @param N la quantite maximal
 * @return le nombre de modifications effectue a la solution actuel
 */
int heuristic_local(vector<Restaurant>& solution, vector<Restaurant> restos, int N);
/**
 * fonction qui remplace dans un vecteur le contenue d'un deuxieme par le contenue du troisieme
 * @param container le vecteur sur lequel onv eut effectuer le changement
 * @param old le vecteur contenant les element a enlever
 * @param current le vecteur qui contient les element a mettre
*/
void swap_vectors(vector<Restaurant> &container, vector<Restaurant> old, vector<Restaurant> current);
/**
 * fonction qui calcule la difference de la somme des quantite des restaurant dans les vecteur
 * @param old premier vecteur
 * @param current deuxieme vecteur
 * @return  >0 si qtty current > qtty old
*/
int compare_qtty(vector<Restaurant> old, vector<Restaurant> current);
/**
fonction qui calcule la difference de la somme des revenues des restaurant dans les vecteur
 * @param old premier vecteur
 * @param current deuxieme vecteur
 * @return  >0 si revenu current > revenu old
*/
int compare_revenue(vector<Restaurant> old, vector<Restaurant> current);
/**
 * fonction qui retourne les combinaise de 1 et de 2 du vecteur
 * 1C(restos.size) + 2C(vecteur.size)
 * @param restos le vecteur de restos
 * @return la liste de ttes les combinaisons
*/
vector<vector<Restaurant>> combinaison( vector<Restaurant> restos);

int calculer_qtty_disponible(vector<Restaurant> restos, int N);
bool is_in(const Restaurant resto, const vector<Restaurant> restos);
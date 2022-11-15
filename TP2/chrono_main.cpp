#include <iostream>
#include <string>
#include <dirent.h>
#include "chronometre.hpp"
#include <fstream>
#include <omp.h>
#include <unordered_map>
using namespace std;
int calculerRevenue(vector<Restaurant> solution)
{
    int revenue_total = 0;
    for (auto resto : solution)
    {
        revenue_total += resto.revenue;
    }
    cout << revenue_total;
    return revenue_total;
}
vector<Restaurant> readFile(string filename, int &capacity);
int main(int argc, char **argv)
{
    unordered_map<string, timed_algos> algorithms =
        {
            {"local", chrono_local},
            {"glouton", chrono_greedy},
            {"progdyn", chrono_progdyn}};
    DIR *directory;   // creating pointer of type dirent
    struct dirent *x; // pointer represent directory stream
    vector<string> filenames;
    bool result = false; // declaring string variable and assign it to false.
    if ((directory = opendir("./exemplaires")) != NULL)
    { // check if directory  open

        while ((x = readdir(directory)) != NULL)
        {
            filenames.push_back(x->d_name);
        }

        closedir(directory); // close directory....
    }
    else
    {
        cout << "wasnt opened" << endl;
    }
    ofstream outfile;
    outfile.open("stat.txt", std::ofstream::out);
    outfile << "nb_resto, time_greedy, time_progdyn, time_local, capacity, filename, revenue_greedy, revenue_progdyn, revenue_local" << endl;
    cout << "file count: " << filenames.size() << endl;
    /*/#pragma omp parralel for*/
    for (int i = 0; i < filenames.size(); ++i)
    {
        string name = "./exemplaires/" + filenames[i];
        cout << "starting file " << name << endl;
        int capacity;
        vector<Restaurant> restos = readFile(name, capacity);


        int64_t time_greedy=0, time_progdyn=0 , time_local = 0;
        int revenue_greedy=0 , revenue_progdyn =0 , revenue_local=0;
 
        // cout<<"starting greedy with N ="<<capacity << " vec_size = "<<restos.size()<<endl;
        auto solutionGreedy = algorithms["glouton"](restos, capacity, time_greedy);
        for (auto resto : solutionGreedy)
        {
            revenue_greedy += resto.revenue;
        }
        cout << endl;
        // cout<<"starting progdyn with N ="<<capacity<<" vec_size = "<<restos.size()<<endl;
        auto solutionDyn = algorithms["progdyn"](restos, capacity, time_progdyn);
        revenue_progdyn = 0;
        for (auto resto : solutionDyn)
        {
            revenue_progdyn += resto.revenue;
        }
        cout << "greedy :" << revenue_greedy << " prgdyn: " << revenue_progdyn << endl;

        // if(restos.size() < 10000){
        //     solution = algorithms[2](restos,capacity,time_local);
        //     revenue_local = calculerRevenue(solution);
        // }
        outfile << restos.size() << " " << time_greedy << " " << time_progdyn << " " << time_local << " " << capacity << " " << filenames[i] << " " << revenue_greedy << " " << revenue_progdyn << " " << revenue_local << endl;
    }
}

vector<Restaurant> readFile(string filename, int &capacity)
{
    vector<Restaurant> restos;
    ifstream input;
    input.open(filename);
    if (!input)
    {
        cout << "Can't find source file: \'" << filename << "'" << endl;
        return restos;
    }

    int n_resto = 0;
    int id, qtty, revenue;
    input >> n_resto;
    for (int i = 0; i < n_resto; ++i)
    {
        input >> id >> revenue >> qtty;
        restos.push_back(Restaurant(id, qtty, revenue));
    }
    input >> capacity;
    return restos;
}
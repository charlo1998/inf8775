#include <iostream>
#include <string>
#include <dirent.h>
#include "chronometre.hpp"
#include <fstream>
using namespace std;

vector<Restaurant> readFile(string filename, int &capacity);
int main(int argc, char **argv)
{
    timed_algos algorithms[] = 
    {
        chrono_greedy,
        chrono_progdyn,
        chrono_local
    };
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
    outfile <<"nb_resto, time_greedy, time_progdyn, time_local, capacity"<<endl;
    cout << "file count: "<<filenames.size()<<endl;
    //#pragma omp parralel for
    for (int i =0; i<filenames.size(); ++i)
    {
        string name ="./exemplaires/" + filenames[i];
        cout <<"starting file "<<name<<endl;
        int capacity;
        //cout <<"reading next file .... "<<endl<<endl;
        vector<Restaurant> restos = readFile( name, capacity);
        int64_t time_greedy, time_progdyn, time_local =0 ;
        vector<Restaurant> solution;
        //cout<<"starting greedy with N ="<<capacity << " vec_size = "<<restos.size()<<endl;
        solution = algorithms[0](restos,capacity,time_greedy);
        //cout<<"starting progdyn with N ="<<capacity<<" vec_size = "<<restos.size()<<endl;
        solution = algorithms[1](restos,capacity,time_progdyn);
        if(restos.size() < 10000){
            solution = algorithms[1](restos,capacity,time_local);
        }
        outfile << restos.size() <<" " << time_greedy<<" "<< time_progdyn<<" "<< time_local<< " "<<capacity<<endl;
    }
}

vector<Restaurant> readFile(string filename, int &capacity)
{
    vector<Restaurant> restos;
    ifstream input;
    input.open(filename);
    if (!input)
    {
        cout << "Can't find source file: \'" << filename <<"'"<< endl;
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
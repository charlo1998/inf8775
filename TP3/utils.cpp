#include <stdint.h>
#include <math.h>
#include <vector>
#include "municipalite.hpp"
#include <fstream>
int distance(const Municipalite& m1, const Municipalite &m2){
    return abs(m1.x - m2.x) + abs(m1.y - m2.y);
}
std::vector<Municipalite> read_input_data(const std::string& filename){
    std::vector<Municipalite> municipalities;
    std::ifstream input;
    input.open(filename);
    if (!input)
    {
        std::cout << "Can't find source file: \'" << filename << "'" << std::endl;
        return municipalities;
    }
    int width, height;
    input >> width >> height;
    for(int y =0; y<height;y++){
        for(int x=0; x<width ; ++x){
            int pop;
            input >> pop;
            Municipalite mun ={x,y,pop};
            municipalities.push_back(mun);
        }
    }
    return municipalities;
}
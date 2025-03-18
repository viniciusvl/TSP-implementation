#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "data.h"

struct Solution{
    Data & data = Data::getInstance();

    std::vector<int> CL;
    std::vector<int> route = {1, 1};
    double cost = 0;

    void initialSubTour();
    double CustoRota();
    void print();


};

#endif
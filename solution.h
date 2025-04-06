#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "data.h"

struct Solution{
    std::vector<int> route = {1, 1};
    double cost = 0;

    void initialSubTour(std::vector<int> &CL);
    double CustoRota();
    void print();
}; 

Solution Pertubacao(Solution s);

Solution Solve(int maxIter, int maxIterIls);



#endif
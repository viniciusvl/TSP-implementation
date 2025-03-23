#include "solution.h"
#include "data.h"
#include <iostream>

void Solution::CustoRota()
{
    Data &data = Data::getInstance();
    cost = 0;
    
    for (int i = 0; i < data.n - 1; i++){
        cost += data.matrizAdj[route[i]][route[i+1]];
    }
}

void Solution::print()
{
    Data &data = Data::getInstance();

    for (int i = 0; i < data.n; i++)
    {
        std::cout << route[i] << " - ";
    }
    
    std::cout << route[data.n] << '\n';
    std::cout << "Custo: " << cost << '\n';
}


#include "solution.h"
#include "data.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

double Solution::CustoRota()
{
    Data &data = Data::getInstance();
    double custo = 0;
    for (int i = 0; i < data.n - 1; i++){
        custo += data.matrizAdj[route[i]][route[i+1]];
    }

    return custo;
}

void Solution::print()
{
    Data &data = Data::getInstance();

    for (int i = 0; i < data.n - 1; i++)
    {
        std::cout << route[i] << " - ";
    }
    
    std::cout << route[data.n] << '\n';
    std::cout << "Custo: " << CustoRota();
}


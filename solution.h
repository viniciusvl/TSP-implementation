#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "data.h"

struct insertionInfo // guarda as informações de cada inserção feita 
{
    int k; // número a ser testado
    int aresta; // aresta a ser removida
    double cost; // custo da inserção
};

struct Solution{
    Data & data = Data::getInstance();

    std::vector<int> CL;
    std::vector<int> route = {1, 1};
    double cost = 0;

    void initialSubTour();
    double CustoRota();
};

Solution Construcao(); //retorna a primeira solucao básica tsp

#endif
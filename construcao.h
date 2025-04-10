#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include "solution.h"

struct insertionInfo // guarda as informações de cada inserção feita 
{
    int k; // número a ser testado
    int aresta; // aresta a ser removida
    double cost; // custo da inserção
};

Solution Construcao();

#endif
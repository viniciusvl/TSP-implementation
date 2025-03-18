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

std::vector<insertionInfo> CalcularCustos(Solution &s);

void AdicionaAresta(Solution &s, std::vector<insertionInfo> &custos);

bool comp_custos(const insertionInfo &a, const insertionInfo &b); //funcao para o sort

#endif
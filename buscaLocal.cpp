#include "buscaLocal.h"
#include "solution.h"
#include "data.h"
#include <vector>
#include <algorithm>
#include <iostream>

double Solution::custoSwap(int i, int j) //método do struct para ter acesso direto à rota
{
    Data &data = Data::getInstance();
    auto &m = data.matrizAdj;
    double pre_swap, pos_swap;

    // é necessario dividir entre calculo de adjacentes, pois pelo kit subtraimos os adjacentes duas vezes
    if (j == i+1) //verifica se sao adjacentes
    {
        pre_swap = m[route[i-1]][route[i]] + m[route[j]][route[j+1]];

        pos_swap = m[route[i-1]][route[j]] + m[route[i]][route[j+1]];
    }else
    {
        pre_swap = m[route[i-1]][route[i]] + m[route[i]][route[i+1]] 
                  + m[route[j-1]][route[j]] + m[route[j]][route[j+1]];

        //arcos apos swap: (i-1, j) (j, i+1) (j-1, i) (i, j+1)
        pos_swap = m[route[i-1]][route[j]] + m[route[j]][route[i+1]] 
                  + m[route[j-1]][route[i]] + m[route[i]][route[j+1]];
    }

    return pos_swap - pre_swap;
}

bool bestImprovementSwap(Solution &s)
{
    Data &data = Data::getInstance();
    auto &m = data.matrizAdj;

    int best_i, best_j; // salva o melhor indice para troca 
    double best_delta = 0;

    for (int i = 1; i < s.route.size() - 1; i++) //itera sobre cada cidade i da rota
    {
        for (int j = i + 1; j < s.route.size() - 1; j++) // itera cada possibilidade de i
        {
            double delta = s.custoSwap(i, j);
            if (delta < best_delta)
            {
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        }        
    }

    if (best_delta < 0) // só há melhora se (custo pós-swap - custo pré-swap) é negativo
    {
        std::swap(s.route[best_i], s.route[best_j]);
        s.cost += best_delta;
        return true;
    }else
    {
        return false;
    }
}

bool bestImprovement2opt(Solution &s)
{
    Data &data = Data::getInstance();
    auto &m = data.matrizAdj;

    int best_i, best_j; // salva o melhor indice para troca 
    double best_delta = 0;

    for (int i = 1; i < s.route.size() - 2; i++) //itera sobre cada cidade i da rota
    {
        for (int j = i + 1; j < s.route.size() - 1; j++) // itera cada possibilidade de i
        {
            double delta = s.custoSwap(i, j);
            if (delta < best_delta)
            {
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        }        
    }

    if (best_delta < 0) 
    {
        for (int i = best_i, j = best_j; i < j; i++, j--) //inverte o segmento i ate j
        {
            int aux = s.route[i];
            s.route[i] = s.route[j];
            s.route[j] = aux;
        }

        s.cost += best_delta;
        return true;
    }else
    {
        return false;
    }
}

void BuscaLocal(Solution &s)
{
}
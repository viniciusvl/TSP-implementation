#include "buscaLocal.h"
#include "solution.h"
#include "data.h"
#include <vector>
#include <algorithm>
#include <iostream>


bool bestImprovementeSwap(Solution &s)
{
    Data &data = Data::getInstance();
    auto &m = data.matrizAdj;

    int best_i, best_j; // salva o melhor indice para troca 
    double best_delta = 0;

    for (int i = 1; i < s.route.size() - 2; i++) //itera sobre cada cidade i da rota
    {
        std::cout << "Swap" << '\n';
        int vi = s.route[i]; 
        int vi_prev = s.route[i - 1];  
        int vi_next = s.route[i + 1]; 

        for (int j = i + 1; i < s.route.size() - 1; i++) // itera cada possibilidade de i
        {
            int vj = s.route[j];  
            int vj_prev = s.route[j - 1];
            int vj_next = s.route[j + 1];

            // calcula (custo pós swap - custo pré swap)
            double delta =  m[vi_prev][vj] + m[vj][vi_next] + m[vj_prev][vi] + m[vi][vj_next] 
                          - (m[vi_prev][vi] + m[vi][vi_next] + m[vj_prev][vj] + m[vj][vj_next]); 
        
            if (delta < best_delta)
            {
                best_i = i;
                best_j = j;
                best_delta = delta;
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


void BuscaLocal(Solution &s)
{
    
}
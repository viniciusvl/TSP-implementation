#include "buscaLocal.h"
#include "solution.h"
#include "data.h"
#include <vector>
#include <algorithm>


bool bestImprovementeSwap(Solution &s)
{
    Data &data = Data::getInstance();
    auto &m = data.matrizAdj;

    int best_i, best_j; // salva o melhor indice para troca 
    double best_delta = 0;

    for (int i = 1; i < s.route.size()-2; i++)
    {
        int vi = s.route[i]; 
        int vi_prev = s.route[i - 1]; // pega cidade anterior
        int vi_next = s.route[i + 1]; // pega cidade posterior

        for (int j = i + 1; i < s.route.size()-1; i++)
        {
            int vj = s.route[j];
            int vj_prev = s.route[j - 1];
            int vj_next = s.route[j + 1];

            double delta =  m[vi_prev][vj] + m[vj][vi_next] + m[vj_prev][vi] + m[vi][vj_next] 
                          - m[vi_prev][vi] - m[vi][vi_next] - m[vj_prev][vj] - m[vj][vj_next]; // calcula diferença do custo
        
            
        


        }        
    }



}


void BuscaLocal(Solution &s)
{

}
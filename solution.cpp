#include "solution.h"
#include "data.h"
#include "construcao.h"
#include "buscaLocal.h"
#include <iostream>
#include <cmath>
#include <set>

bool Duplicata(const std::vector<int>& vec) {
    std::set<int> elementos(vec.begin(), vec.end());

    return vec.size() - elementos.size();
}

double Solution::CustoRota()
{
    Data &data = Data::getInstance();
    double custo = 0;
    
    for (int i = 0; i < data.n; i++){
        custo += data.matrizAdj[route[i]][route[i+1]];
    }
    return custo;
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

void print(std::vector<int> &a)
{
    for (auto k: a)
    {
        std::cout << k << " ";
    }
    std::cout << '\n';
}

/*

    i = rand() % (s.route.size()/2 - 1) + 1; // retorna entre 1 e o elemento anterior ao valor do meio

    int soma_j = (s.route.size() - tam_j) - (i + tam_i); // retorna o numero aleatorio para adicionar em j APÓS i
    j = (i + tam_i) + (rand() % soma_j); // retorna o indice de j

*/


Solution Pertubacao(Solution s)
{
    Data &data = Data::getInstance();
    auto &m = data.matrizAdj;

    int max = ceil((float)14/10); // retorna o tamanho maximo do bloco
    int tam_i = rand() % (max - 1) + 2; // retorna valor entre 2 e max
    int tam_j = rand() % (max - 1) + 2; // retorna entre 2 e max
    int i, j;

    i = rand() % (s.route.size()/2 - 1) + 1; // retorna entre 1 e o elemento anterior ao valor do meio

    int soma_j = (s.route.size() - tam_j) - (i + tam_i); // retorna o numero aleatorio para adicionar em j APÓS i
    j = (i + tam_i) + (rand() % soma_j); // retorna o indice de j

    std::vector<int> copia_i(s.route.begin() + i, s.route.begin() + i + tam_i);
    std::vector<int> copia_j(s.route.begin() + j, s.route.begin() + j + tam_j);

    s.route.insert(s.route.begin() + i, copia_j.begin(), copia_j.end());
    s.route.erase(s.route.begin() + i+tam_j, s.route.begin() + i +tam_j+tam_i);
 
    s.route.insert(s.route.begin() + j, copia_i.begin(), copia_i.end());
    s.route.erase(s.route.begin() + j + tam_i, s.route.begin() + j + tam_i + tam_j);

    s.cost = s.CustoRota();

    return s;
}

Solution Solve(int maxIter, int maxIterIls)
{
    Solution bestOfAll;
    bestOfAll.cost = INFINITY;

    for (int i = 0; i < maxIter; i++)
    {
        Solution s = Construcao(); // constroi solucao inicial  
        Solution best = s;

        int iterIls = 0;

        while (iterIls <= maxIterIls)
        {
            BuscaLocal(s);
            if (s.cost < best.cost)            
            {
                best = s;
                iterIls = 0;
            }

            s = Pertubacao(best);

            iterIls++;
        }
        if (best.cost < bestOfAll.cost){
            bestOfAll = best;
        }
    }

    return bestOfAll;
}






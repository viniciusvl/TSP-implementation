#include "buscaLocal.h"
#include "solution.h"
#include "data.h"
#include <vector>
#include <algorithm>

double Solution::custoSwap(int i, int j) //calcula custos do 2 opt
{
    Data &data = Data::getInstance();
    auto &m = data.matrizAdj;
    double pre_swap, pos_swap;

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

double Solution::custoOrOpt(int i, int j, int bloco) // calcula o custo dos movimentos do OrOpt
{
    Data &data = Data::getInstance();
    auto &m = data.matrizAdj;

    double a_subtrair, a_somar;

    a_subtrair = m[route[i-1]][route[i]]
                + m[route[i + bloco - 1]][route[i + bloco]]    
                + m[route[j]][route[j+1]];                        

    a_somar = m[route[i - 1]][route[i + bloco]]
            + m[route[j]][route[i]]
            + m[route[i + bloco - 1]][route[j + 1]];

    return a_somar - a_subtrair;
}

bool bestImprovementSwap(Solution &s)
{
    int best_i, best_j; // salva o melhor indice para troca 
    double best_delta = 0, delta;

    for (int i = 1; i < s.route.size() - 2; i++) //itera sobre cada cidade i da rota
    {
        for (int j = i + 1; j < s.route.size() - 1; j++) // itera cada possibilidade de i
        {
            delta = s.custoSwap(i, j);
            
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

bool bestImprovementOrOpt(Solution &s, int bloco)
{
    double best_delta = 0;
    int best_insert, remove, best_i, valor;

    for (int i = 1; i < s.route.size() - bloco - 1; i++)
    {
        for (int j = 0; j < s.route.size() - 2; j++)
        {   
            if (i - 1 <= j && j <= i + bloco-1) 
                continue;

            double delta = s.custoOrOpt(i, j, bloco);

            if (delta < best_delta)
            {
                best_insert = j; // guarda qual melhor indice para adicionar
                best_i = i;
                remove = (j < i) ? i + bloco : i; // indice a remover 
                valor = s.route[i];
                best_delta = delta;
            }
        }
    }

    if (best_delta < 0)
    {
        std::vector<int> copia(s.route.begin() + best_i, s.route.begin() + best_i + bloco);

        s.route.insert(s.route.begin() + best_insert+1, copia.begin(), copia.end());
        s.route.erase(s.route.begin() + remove, s.route.begin() + remove + bloco);
        s.cost += best_delta;

        return true;
    }else{
        return false;
    }
}

void BuscaLocal(Solution &s)
{
    std::vector<int> NL = {1, 2, 3, 4, 5};
    int n;
    bool improved = false;

    while (!NL.empty())
    {
        n = rand() % NL.size(); 

        switch (NL[n]){
            case 1: 
                improved = bestImprovementSwap(s);
                break;
            case 2: 
                improved = bestImprovement2opt(s);
                break;
            case 3: 
                improved = bestImprovementSwap(s);
                break;
            case 4: 
                improved = bestImprovementOrOpt(s, 2);
                break;
            case 5: 
                improved = bestImprovementOrOpt(s, 3);
                break;
        }

        if (improved && NL.size() != 5)
        {
            NL = {1, 2, 3, 4, 5};
        }else if (improved == false){
            NL.erase(NL.begin() + n);
        }
    }
}


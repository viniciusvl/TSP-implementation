#include "solution.h"
#include "data.h"
#include "construcao.h"
#include <vector>
#include <algorithm>
#include <cmath>

void Solution::initialSubTour(std::vector<int> &CL) //constroi um subtour inicial aleatório
{
    Data &data = Data::getInstance();
    int indiceAleatorio;

    for (int i = 2; i <= data.n; i++){
        CL.push_back(i);
    }

    while (route.size() < 5){
        indiceAleatorio = rand() % CL.size();

        route.insert(route.begin()+1, CL[indiceAleatorio]);
        CL.erase(CL.begin()+indiceAleatorio);
    }
}

std::vector<insertionInfo> CalcularCustos(Solution &s, std::vector<int> &CL)
{
    Data &data = Data::getInstance();

    auto &mAdj = data.matrizAdj; 
    std::vector<insertionInfo> custosInsercoes(CL.size() * (s.route.size()-1)); //tamanho de possibilidades
    
    int l = 0; //itera no array de Structs
    for (int v = 0; v < (int)s.route.size()-1; v++)
    {
        int i = s.route[v]; //cidade analisada
        int j = s.route[v+1];

        for (auto k: CL)
        {
            custosInsercoes[l].cost = (mAdj[i][k] + mAdj[j][k]) - mAdj[i][j]; //custo de cada inserção
            custosInsercoes[l].aresta = v+1;
            custosInsercoes[l].k = k;

            l++;
        }
    }

    return custosInsercoes;
}

bool comp_custos(const insertionInfo &a, const insertionInfo &b) //funcao para o sort
{
    return a.cost < b.cost;
}

Solution Construcao()
{
    Solution s;
    double alfa;
    int i;

    std::vector<int> CL;
    s.initialSubTour(CL);

    while (!CL.empty())
    {  
        std::vector<insertionInfo> custosInsercao = CalcularCustos(s, CL); //array com todos os custos
        std::sort(custosInsercao.begin(), custosInsercao.end(), comp_custos); 
        
        alfa = 0.5;
        i = rand() % ((int) ceil(alfa * custosInsercao.size())); //indice aleatorio
    
        s.route.insert(s.route.begin() + custosInsercao[i].aresta, custosInsercao[i].k); //insere na rota
    
        auto itRemove = std::find(CL.begin(), CL.end(), custosInsercao[i].k); //encontra o indice
        CL.erase(itRemove); //exclui de CL
    }
    s.cost = s.CustoRota();

    return s;
}

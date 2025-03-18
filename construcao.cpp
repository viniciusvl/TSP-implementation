#include "solution.h"
#include "data.h"
#include "construcao.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

//:: para ter acesso aos atributos da classe
void Solution::initialSubTour() //constroi um subtour inicial aleatório
{
    Data &data = Data::getInstance();
    int indiceAleatorio;

    for (int i = 2; i <= data.n; i++){
        CL.push_back(i);
    }
    srand(time(NULL));

    while (route.size() < 5){
        indiceAleatorio = rand() % CL.size();

        route.insert(route.begin()+1, CL[indiceAleatorio]);
        CL.erase(CL.begin()+indiceAleatorio);
    }
}

std::vector<insertionInfo> CalcularCustos(Solution &s)
{
    Data &data = Data::getInstance();

    auto &mAdj = data.matrizAdj; 
    std::vector<insertionInfo> custosInsercoes(s.CL.size() * (s.route.size()-1)); //tamanho de possibilidas
    
    int l = 0; //itera no array de Structs
    for (int v = 0; v < (int)s.route.size()-1; v++)
    {
        int i = s.route[v]; //cidade analisada
        int j = s.route[v+1];

        for (auto k: s.CL)
        {
            custosInsercoes[l].cost = (mAdj[i][k] + mAdj[j][k]) - mAdj[i][j]; //custo de cada inserção
            custosInsercoes[l].aresta = v+1;
            custosInsercoes[l].k = k;

            l++;
        }
    }

    return custosInsercoes;
}

void AdicionaAresta(Solution &s, std::vector<insertionInfo> &custos)
{
    // alfa nao pode ser 0, ja que rand() % 0 é indefinido
    double alfa = (double)rand() / RAND_MAX; //RANDMAX é o maior vale que RAND() pode retornar
    int i = rand() % ((int) ceil(alfa * custos.size())); //indice aleatorio

    s.route.insert(s.route.begin() + custos[i].aresta, custos[i].k); //insere na rota

    auto itRemove = std::find(s.CL.begin(), s.CL.end(), custos[i].k); //encontra o indice
    s.CL.erase(itRemove); //exclui de CL
}

bool comp_custos(const insertionInfo &a, const insertionInfo &b) //funcao para o sort
{
    return a.cost < b.cost;
}

Solution Construcao()
{
    Solution s;
    s.initialSubTour();

    while (!s.CL.empty())
    {  
        std::vector<insertionInfo> custosInsercao = CalcularCustos(s); //array com todos os custos
        std::sort(custosInsercao.begin(), custosInsercao.end(), comp_custos); 
        AdicionaAresta(s, custosInsercao);
    }

    return s;
}

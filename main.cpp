#include "data.h"
#include "solution.h"
#include "construcao.h"
#include "buscaLocal.h"
#include <time.h>
#include <iostream>
#include <chrono>
#include <fstream>

int main(){
    std::ofstream custos("custos.txt", std::ios::app);
    std::ofstream tempo("tempo.txt", std::ios::app);

    char *argv[2];

    argv[0] = (char *) "TSP";
    argv[1] = (char *) "instancias/burma14.tsp";
    srand(time(NULL));

    Data & data = Data::getInstance();
    data.read(2, argv); 

    int maxIter, maxIterIls;
    maxIterIls = (data.n >= 150) ? data.n / 2 : data.n;
    maxIter = 50;

    auto start = std::chrono::steady_clock::now(); 
    Solution s = Solve(maxIter, maxIterIls);
    auto end = std::chrono::steady_clock::now();

    s.print();

    std::cout << "Custo corrigido: " << s.CustoRota() << '\n';

    auto elapsed = std::chrono::duration<double>{end-start}.count();
    std::cout << "Tempo: " << elapsed << '\n';
    custos << s.cost << '\n';
    tempo << elapsed << '\n';

    custos.close();
    tempo.close();


    return 0;
}
#include "data.h"
#include "solution.h"
#include "construcao.h"
#include "buscaLocal.h"
#include <time.h>
#include <iostream>
#include <chrono>

int main(){
    auto start = std::chrono::steady_clock::now();

    char *argv[2];

    argv[0] = (char *) "TSP";
    argv[1] = (char *) "instancias/eil101.tsp";
    srand(time(NULL));

    Data & data = Data::getInstance();
    data.read(2, argv); 

    int maxIter, maxIterIls;
    maxIterIls = (data.n >= 150) ? data.n / 2 : data.n;
    maxIter = 50;

    Solution s = Solve(maxIter, maxIterIls);
    auto end = std::chrono::steady_clock::now();
    s.print();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Duracaoo: " << elapsed.count() << " segundos\n";


    return 0;
}
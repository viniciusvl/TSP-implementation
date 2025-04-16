#include "data.h"
#include "solution.h"
#include "construcao.h"
#include "buscaLocal.h"
#include <time.h>
#include <iostream>

int main(){
    char *argv[2];

    argv[0] = (char *) "TSP";
    argv[1] = (char *) "instancias/CHOOSE_A_INSTANCE_HERE.tsp"; 
    srand(time(NULL));

    Data & data = Data::getInstance();
    data.read(2, argv); 

    int maxIterIls = (data.n >= 150) ? data.n / 2 : data.n;
    int maxIter = 50;

    Solution s = Solve(maxIter, maxIterIls);
    s.print();

    return 0;
}
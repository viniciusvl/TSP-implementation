#include "data.h"
#include "solution.h"
#include "construcao.h"
#include "buscaLocal.h"
#include <time.h>
#include <iostream>

int main(){
    char *argv[2];

    argv[0] = (char *) "TSP";
    argv[1] = (char *) "instancias/burma14.tsp";
    srand(time(NULL));

    Data & data = Data::getInstance();
    data.read(2, argv); 



    Solution s = Construcao();
    
    return 0;
}
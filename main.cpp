#include "data.h"
#include "solution.h"
#include "construcao.h"
#include <time.h>
#include <iostream>
#include <vector>

int main(){
    char *argv[2];

    argv[0] = (char *) "TSP";
    argv[1] = (char *) "instancias/burma14.tsp";
    srand(time(NULL));

    Data & data = Data::getInstance();
    data.read(2, argv); 

    Solution s = Construcao();
    s.print();
    
    return 0;
}
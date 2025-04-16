#include <iostream>
#include <fstream>
#include <iomanip>

int main(){
    std::ifstream custos("custos.txt");
    std::ifstream tempo("tempo.txt");
    std::ofstream benchmark("benchmark.txt", std::ios::app);

    double somaTempo = 0, somaCustos = 0;
    double x = 0;
    int count = 0;

    while (tempo >> x)
    {
        somaTempo += x;
        count++;
    }

    count = 0;
    while (custos >> x)
    {
        somaCustos += x;
        count++;
    }

    double mediaTempo = somaTempo / count;
    double mediaCusto = somaCustos / count;

    benchmark << "fl417: " << " tempo: " << mediaTempo << " custo: " <<  mediaCusto << '\n';



    return 0;
}
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "omp.h"
#include <chrono>
#include <fstream>



using namespace std;
using namespace std::chrono;

ofstream timeresult;
ofstream primeresult;
bool isPrime(int p){
    if (p<2) return false;
    for(int i=2; i<p; i++){
        if(p%i == 0){
            return false;
        }
    }
    return true;
}


int main(int argc, char const *argv[]){
    int n = atoi(argv[1]);
    int  limit = floor(sqrt(n));
    int *list = new int [n];
    int runs,run,threads;
     bool *marked = new bool[n];
    threads=atoi(argv[2]);
    timeresult.open ("bruteForceResult.txt",fstream::app);
    primeresult.open("bruteForceList.txt");
    auto beginParallelBrute = std::chrono::high_resolution_clock::now();
    
    int i,j;
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp for
        for(int i=2;i<n;i++){
            if(isPrime(i)) {
                primeresult<< i <<endl;
            }
        }
    }
    
    auto endParallelBrute = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(endParallelBrute - beginParallelBrute);
    timeresult <<duration.count()<< endl;    
    
    primeresult.close();
    timeresult.close();
    delete list;
    delete marked;
    return 0;
}
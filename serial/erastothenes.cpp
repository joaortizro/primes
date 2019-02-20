#include <iostream>
#include <cstdlib>
#include <math.h>
#include "omp.h"
#include <chrono>
#include <fstream>

typedef unsigned long long ULL;
using namespace std;
using namespace std::chrono;
ofstream primeresult;
ofstream timeresult;

void erastothenes_sieve(ULL  size, ULL* list, ULL* marked, ULL  limit){
    for ( ULL i =2;i<size;i++){
        list[i]=i;
        marked[i]=0;
    }
    for(ULL p=2;p<limit;p++){
        for(ULL multiple=2*p; multiple<size; multiple+=p){
            marked[multiple]=1;
        }    
    }
    for(ULL i=2;i<size;i++){
        if(marked[i]==0){
            primeresult<< list[i]<<endl;
        }
    }
}



int main(int argc, char **argv){
    primeresult.open("sieveList.txt");
    timeresult.open("sieveResult.txt",ios::out | ios::app );
    ULL  n=atoi(argv[1]);
    ULL  limit = floor(sqrt(n));
    ULL  *list = new ULL [n];
    ULL  *marked = new ULL [n];
    auto begin = std::chrono::high_resolution_clock::now();
    erastothenes_sieve(n,list,marked,limit);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(end - begin);
    timeresult<<duration.count()<<endl;
    delete list;
    delete marked;
    primeresult.close();
    timeresult.close();
    return 0;
}
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "omp.h"
#include <chrono>
#include <fstream>

typedef unsigned long long ULL;
using namespace std;
using namespace std::chrono;

ofstream list;
ofstream timeresult;
bool isPrime(ULL p){
    if (p<2) return false;
    for(ULL i=2; i<p; i++){
        if(p%i == 0){
            return false;
        }
    }
    return true;
}
void bruteforce(ULL n){
    for(ULL i=2;i<n;i++){
            if(isPrime(i)) list<< i <<endl;  
    }
}


int main(int argc, char **argv){
    list.open("bruteForceList.txt");
    timeresult.open("bruteForceResult.txt",ios::out | ios::app );
    ULL  n=atoi(argv[1]);
    auto begin = std::chrono::high_resolution_clock::now();
    bruteforce(n);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(end - begin);
    timeresult<<duration.count()<<endl;
    list.close();
    timeresult.close();
    return 0;
}
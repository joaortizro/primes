#include <iostream>
#include <cstdlib>
#include <math.h>
#include "omp.h"
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;
ofstream primeresult;
ofstream timeresult;

int main(int argc, char const *argv[]){

    int n =atoi(argv[1]);
    int  limit = floor(sqrt(n));
    int *list = new int [n];
    int runs,run,threads;
    bool *marked = new bool[n];

    threads=atoi(argv[2]);
    primeresult.open("sieveList.txt");
    timeresult.open("sieveResult.txt",ios::out | ios::app );

    auto begin = std::chrono::high_resolution_clock::now();
    int i,j,p,multiple;
    
    //#pragma omp parallel for num_threads(threads) schedule(dynamic) shared(list,marked) private (i)
    for (i =2;i<n;i++){
        list[i]=i;
        marked[i]=false;
    }

    #pragma omp parallel num_threads(threads) schedule(dynamic) //shared(marked) private(p,multiple)
    {
        #pragma omp for
        for(p=2;p<=limit;p++){
            for(multiple=2*p; multiple<n; multiple+=p){
                marked[multiple]=true;
            }    
        }
    }


    //#pragma omp parallel for num_threads(threads) shared(marked)
    for(int j=2;j<n;j++){
        if(marked[j]==false){
            //#pragma omp critical
                primeresult<< list[j]<<endl;
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(end - begin);
    timeresult<< duration.count()<< endl;
    primeresult.close();
    timeresult.close();
    delete list;
    delete marked;
    return 0;
}
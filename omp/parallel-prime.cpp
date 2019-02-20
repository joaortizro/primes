#include <iostream>
#include <cstdlib>
#include <math.h>
#include "omp.h"
#include <chrono>
#include <fstream>


#define n (int) 1e5
using namespace std;
using namespace std::chrono;

int  limit = floor(sqrt(n));
int list [n];
int runs,run,threads;
bool marked[n],print;
ofstream times;

bool isPrime(int p){
    if (p<2) return false;
    for(int i=2; i<p; i++){
        if(p%i == 0){
            return false;
        }
    }
    return true;
}

void erastothenes_sieve(){
    for (int i =2;i<n;i++){
        list[i]=i;
        marked[i]=false;
    }
    
    for(int p=2;p<limit;p++){
        for(int multiple=2*p; multiple<n; multiple+=p){
            marked[multiple]=true;
        }    
    }
    for(int i=2;i<n;i++){
            if(marked[i]==false){
                cout<< list[i]<<endl;
        }
    }
}
void bruteforce(){
    for(int i=2;i<n;i++){
            if(isPrime(i)) cout<< i <<endl;
    }
}



void parallel_erastothenes_sieve(){
    int multiple,i,j;
    #pragma omp parallel for num_threads(threads) shared(list,marked)
    for (i =2;i<n;i++){
        list[i]=i;
        marked[i]=false;
    }
    
    #pragma omp parallel for num_threads(threads) schedule(dynamic) private(multiple) shared(marked)
    for(int p=2;p<limit;p++){
        for(multiple=2*p; multiple<n; multiple+=p){
            marked[multiple]=true;
        }    
    }
    #pragma omp parallel for num_threads(threads) shared(marked)
    for(int j=2;j<n;j++){
        if(marked[j]==false){
            #pragma omp critical
                cout<< list[j]<<endl;
        }
    }
}


void parallel_bruteforce(){
    int i,j;
    #pragma omp parallel 
    {
        #pragma omp for
        for(int i=2;i<n;i++){
            if(isPrime(i)) {
                #pragma omp critical
                cout<< i <<endl;
            }
        }
    }


}
void timeBruteForce(){
    auto begin = std::chrono::high_resolution_clock::now();
    bruteforce();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(end - begin);
    cout<<"Finished Serial BF ms:"<<duration.count()<<endl;
    times <<run<<"\t"<<threads<<"\t"<<"Serial \t\tBF:"<<"\t\t"<< duration.count()<< endl;
}
void timeErastothenesSieve(){
    auto begin = std::chrono::high_resolution_clock::now();
    erastothenes_sieve();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(end - begin);
    cout<<"Finished Serial sieve ms:"<<duration.count()<<endl;
    times <<run<<"\t"<<threads<<"\t"<<"Serial \t\tSieve:"<< "\t" << duration.count()<< endl;
}
void timeParallelBruteForce(){
    auto beginParallelBrute = std::chrono::high_resolution_clock::now();
    parallel_bruteforce();
    auto endParallelBrute = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(endParallelBrute - beginParallelBrute);
    cout<<"Finished Parallelized BF ms:"<<duration.count()<<endl;
    times <<run<<"\t"<<threads<<"\t"<<"Parallel \tBF:"<<"\t\t"<< duration.count()<< endl;
}

void timeParallelErastothenesSieve(){
    auto beginParallelSieve = std::chrono::high_resolution_clock::now();
    parallel_erastothenes_sieve();
    auto endParallelSieve = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(endParallelSieve - beginParallelSieve);
    cout<<"Finished Parallelized Sieve ms:"<<duration.count()<<endl;
    times <<run<<"\t"<<threads<<"\t"<<"Parallel \tSieve:"<<"\t"<< duration.count()<< endl;
}
int main(int argc, char const *argv[]){
    runs=atoi(argv[1]);
    threads=atoi(argv[2]);
    times.open ("times.txt",fstream::app);

    for ( run=0; run<runs ; run++ ){
        timeBruteForce();
        
    }
    for ( run=0; run<runs ; run++ ){
        timeErastothenesSieve();
        
    }
    for ( run=0; run<runs ; run++ ){
        timeParallelBruteForce();
        
    }
    for ( run=0; run<runs ; run++ ){
        timeParallelErastothenesSieve();
    }
    times.close();
    return 0;
}
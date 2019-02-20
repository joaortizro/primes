#include <iostream>
#include <cstdlib>
#include <math.h>
#include "omp.h"
#include <chrono>



#define n (int) 1e6


using namespace std;
using namespace std::chrono;

int  limit = floor(sqrt(n));
int list [n];
bool marked[n];

bool isPrime(int p){
    if (p<2) return false;
    for(int i=2; i<p; i++){
        if(p%i == 0){
            return false;
        }
    }
    return true;
}
void bruteforce(){
    for(int i=2;i<n;i++){
            if(isPrime(i)) cout<< i <<endl;
    }
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





int main(int argc, char **argv){
    
    //erastothenes_sieve();
    auto beginBrute = std::chrono::high_resolution_clock::now();
    bruteforce();
    auto endBrute = std::chrono::high_resolution_clock::now();


}
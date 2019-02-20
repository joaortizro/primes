#include <iostream>
#include <cstdlib>
#include "omp.h"
#include <chrono>
#include <cassert>
#include <fstream>
using namespace std;
using namespace std::chrono;

int n,threads,runs,run;
int *a,*b,*c ,*d;
ofstream myfile;

void show(int *x){
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      cout<<x[i*n+j]<<"\t";
    }
    cout <<endl;
  }
  cout <<endl;
}

void check(){
    for(int i =0;i<n*n;i++)
        assert(c[i]==d[i]);
}
void initialize(int *x){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            x[i*n+j]= rand() % 100;
    }

  }
}

void initialize_all(){
    a = new int [n*n];
    b = new int [n*n];
    c = new int [n*n];
    d = new int [n*n];
    initialize(a);
    initialize(b);
    
}

void parallel(){
    int i,j,k;
     auto begin = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for num_threads(threads) collapse(2) private(i,j,k) shared(a,b,c)
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                for(k=0;k<n;k++){
                     c[i*n+j] += a[i*n+k] * b[k*n+j];
                }
            }
        }
    
     auto end = std::chrono::high_resolution_clock::now();

         
     auto duration = duration_cast<std::chrono::microseconds>(end - begin);

    myfile <<run<<"\t"<< n << "\t" << threads  << "\t"<<"Parallel:"<< duration.count() << endl;
    cout <<run<<"\t"<< n << "\t"<< threads << "\t"<<"Parallel:"<< duration.count()<< endl;
}

void serial(){
     auto begin = std::chrono::high_resolution_clock::now();
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            int aux = 0;
            for(int k=0;k<n;k++){
                    aux += a[i*n+k] * b[k*n+j];
            }
            d[i*n+j]=aux;
        }
    }
     auto end = std::chrono::high_resolution_clock::now();
    
     auto duration = duration_cast<std::chrono::microseconds>(end - begin);

    myfile <<run<<"\t"<< n << "\t"<< threads << "\t"<<"Serial:"<< duration.count()<< endl;
    cout <<run<<"\t"<< n << "\t"<< threads << "\t"<<"Serial:"<< duration.count()<< endl; 
}

int main(int argc, char const *argv[])
{

    
    myfile.open ("results.txt",fstream::app);
    
    n=atoi(argv[1]);
    threads=atoi(argv[2]);
    runs=atoi(argv[3]);
    
    for(run=0;run<runs;run++){
        initialize_all();
        serial();
        parallel();
        check();
    }
  
    

    delete a;
    delete b;
    delete c;
    delete d;

    myfile.close();
    return 0;
}

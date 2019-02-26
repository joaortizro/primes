#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <mpi.h>
#include <math.h>
#include <chrono>
#include <fstream>
typedef unsigned long long ULL;
using namespace std;
using namespace std::chrono;
ofstream primeresult;
ofstream timeresult;


int main(int argc, char **argv ) {
    int rank, size;
    
    ULL  n=atoi(argv[1]);
    auto begin= std::chrono::high_resolution_clock::now();
    ULL  *list = new ULL [n];    
    ULL  limit = floor(sqrt(n));
    //memset(list,0,n*sizeof(ULL));
    for(ULL i = 0;i<n;i++){
        list[i]=i;
    }
    list[0]=1;
    list[1]=1;
    primeresult.open("mpiSieveList.txt");
    timeresult.open("mpiSieveResult.txt",ios::out | ios::app );
    MPI_Init( &argc, &argv );
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int elements_per_block = floor(n/size);
    ULL low  = rank*elements_per_block;
    ULL high = (rank*elements_per_block)+elements_per_block;
    //printf("Hello  from process %d of %d split is %llu \n", rank, size, split );
    ULL *sub_list = new ULL[elements_per_block];
    vector<ULL> local_primes;
    
    
    
    MPI_Scatter(list,
                elements_per_block,
                MPI_LONG_LONG,  
                sub_list,   
                elements_per_block, 
                MPI_LONG_LONG,
                0,
                MPI_COMM_WORLD);
    MPI_Bcast(&limit,1,MPI_LONG_LONG,0,MPI_COMM_WORLD);
    printf("rank %d low %llu high %llu \n",rank,low,high);
    for(ULL p=2;p<=limit;p++){
        for(ULL multiple=2*p; multiple<high; multiple+=p){
            if(multiple>=low) sub_list[multiple % elements_per_block]=1; 
        }
    }

    for(ULL i =0;i<elements_per_block;i++){
        if(sub_list[i]!=1){
            //if (rank==3) printf("rank %d , prime %llu \n",rank,sub_list[i]);
            local_primes.push_back(sub_list[i]);
        }
    } 
    ULL *primes = NULL;
    if(rank==0){
         primes = new ULL[n];
         memset(primes,0,n*sizeof(ULL));
    }
    
    MPI_Gather( &local_primes[0], local_primes.size(), MPI_LONG_LONG, 
                &primes[0], local_primes.size(), MPI_LONG_LONG, 
                0, MPI_COMM_WORLD);
    

    delete sub_list;
    
    if(rank==0){
        auto end = std::chrono::high_resolution_clock::now();
        for (ULL i=0;i<n;i++){
            if(primes[i]!=0)
                primeresult<<primes[i]<<endl;
        }
        auto duration = duration_cast<std::chrono::microseconds>(end - begin);
        timeresult<<duration.count()<<endl;
        delete list;
        delete primes;
        primeresult.close();
        timeresult.close();
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize( );
    
return 0;
}
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <chrono>
#include <iomanip>
#include <fstream>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ULL;
ofstream primeresult;
ofstream timeresult;

__global__ void cuda_erastothenes_sieve (ULL *marked, ULL *limit, ULL *n, int *totalThreads) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    //printf("index %d,limit %llu , n %llu , totalThreads %d \n",index, *limit , *n , *totalThreads);
    //printf("block %d, thread %d \n", blockIdx.x, threadIdx.x);
    marked[0]=1;
    marked[1]=1;
    index=index+2;
    if(*totalThreads>*n || index >*limit){
        return ;
    }else if(*totalThreads ==1){
        for(ULL p=2;p<=*limit;p++){
            for(ULL multiple=2*p; multiple<*n; multiple+=p){
                marked[multiple]=1;
            }    
        }
    }
    else{
        //printf("index %d,limit %llu , n %llu , totalThreads %d \n",index, *limit , *n , *totalThreads);
        for(ULL p=index;p<=*limit;p+=*totalThreads){
                if(marked[p]==1 || p%2==0 && p>2) return;
                //printf("index %d , p%llu \n",index,p);
                for(ULL multiple=2*p; multiple<*n; multiple+=p){
                    //printf("multiple %llu \n",multiple);
                    marked[multiple]=1;
                }
        }
    }
    __syncthreads();
}


int main(int argc, char **argv){
    ULL size;
    ULL *list,*d_list,limit,*d_limit,*d_n,n;
    n=atoi(argv[1]);
    int threads=atoi(argv[2]);
    //int thread_per_block=atoi(argv[3]);
    int blocks= floor(n/threads);
    int totalThreads = threads;
    int *d_totalThreads; 
    primeresult.open("cudaSieveList.txt");
    timeresult.open("cudaSieveResult.txt",ios::out | ios::app );

    size = n*sizeof(ULL);
    limit = floor(sqrt(n));

    
    cudaMalloc((void**)&d_list,size);
    cudaMalloc((void**)&d_limit,sizeof(ULL));
    cudaMalloc((void**)&d_n,sizeof(ULL));
    cudaMalloc((void**)&d_totalThreads,sizeof(int));
    
    list = (ULL*) malloc(size);
 
    memset(list,0,size);
    cudaMemset(d_list, 0, size);

    cudaMemcpy(d_list           ,list           ,size           ,cudaMemcpyHostToDevice);
    cudaMemcpy(d_limit          ,&limit         ,sizeof(ULL)    ,cudaMemcpyHostToDevice);
    cudaMemcpy(d_n              ,&n             ,sizeof(ULL)    ,cudaMemcpyHostToDevice);
    cudaMemcpy(d_totalThreads   ,&totalThreads  ,sizeof(int)    ,cudaMemcpyHostToDevice);


    auto begin= std::chrono::high_resolution_clock::now();
    cuda_erastothenes_sieve<<<blocks,threads>>>(d_list,d_limit,d_n,d_totalThreads);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = duration_cast<std::chrono::microseconds>(end - begin);
    
    timeresult<<duration.count()<<endl;

    cudaMemcpy(list,d_list, size, cudaMemcpyDeviceToHost);

    cudaDeviceSynchronize();

    // check for error
    cudaError_t error = cudaGetLastError();
    if(error != cudaSuccess)
    {
      // print the CUDA error message and exit
      printf("CUDA error: %s\n", cudaGetErrorString(error));
      return 0;
    }
    
   for(ULL i=0;i<n;i++){
       if(list[i]==0){
            primeresult<<i<<endl;
            //cout<<i<<endl;
        };
    } 


    
    //cout<<duration.count()<<endl;

    free(list);
    cudaFree(d_list);
    cudaFree(d_limit);
    cudaFree(d_n);
    primeresult.close();
    timeresult.close();
    return 0;
}
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <mpi.h>
typedef unsigned long long ULL;
using namespace std;

int main(int argc, char **argv ) {
    int rank, size;
    ULL  n=atoi(argv[1]);
    ULL  *list = new ULL [n];
    MPI_Init( &argc, &argv );
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    getPrimes(&list);
    printf("Hello world from process %d of %d\n", rank, size );
    cout<<n<<endl;
    MPI_Finalize( );
    delete list;
return 0;
}
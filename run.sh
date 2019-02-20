#!/bin/bash
size=(16 32 64 128 512 1024)
th=(1 2 4 8 16)
runs=5
g++ omp_matrix.cpp -o omp -fopenmp
for s in ${size[*]} 
do
        for t in ${th[*]}
        do
            echo " N = " $s "Threads=" $t
            ./omp $s $t $runs
        done
done


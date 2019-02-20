#!/bin/bash
>times.txt
th=(1 2 4 8 16)
runs=1
g++ parallel-prime.cpp -o pprime -fopenmp

for t in ${th[*]}
        do
            echo "Threads=" $t
            ./pprime $runs $t 
done

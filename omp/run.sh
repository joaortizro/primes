#!/bin/bash
#size=($((2**4)) $((2**7)) $((2**10)) $((2**13)) $((2**16)) $((2**19)) $((2**21)) $((2**24)))
size=($((2**4)) $((2**5)) $((2**6)) $((2**7)) $((2**8)) $((2**9)) $((2**10)) $((2**11)) $((2**12)) $((2**13)) $((2**14)) $((2**15)) $((2**16)) $((2**17)) $((2**18)) $((2**19)) $((2**20)) )
th=(1 2 3 5 7 11 13 )
runs=5

rm -r sieveList.txt
rm -r sieveResult.txt
rm -r images/
mkdir images

g++ omp-sieve.cpp -o ompsieve -fopenmp
#g++ omp-bruteForce.cpp -o ompbrute -fopenmp

echo ${size[*]} >>sieveResult.txt
echo ${th[*]} >>sieveResult.txt
echo $runs >>sieveResult.txt

for s in ${size[*]}
do
    for t in ${th[*]}
    do
            for r in 1 2 3 4 5
            do
                echo "N" $s "Threads=" $t "run" $r
                ./ompsieve $s $t 
                #./ompbrute $s $t
            done
    done
done

python plot.py
#!/bin/bash
size=($((2**4)) $((2**5)) $((2**6)) $((2**7)) $((2**8)) $((2**9)) $((2**10)) $((2**11)) $((2**12)) $((2**13)) $((2**14)) $((2**15)) $((2**16)) $((2**17)) $((2**18)) $((2**19)) $((2**20)) )
runs=5

g++ brute.cpp -o brute
g++ erastothenes.cpp -o erastothenes


rm -r bruteForceList.txt
rm -r bruteForceResult.txt
rm -r sieveList.txt
rm -r sieveResult.txt
rm -r test.png

echo ${size[*]} >>bruteForceResult.txt
echo $runs >>bruteForceResult.txt
echo ${size[*]} >>sieveResult.txt
echo $runs >>sieveResult.txt

for s in ${size[*]} 
do
        for r in 1 2 3 4 5
        do
            echo " N = " $s " R = " $r
            ./brute $s
            ./erastothenes $s  
        done
done

python plot.py

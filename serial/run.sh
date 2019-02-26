#!/bin/bash
size=($((10**1)) $((10**2)) $((10**3)) $((10**4)) $((10**5)) $((10**6)))
runs=5

g++ brute.cpp -o brute
g++ erastothenes.cpp -o erastothenes

rm -r bruteForceList.txt
rm -r bruteForceResult.txt
rm -r sieveList.txt
rm -r sieveResult.txt


echo "size= "${size[*]} >>bruteForceResult.txt
echo "runs= "$runs >>bruteForceResult.txt
echo "size= "${size[*]} >>sieveResult.txt
echo "runs= "$runs >>sieveResult.txt

for s in ${size[*]} 
do
        for r in 1 2 3 4 5
        do
            echo " N = " $s " R = " $r
            ./brute $s
            ./erastothenes $s
        done
done


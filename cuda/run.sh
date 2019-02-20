#!/bin/bash
size=($((10**1)) $((10**2)) $((10**3)) $((10**4)) $((10**5)) $((10**6)) $((10**7)) $((10**8)) $((10**9)))
#size=($((10**6)) $((10**7)))
blocks=( $((2**0)) $((2**1)) $((2**3)) $((2**4)) $((2**5)) $((2**6)) $((2**7)))
threads_per_block=($((2**0)) $((2**1)) $((2**3)) $((2**4)) $((2**5)) $((2**6)) $((2**7)) $((2**8)) $((2**9)) $((2**10)))


nvcc cudaSieve.cu -o cudaSieve

rm -r cudaSieveList.txt
rm -r cudaSieveResult.txt



echo ${size[*]} >>cudaSieveResult.txt
echo ${blocks[*]} >>cudaSieveResult.txt
echo ${threads_per_block[*]} >>cudaSieveResult.txt

for s in ${size[*]} 
do
        for b in ${blocks[*]}
        do
            for t in ${threads_per_block[*]}
            do
                echo "N=" $s "Blocks=" $b "TPB=" $t
                ./cudaSieve $s $b $t
            done  
        done
done

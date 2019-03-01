#!/bin/bash
#size=($((10**1)) $((10**2)) $((10**3)) $((10**4)) $((10**5)) $((10**6)) $((10**7)))
size=($((2**4)) $((2**5)) $((2**6)) $((2**7)) $((2**8)) $((2**9)) $((2**10)) $((2**11)) $((2**12)) $((2**13)) $((2**14)) $((2**15)) $((2**16)) $((2**17)) $((2**18)) $((2**19)) $((2**20)) )
blocks=( $((2**0)) $((2**1)) $((2**2)) $((2**3)) $((2**4)) )
threads_per_block=($((2**0)) $((2**1)) $((2**3)) $((2**4)) $((2**5)) $((2**6)) $((2**7)) )


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

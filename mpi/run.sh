
size=($((10**1)) $((10**2)) $((10**3)) $((10**4)) $((10**5)) )
th=( $((2**0)) $((2**1)) $((2**2)) $((2**3)))
mpic++ sieve.cpp -o sieve

rm -r mpiSieveList.txt
rm -r mpiSieveResult.txt

echo ${size[*]} >>mpiSieveResult.txt
echo ${th[*]} >>mpiSieveResult.txt

for s in ${size[*]}
do
    for t in ${th[*]}
    do
        echo "N" $s "Threads=" $t
        mpirun -np $t --allow-run-as-root ./sieve $s
    done
done

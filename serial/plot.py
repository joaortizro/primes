import matplotlib.pyplot as plt
import numpy as np
with open('sieveResult.txt') as f:
    lines = f.read().splitlines() 
with open('bruteForceResult.txt')as b:
    linesBrute = b.read().splitlines()

size = np.asarray(lines[0].split(" "));
runs=  int(np.asarray(lines[1].split(" ")));
data=  np.asarray(lines[2:])
dataBrute= np.asarray(linesBrute[2:])

average={}
averageBrute={}
for s in range(len(size)):
    sum = 0.0 
    sumBrute = 0.0
    for r in range(runs):
        sum =sum + int(data[(r)+(runs*s)])
        sumBrute = sumBrute + int(dataBrute[(r)+(runs*s)])
    average[size[s]]=sum/runs
    averageBrute[size[s]]=sumBrute/runs

plt.plot(average.keys(),average.values(),'ro')
plt.plot(averageBrute.keys(),averageBrute.values(),'b+')
plt.title("Erastothenes Sieve Time vs N" , fontsize=16)
plt.xlabel("N")
plt.ylabel("Time (ms)")
plt.savefig("test.png")
plt.close()



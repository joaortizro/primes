import matplotlib.pyplot as plt
import numpy as np
import collections
with open('cudaSieveResult.txt') as f:
    lines = f.read().splitlines() 

size = np.asarray(lines[0].split(" "))[0];
threads= np.asarray(lines[1].split(" "));
data = np.asarray(lines[2:])

print size
print threads
print data

times=collections.OrderedDict()


for t in xrange(len(threads)):
    times[threads[t]]=data[t]


serial ={'8192': 3136.2, '1024': 453.4, '4096': 1482.2, '16': 51.4, '32': 66.2, '1048576': 319251.2, '2048': 900.6, '262144': 79059.6, '64': 94.6, '16384': 6929.2, '128': 109.2, '65536': 22535.8, '512': 250.4, '256': 176.8, '32768': 11407.4, '131072': 51058.4, '524288': 156171.0}
print times

plt.plot(times.keys(),times.values(),'ro--')
plt.title("Erastothenes Sieve Time vs Threads" , fontsize=16)
plt.xlabel("Threads")
plt.ylabel("Time (ms)")
plt.savefig(size+".png")
plt.close()

speed=collections.OrderedDict()

for t in times.keys():
    print serial[size] , times[t] 
    speed[t]=serial[size]/float(times[t])

plt.plot(speed.keys(),speed.values(),'ro--')
plt.title("Erastothenes Sieve Time vs Threads" , fontsize=16)
plt.xlabel("Threads")
plt.ylabel("Time (ms)")
plt.savefig(size+"-speed.png")
plt.close()




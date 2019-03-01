import matplotlib.pyplot as plt
import numpy as np
import collections
with open('mpiSieveResult.txt') as f:
    lines = f.read().splitlines() 


size    = np.asarray(lines[0].split(" "));
threads = np.asarray(lines[1].split(" "));
data    =  np.asarray(lines[2:]);

print data

times=collections.OrderedDict()
for s in range(len(size)):
    times[size[s]]=collections.OrderedDict()
    for t in range(len(threads)):
        index = t + s*len(threads)
        times[size[s]][threads[t]]=data[index]

for s in range(len(size)):
    x=times[size[s]].keys()
    y=times[size[s]].values()
    plt.plot(x,y,marker='o',linestyle='--')
    plt.legend()
    plt.title("N="+size[s])
    plt.savefig("images/"+str(size[s])+".png")



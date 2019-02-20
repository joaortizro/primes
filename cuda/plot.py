import matplotlib.pyplot as plt
import numpy as np
with open('cudaSieveResult.txt') as f:
    lines = f.read().splitlines() 

size = np.asarray(lines[0].split(" "));
blocks= np.asarray(lines[1].split(" "));
tpb = np.asarray(lines[2].split(" "));


data = np.asarray(lines[3:])
a=np.asarray(lines[3:3+len(tpb)])

for n in range(len(size)):
    for b in range(len(blocks)):
        for t in range (len(tpb)):
            plt.plot(tpb,data[n*b*t:len(tpb)+(b*t*n)],label="TPB="+tpb[t])
        plt.legend()
        plt.savefig(str(size[n])+"-"+str(blocks[b])+".png")
        plt.close()

#print data[0:11]
#print data[11:22]


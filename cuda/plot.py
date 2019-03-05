import matplotlib.pyplot as plt
import numpy as np
import collections
with open('cudaSieveResult.txt') as f:
    lines = f.read().splitlines() 

size = np.asarray(lines[0].split(" "));
blocks= np.asarray(lines[1].split(" "));
tpb = np.asarray(lines[2].split(" "));
data = np.asarray(lines[3:])


times=collections.OrderedDict()
for s in range(len(size)):
    times[size[s]]=collections.OrderedDict()
    for b in range (len(blocks)):
        times[size[s]][blocks[b]]=collections.OrderedDict()
        for t in range(len(tpb)):
            index = t + (b*len(tpb)) + s*((len(blocks)*len(tpb)))
            times[size[s]][blocks[b]][tpb[t]]=data[index]
            #print index



for s in range(len(size)):
    for b in range(len(blocks)):
        x=times[size[s]][blocks[b]].keys()
        y=times[size[s]][blocks[b]].values()
        plt.plot(x,y,label="B="+blocks[b],marker='o',linestyle='--')
        plt.legend()
        plt.title("N="+size[s]+"Blocks="+blocks[b])
        plt.savefig("images/"+str(size[s])+"-"+str(blocks[b])+".png")
    plt.clf()

###SPEED UP
serial={ 
        '1048576': 319251.2,  
        '256': 176.8, 
}

speed=collections.OrderedDict()
for k in serial:
    speed[k]=collections.OrderedDict()
    for b in range(len(blocks)):
        speed[k][blocks[b]]=collections.OrderedDict()
        for t in range(len(tpb)):
            speed[k][blocks[b]][tpb[t]]=serial[k]/float(times[k][blocks[b]][tpb[t]])
            plt.clf()
        x=speed[k][blocks[b]].keys()
        y=speed[k][blocks[b]].values()
        plt.plot(x,y,'--o');
        plt.xlabel("Hilos por Bloque");
        plt.ylabel("Speed up")
        plt.title("N="+k+"B="+blocks[b])
        plt.savefig("speed/"+k+"-"+str(blocks[b])+".png")
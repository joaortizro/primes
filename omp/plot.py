import matplotlib.pyplot as plt
import numpy as np
import collections
with open('sieveResult.txt') as f:
    lines = f.read().splitlines() 

with open('bruteForceResult.txt') as bf:
    linesBrute = bf.read().splitlines() 

size    = np.asarray(lines[0].split(" "));
threads = np.asarray(lines[1].split(" "));
runs    =  int(np.asarray(lines[2].split(" ")));
data    =  np.asarray(lines[3:])
dataBrute = np.asarray(linesBrute[3:])



average=collections.OrderedDict()
averageBrute=collections.OrderedDict()
for s in range(len(size)):
    average[size[s]]=collections.OrderedDict()
    averageBrute[size[s]]=collections.OrderedDict()
    for t in range(len(threads)):
        sum=0.0
        sumBrute=0.0
        for r in range(runs):
            index = r +((runs*(t+s)))
            sum = sum + int(data[index])
            sumBrute = sumBrute + int(dataBrute[index])
            #print size[s],index,data[index],sum
        #print size[s],average[size[s]]
        average[size[s]][threads[t]] = sum/runs
        averageBrute[size[s]][threads[t]] = sumBrute/runs
    
for s in range(len(size)):
    x=average[size[s]].keys()
    y=average[size[s]].values()
    xb=averageBrute[size[s]].keys()
    yb=averageBrute[size[s]].values()
    #print average[size[s]]
    #print size[s],average[size[s]].keys(), average[size[s]].values()
    plt.clf();
    plt.plot(x,y,'--o',label="N="+size[s]);
    plt.xlabel("Hilos");
    plt.ylabel("Tiempo");
    plt.tight_layout(rect=[0,0,0.75,1])
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5));
    #plt.plot(xb,yb,'b+');
    plt.title("N="+size[s]);
    plt.savefig("images/"+str(size[s])+".png")


######SPEED UP
serial={'8192': 3136.2, 
        '1024': 453.4, 
        '4096': 1482.2, 
        '16': 51.4, 
        '32': 66.2, 
        '1048576': 319251.2, 
        '2048': 900.6, 
        '262144': 79059.6, 
        '64': 94.6, 
        '16384': 6929.2, 
        '128': 109.2, 
        '65536': 22535.8, 
        '512': 250.4, 
        '256': 176.8, 
        '32768': 11407.4, 
        '131072': 51058.4, 
        '524288': 156171.0}

speed=collections.OrderedDict()
for k in serial:
    speed[k]=collections.OrderedDict()
    for t in range(len(threads)):
        speed[k][threads[t]]=serial[k]/float(average[k][threads[t]])
    plt.clf()
    plt.cla()
    x=speed[k].keys()
    y=speed[k].values()
    plt.xlabel("Hilos")
    plt.ylabel("speedUp")
    plt.title("N="+k)
    plt.plot(x,y,'--o',label="Speed Up para" + k);
    plt.savefig("speed/"+k+".png")

#print speed
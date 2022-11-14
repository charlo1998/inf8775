
import matplotlib.pyplot as plt
from numpy import log, poly1d, polyfit

nb_resto = []
greedy_time = []
progdyn_time = []
local_time = []
capacity = []
grouped_times = {}
################################
##      Reading files         ##
################################
with open("stat.txt", 'r') as input:
    input.readline()
    for line in input:
        data = line.split()
        n_resto = int(data[0])
        greedy  = int(data[1])
        progdyn = int(data[2])
        local   = int(data[3])
        cap     = int(data[4])
        nb_resto    .append(n_resto )
        greedy_time .append(greedy  )
        progdyn_time.append(progdyn )
        local_time  .append(local   )
        capacity    .append(cap     )
        if n_resto in grouped_times.keys():
            grouped_times[n_resto].append({"t" :greedy,"cap":cap})
        else :
            grouped_times[n_resto] = [{"t" :greedy,"cap":cap}]

for key,val in grouped_times.items():
    print(key)
    for v in val:
        print(v)
#########################################
###         Test pour glouton         ###
#########################################

# hypothese: taux de croissance de O(N^2)



plt.scatter([x["cap"] for x in grouped_times[10000]], [x["t"] for x in grouped_times[10000]] )
plt.show()
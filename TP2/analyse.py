
import matplotlib.pyplot as plt
from numpy import log, poly1d, polyfit

nb_resto = []
greedy_time = []
progdyn_time = []
local_time = []
capacity = []
densite = []
grouped_times = {}
revenue_greedy = []
revenue_progdyn = []
revenue_local = []
grouped_revenues = {}
################################
##      Reading files         ##
################################
with open("stat.txt", 'r') as input:
    input.readline()
    for line in input:
        data = line.split()
        n_resto = int(data[0])
        greedy = int(data[1]) /10e6
        progdyn = int(data[2])
        local = int(data[3])
        cap = int(data[4])
        dens = int(data[5].split("-")[2])
        rev_greedy =  int(data[6])
        rev_progdyn = int(data[7])
        rev_local =   int(data[8])
        nb_resto    .append(n_resto)
        greedy_time .append(greedy)
        progdyn_time.append(progdyn)
        local_time  .append(local)
        capacity    .append(cap)
        densite.append(dens)
        revenue_greedy  .append(rev_greedy)
        revenue_progdyn .append(rev_progdyn)
        revenue_local   .append(rev_local)
        key = f'{n_resto},{dens}'
        if key in grouped_times.keys():
            grouped_times[key].append(
                {"greedy": greedy, "progdyn": progdyn, "local": local})
            grouped_revenues[key].append({
                "greedy": rev_greedy, "progdyn": rev_progdyn, "local": rev_local
            })
        else:
            grouped_times[key] = [
                {"greedy": greedy, "progdyn": progdyn, "local": local}]
            grouped_revenues[key] = [{
                "greedy": rev_greedy, "progdyn": rev_progdyn, "local": rev_local
            }]

avg = {}
max_rev = {}
for key, values in grouped_times.items():
    if key not in avg.keys():
        avg[key] = {"greedy": 0, "progdyn": 0, "local": 0}
    for val in values:
        avg[key]["greedy"] += val["greedy"] / len(values)
        avg[key]["progdyn"] += val["progdyn"] / len(values)
        avg[key]["local"] += val["local"] / len(values)

for key, values in grouped_revenues.items():
    if key not in max_rev.keys():
        max_rev[key] = {"greedy": 0, "progdyn": 0, "local": 0}
    for val in values:
        max_rev[key]["greedy"]  = max(val["greedy"], max_rev[key]["greedy"])
        max_rev[key]["progdyn"] = max(val["progdyn"], max_rev[key]["progdyn"])
        max_rev[key]["local"]   = max(val["local"], max_rev[key]["local"])

for key, val in avg.items():
    print(f'{key} :')
    print(val)
#########################################
###         Test pour glouton         ###
#########################################

# hypothese: taux de croissance de O(N^2)

x_graph = []
y_greedy = []
y_graph =[]
for key,val in avg.items():
    x_graph.append(int(key.split(',')[0]))
    y_greedy.append(val["greedy"])
for i in range(len(nb_resto)):
    if densite[i] == 1000 :
        x_graph.append(nb_resto[i])
        y_graph.append(greedy_time[i])
plt.scatter([x["cap"] for x in grouped_times[1000]], [x["t"] for x in grouped_times[1000]] )
# plt.scatter(x_graph, y_greedy)
plt.show()

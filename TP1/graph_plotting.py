
import matplotlib.pyplot as plt
from numpy import poly1d, polyfit
  
# x axis values
x = []
y_brute = []
y_recur = []
y_seuil = []

with open('analyse.csv', 'r') as infile:
    infile.readline()
    for line in infile:
        nums= line.split(',')
        x.append(float(nums[0].strip()))
        y_brute.append(float(nums[1].strip())*1000)
        y_recur.append(float(nums[2].strip())*1000)
        y_seuil.append(float(nums[3].strip())*1000)


        
# setting up the graph
plt.xlabel('x - nombre de points (unite)')
plt.ylabel("y - temps d'execution (us)")
# plt.xscale('log')
# plt.yscale('log')

# plotting the points 
brute_points = plt.scatter(x, y_brute)
recursif_points = plt.scatter(x,y_recur)
seuil_points = plt.scatter(x,y_seuil)


#courbe tendance
brute_tendance = polyfit(x,y_brute, 2)
brute_func = poly1d(brute_tendance)
print(brute_func)
recursif_tendance = polyfit(x,y_recur,1)
recur_func = poly1d(recursif_tendance)
print(recur_func)
seuil_tendance = polyfit(x,y_seuil,1)
seuil_func = poly1d(seuil_tendance)
print(seuil_func)
plt.plot(x,brute_func(x), label = "tendance brute")
plt.plot(x,recur_func(x), label = "DpR sans seuil")
plt.plot(x,seuil_func(x), label = "DpR avec Seuil")
# plt.legend((brute_points, recursif_points,seuil_points),("force brute", "recursif sans seuil","recusrif avec seuil"), loc="upper left")
# giving a title to my graph
plt.title('Time usage per amount of points')
  
# function to show the plot
plt.show()
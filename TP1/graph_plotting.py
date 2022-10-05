
from cmath import log
import matplotlib.pyplot as plt
from numpy import poly1d, polyfit
  
# x axis values
x = []
y_brute = []
y_recur = []
y_seuil = []

#lire le fichier generer. 
with open('analyse.csv', 'r') as infile:
    #ignorer la premiere ligne
    infile.readline()
    for line in infile:
        nums= line.split(',')
        x.append(float(nums[0].strip()))
        # le facteur multiplicatif est pour transformer en us
        y_brute.append(float(nums[1].strip())*1000)
        y_recur.append(float(nums[2].strip())*1000)
        y_seuil.append(float(nums[3].strip())*1000)

y_degree2 = [absix**2 for absix in x ]
y_nlogn = [absix*log(absix) for absix in x ]
        
# setting up the graph
plt.xlabel('x - nombre de points (unite)')
plt.ylabel("y - temps d'execution (us)")
plt.xscale('log')
plt.yscale('log')

# plotting the points 
brute_points = plt.scatter(x, y_brute)
recursif_points = plt.scatter(x,y_recur)
seuil_points = plt.scatter(x,y_seuil)


#calcul des courbes
brute_tendance = polyfit(x,y_brute, 2)
brute_func = poly1d(brute_tendance)
print(brute_func)

recursif_tendance = polyfit(x,y_recur,2)
recur_func = poly1d(recursif_tendance)
print(recur_func)

seuil_tendance = polyfit(x,y_seuil,2)
seuil_func = poly1d(seuil_tendance)
print(seuil_func)

# plot it.
# plt.plot(x,brute_func(x), label = "tendance brute")
# plt.plot(x,recur_func(x), label = "DpR sans seuil")
# plt.plot(x,seuil_func(x), label = "DpR avec Seuil")
plt.plot(x,y_degree2, label = "croissance n^2 ")
plt.plot(x,y_nlogn, label = "croissance nlogn ")
plt.legend( loc="upper left")

# un beau petit titre
plt.title('Time usage per amount of points')

#afficher
plt.show()
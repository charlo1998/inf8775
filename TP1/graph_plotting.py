
from cmath import log
import matplotlib.pyplot as plt
from numpy import poly1d, polyfit, log
  
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
        
#-------------------------- tests de rapport ---------------------------------------
# setting up the graph
plt.figure()
plt.xlabel('x - nombre de points (unite)')
plt.ylabel("y - temps d'execution (ns)")
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

#-------------------------- tests de rapport ---------------------------------------
# setting up the graph
f = plt.figure()    
f, axes = plt.subplots(nrows = 1, ncols = 3, sharex=True, sharey = True)

# plotting the brute force
rapport = [y/x**2 for x,y in zip(x,y_brute)]
axes[0].scatter(x, rapport)
axes[0].set_xlabel('x - nombre de points (unite)')
axes[0].set_ylabel("y - consommation")
axes[0].set_title('force brute')
# plotting the recursif_points
rapport = [y/x**2 for x,y in zip(x,y_recur)]
axes[1].scatter(x, rapport)
axes[1].set_xlabel('x - nombre de points (unite)')
axes[1].set_ylabel("y - consommation")
axes[1].set_title('recursif')
# plotting the recursif_points
rapport = [y/x**2 for x,y in zip(x,y_seuil)]
axes[2].scatter(x, rapport)
axes[2].set_xlabel('x - nombre de points (unite)')
axes[2].set_ylabel("y - consommation")
axes[2].set_title('seuil')
plt.suptitle("Hypothèse: f(x) = 1/x^2")


# setting up the graph
f = plt.figure()  
f, axes = plt.subplots(nrows = 1, ncols = 2, sharex=True, sharey = True)

# plotting the recursif_points
rapport = [y//x/log(x) for x,y in zip(x,y_recur)]
axes[0].scatter(x, rapport)
axes[0].set_xlabel('x - nombre de points (unite)')
axes[0].set_ylabel("y - consommation")
axes[0].set_title('recursif')
# plotting the recursif_points
rapport = [y/x/log(x) for x,y in zip(x,y_seuil)]
axes[1].scatter(x, rapport)
axes[1].set_xlabel('x - nombre de points (unite)')
axes[1].set_ylabel("y - consommation")
axes[1].set_title('seuil')
plt.suptitle("Hypothèse: f(x) = 1/xlogx")

# plotting the brute force points
plt.figure() 
rapport = [y/x/log(x) for x,y in zip(x,y_brute)]
plt.scatter(x, rapport)
plt.xlabel('x - nombre de points (unite)')
plt.ylabel("y - consommation")
plt.title('force brute avec hypothèse: f(x) = 1/xlogx')




  
# function to show the plot

#afficher
plt.show()
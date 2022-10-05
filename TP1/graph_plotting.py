
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
        x.append(log(float(nums[0].strip())))
        # le facteur multiplicatif est pour transformer en us
        y_brute.append(log(float(nums[1].strip())))
        y_recur.append(log(float(nums[2].strip())))
        y_seuil.append(log(float(nums[3].strip())))

y_degree2 = [absix**2 for absix in x ]
y_nlogn = [absix*log(absix) for absix in x ]
        
#-------------------------- tests de rapport ---------------------------------------
# setting up the graph
plt.figure()
plt.xlabel('x - nombre de points (unite)')
plt.ylabel("y - temps d'execution (ns)")
# plt.xscale('log')
# plt.yscale('log')

# plotting the points 
brute_points = plt.scatter(x, y_brute)
recursif_points = plt.scatter(x,y_recur)
seuil_points = plt.scatter(x,y_seuil)


#calcul des courbes
brute_tendance = polyfit(x,y_brute, 1)
brute_func = poly1d(brute_tendance)

recursif_tendance = polyfit(x,y_recur,1)
recur_func = poly1d(recursif_tendance)

seuil_tendance = polyfit(x,y_seuil,1)
seuil_func = poly1d(seuil_tendance)


# plot it.
plt.plot(x,brute_func(x), label = f"tendance brute:{brute_func}",color="#9ed0f0")
plt.plot(x,recur_func(x), label = f"DpR sans seuil:{recur_func}", color="#c7a150")
plt.plot(x,seuil_func(x), label = f"DpR avec Seuil:{seuil_func}")
plt.legend( loc="upper left")

# un beau petit titre
plt.title('Test de Puissance')

#-------------------------- tests de rapport ---------------------------------------
# setting up the graph
plt.figure()
plt.xlabel('x - nombre de points (unite)')
plt.ylabel("y - consommation")
# plotting the points 
rapport = [y/x/x for y,x in zip(x,y_brute)]
brute_points = plt.scatter(x, rapport)
rapport2 = [y/x/log(x) for y,x in zip(x,y_brute)]
brute_points2 = plt.scatter(x, rapport2)
plt.legend(['hypothèse pour force brute: f(x) = 1/n^2', 'hypothèse pour force brute: f(x) = 1/nlogn'])
# giving a title to my graph
plt.title('test de rapport pour brute force')

plt.figure()
plt.xlabel('x - nombre de points (unite)')
plt.ylabel("y - consommation")
# plotting the points 

# giving a title to my graph
plt.title('hypothèse pour force brute: f(x) = 1/nlogn')



  
# function to show the plot

#afficher
plt.show()
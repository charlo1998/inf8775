
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
        y_brute.append(float(nums[1].strip()))
        y_recur.append(float(nums[2].strip()))
        y_seuil.append(float(nums[3].strip()))

y_degree2 = [absix**2 for absix in x ]
y_nlogn = [absix*log(absix) for absix in x ]
        
#-------------------------- tests de puissance ---------------------------------------
# setting up the graph
plt.xlabel('x - log(taille de l\'exemplaire)')
plt.ylabel("y - log(consommation)")

# plotting the points 
log_x = log(x)
log_y_brute = log(y_brute)
log_y_recur = log(y_recur)
log_y_seuil = log(y_seuil)
brute_points = plt.scatter(log_x, log_y_brute)
recursif_points = plt.scatter(log_x,log_y_recur)
seuil_points = plt.scatter(log_x,log_y_seuil)


#calcul des courbes
brute_tendance = polyfit(log_x,log_y_brute, 1)
brute_func = poly1d(brute_tendance)

recursif_tendance = polyfit(log_x,log_y_recur,1)
recur_func = poly1d(recursif_tendance)

seuil_tendance = polyfit(log_x,log_y_seuil,1)
seuil_func = poly1d(seuil_tendance)


# plot it.
plt.plot(log_x,brute_func(log_x), label = f"tendance brute:{brute_func}",color="#9ed0f0")
plt.plot(log_x,recur_func(log_x), label = f"DpR sans seuil:{recur_func}", color="#c7a150")
plt.plot(log_x,seuil_func(log_x), label = f"DpR avec Seuil:{seuil_func}")
plt.legend( loc="upper left")

# un beau petit titre
plt.title('Test de Puissance')

#-------------------------- tests de rapport ---------------------------------------
# setting up the graph
f = plt.figure()    
f, axes = plt.subplots(nrows = 1, ncols = 3, sharex=True, sharey = True)

# plotting the brute force
rapport = [y/x**2 for x,y in zip(x,y_brute)]
axes[0].scatter(x, rapport)
axes[0].set_xlabel('x - taille de l\'exemplaire')
axes[0].set_ylabel("y - consommation")
axes[0].set_title('force brute')
# plotting the recursif_points
rapport = [y/x**2 for x,y in zip(x,y_recur)]
axes[1].scatter(x, rapport)
axes[1].set_xlabel('x - taille de l\'exemplaire')
axes[1].set_ylabel("y - consommation")
axes[1].set_title('recursif')
# plotting the recursif_points
rapport = [y/x**2 for x,y in zip(x,y_seuil)]
axes[2].scatter(x, rapport)
axes[2].set_xlabel('x - taille de l\'exemplaire')
axes[2].set_ylabel("y - consommation")
axes[2].set_title('seuil')
plt.suptitle("Hypothèse: f(x) = 1/x^2")


# setting up the graph
f = plt.figure()  
f, axes = plt.subplots(nrows = 1, ncols = 2, sharex=True, sharey = True)

# plotting the recursif_points
rapport = [y//x/log(x) for x,y in zip(x,y_recur)]
axes[0].scatter(x, rapport)
axes[0].set_xlabel('x - taille de l\'exemplaire')
axes[0].set_ylabel("y - consommation")
axes[0].set_title('recursif')
# plotting the seuil_points
rapport = [y/x/log(x) for x,y in zip(x,y_seuil)]
axes[1].scatter(x, rapport)
axes[1].set_xlabel('x - taille de l\'exemplaire')
axes[1].set_ylabel("y - consommation")
axes[1].set_title('seuil')
plt.suptitle("Hypothèse: f(x) = 1/xlogx")

# plotting the brute force points
plt.figure() 
rapport = [y/x/log(x) for x,y in zip(x,y_brute)]
plt.scatter(x, rapport)
plt.xlabel('x - taille de l\'exemplaire')
plt.ylabel("y - consommation")
plt.title('force brute avec hypothèse: f(x) = 1/xlogx')

#-------------------------- tests des constantes ---------------------------------------

f_brute = [i*i for i in x] #hypothèse: force brute s'apparente à n^2
f_recur = [i*log(i) for i in x] #hypothèse: récursif s'apparente à nlog(n)
f_seuil = [i*log(i) for i in x] #hypothèse: récursif avec seuil s'apparente à nlog(n)

brute_tendance = polyfit(f_brute,y_brute, 1)
brute_func = poly1d(brute_tendance)

recursif_tendance = polyfit(f_recur,y_recur,1)
recur_func = poly1d(recursif_tendance)

seuil_tendance = polyfit(f_seuil,y_seuil,1)
seuil_func = poly1d(seuil_tendance)

# setting up the graph
f = plt.figure()  
f, axes = plt.subplots(nrows = 1, ncols = 2, sharex=True, sharey = True)

# plotting the recursif_points
axes[0].scatter(f_recur, y_recur)
axes[0].plot(f_recur, recur_func(f_recur), label = f"régression: {recur_func}",color="#9ed0f0")
axes[0].set_xlabel('x - f(taille de l\'exemplaire)')
axes[0].set_ylabel("y - consommation")
axes[0].set_title('récursif')
axes[0].legend()
# plotting the seuil_points
axes[1].scatter(f_seuil, y_seuil)
axes[1].plot(f_seuil, seuil_func(f_seuil), label = f"régression: {seuil_func}",color="#9ed0f0")
axes[1].set_xlabel('x - f(taille de l\'exemplaire)')
axes[1].set_ylabel("y - consommation")
axes[1].set_title('seuil')
axes[1].legend()
plt.suptitle("Test des constantes avec f(x) = xlog(x)")
#axes[0].set_xscale('log')
#axes[0].set_yscale('log')

# plotting the brute force points
plt.figure() 
plt.scatter(f_brute, y_brute)
plt.plot(f_brute, brute_func(f_brute), label = f"régression: {brute_func}",color="#9ed0f0")
plt.xlabel('x - f(taille de l\'exemplaire)')
plt.ylabel("y - consommation")
plt.title("Test des constantes - force brute avec f(x) = x^2")
plt.legend( loc="upper left")
#plt.xscale('log')
#plt.yscale('log')
  
# function to show the plot

#afficher
plt.show()
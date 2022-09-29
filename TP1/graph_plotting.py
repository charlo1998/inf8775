
import matplotlib.pyplot as plt
from numpy import poly1d, polyfit
  
# x axis values
x = [250,  1250, 6250, 31250,156250]
# corresponding y axis values
y_brute = [18003463.745117188,430096387.8631592,10510353326.797485,263434805631.6376,6582784409523.01]
y_recur = [1000165.9393310547 ,8000850.677490234,94021081.92443848,769171714.7827148,5304196357.727051]
y_seuil = [ 1000165.9393310547 , 6001472.473144531 , 60011863.708496094 , 582129716.873169 , 3918689012.527466]

# setting up the graph
plt.xlabel('x - nombre de points (unite)')
plt.ylabel("y - temps d'execution (us)")
plt.xscale('log')
plt.yscale('log')

# plotting the points 
brute_points = plt.scatter(x, y_brute)
recursif_points = plt.scatter(x,y_recur)
seuil_points = plt.scatter(x,y_seuil)


#courbe tendance
brute_tendance = polyfit(x,y_brute, 3)
brute_func = poly1d(brute_tendance)
print(brute_func)
recursif_tendance = polyfit(x,y_recur,3)
recur_func = poly1d(recursif_tendance)
print(recur_func)
seuil_tendance = polyfit(x,y_seuil,3)
seuil_func = poly1d(seuil_tendance)
print(seuil_func)
plt.plot(x,brute_func(x), label = "tendance brute")
plt.plot(x,recur_func(x), label = "DpR sans seuil")
plt.plot(x,seuil_func(x), label = "DpR avec Seuil")
plt.legend((brute_points, recursif_points,seuil_points),("force brute", "recursif sans seuil","recusrif avec seuil"), loc="upper left")
# giving a title to my graph
plt.title('Time usage per amount of points')
  
# function to show the plot
plt.show()
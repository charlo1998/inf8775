
import matplotlib.pyplot as plt
  
# x axis values
x = [10,50,  250,  1250, 6250, 31250,156250]
# corresponding y axis values
y_brute = [0.0,1.0013580322265625,18.003463745117188,430.0963878631592,10510.353326797485,263434.8056316376,6582784.40952301]
y_recur = [0.0,0.0,1.0001659393310547 ,8.000850677490234,94.02108192443848,769.1717147827148,5304.196357727051]
y_seuil = [ 0.0, 0.0, 1.0001659393310547 , 6.001472473144531 , 60.011863708496094 , 582.129716873169 , 3918.689012527466]
# plotting the points 
plt.plot(x, y_brute,"-r",label="brute force")
plt.plot(x,y_recur, "-b", label = "recursif sans seuil")
plt.plot(x,y_seuil, "-g", label = "recursif avec seuil")
  
# naming 
plt.xlabel('x - nombre de points (unite)')
plt.ylabel("y - temps d'execution (ms)")

plt.legend(loc="upper left")
# giving a title to my graph
plt.title('Time usage per amount of points')
  
# function to show the plot
plt.show()
import sys
from util import Point
import bruteforce
import DpR
import time
def fileToPointArray(filename):
    points = []
    with open(filename, 'r') as file:
        count = file.readline()
        for line in file:
            x,y = line.split()
            points.append(Point(int(x),int(y)))
    return points

SEUIL = 50
algos= {
    'brute':bruteforce.bruteforce,
    'recursif':DpR.DpR_sans_seuil,
    'seuil':DpR.DpR_avec_seuil
}

algo, filepath = '', '', 
distance_flag,time_flag=False, False

for i in range(len(sys.argv)):
    if sys.argv[i] == '-a':
        algo = sys.argv[i+1]
    if sys.argv[i] == '-e':
        filepath = sys.argv[i+1]
    if sys.argv[i] == '-p':
        distance_flag = True
    if sys.argv[i] =='-t':
        time_flag = True

if algo not in algos :
    print(f"algorithme inconnue, les algorithmes connues sont {algos.keys()}")
    sys.exit()
start_time = time.time()
distance = algos[algo](fileToPointArray(filepath))
time = time.time() - start_time

# output format

if distance_flag :
    print(distance)
    sys.exit()

if time_flag:
    print(time)
    sys.exit()

print(f"la distance la plus courte est {distance}.")
print(f"l'execution a pris un total de {time} seconde")

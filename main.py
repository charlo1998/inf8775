import sys
from util import Point
import bruteforce
import DpR
import time


def fileToPointArray(filename):
    '''
    Reads a data file and creates a list of points
    '''

    points = []
    with open(filename, 'r') as file:
        count = file.readline()
        for line in file:
            x,y = line.split()
            points.append(Point(int(x),int(y)))
    return points

algos= {
    'brute':bruteforce.bruteforce,
    'recursif':DpR.DpR_sans_seuil,
    'seuil':DpR.DpR_avec_seuil
}

algo, filepath = '', '', 
distance_flag,time_flag=False, False

#options parser
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
    print(f"algorithme inconnu, les algorithmes connus sont {algos.keys()}")
    sys.exit()

#lire le fichier de points
points = fileToPointArray(filepath)

#calculer la distance minimale en utilisant l'algorithme spécifié
start_time = time.time()
for i in range(50):
    distance = algos[algo](points)
duration = time.time() - start_time

# output format
if distance_flag :
    print(f"La distance la plus courte est {distance}.")

if time_flag:
    print(f"Le temps d'exécution est de {duration} secondes")

import math
from os import times
import time
from DpR import DpR_avec_seuil, DpR_sans_seuil
from bruteforce import bruteforce
from gen import generate
from util import fileToPointArray
NOMBRE_ECHANTILLONS = 11
# Nombre de point a la premiere generation
NOMBRE_POINTS_INIT = 20

# facteur entre 2 generation 
addition = 2

# contient les resultat sous la forme : 
# {key: nbr de poitns , value = [brute_force_time, DpR_time, DpR_seuil_time]}
results = {}
nb_points = NOMBRE_POINTS_INIT


for i in range(NOMBRE_ECHANTILLONS):
    print(f"\ngeneration de {nb_points} points")
    generate(nb_points, 'points.txt')
    points = fileToPointArray('points.txt')
    print('-----START-----')
    
    #brute force
    brute_time = time.perf_counter_ns()
    bruteforce(points)
    brute_time = time.perf_counter_ns() - brute_time
    print(f"force brute : {brute_time } ns")
    print('---------------')

    #DpR
    dpr_time = time.perf_counter_ns()
    DpR_sans_seuil(points)
    dpr_time = time.perf_counter_ns() - dpr_time
    print(f"DPR : {dpr_time } ns")
    print('---------------')

    #Dpr + seuil
    seuil_time = time.perf_counter_ns()
    DpR_avec_seuil(points)
    seuil_time = time.perf_counter_ns() - seuil_time
    print(f"dPR+SEUIL : {seuil_time} ns")
    print('---------------')

    results[nb_points] = [brute_time, dpr_time,seuil_time]
    print('-----DONE------')
    nb_points = addition * nb_points


#save in csv for escel manipulation

with open('analyse.csv', 'w') as outfile:
    outfile.write('nombre de points, force brute, DPR brute, DPR mixte\n')
    for key,timeList in results.items() :
        outfile.write(f'{key}, {timeList[0]}, {timeList[1]}, {timeList[2]}\n')

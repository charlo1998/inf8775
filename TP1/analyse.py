import math
from os import times
import time
from DpR import DpR_avec_seuil, DpR_sans_seuil
from bruteforce import bruteforce
from gen import generate
from util import fileToPointArray
NOMBRE_ECHANTILLONS = 50
# Nombre de point a la premiere generation
NOMBRE_POINTS_INIT = 150

# facteur entre 2 generation 
addition = 200

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
    brute_time = time.perf_counter()
    bruteforce(points)
    brute_time = time.perf_counter() - brute_time
    print(f"force brute : {brute_time * 1000} ms")
    print('---------------')

    #DpR
    dpr_time = time.perf_counter()
    DpR_sans_seuil(points)
    dpr_time = time.perf_counter() - dpr_time
    print(f"DPR : {dpr_time * 1000} ms")
    print('---------------')

    #Dpr + seuil
    seuil_time = time.perf_counter()
    DpR_avec_seuil(points)
    seuil_time = time.perf_counter() - seuil_time
    print(f"dPR+SEUIL : {seuil_time * 1000} ms")
    print('---------------')

    results[nb_points] = [brute_time*1000, dpr_time*1000,seuil_time*1000]
    print('-----DONE------')
    nb_points = addition + nb_points


#save in csv for escel manipulation

with open('analyse.csv', 'w') as outfile:
    outfile.write('nombre de points, force brute, DPR brute, DPR mixte\n')
    for key,timeList in results.items() :
        outfile.write(f'{key}, {timeList[0]}, {timeList[1]}, {timeList[2]}\n')

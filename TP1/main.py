import sys
from util import fileToPointArray
import bruteforce
import DpR
import time






def main():
    algos= {
        'brute':bruteforce.bruteforce,
        'recursif':DpR.DpR_sans_seuil,
        'seuil':DpR.DpR_avec_seuil
    }
    algo, filepath = '', '',
    distance_flag, time_flag = False, False

    # options parser
    for i in range(len(sys.argv)):
        if sys.argv[i] == '-a':
            algo = sys.argv[i+1]
        if sys.argv[i] == '-e':
            filepath = sys.argv[i+1]
        if sys.argv[i] == '-p':
            distance_flag = True
        if sys.argv[i] == '-t':
            time_flag = True

    if algo not in algos:
        print(
            f"algorithme inconnu, les algorithmes connus sont {algos.keys()}")
        sys.exit()

    # lire le fichier de points
    points = fileToPointArray(filepath)

    # calculer la distance minimale en utilisant l'algorithme spécifié
    start_time = time.time()
    distance = algos[algo](points)
    duration = time.time() - start_time

    # output format
    if distance_flag:
        print(distance)
    elif time_flag:
        print(duration)
    else:
        print(f"La distance la plus courte est {distance}.")
        print(f"Le temps d'exécution est de {duration} secondes.")
    return duration

if __name__ == "__main__":
    main()
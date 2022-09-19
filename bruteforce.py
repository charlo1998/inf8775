from math import sqrt
from util import euclidian, Point
import time


def bruteforce(points):
    '''
    Algorithme de force brute pour résoudre le problème.
    Un point est représenté par un typle (position_x, position_y).
    Les coordonnées des points sont compris entre 0 et 1,000,000.
    la distance entre chaque point est calculé et le minimum gardé en mémoire
    '''
    
    min = 2e6
    for i in range(len(points)):
        for j in range(i+1,len(points)):
            distance = euclidian(points[i],points[j])
            if ( distance< min):
                min = distance
    

    return sqrt(min)




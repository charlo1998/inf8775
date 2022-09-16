from math import sqrt
from util import euclidian, Point
import time


def bruteforce(points):
    min = 2e6
    for i in range(len(points)):
        for j in range(i+1,len(points)):
            distance = euclidian(points[i],points[j])
            if ( distance< min):
                min = distance
    return sqrt(min)




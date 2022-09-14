from math import sqrt
from util import euclidian, point
import time


def bruteforce(points):
    min = 2e6
    for i in range(len(points)):
        for j in range(i+1,len(points)):
            distance = euclidian(points[i],points[j])
            if ( distance< min):
                min = distance
    return sqrt(min)


if __name__ == "__main__":
    points = []
    with open("points.txt", 'r') as file:
        count = file.readline()
        for line in file:
            x,y = line.split()
            points.append(point(int(x),int(y)))
    start_time = time.time()
    print(bruteforce(points))
    delta_time = start_time - time.time()
    print(f'it took a total of {delta_time*1000} ms')

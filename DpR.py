import sys
import time
from bruteforce import bruteforce
from util import euclidian, Point
sys.setrecursionlimit(1500)


def find_min_strip(points_y, d):
    strip_min = d
    l = len(points_y)
    for pos, pt1 in enumerate(points_y):
        for pt2 in points_y[(pos+1):(min(l, pos+7))]:
            strip_min = min(strip_min, euclidian(pt1, pt2))
    return strip_min   



'''
Algorithme Diviser pour Régner pour résoudre le problème.
Un point est représenté par un typle (position_x, position_y).
Les coordonnées des points sont compris entre 0 et 1,000,000.
points_x contient la liste des points triés sur l'axe des abscisses.
points_y contient la liste des points triés sur l'axe des ordonnées.
seuil_recur est le seuil à partir duquel on utilie l'algo force brute.
'''
def DpR(points_x, points_y, seuil_recur = 2):

    nb_points = len(points_x)

    # Si le nombre de points est inférieur au seuil de récursivité, on change 
    # d'algorithme pour trouver la plus petite distance
    if nb_points <= seuil_recur:
        min_dist = bruteforce(points_x)
        return min_dist

    # On divise nos points en deux groupes, en fonction de leur abscisse
    # puis on cherche récursivement le minimum dans chaque groupe
    middle = nb_points // 2
    left_group_x = points_x[:middle]
    right_group_x = points_x[middle:]
    
    # middle_x correspond à l'abscisse du premier point du groupe de droite
    middle_x = points_x[middle].x

    # On sépare la liste triée selon y en deux groupes également
    left_group_y = []
    right_group_y = []
    for p in points_y:
        if p.x < middle_x:
            left_group_y.append(p)
        else:
            right_group_y.append(p)

    # On appelle récursivement l'algo Diviser pour Régner
    min_left = DpR(left_group_x, left_group_y, seuil_recur)
    min_right = DpR(right_group_x, right_group_y, seuil_recur)
    d = min(min_left, min_right)
    
    # On construit une bande verticale dans laquelle les points ont une abscisse à moins
    # d'une distance d de middle_x à gauche et à droite (d = distance minimale trouvée
    # dans le groupe de gauche et dans le groupe de droite)
    strip = [p for p in points_y if abs(p.x - middle_x) < d]
    min_strip = find_min_strip(strip, d)
    min_dist = min(d, min_strip)

    return min_dist

def DpR_sans_seuil(points):
    points_x = sorted(points, key=lambda x: x.x)
    points_y = sorted(points, key=lambda x: x.y)
    start_time = time.time()
    print(DpR(points_x, points_y))
    delta_time = start_time - time.time()
    print(f'it took a total of {delta_time*1000} ms')

def DpR_avec_seuil(points):
    # ToDo trouver le seuil optimal
    seuil = 25
    points_x = sorted(points, key=lambda x: x.x)
    points_y = sorted(points, key=lambda x: x.y)
    print(DpR(points_x, points_y, seuil))


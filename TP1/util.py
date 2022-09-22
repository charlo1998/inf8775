
def euclidian(p1,p2 ):
    return (p1.x-p2.x)**2 + (p1.y - p2.y)**2
class Point:
    def __init__(self,x,y):
        self.x = x
        self.y = y

def fileToPointArray(filename):
    '''
    Reads a data file and creates a list of points
    '''

    points = []
    with open(filename, 'r') as file:
        count = file.readline()
        for line in file:
            x, y = line.split()
            points.append(Point(int(x), int(y)))
    return points
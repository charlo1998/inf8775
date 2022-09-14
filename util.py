
def euclidian(p1,p2 ):
    return (p1.x-p2.x)**2 + (p1.y - p2.y)**2
class point:
    def __init__(self,x,y):
        self.x = x
        self.y = y
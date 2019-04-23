import DetectedType.py

class Obstacle(object):
    
    def __init__(self, xs, ys, t, h):
        self.x_start = xs
        self.y_start = ys
        self.x_end = xs
        self.y_end = ys
        self.__type = t
        self.height = h
        self.isFinished = False

    def isInObstacle(x, y):
        if not self.isFinished:
            return True

        inBounds_X = (x >= self.x_start and x <= self.x_end)
        inBounds_Y = (y >= self.y_start and y <= self.y_end)

        if inBounds_X and inBounds_Y:
            return True 

        return False

    def getType(): 
        return self.__type
    
    def getWidth():
        return (self.y_end - self.y_start)
    
    def getLength():
        return (self.x_end - self.x_start)

    def getPosition_x():
        return self.x_start

    def getPosition_y():
        return self.y_start
        
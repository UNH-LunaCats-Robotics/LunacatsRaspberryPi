import LinkedList.py

class ObstacleManager(object):
    def __init__(self):
        self.obstacleList = LinkedList(None, None, None)
        self.count = 0
            
    def insertObstacle(obs, alist):
        if alist.obstacle.y > obs.y:
            if alist.next == None:
                alist.next = LinkedList(obs, alist, None)
                self.count += 1
            else:
                insertObstacle(obs, alist.next)
        else:
            prevNext = alist.next
            if alist.prev == None:
                prevObs = alist.obstacle
                alist.obstacle = obs
                alist.next = LinkedList(prevObs, prevNext)
                self.count += 1
            else:
                alist.prev.next = LinkedList(obs, alist.prev, alist)
                self.count += 1
                
    def insertObstacle(obs):
        if self.obstacleList.obstacle == None:
            self.obstacleList.obstacle = obs
            self.count += 1
        else:
            insertObstacle(obs, self.obstacleList)

    def getPossibleObstacle(DetectedType, y, x, alist):
        if alist == None:
            return None
        if alist.obstacle == None:
            return None

        inBounds_X = (x >= alist.obstacle.x_start and x <= alist.obstacle.x_end)
        inBounds_Y = (y >= alist.obstacle.y_start and y <= alist.obstacle.y_end)

        if inBounds_X and inBounds_Y and DetectedType == alist.obstacle.type:
            return alist.obstacle
            
        return isAlreadyObstacle(DetectedType, y, alist.next)

    def getPossibleObstacle(DetectedType, y, x):
        if self.count == 0:
            return None
        else: 
            return isAlreadyObstacle(DetectedType, y, x, self.obstacleList)



    
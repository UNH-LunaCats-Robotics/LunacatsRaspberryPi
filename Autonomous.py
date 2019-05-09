from RobotCommunication import *
import GetPixyInfo
from time import sleep
import json



# The height that the picture should be at the target position
miningZoneDistance = 3
miningZoneXOffset = 100


# The height that the picture should be at the target position
depositBoxDistance = 0.8
depositBoxXOffset = 50


# The allowed variation for the height
heightVary = 0.3
OffsetVary = 25


LidarObstacleDistance = 30
LidarHoleDistance     = 70

def getLidarFL():
    return 50

def getLidarFR():
    return 50

def getLidarBL():
    return 50

def getLidarBR():
    return 50




def faceTarget(angle,target):
    if angle - 50 > target:
        right(15)
        return False

    elif angle + 50 < target:
        left(15)
        return False

    return True

def goForward():
    if getLidarFL() > LidarHoleDistance or getLidarFR() < LidarObstacleDistance:
        goLeft()
        sleep(1.7)

        goForward()

        goRight()
        sleep(1.7)

        goForward()
    else:
        sendMessage({"c":0})


def goBack():
    if getLidarFL() > LidarHoleDistance or getLidarFR() < LidarObstacleDistance:
        goLeft()
        sleep(1.7)

        goForward()

        goRight()
        sleep(1.7)

        goBack()
    else:
        sendMessage({"c":1})

def goLeft():
    sendMessage({"c":2})
def goRight():
    sendMessage({"c":3})

def holdPos():
    sendMessage({"c":4})

def raiseFrame():
    sendMessage({"c":11})
def lowerFrame():
    sendMessage({"c":10})

def depositMaterials():
    sendMessage({"c":14})

def processHeight(processHeight):

    height = GetPixyInfo.getDistance(findBin())
    print "Height At:" + str(height)

    if height > processHeight + heightVary:
        goBack()
    elif height < processHeight - heightVary:
        goForward()
    else:
        holdPos()
        return True
    return False
        

def processWidth(processWidth):
    width = data["W"]

    if width > posWidth + widthVary:
        goLeft()
    elif width < posWidth - widthVary:
        goRight()
    else:
        holdPos()


def findBin():
    print "Finding Bin"
    allData = GetPixyInfo.getGoodSig();
    while len(allData) == 0:
            goLeft()
            allData = GetPixyInfo.getGoodSig()
    return allData[0]



def goToPos(positionHeight):

    findBin()

    while not processHeight(positionHeight):
        sleep(0.1)
        findBin()
    holdPos()


def driveToMiningZone():
    print "Driving To Mining Zone"
    goToPos(miningZoneDistance)
    
def mineAtMiningZone():
    print "Mining At Mining Zone"
    raiseFrame()
    sleep(12)
    holdPos()
    sleep(5)
    lowerFrame()
    sleep(12)
    holdPos()

def returnToBox():
    print "Driving Back from Mining Zone"
    goToPos(depositBoxDistance)

def Deposit():
    print "Depositing"

    goRight()
    sleep(1.7)

    goBack()
    sleep(2)

    goLeft()
    sleep(1.7)

    goBack()
    sleep(2.5)

    goLeft()
    sleep(1.7)
    
    goBack()
    sleep(1)

    holdPos()
    depositMaterials()
    sleep(15)

def backToPlack():
    print "Driving Back To see Plaquard"

    holdPos()
    goForward()
    sleep(1)

    goRight()
    sleep(1.7)

    goForward()
    sleep(2.5)

    goRight()
    sleep(1.7)

    goForward()
    sleep(2)

    goLeft()
    sleep(1.7)

if __name__ == '__main__':
    print "Starting Autonomous Operation"
    GetPixyInfo.startup()

    while True:
        driveToMiningZone()
        mineAtMiningZone()
        returnToBox()
        Deposit()
        backToPlack()

    # GetPixyInfo.startup()

    # while mode == "Drive":
    #     allData = GetPixyInfo.getGoodSig();
        
    #     if len(allData) == 0:
    #         goLeft()
    #         continue
        
    #     data = allData[0]

    #     if processHeight(data):
    #         mode = "Dig"
    
    # if mode == "Dig":
    #     raiseFrame()
    #     sleep(15)
    #     holdPos()





        # if data["S"] == 1 and atGoodHeight:
        #     processWidth(data, i,data["A"])


        sleep(0.2)
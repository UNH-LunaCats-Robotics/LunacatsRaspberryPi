from RobotCommunication import *
import GetPixyInfo
from time import sleep
import json



# The height that the picture should be at the target position
miningZoneHeight = 30
miningZoneWidth  = 20

# The height that the picture should be at the target position
depositBoxHeight = 60
depositBoxWidth  = 45


# The allowed variation for the height
heightVary = 5
widthVary = 5;




def faceTarget(angle,target):
    if angle - 50 > target:
        right(15)
        return False
    elif angle + 50 < target:
        left(15)
        return False
    return True

def goForward():
    sendMessage({"c":0})
def goBack():
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

    data = findBin()
    height = data["H"]

    if height > processHeight + heightVary:
        goForward()
    elif height < processHeight - heightVary:
        goBack()
    else:
        holdPos()
        return True
        

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
            sleep(0.1)
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
    goToPos(miningZoneHeight)
    
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
    goToPos(depositBoxHeight)

def Deposit():
    print "Depositing"

    goRight()
    sleep(1.7)

    goBack()
    sleep(2)

    goLeft()
    sleep(1.7)

    goBack()
    sleep(3.5)

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
    sleep(3.5)

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
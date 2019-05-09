from RobotCommunication import *
import GetPixyInfo
from time import sleep
import json



# The height that the picture should be at the target position
posHeight = 200
posWidth  = 30

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

def processHeight(data):
    height = data["H"]

    if height > posHeight + heightVary:
        goForward()
    elif height < posHeight - heightVary:
        goBack()
    else:
        holdPos()
        

def processWidth(data):
    width = data["W"]

    if width > posWidth + widthVary:
        goLeft()
    elif width < posWidth - widthVary:
        goRight()
    else:
        holdPos()





if __name__ == '__main__':

    GetPixyInfo.startup()

    while True:
        allData = GetPixyInfo.getGoodSig();
        
        if len(allData) == 0:
            goLeft()
            continue
        
        data = allData[0]

        if data["S"] == 1:
            processHeight(data)
        # if data["S"] == 1 and atGoodHeight:
        #     processWidth(data, i,data["A"])


        sleep(0.2)
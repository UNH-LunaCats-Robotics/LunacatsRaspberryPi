from RobotCommunication import *
#from PixyFollowSig import *

# from time import sleep
import json

# The height that the picture should be at the target position
posHeight = 60
posWidth = 30

# The allowed variation for the height
heightVary = 20
widthVary = 5

lidarDistance = 0
objectDetected = False
atGoodHeight = False

taskInput = ""

def performAction(action, args):
    global taskInput
    if taskInput != "S":
        action(args)
        return False
    return True


def terminTask():
    global taskInput
    while taskInput != "S":
        taskInput = raw_input("Input")


def faceTarget(angle, target):
    print "Facing Target"
    return True


def goForward(angle):
    global lidarDistance
    global objectDetected

    print "Going Forward:" + str(angle)


def goBack(angle):
    print "Going Back:" + str(angle)


def goLeft(angle):
    print "Going Left"


def goRight(angle):
    print "Going Right"


def holdPos():
    stop()
    print "Holding Position"


def processHeight(data, i, angle):
    global atGoodHeight
    height = data["H" + str(i)]

    objectDetected = False
    # print "getting Height:" + str(height)

    if height > posHeight + heightVary:
        goBack(angle)
        atGoodHeight = False
    elif height < posHeight - heightVary:
        goForward(angle)
        atGoodHeight = False
    else:
        atGoodHeight = True


def processWidth(data, i, angle):
    width = data["W" + str(i)]
    # print "getting Width:" + str(width)

    if width > posWidth + widthVary:
        goLeft(angle)
    elif width < posWidth - widthVary:
        goRight(angle)
    else:
        holdPos()


def getAutonStatus():
    global taskInput
    return taskInput


def stopAutonomous():
    global taskInput
    taskInput = False


def runAutonomous():
    global taskInput,objectDetected
    taskInput = True

    while getAutonStatus():
        # PixyFollowSig.track()

        #dataString = PixyFollowSig.getSig()
        #data = json.loads(dataString)

        if objectDetected:
            print "Object Detected!!!!!"
            performAction(back, (15))
            # back(15)
            performAction(sleep, 0.5)
            performAction(left, 15)
            performAction(sleep, 2)
            performAction(forward, 15)
            performAction(sleep, 1.5)
            objectDetected = False
            print "Object evaded!"
        # if data["C"] == 0:
        #    stop()
        else:
            print "Processing Data!"

            # for i in range(0,data["C"]):
            #     if data["S"+str(i)] == 1:
            #         processHeight(data,i,data["A"])
            #     if data["S" + str(i)] == 1 and atGoodHeight:
            #         processWidth(data, i,data["A"])

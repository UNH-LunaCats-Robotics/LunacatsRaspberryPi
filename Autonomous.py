from RobotCommunication import *
import GetPixyInfo

from time import sleep


runAutonomous = False

def forward(angle):
    global lidarDistance
    global objectDetected

    print ("Going Forward:" + str(angle))


def back(angle):
    print ("Going Back:" + str(angle))


def left(angle):
    print ("Going Left")


def right(angle):
    print ("Going Right")

def stop(angle):
    print ("Stopping")



def getAutonStatus():
    global runAutonomous
    return runAutonomous


def stopAutonomous():
    global runAutonomous
    runAutonomous = False


def runAutonomous():
    global runAutonomous,objectDetected
    runAutonomous = True

    while getAutonStatus():
        pixyInfo = GetPixyInfo.getSig()

        if pixyInfo["C"] > 0:
            print ("I SEE SOMETHING!!!!!")
        else:
            print ("I see Nothing...")
            turnCount = 5
            turnAngle = 5
            sleepTime = 2
            foundBoard = False
            for i in range(turnCount):
                left(turnAngle)
                sleep(sleepTime)
                pixyInfo = GetPixyInfo.getSig()
                if pixyInfo["C"] > 0:
                    print ("I SEE SOMETHING!!!!!")
                    foundBoard = True
                    break
            if not foundBoard:
                right(turnAngle*turnCount)
                sleep(sleepTime*turnCount)
                for i in range(turnCount):
                    right(turnAngle)
                    sleep(sleepTime)
                    pixyInfo = GetPixyInfo.getSig()
                    if pixyInfo["C"] > 0:
                        print ("I SEE SOMETHING!!!!!")
                        foundBoard = True
                        break

            

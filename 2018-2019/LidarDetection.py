from __future__ import division
'''
#-----------------!!NOTICE!!-----------------#

The robot capacitor is hooked up the same way 
as described in the other lidar test files. 

Be careful of touching wires, the negative lead
touched the capacitor and caused the other wires
near by to melt together. 

This file takes an average value of the four lidars 

PLEASE READ, values inside the DIGITALOUTPUTDEVICE is the
GPIO pin numbers, NOT actual pin number!! (i.e.
GPIO 26 = pin 37
GPIO 19 = pin 35
GPIO 13 = pin 33
GPIO  6 = pin 31
)

#--------------------------------------------#
'''
from lidar_lite import Lidar_Lite
from time import sleep
from gpiozero import DigitalOutputDevice 
from threading import Thread

lidarController = [DigitalOutputDevice(26), 
                   DigitalOutputDevice(19),
                   DigitalOutputDevice(13),
                   DigitalOutputDevice(6) ]

#numbers gathered from experimental data
floorValue = [72, 38, 43, 33]

detectObjects = [False, False, False, False]

offset = 25

lidar = Lidar_Lite()

connected = lidar.connect(1)

if connected < -1:
  print("Not Connected")

#fl 0
#fr 2
#br 3
#bl 1
def checkLidar_FR():
    global detectObjects
    return detectObjects[2]

def checkLidar_FL():
    global detectObjects
    return detectObjects[0]

def checkLidar_BR():
    global detectObjects
    return detectObjects[3]

def checkLidar_BL():
    global detectObjects
    return detectObjects[1]

def runLidarDetection(): 
    for i in range(0,4):
        if i == 0:
            lidarController[3].off()
        else:
            lidarController[i-1].off()
        lidarController[i].on()
        print( str(i) + " " + str(lidarController[i].value) )
        
        j = 0
        while j != 20: 
            try:
                dist = lidar.getDistance()
                #print("Distance: "+ str(i) + " " + str(dist))
                if dist >= (floorValue[i] + offset) or dist <= (floorValue[i] - offset):
                    detectObjects[i] = True
                    #sleep(0.5)
                else:
                    detectObjects[i] = False
                #print("Average Value for "+ str(i) + " " + str(avgValues[i]))
                sleep(0.02)
                pass
            except:
                #note that this error will cause problems for the average
                print("\tRemote I/O Error Occur, Check connection")
                sleep(0.02)
                
            j += 1


t = Thread(target = runLidarDetection)

def startup():
    t.start()

if __name__ == "__main__":
    print("Starting Test")
    #startup()
    while True:
        runLidarDetection()
        c0 = checkLidar_FL()
        c1 = checkLidar_BL()
        c2 = checkLidar_FR()
        c3 = checkLidar_BR()
        print("0: "+str(c0)+" 1: "+str(c1)+" 2: "+str(c2)+" 3: "+str(c3))


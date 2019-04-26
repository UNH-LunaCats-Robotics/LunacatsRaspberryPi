from time import sleep
from serial import *
import threading

# This is the port the arduino is connected on, this can be found by
# Plugging an arduino into your computer and opening up the arduino IDE,
# And then going to Tools->Port to see where it's plugged in
# Port = '/dev/ttyACM0'
Port = '/dev/cu.usbmodem1411'

# sendData = True
# def getDataState():
#     return sendData

# def setDataState(newState):
#     sendData = newState

ser = Serial(Port, 115200)

def send_json(data):
        # print ("Trying to send:"+ str(getDataState()));
        # timeout = 0;
        # if not getDataState():
        #     print ("Timed out on sending:" + data);
        #     return "Timeout"

        
        # setDataState(False);
        # if ser.isOpen() == False:
        #     ser.open()

        # try:
        #     """This function sends some json to the robot, which will in turn send some json data back"""
        #     ser.flush()
            
        #     if not ser.isOpen():
        #         ser.open()
        #     ser.writelines(str(data))

        #     sleep(1.2);
        #     #print ("Serial:" + ser.isOpen());
        #     #line = ser.readline()

        #     # ser.close()

        #     # sleep(0.2);
        #     setDataState(True);

        #     return "Sent!"
        # except:
        #     setDataState(True)
        #     print ("There was an error:",sys.exc_info()[0])
        print("trying to send: " + str(data))
        thread = threading.Thread(target=send_task, args=(data,))
        thread.start()
        return_value = thread.join()
        return return_value

def send_task(data):
    ser.flush()
    
    if not ser.isOpen():
        ser.open()
    ser.writelines(str(data))
    print ("Serial:" + str(ser.isOpen()));
    line = ser.readline()
    return line
        


        



from time import sleep
from serial import *

# This is the port the arduino is connected on, this can be found by
# Plugging an arduino into your computer and opening up the arduino IDE,
# And then going to Tools->Port to see where it's plugged in
Port = '/dev/ttyACM0'

sendData = True;
def getDataState():
    return sendData;

def setDataState(newState):
    sendData = newState;

ser = Serial(Port, 115200)

def send_json(data):
        print "Trying to send:"+ str(getDataState());
        timeout = 0;
        if not getDataState():
            print "Timed out on sending:" + data;
            return "Timeout"

        
        setDataState(False);
        # if not ser.isOpen():
        #     ser.open()

        try:
            """This function sends some json to the robot, which will in turn send some json data back"""
            ser.flush()
            
            if ser.isOpen():
                ser.writelines(str(data))

            sleep(0.6);
            print "Serial:" + ser.isOpen();
            line = ser.readline()

            # ser.close()

            # sleep(0.2);
        except:
            setDataState(True)
            print "There was an error:",sys.exc_info()[0]

        


        setDataState(True);

        return line



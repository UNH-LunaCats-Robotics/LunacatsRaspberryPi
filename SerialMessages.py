from time import sleep
from serial import *

# This is the port the arduino is connected on, this can be found by
# Plugging an arduino into your computer and opening up the arduino IDE,
# And then going to Tools->Port to see where it's plugged in
Port = '/dev/ttyACM0'


# This establishes a serial connection, it also uses a 0.2 second timeout
try:
    try:
        ser = Serial(Port, 2000000)
    except:
        ser = Serial('/dev/ttyACM1', 2000000)
        
    ser.timeout = 0.2
    
    def send_json(data):
        """This function sends some json to the robot, which will in turn send some json data back"""
        ser.flush()
        
        if ser.isOpen():
            ser.writelines(str(data))
            sleep(0.05);
        return ser.readline()
except:
    def send_json(data):
        return "ERROR - Cannot Communicate to Serial"    





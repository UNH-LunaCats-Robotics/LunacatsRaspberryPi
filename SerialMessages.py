#from queue import Queue
#import threading
from time import sleep
import serial
from threading import Thread, Lock
import atexit
import json

port = '/dev/ttyACM0'
baudrate = 115200
ser = serial.Serial(port, baudrate, timeout = 1)

def closePort():
    if ser != None:
        ser.close()

atexit.register(closePort)

mutex = Lock()

def writeToArduino(msg):
    print "Sending: "+msg
    ser.write(bytes(msg))

def send_json(data):
    mutex.acquire()
    try:
        writeToArduino(json.dumps(data))
        # rs1 = ser.readline()
        # print "Arduino Responded:" + json.dumps(rs1)
        sleep(0.1) #give some buffer time for arduino
        return "Sent!"
    finally:
        mutex.release()

if __name__ == "__main__":
        for i in range (0, 100):
                send_json({"c":4})
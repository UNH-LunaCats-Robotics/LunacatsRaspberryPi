from queue import Queue
from time import sleep
import serial
import threading
import atexit
import json

port = '/dev/cu.usbmodem101'
baudrate = 115200

ser = serial.Serial(port, baudrate, timeout = 0.05)


def closePort():
    if ser != None:
        ser.close()

atexit.register(closePort)

def writeToArduino(msg):
    print("Sending: " + str(msg))
    ser.write(bytes([msg]))

def startup():
        thread = threading.Thread(target=send_task,args=())
        thread.start()

messageQueue = Queue(maxsize=2)

def send_json(data):
        global messageQueue;
        messageQueue.put(data["c"])

def send_task():
        while True:
                global messageQueue;
                item = messageQueue.get()
                if item is None:
                        break
                
                writeToArduino(item)
                # print("Arduino Responded:" + str(ser.read()))
                messageQueue.task_done()

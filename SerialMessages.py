from queue import Queue
from time import sleep
import serial
import threading
import atexit
import json

port = '/dev/ttyACM0'
baudrate = 115200

ser = serial.Serial(port, baudrate, timeout = 10)


def closePort():
    if ser != None:
        ser.close()

atexit.register(closePort)

def writeToArduino(msg):
    print("Sending: "+msg)
    ser.write(bytes(msg,'utf-8'))


def startup():
        thread = threading.Thread(target=send_task,args=())
        thread.start()

messageQueue = Queue(maxsize=3)

def send_json(data):
        global messageQueue;
        messageQueue.put(data)

def send_task():
        while True:
                global messageQueue;
                item = messageQueue.get()
                if item is None:
                        break
                sleep(1)
                print("Sending:" + item)
                #writeToArduino(item)
                messageQueue.task_done()

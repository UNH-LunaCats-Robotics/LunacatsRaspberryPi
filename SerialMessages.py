from queue import Queue
from time import sleep
import serial
import threading
import atexit
import json

port = '/dev/ttyACM0'
baudrate = 115200
ser = serial.Serial(port, baudrate, timeout = 1)

def closePort():
    if ser != None:
        ser.close()

atexit.register(closePort)

def startup():
        thread = threading.Thread(target=send_task,args=())
        thread.start()

messageQueue = Queue(maxsize=2)


def send_json(data):
        global messageQueue;
        messageQueue.put(data)

def send_task():
        while True:
                global messageQueue;
                item = messageQueue.get()
                if item is None:
                        break

                print("Sending:" + json.dumps(item) )
                ser.write(bytes(json.dumps(item),'utf-8'))
                print("Arduino Responded:" + str(ser.read()))
                messageQueue.task_done()
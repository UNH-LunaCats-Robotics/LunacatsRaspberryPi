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
        print "Arduino Responded:" + ser.read()
        sleep(0.025) #give some buffer time for arduino 
    finally:
        mutex.release()

'''
#testing main function
if __name__ == "__main__":
    #initArduino()
    sleep(0.5)
    for i in range(10):
        t = Thread(target = processData, args = (i,))
        t.start() 
'''

'''
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

                print "Sending:" + json.dumps(item) 
                ser.write(bytes(json.dumps(item),'utf-8'))
                print "Arduino Responded:" + ser.read()
                messageQueue.task_done()
'''
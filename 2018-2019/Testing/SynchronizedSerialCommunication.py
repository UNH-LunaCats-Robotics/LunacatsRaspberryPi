from threading import Thread, Lock
from PythonSerialCommunication import *

mutex = Lock()

'''
def processData(data):
    mutex.aquire()
    try:
        test_rw(data)
    finally:
        mutex.release()
'''

''' multiprocessing library
def processData(data):
    with mutex:
        text_rw(data)
'''

def processData(data):
    mutex.acquire()
    try:
        test_rw(str(data))
        sleep(0.025)
        #print "lets run this"
    finally:
        mutex.release()

if __name__ == "__main__":
    #initArduino()
    sleep(0.5)
    for i in range(10):
        t = Thread(target = processData, args = (i,))
        t.start()
    
    
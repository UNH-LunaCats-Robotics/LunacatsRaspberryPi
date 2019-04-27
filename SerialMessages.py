from time import sleep
from serial import *
import threading
import atexit

def startup():
        thread = threading.Thread(target=send_task,args=())
        thread.start()


res = ""
sendMsg = ""

def send_json(data):
        global res,sendMsg;
        
        while sendMsg != "" or res != "":
                sleep(0.001)
        sendMsg = data;

        while res == "":
                sleep(0.001);
        ret = res
        res = ""


        print("Got:"+ret);
        return ret



def send_task():
        global res,sendMsg;
        while True:
                sleep(0.001);
                if sendMsg == "":
                        continue
                msg = sendMsg
                print("Processing:" + msg)

                sleep(1) # Need to replace with pyserial
                res = msg + " and sent!"
                sendMsg = ""
                


        
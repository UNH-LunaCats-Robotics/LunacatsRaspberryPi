from time import sleep
import serial
import threading
import atexit
import json
import RPi.GPIO as GPIO

port = 'COM4'
baudrate = 115200
try:
    ser = serial.Serial(port, baudrate, timeout = 10) 
except:
    ser = None

def closePort():
#     if ser != None:
#         ser.close()
        print("Closed Port!")

atexit.register(closePort)

def writeToArduino(msg):
    print("Sending: "+msg)
    ser.write(bytes(msg,'utf-8'))

action = 31
q2 = 33
q1 = 35
q0 = 37
def startup():
        sleep(2)
        writeToArduino("init")
        # response = ser.readline()
        # print("Result: "+str(response))
        # if str(response) == "b'success\r\n'":
        #         print("the Arduino is ready to respond to messages!")
        # elif response == "b''":
        #         print("WARNING -- Arduino Communication Timed Out!")
        # else:
        #         print("WARNING -- Arduino failed initialization test.")

        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(action, GPIO.OUT, initial=GPIO.LOW) # Action Pin
        GPIO.setup(q2, GPIO.OUT, initial=GPIO.LOW) # Q2
        GPIO.setup(q1, GPIO.OUT, initial=GPIO.LOW) # Q1
        GPIO.setup(q0,  GPIO.OUT, initial=GPIO.LOW)# Q0

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


        print("Got:"+ str(ret));
        return ret


# Halt:     000
# Forward   001
# Back      010
# Left      011
# Right     100
# ACT_STP   101
# ACT_UP    110
# ACT_DN    111

def halt():
    GPIO.output(q2,GPIO.LOW)
    GPIO.output(q1,GPIO.LOW)
    GPIO.output(q0,GPIO.LOW)
def Forward():
    GPIO.output(q2,GPIO.LOW)
    GPIO.output(q1,GPIO.LOW)
    GPIO.output(q0,GPIO.HIGH)
def Back():
    GPIO.output(q2,GPIO.LOW)
    GPIO.output(q1,GPIO.HIGH)
    GPIO.output(q0,GPIO.LOW)
def Left():
    GPIO.output(q2,GPIO.LOW)
    GPIO.output(q1,GPIO.HIGH)
    GPIO.output(q0,GPIO.HIGH)

def Right():
    GPIO.output(q2,GPIO.HIGH)
    GPIO.output(q1,GPIO.LOW)
    GPIO.output(q0,GPIO.LOW)
def ACT_STP():
    GPIO.output(q2,GPIO.HIGH)
    GPIO.output(q1,GPIO.LOW)
    GPIO.output(q0,GPIO.HIGH)
def ACT_UP():
    GPIO.output(q2,GPIO.HIGH)
    GPIO.output(q1,GPIO.HIGH)
    GPIO.output(q0,GPIO.LOW)
def ACT_DN():
    GPIO.output(q2,GPIO.HIGH)
    GPIO.output(q1,GPIO.HIGH)
    GPIO.output(q0,GPIO.HIGH)


def send_task():
        global res,sendMsg;
        while True:
                sleep(0.001);
                if sendMsg == "":
                        continue
                msg = sendMsg
                
                Right();
                
                # writeToArduino(msg)
                # res = str(ser.readline().strip())
                # print ("Got:" + str(res))
                # print("Type: " + str(type(res)))
                res = "Sent!"
                sendMsg = ""

from time import sleep
import serial
import threading
import atexit

port = 'COM4'
baudrate = 115200

ser = serial.Serial(port, baudrate, timeout = 10) 

def closePort():
    ser.close()

atexit.register(closePort)

def writeToArduino(msg):
    print("Sending: "+msg)
    ser.write(bytes(msg,'utf-8'))

def startup():
        sleep(2)
        writeToArduino("init")
        response = ser.readline()
        print("Result: "+str(response))
        if str(response) == "b'success\r\n'":
                print("the Arduino is ready to respond to messages!")
        elif response == "b''":
                print("WARNING -- Arduino Communication Timed Out!")
        else:
                print("WARNING -- Arduino failed initialization test.")
                
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



def send_task():
        global res,sendMsg;
        while True:
                sleep(0.001);
                if sendMsg == "":
                        continue
                msg = sendMsg
                
                writeToArduino(msg)
                res = str(ser.readline().strip())
                print ("Got:" + str(res))
                print("Type: " + str(type(res)))
                sendMsg = ""

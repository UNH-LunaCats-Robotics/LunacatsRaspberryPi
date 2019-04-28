import serial
import atexit
from time import sleep

port = "/dev/ttyACM0"
baudrate = 115200

ser = serial.Serial(port, baudrate, timeout = 3) 

def closePort():
    ser.close()

atexit.register(closePort)

def writeToArduino(msg):
    print("Sending "+msg)
    ser.write(bytes(msg,'utf-8'))

def initArduino():
    sleep(2)
    writeToArduino("init")
    pong = ser.readline()

def test_rw(ping):
    writeToArduino("init")
    pong = ser.readline().strip()
    print("\Init Response: "+str(pong))
    #sleep(0.5)

def test_w(ping): 
    writeToArduino(ping)
    print("Wrote Bytes: "+str(ser.in_waiting))
    sleep(0.5)

def test_r():
    pong = ser.readline().strip()
    print("\tRead: "+str(pong))

if __name__ == "__main__":
    ping = "Stop Repeating Me"
    #writeToArduino("init")
    initArduino()
    while True: 
        test_r()tRead
        
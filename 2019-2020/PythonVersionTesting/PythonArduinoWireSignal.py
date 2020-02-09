import gpiozero
import enum
from time import sleep

'''
#-----------------!!NOTICE!!-----------------#
This code is not used and hasnt been tested.

Original Problem: 
    Serial Communication  on Arduino had a large 
    delay when recieving serial input
File's Purpose:
    Communicate with arduino using pins as binary
    inputs for driving for instantanious actions.
Solution:
    Serial Communication Delay was programmed into
    the arduino. Changing the delay value allowed 
    for instantious actions. 
'''

actionEnable = gpiozero.DigitalOutputDevice(31, False)
action_q0 = gpiozero.DigitalOutputDevice(37, False)
action_q1 = gpiozero.DigitalOutputDevice(35, False)
action_q2 = gpiozero.DigitalOutputDevice(33, False)

class Actions(enum.Enum):
    HALT =      0
    FORWARD =   1
    BACKWARD =  2
    LEFT =      3
    RIGHT =     4
    ACTSTOP =   5
    ACTUP =     6
    ACTDOWN =   7

def sendDecimalToArduino(num):
    setPinCorrectValue(((int)(num/4)     == 1), action_q2)
    setPinCorrectValue(((int)((num/2)%2) == 1), action_q2)
    setPinCorrectValue(((int)(num%2)     == 1), action_q0)

def setPinCorrectValue(status, pin):
    if status:
        pin.on()
    else:
        pin.off()

'''
#define HALT      0   // 0   0   0    
#define FORWARD   1   // 0   0   1
#define BACKWARD  2   // 0   1   0
#define LEFT      3   // 0   1   1 
#define RIGHT     4   // 1   0   0
#define ACTSTOP   5   // 1   0   1
#define ACTUP     6   // 1   1   0
#define ACTDOWN   7   // 1   1   1    
'''

if __name__ == "__main__":
    pass
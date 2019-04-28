import gpiozero
import enum
from time import sleep

actionEnable = gpiozero.DigitalOutputDevice(31, False)
action_q0 = gpiozero.DigitalOutputDevice(37, False)
action_q1 = gpiozero.DigitalOutputDevice(35, False)
action_q2 = gpiozero.DigitalOutputDevice(33, False)

class Actions(enum.Enum):
    

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
    
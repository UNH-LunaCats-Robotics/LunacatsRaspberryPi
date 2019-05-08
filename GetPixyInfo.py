import pixy 
from ctypes import *
from pixy import *
from flask import jsonify
from time import sleep
import atexit

# This code will  what the pixy camera sees in get sig and will not try to move it


class Blocks (Structure):
  _fields_ = [ ("m_signature", c_uint),
    ("m_x", c_uint),
    ("m_y", c_uint),
    ("m_width", c_uint),
    ("m_height", c_uint),
    ("m_angle", c_uint),
    ("m_index", c_uint),
    ("m_age", c_uint) ]

blocks = BlockArray(100)

def startup():

  pixy_init()

def getSig():
    global blocks
    #jsonify({'some':'data'})

    count = pixy_get_blocks(100, blocks)
    
    ret = {}
    print "Count:" + str(count)
    if count > 0:
      for index in range (0, count):
        if blocks[index].signature == 0:
          continue
        ret[blocks[index].signature] = { 
                      "X" : blocks[index].x, 
                      "Y" : blocks[index].y, 
                      "W" : blocks[index].width, 
                      "H" : blocks[index].height}
    return ret

if __name__ == "__main__":
  startup()
  while True:
    print str(getSig())
    sleep(1)
  
atexit.register(pixy_close())

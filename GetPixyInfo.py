import pixy 
from ctypes import *
from pixy import *
from flask import jsonify
from time import sleep

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


blocks = BlockArray(5)
pixyCam = None

def startup():
  global pixyCam

  pixy_init()

def getSig():
    global pixyCam
    #jsonify({'some':'data'})

    if pixyCam == -1:
      return "Can't connect to PixyCamera"
    count = pixy_get_blocks(5, blocks)
    
    ret = {}
    if count > 0:
      for index in range (0, count):
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
    
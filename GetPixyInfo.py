import pixy 
from ctypes import *
from pixy import *
from flask import jsonify

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
frame = 0
pixyCam = None

def startup():
  global pixyCam

  pixyCam = pixy.init ()
  if pixyCam == -1:
    print "Can't connect to pixycamera!!!!!"
  else:
    pixy.change_prog ("color_connected_components")


def getSig():
    global pixyCam
    #jsonify({'some':'data'})

    if pixyCam == -1:
      return "Can't connect to PixyCamera"
    count = pixy.ccc_get_blocks (100, blocks)
    ret=  {"C":count}

    for i in range(count):
      ret ["S"+str(i)] = blocks[i].m_signature
      ret ["X"+str(i)] = blocks[i].m_x
      ret ["Y"+str(i)] = blocks[i].m_y
      ret ["W"+str(i)] = blocks[i].m_width
      ret ["H"+str(i)] = blocks[i].m_height
    return jsonify(ret)
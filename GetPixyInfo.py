import pixy 
from ctypes import *
from pixy import *
from flask import jsonify
from time import sleep

# This code will  what the pixy camera sees in get sig and will not try to move it

FocalLengthHeight = 268.0
FocalLengthWidth = 292.4
widthOfObject  = 0.508 # Measured in meters, Used to get FocalLengthWidth
heightOfObject = 0.4318 # Measured in meters, Used to get FocalLengthHeight

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
    ret =  {"C":count}
    
    for i in range(count):
      ret ["S"+str(i)] = blocks[i].m_signature
      ret ["X"+str(i)] = blocks[i].m_x
      ret ["Y"+str(i)] = blocks[i].m_y
      ret ["W"+str(i)] = blocks[i].m_width
      ret ["H"+str(i)] = blocks[i].m_height
    return ret

def getGoodSig():
    global pixyCam

    if pixyCam == -1:
      return "Can't connect to PixyCamera"
    
    count = pixy.ccc_get_blocks (100, blocks)
    ret =  {}
    
    for i in range(count):
      blk = {}
      blk ["S"] = blocks[i].m_signature
      blk ["X"] = blocks[i].m_x
      blk ["Y"] = blocks[i].m_y
      blk ["W"] = blocks[i].m_width
      blk ["H"] = blocks[i].m_height
      ret[i] = blk

    return ret



def getFocalLength(data,KnownDistance):
    global pixelsWidth,pixelsHeight,boxWidth,boxHeight,widthOfObject,heightOfObject,FocalLengthWidth,FocalLengthHeight
    FocalLengthWidth =  (data["W0"]   * KnownDistance) / widthOfObject
    FocalLengthHeight = (data["H0"]   * KnownDistance) / heightOfObject

def getDistance(data):
    global pixelsWidth,pixelsHeight,boxWidth,boxHeight,widthOfObject,heightOfObject,FocalLengthWidth,FocalLengthHeight
    focalWidthMeasure  =  (widthOfObject * FocalLengthWidth) / data["W0"]
    focalHeightMeasure =  (heightOfObject * FocalLengthHeight) / data["H0"]
    return (focalWidthMeasure + focalHeightMeasure)/2

if __name__ == "__main__":
  startup()
  while True:
    data = getSig()
    print str(data)
    # getFocalLength(data,1.7272)
    # print str(FocalLengthHeight) + " " + str(FocalLengthWidth)
    print str(getDistance(data))
    sleep(0.1)
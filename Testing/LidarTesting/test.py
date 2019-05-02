from lidar_lite import Lidar_Lite
from time import sleep

lidar = Lidar_Lite()
connected = lidar.connect(1)

if connected < -1:
  print("Not Connected")

if __name__ == "__main__":
    while True:
      print("Distance: "+str(lidar.getDistance()))
      print("Velocity: "+str(lidar.getVelocity()))
      sleep(0.1)
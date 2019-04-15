from RobotCommunication import *
from time import sleep
import socket


# For some reason the serial connection won't send data until after 1 second has passed
sleep(1.5)

#
# def test_autonomous():
#     """This is a test program to make sure all of the functions on the arduino work the way they should"""
#     print forward(80)
#     sleep(0.5)
#     print back(80)
#     sleep(0.5)
#     print left(80)
#     sleep(0.5)
#     print right(80)
#     sleep(0.5)
#     print stop()
#     sleep(0.5)
#
#     print forward(80, 1)
#     sleep(0.5)
#     print back(80, 1)
#     sleep(0.5)
#     print left(80, 1)
#     sleep(0.5)
#     print right(80, 1)
#     sleep(0.5)
#     print stop()
#     # dig(80)
#
#
# def real_auto():
#     forward(80)
#     sleep(5)
#     stop()
#
# real_auto()
# # RobotCommunication.test()

# app = Flask(__name__)
#
# # {'cmd': '0', 'power': 50}
# @app.route('/cmd/<string:data>', methods=['GET'])
# def get_task(data):
#     return send_json(data)
#
#
# if __name__ == '__main__':
#     app.run()


# import socket
# s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# s.bind(('localhost', 50000))
# s.listen(1)
# conn, addr = s.accept()
# while 1:
#     data = conn.recv(1024)
#     if not data:
#         break
#     conn.sendall(data)
# conn.close()


HOST = ('0.0.0.0', 65432)

sock_obj = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)

sock_obj.bind(HOST)
sock_obj.listen(1)

conn, addr = sock_obj.accept()
print "Conn from:" + str(addr)


while True:
    data = conn.recv(1024)

    print "Recieved:" + str(data)

    if not data:
        break
    conn.sendall(send_json(data))



# with  as s:
#     s.bind((HOST, PORT))
#     s.listen()
#     conn, addr = s.accept()
#     with conn:
#         print('Connected by', addr)
#         while True:
#             data = conn.recv(1024)
#             if not data:
#                 break
#             conn.sendall(data)
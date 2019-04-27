from flask import Flask, jsonify
from flask import request
from RobotCommunication import *
import GetPixyInfo
from time import sleep
import requests
import json
from Autonomous import *


def shutdown_server():
    func = request.environ.get('werkzeug.server.shutdown')
    if func is None:
        raise RuntimeError('Not running with the Werkzeug Server')
    func()


app = Flask(__name__)

# {'cmd': '0', 'power': 50}
@app.route('/cmd/<string:data>', methods=['GET'])
def get_task(data):
    print ("Got:\t"+data)
    autonStatus = getAutonStatus()
    response = jsonify()

    if data == "{'c':5}":
        response = json.dumps(GetPixyInfo.getSig())
    if data == "{'s':0}":
        shutdown_server()
        response = jsonify({"C": 'Shutting Down'})
        
    elif data == "{'c':7}":
        print ("looks like its time to start the autonomous")
        runAutonomous()
    elif data == "{'c':8}":
        print ("Stopping the autonomonous!!!!!")
        stopAutonomous()
    else:
        text = send_json(data)
        print ("Arduino Responded:" + str(text))
        response = jsonify(text)

    print ("Sending to Laptop")
    response.headers.add('Access-Control-Allow-Origin', '*')
    return response


@app.route('/sendPixyData', methods=['GET'])
def get_pixy_data():
    while True:
        response = json.dumps(GetPixyInfo.getSig())
        print ("Got: "+response)
        link = "http://"+request.remote_addr+":3000/setPixyData/"+response
        print("Sending Pixy Info to "+link)
        r = requests.get(link)
        sleep(2)


@app.route("/get_my_ip", methods=["GET"])
def get_my_ip():
    return jsonify({'ip': request.remote_addr}), 200


if __name__ == '__main__':
    GetPixyInfo.startup()
    startup()
    app.run(host='0.0.0.0')



@app.route('/shutdown/<string:data>', methods=['GET'])
def shutdown():
    shutdown_server()
    return 'Server shutting down...'

from flask import Flask, jsonify
from flask import request
from time import sleep
import requests
import json

import GetPixyInfo
import RobotCommunication
import Autonomous


def shutdown_server():
    func = request.environ.get('werkzeug.server.shutdown')
    if func is None:
        raise RuntimeError('Not running with the Werkzeug Server')
    func()


app = Flask(__name__)

# {'cmd': '0', 'power': 50}
@app.route('/cmd/<string:data>', methods=['GET'])
def get_task(data):

    dataJson = json.loads(data)
    
    response = jsonify()

    if   dataJson["c"] == 5:
        response = json.dumps(GetPixyInfo.getSig())
    elif dataJson["c"] == 7:
        response = Autonomous.runAutonomous()
    elif dataJson["c"] == 8:
        response = Autonomous.stopAutonomous()
    else:
        response = jsonify(RobotCommunication.sendMessage(dataJson))
        
    response.headers.add('Access-Control-Allow-Origin', '*')
    return response

    


@app.route('/sendPixyData', methods=['GET'])
def get_pixy_data():
    while True:
        response = json.dumps(GetPixyInfo.getSig())
        print "Got: " + response
        link = "http://"+request.remote_addr+":3000/setPixyData/"+response
        print "Sending Pixy Info to "+link
        r = requests.get(link)
        sleep(2)


@app.route("/get_my_ip", methods=["GET"])
def get_my_ip():
    return jsonify({'ip': request.remote_addr}), 200


if __name__ == '__main__':
    GetPixyInfo.startup()
    RobotCommunication.startup()
    app.run(host='0.0.0.0')



@app.route('/shutdown/<string:data>', methods=['GET'])
def shutdown():
    shutdown_server()
    return 'Server shutting down...'

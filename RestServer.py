from flask import Flask, jsonify
from RobotCommunication import *
import GetPixyInfo
from time import sleep
import requests
import threading

def sendPixyInfo():
    threading.Timer(2.5,sendPixyInfo).start()
    print "Sending Pixy Info On thread"
    try:
        r = requests.get("http://10.0.10.14:3000/cmd/{'C':0}")
    except:
        print "\tCan't send info!!!!!"
#sendPixyInfo()


def shutdown_server():
    func = request.environ.get('werkzeug.server.shutdown')
    if func is None:
        raise RuntimeError('Not running with the Werkzeug Server')
    func()

app = Flask(__name__)

# {'cmd': '0', 'power': 50}
@app.route('/cmd/<string:data>', methods=['GET'])
def get_task(data):

    print "Got:\t"+data;
    #if data[1:6] == "'c':7":
        #response = ExecuteRemoteCode.execute(data)
    if data == "{'c':5}":
        
        response = GetPixyInfo.getSig()#jsonify({'some':'data'})
        
    
        #response = GetPixyInfo.getSig()
    elif data == "{'s':0}":
        shutdown_server()
        response = jsonify({"C":'Shutting Down'})
    else:
        print "Sending to Arduino"
        response = jsonify(send_json(data))

    print "Sending to Laptop"
    response.headers.add('Access-Control-Allow-Origin','*')
    return response


if __name__ == '__main__':
    GetPixyInfo.startup()
    app.run(host = '0.0.0.0')

@app.route('/shutdown/<string:data>', methods=['GET'])
def shutdown():
    shutdown_server()
    return 'Server shutting down...'

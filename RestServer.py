from flask import Flask, jsonify
from RobotCommunication import *
import GetPixyInfo
from time import sleep
import requests
import threading

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

@app.route('/sendPixyData/<string:data>', methods=['GET'])
def get_pixy_data(data):
    
    while True:
        print "Sending Pixy Info"
        r = requests.get("http://10.0.10.11:3000/cmd",auth=('tester','test'))
        sleep(2)




if __name__ == '__main__':
    GetPixyInfo.startup()
    
    app.run(host = '0.0.0.0')
    threading.Timer(2.5,sendPixyInfo())
    

@app.route('/shutdown/<string:data>', methods=['GET'])
def shutdown():
    shutdown_server()
    return 'Server shutting down...'
    runConnectThread = False;



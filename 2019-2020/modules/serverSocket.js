//documentation: https://socket.io/
var app = require('./server.js').app;
var commands = require('./commands.js').cmds;
var ctrl = require('./commands').controller;
var http = require('http').Server(app);

const arduino = require('./arduino.js');
var robot = arduino.robot;
var io = require('socket.io')(http);
const rpserver = require('../build/Release/rpserver.node');

var port = 3002;

// assemble message and send to the robot
function sendToRobot(cmd, val){
  var action = cmd + ":" + val;
  //write to robot
  console.log("(remote control) sending message -> " + action);
  robot.write(action, (err) => {
            if(err) return console.log("Error on write: ", err.message);
            console.log("(remote control) message written -> " + action + "!");
        });
  //console.log("(remote control) message written -> " + action + "!");
}


//string format -> A:0
function sendButtonCommand(str){
  var tmp = str.split(":", 2)
  var cmd = tmp[0]
  var on = tmp[1]
  if(Object.values(commands).indexOf(cmd) == -1){
    console.log("??? Invalid command -> " + cmd + " ???");
  }else{
    sendToRobot(cmd, on);
  }
  
}

// string format -> L:45:0
// todo: need to confirm the format
function sendAxisCommand(str){
  var tmp = str.split(":", 3)
  //tmp[0]
  var angle = tmp[1]
  var on = tmp[2]

  sendToRobot(commands.MOVE, angle);
}

var connectSocket = function(){
  io.listen(port);
  console.log("listening on port ", port);
  
  //connection event
  io.on('connection', function(socket) {
    console.log('a user connected: '+ socket);
  
    //button event: A button down -> A:0
    socket.on('button', (value) => {
      sendButtonCommand(value);
    });

    //joystick event: left joystick 45 -> L:45:0
    socket.on('joystick', (angle) => {
      sendAxisCommand(angle);
    });
    
    /*
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * Rui: did not see this new update, found conflict and moved them here
     * Hopefully it still works.
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */
    var n = 0;
     setInterval( () => {
       var p = new rpserver.Point(n, n, 0);
       var res = p.X() + ":" + p.Y() + ":" + p.Z();
       socket.emit('lidar', res);
       n++;
       console.log("X: ", p.X(), " Y: ", p.Y(), " Z: ", p.Z());
     }, 1000);  
     // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  });
}

var getCommand = function() {
    return cmd;
}

module.exports = {
    io: io,
    connectSocket: connectSocket,
    getCommand: getCommand
}
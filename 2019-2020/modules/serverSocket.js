//documentation: https://socket.io/
var app = require('./server.js').app;
var commands = require('./commands.js').cmds;
var ctrl = require('./commands').controller;
var http = require('http').Server(app);

const arduino = require('./arduino.js');
var robot = arduino.robot;

var port = 3002;
var io = require('socket.io')(3002);


function sendToArduino(cmd, val){
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
    sendToArduino(cmd, on);
  }
  
}

// string format -> L:45:0
// todo: need to confirm the format
function sendAxisCommand(str){
  var tmp = str.split(":", 3)
  //tmp[0]
  var angle = tmp[1]
  var on = tmp[2]

  sendToArduino(commands.MOVE, angle);
}

var connectSocket = function(){
  //io.listen(port);
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
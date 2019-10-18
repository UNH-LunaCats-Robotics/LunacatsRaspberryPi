//c++ code
const rpserver = require('./build/Release/rpserver.node');

//serial port
const arduino = require('./modules/arduino.js');
var robot = arduino.robot;

//network
const sensorServer = require('./modules/server.js');
const serverSocket = require('./modules/serverSocket.js');

//tether
var controller = require('./modules/tether.js');

/*
//this is how you can write to the arduino
setTimeout(() => {
    console.log("writing...");
    robot.write("hello", (err) => {
        if(err) {
            return console.log("Error on write: ", err.message);
        }
        console.log("message written");
    });
}, 3000);
*/

//tether means that the robot will drive from controller connection
console.log("Tethered Connection:", controller.isTethered);

serverSocket.connectSocket();
exports.server = sensorServer.app;

console.log("--------- C++ Function Examples ---------");
console.log("rpserver: ", rpserver);
console.log("Hello World: ", rpserver.helloWorld());
console.log("Add 2 + 3: ", rpserver.add(2,3));
console.log("-----------------------------------------");

//send the commands from the controller or the server to the arduino
setInterval(() => {
    if(controller.isTethered) {
        robot.write(controller.getCommand(), (err) => {
            if(err) {
                return console.log("Error on write: ", err.message);
            }
            //console.log("message written");
        });
    } else {
        robot.write(serverSocket.getCommand(), (err) => {
            if(err) {
                return console.log("Error on write: ", err.message);
            }
            //console.log("message written");
        });
    }
}, 20);



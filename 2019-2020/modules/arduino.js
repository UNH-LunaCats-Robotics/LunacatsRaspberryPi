//serial port
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

//serial port
//const robot = new SerialPort('/dev/cu.usbmodem145101', { baudRate: 115200 }); //mac
var robot; //linux
var cmdParser;
var can_write_cmd = false;
var isConnected = false;

//each sensor aduino should be added here. 
//const sensorPorts = ['/dev/ttyACM1'];

var connectArd = function() {
    robot = new SerialPort('/dev/ttyACM0', { baudRate: 115200 }); //linux
    cmdParser = robot.pipe(new Readline({ delimiter: '\n' }));// Read the port data
    //stop process if arduino cannot be reached
    robot.on("error", function(err) {
        can_write_cmd = false;
        isConnected = false;
        reconnectArd();
    })

    robot.on("close", () => {
        console.log("!!!ERROR: LOST CONNECTION TO CONTROLLER!!!");
        can_write_cmd = false;
        isConnected = false;
        reconnectArd();
    });

    //just because it is open does not mean it is ready to recieve data
    robot.on("open", () => {
        console.log('robot serial port open');
        isConnected = true;
    });

    //print data recieved from arduino and init.
    var i = 0;
    cmdParser.on('data', data =>{
        console.log('got word from arduino:', data);
        
        //note that all strings will terminate with \r
        if(data === 'init\r') {
            cmd_can_read = true;   
        }
    /*  //ping pong
        if(cmd_can_read) {
            robot.write( i++ + ": hello from node", (err) => {
                if(err) {
                    return console.log("Error on write: ", err.message);
                }
                console.log("message written");
            }); 
        }
    */
    });
}

var reconnectArd = function() {
    setTimeout(function() {
        console.log("SEARCHING...");
        connectArd();
    }, 1000);
}

connectArd();

var lastCommand = {
    cmd: "",
    success: "pending"
}

function writeToRobot(cmd) {
    
}


/* //quickly looking like we wont need this
sensorPorts.forEach( (str) => {
    //unlike other languages, functions in javascript are allocated on the heap 
    //  and not a stack, so these variables will remain in the scope of 
    //  the async functions after the function ends
    const port = new SerialPort(str, { baudRate: 9600 });
    const parser = port.pipe(new Readline({ delimiter: '\n' }));// Read the port data
    var no_error = true;

    port.on('error', function(err) {
        console.log("Sensor", err.message);
        no_error = false;
    })

    if(no_error) {
        port.on("open", () => {
            console.log("sensor serial port open");
        });

        //since these are read-only arduinos for the server,
        //we do not need to wait for when we can write to them.
        parser.on('data', data => {
            console.log("sensor info: ", data);
        });
    }
});
*/

function getConnected() {
    return isConnected;
}

function getCanWrite() {
    return can_write_cmd;
}

module.exports = {
    connectArd: connectArd,
    reconnectArd: reconnectArd,
    robot: robot,
    isConnected: getConnected,
    canWrite: getCanWrite
};
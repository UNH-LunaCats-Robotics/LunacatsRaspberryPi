/*
const rpserver = require('./build/Release/rpserver.node');
*/
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

const express = require('express');
var cors = require('cors')
const bodyParser = require('body-parser');

const app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
//const ctrl = new Gamecontroller('');
var isTethered = false;

var gamepad = require('gamepad');
gamepad.init();

console.log(gamepad.numDevices());
for(var i = 0, l = gamepad.numDevices(); i < l; i++) {
    console.log(i, gamepad.deviceAtIndex())
    isTethered = true;
}

console.log(isTethered);

if(!isTethered) {
    app.use(cors())
    app.use(bodyParser.json());
    app.use(bodyParser.urlencoded({  extended: true }));

    app.use((error, request, response, next) => {
        if (error !== null) {
            return response.json(ERROR(700)); //invalid json
        }
        return next();
    });

    var port = 3001;
    var port2 = 3002;

    io.on('connection', function(socket) {
        console.log('a user connected');
        socket.on('subscribeToTimer', (interval) => {
            console.log('client is subscribing to timer with interval ', interval);
            setInterval(() => {
                socket.emit('timer', new Date());
            }, interval);
        });
    });

    io.listen(port2);
    console.log("listening on port ", port2);

    var webserver = {
        name: 'Robot Web Services',
        hostname: 'http://localhost',
        version: '1.0.0',
        env: process.env.NODE_ENV || 'development',
        port: 3000,
        cors: {
            preflightMaxAge: 5, //Optional
            origins: ['*'],
            allowHeaders: ['Origin', 'X-Requested-With', 'Content-Type', 'Accept', 'Access-Control-Allow-Origin'],
            acceptable: ['POST']
        }
    }

    app.listen(port, () => {
        console.log('%s Version: %s ',webserver.name, webserver.version);
        console.log('URL: %s:%s', webserver.hostname, port);
    });

    app.get('/', function (req, res) {
        res.send('System Active!');
    });
    /*
    app.post('/test', function (req, res) {
        res.send(req.body);
    });

    app.get('/', function (req, res) {
        res.send('System Active!');
    });

    app.get('/maps/search/', function(req, res) {
        res.send("tagId is set to " + req.query.api);
    });
    
    app.use(require('express-status-monitor')());
    */

    exports.server = app;
} else {
    setInterval(gamepad.processEvents, 16);
    setInterval(gamepad.detectDevices, 500);

    /* axis numbers
        left y axis: 0
        left x axis: 1
        right y axis: 3
        right x axis: 2
    */
    //listen for move events on all gamepads
    gamepad.on("move", function (id, axis, value) {
        if(axis != 0 || value > 0.1) {
            console.log("move", {
                id: id,
                axis: axis,
                value: value
            });
        }
    });

    //listen for button up events
    gamepad.on("up", function(id, num) {
        console.log("up", {
            id: id,
            num: num
        });
    });

    /* num for buttons
        y: 0
        x: 3
        a: 2
        b: 1

        +: 9
        home: 12
        square: 13
        -: 8

        R: 5
        ZR: 7
        L: 4
        ZL: 6

        arrow keys are axis
        left joystick button: 10
        right joystick button: 11
    */
    gamepad.on('down', function(id, num) {
        console.log("down", {
            id: id,
            num: num
        });
    });
}
/*
console.log("--------- C++ Function Examples ---------");
console.log("rpserver: ", rpserver);
console.log("Hello World: ", rpserver.helloWorld());
console.log("Add 2 + 3: ", rpserver.add(2,3));
console.log("-----------------------------------------");
*/
//this is the main robot controller arduino that moves the arduino

const robot = new SerialPort('/dev/cu.usbmodem145101', { baudRate: 9600 });
const cmdParser = robot.pipe(new Readline({ delimiter: '\n' }));// Read the port data
var cmd_can_read = false;
var commandServer; 

//each sensor aduino should be added here. 
const sensorPorts = ['/dev/ttyACM1'];

//sensor info 'stack' to be sent
var sensorInfo = []; 

robot.on("error", function(err) {
    console.log('Controller Arduino', err.message);
    //process.exit();
})

//just because it is open does not mean it is ready to recieve data
robot.on("open", () => {
    console.log('robot serial port open');
});

//ping pong

var i = 0;
cmdParser.on('data', data =>{
    console.log('got word from arduino:', data);
    
    //note that all strings will terminate with \r
    if(data === 'init\r') {
        cmd_can_read = true;   
    }
/*
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
            //sensorInfo.push(data);
        });
    }
});

/* 
//post data from the sensorInfo stack every 20 ms
//probably a better way, so don't use this.
setInterval(function() {
    if(sensorInfo.length != 0) {
        console.log(sensorInfo);
        console.log("data: ", sensorInfo.pop());
    }
}, 20);
*/
/*
module.exports = rpserver;
*/
var gamepad = require('gamepad');

//tethered
var isTethered = false;

//initialize gamepad for input reading
gamepad.init();

var state = {
    //axis
    left_x: 0,
    left_y: 0, 
    right_x: 0,
    right_y: 0,
    arrow_x: 0,
    arrow_y: 0,
    //buttons
    y: false,
    b: false,
    a: false,
    x: false,
    L: false,
    R: false,
    ZL: false,
    ZR: false,
    joystick_left: false,
    joystick_right: false
}

//display connected controllers
console.log("Controllers Detected: ", gamepad.numDevices());
for(var i = 0, l = gamepad.numDevices(); i < l; i++) {
    console.log(i, gamepad.deviceAtIndex());
    isTethered = true;
}

//create intervals that will call the functions repeatedly
setInterval(gamepad.processEvents, 16);
setInterval(gamepad.detectDevices, 500);

/* axis numbers
    Left JoyStick: [0,1]
        left y axis: 1
        left x axis: 0
    *
    Right Joystick: [2,3]
        right y axis: 3
        right x axis: 2
    * 
    Arrow Buttons: [4,5]
        arrow y axis:
        arrow x axis: 
*/
//listen for move events on all gamepads
gamepad.on("move", function (id, axis, value) {
    if(value > 0.1 || -value > 0.1) {
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
    
    /*
    robot.write( "{ \"id\": "+id+", \"num\": "+num+" }", (err) => {
        if(err) {
            return console.log("Error on write: ", err.message);
        }
    });
    */
});

/* num for buttons
    Four Main Buttons: [0-3]
        y: 0
        b: 1
        a: 2
        x: 3

    Center Buttons: [8,9],[12,13]
        +: 9
        home: 12
        square: 13
        -: 8

    Trigger Buttons: [4-7]
        L: 4
        R: 5
        ZL: 6
        ZR: 7

    Joystick Buttons: [10,11]
        left: 10
        right: 11
*/
gamepad.on('down', function(id, num) {
    console.log("down", {
        id: id,
        num: num
    });
});

module.exports = {
    state: state,
    isTethered: isTethered
};
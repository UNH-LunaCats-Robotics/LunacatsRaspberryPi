var gamepad = require('gamepad');
var Move = require('./commands.js');

//tethered
var isTethered = false;

//initialize gamepad for input reading
gamepad.init();

var state = {
    //axis
    left_x: 0,    left_y: 0, 
    right_x: 0,   right_y: 0,
    arrow_x: 0,   arrow_y: 0,
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
    joystick_right: false,
    plus: false,
    minus: false
}

//tolerance for deciding driving and direction
var tolerance = 0.5;

function setButton(id, value) {
    switch(id) {
        case 0: state.y = value;
            break;
        case 1: state.b = value;
            break;
        case 2: state.a = value;
            break;
        case 3: state.x = value;
            break;
        case 4: state.L = value;
            break;
        case 5: state.R = value;
            break;
        case 6: state.ZL = value;
            break;
        case 7: state.ZR = value;
            break;
        case 8: state.minus = value;
            break;
        case 9: state.plus = value;
            break;
        case 10: state.joystick_left = value;
            break;
        case 11: state.joystick_right = value;
            break;
        case 12: //home
            break;
        case 13: //square
            break;
        
    }
}

function setAxis(id, val) {
    switch(id) {
        case 0: state.left_x = val;
            break;
        case 1: state.left_y = -val;
            break;
        case 2: state.right_x = val;
            break;
        case 3: state.right_y = -val;
            break;
        case 4: state.arrow_x = val;
            break;
        case 5: state.arrow_y = val;
            break;
    }
}

function getCommand() {
    if(!isTethered) return Move.STOP;

    var moveCmd = Move.STOP;

    //axis
    if(state.left_y > tolerance) moveCmd = Move.FORWARD;
    if(state.left_y < -tolerance) moveCmd = Move.BACK;
    if(state.left_x > tolerance) moveCmd = Move.LEFT;
    if(state.left_x < -tolerance) moveCmd = Move.RIGHT;

    //buttons
    if(state.ZR) moveCmd = Move.RAISE_F;
    if(state.R) moveCmd = Move.LOWER_F;
    if(state.ZL) moveCmd = Move.CONVEYOR_COLLECT;
    if(state.L) moveCmd = Move.CONVEYOR_DUMP;

    if(state.y) moveCmd = Move.BALL_SCREW_DN;
    if(state.b) moveCmd = Move.BALL_SCREW_UP;
    if(state.a) moveCmd = Move.TURN_AUGUR_CLOCKWISE;
    if(state.x) moveCmd = Move.TURN_AUGUR_COUNTER_CLOCKWISE;

    //not sure what hat was so i used + and - buttons
    if(state.plus) moveCmd = Move.INCREASE_SPEED;
    if(state.minus) moveCmd = Move.DECREASE_SPEED;

    return moveCmd;
}

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
        arrow y axis: 5
        arrow x axis: 4
*/
//listen for move events on all gamepads
gamepad.on("move", function (id, axis, value) {
    setAxis(axis, value);
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
    setButton(num, false);

    console.log("up", {
        id: id,
        num: num
    });
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
    setButton(num, true);
    console.log("down", {
        id: id,
        num: num
    });
});

//display connected controllers
console.log("Controllers Detected: ", gamepad.numDevices());
for(var i = 0, l = gamepad.numDevices(); i < l; i++) {
    console.log(i, gamepad.deviceAtIndex());
    isTethered = true;
}

//create intervals that will call the functions repeatedly
setInterval(gamepad.processEvents, 16);
setInterval(() => {
    gamepad.detectDevices();

    if(gamepad.numDevices() > 0) {
        if(!isTethered) console.log("controller connected!");
        isTethered = true;
    }
    else {
        if(isTethered) console.log("controller disconnected");
        isTethered = false;
    }
}, 500);

module.exports = {
    state: state,
    isTethered: isTethered,
    getCommand: getCommand
};
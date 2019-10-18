//documentation: https://socket.io/
var app = require('./server.js').app;
var commands = require('./commands.js');
var http = require('http').Server(app);
var io = require('socket.io')(http);

var port = 3002;

var cmd = commands.STOP;

io.on('connection', function(socket) {
    console.log('a user connected: '+socket);
    socket.on('subscribeToTimer', (interval) => {
        console.log('client is subscribing to timer with interval ', interval);
        setInterval(() => {
            socket.emit('timer', new Date());
        }, interval);
    });

    socket.on('button', (value) => {
        console.log('button', value);
        //cmd = commands.RAISE_F

    });

    //joystick event: joystick 45 -> L:45:0
    socket.on('joystick', (angle) => {
        console.log('joystick', angle);

     });
});

var connectSocket = function(){
    io.listen(port);
    console.log("listening on port ", port);
}

var getCommand = function() {
    return cmd;
}

module.exports = {
    io: io,
    connectSocket: connectSocket,
    getCommand: getCommand
}
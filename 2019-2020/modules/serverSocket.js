//documentation: https://socket.io/
var app = require('./server.js').app;
var http = require('http').Server(app);
var io = require('socket.io')(http);

var port = 3002;

io.on('connection', function(socket) {
    console.log('a user connected: '+socket);
    socket.on('subscribeToTimer', (interval) => {
        console.log('client is subscribing to timer with interval ', interval);
        setInterval(() => {
            socket.emit('timer', new Date());
        }, interval);
    });
});

var connectSocket = function(){
    io.listen(port);
    console.log("listening on port ", port);
}

module.exports = {
    io: io,
    connectSocket: connectSocket
}
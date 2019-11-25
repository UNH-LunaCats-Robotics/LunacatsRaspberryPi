const express = require('express');
var cors = require('cors');
const bodyParser = require('body-parser');
const app = express();

//note that everything set up currently is for testing how
//express and serialio works here.
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

var webserver = {
    name: 'Robot Web Services',
    hostname: 'http://localhost',
    version: '1.0.0',
    env: process.env.NODE_ENV || 'development',
    port: port,
    cors: {
        preflightMaxAge: 5, //Optional
        origins: ['*'],
        allowHeaders: ['Origin', 'X-Requested-With', 'Content-Type', 'Accept', 'Access-Control-Allow-Origin'],
        acceptable: ['POST', 'GET']
    }
}

app.listen(port, () => {
    console.log('%s Version: %s ',webserver.name, webserver.version);
    console.log('URL: %s:%s', webserver.hostname, port);
});

app.get('/', function (req, res) {
    res.send('System Active!');
});
var n = 0;
app.get('/status', cors(webserver.cors), function(req, res, next) {
    console.log("got a message")
    res.json({msg: n});
    n++;
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

module.exports = {
    app: app
}
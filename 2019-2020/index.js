
const rpserver = require('./build/Release/rpserver.node');

console.log("rpserver: ", rpserver);

console.log("--------- C++ Function Examples ---------")
console.log("Hello World: ", rpserver.helloWorld());
console.log("Add 2 + 3: ", rpserver.add(2,3));

module.exports = rpserver;
var serialport = require('node-serialport')

var sp = new serialport.SerialPort("/dev/ttyO3", { 
  parser: serialport.parsers.raw,
  baud: 115200
})

sp.on('data', function(chunk) {
  console.log("data chunk received")
})

console.log("nothing received")

//chunk.toString('hex'), chunk.toString(), chunk
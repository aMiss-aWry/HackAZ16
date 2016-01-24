// /dev/cu.usbmodem1421

// ORANGE  back left     - 0
// BROWN   back right    - 1
// YELLOW  forward right - 2
// RED     forward left  - 3

// Weird things: When outputting both to serial monitor and terminal, the arduino sputters (pun)
// like it's splitting the output between the two? but that doesn't make sense why would it do that

// var arDrone = require('ar-drone');
// var client = arDrone.createClient();

// client.takeoff();

var serialport = require('serialport');// include the library
   SerialPort = serialport.SerialPort; // make a local instance of it
   // get port name from the command line:
   portName = process.argv[2];

var myPort = new SerialPort(portName, {
   baudRate: 9600,
   // look for return and newline at the end of each data packet:
   parser: serialport.parsers.readline("\n")
 });

function showPortOpen() {
   console.log('port open. Data rate: ' + myPort.options.baudRate);
}

function sendSerialData(data) {
   console.log(data);
}

function showPortClose() {
   console.log('port closed.');
}

function showError(error) {
   console.log('Serial port error: ' + error);
}

myPort.on('open', showPortOpen);
//myPort.on('data', sendSerialData);
myPort.on('close', showPortClose);
myPort.on('error', showError);
myPort.on('data', function(data) {
   // print the directions to be followed, for testing purposes
   var stringArray = data.split("=");
   if (stringArray[0] == 0) {         // back left
      if (stringArray[1] < 30) {
         console.log("client.front(1)");
         console.log("client.clockwise(.5)");
      }
   }
   if (stringArray[0] == 1) {
      if (stringArray[1] < 30) {
         console.log("client.front(1)");
         console.log("client.counterClockwise(.5)");
      }
   }
   if (stringArray[0] == 2) {
      if (stringArray[1] < 30) {
         console.log("client.counterClockwise(.5)");
         console.log("client.front(1)");
      }
   }
   if (stringArray[0] == 3) {
      if (stringArray[1] < 30) {
         console.log("client.counterClockwise(.5)");
         console.log("client.front(1)");
      }
   }
	console.log(stringArray[1]);
});

// Limit hover height when indoors to 200 (just under 7 feet)
// If within 20 cm of all directions, this.up(.2) and then check again
// If too close (within 20 centimeters?) of any direction, go in the opposite direction



























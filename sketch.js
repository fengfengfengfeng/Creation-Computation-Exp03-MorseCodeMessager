var aiokey = "7b1557306b2f4d7797c734de505dabf0";
var userName = "FengYOY";
var channelName = "submit";

var pollingRate = 1000;
var lastCheck = 0;

var incomingVal1;
var currentVal1;

var serial; // variable to hold an instance of the serialport library
var portName = '/dev/cu.usbmodem1411';
var inData; 

var alphabet = ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"];
var megCon;
var mySentece;

function setup() { 
 createCanvas(windowWidth,windowHeight);

  serial = new p5.SerialPort(); // make a new instance of the serialport library
  serial.on('list', printList); // set a callback function for the serialport list event
  serial.on('connected', serverConnected); // callback for connecting to the server
  serial.on('open', portOpen);        // callback for the port opening
  serial.on('data', serialEvent);     // callback for when new data arrives
  serial.on('error', serialError);    // callback for errors
  serial.on('close', portClose);      // callback for the port closing
 
 serial.list();// list the serial ports
 var options = { baudrate: 9600}; 
 serial.open(portName);              // open a serial port

 megCon = new Array();
}

Array.prototype.clean = function(deleteValue) {
  for (var i = 0; i < this.length; i++) {
    if (this[i] == deleteValue) {         
      this.splice(i, 1);
      i--;
    }
  }
  return this;
};

function iftttSend1(uName, key, cName, cVal)
{
var sendURL = ("https://io.adafruit.com/api/groups/"+uName+"/send.json?x-aio-key="+key+"&"+cName+"="+cVal);
httpGet(sendURL);
}

function iftttCheck(uName, key)
{
var checkURL = ("https://io.adafruit.com/api/groups/"+uName+"/receive.json?x-aio-key="+key);
loadJSON(checkURL,newData);

console.log(checkURL);

}

function newData(incomingData)
{
  // console.log("here is the data" + incomingData.feeds[1].last_value);
  console.log(incomingData);
}

function serialEvent() {
  inData = Number(serial.read());
  if(inData){
    checkAlp(inData);
  } 
} 
// get the list of ports:
function printList(portList) {
 // portList is an array of serial port names
 for (var i = 0; i < portList.length; i++) {
 // Display the list the console:
 console.log(i + " " + portList[i]);
 }
} 
function serverConnected() {console.log('connected to server.');}
function portOpen() {console.log('the serial port opened.')} 
function serialError(err) {console.log('Something went wrong with the serial port. ' + err);}
function portClose() {console.log('The serial port closed.');}

function mousePressed()
{
  // var sendMeg = mySentece;
  var sendMeg = 1;
  if(sendMeg){
      mySentece = "";
      iftttSend1(userName,aiokey,channelName,sendMeg);
  }else{
    text("No Message!");
  }
}

//var randVal2 = random(100,400);
//iftttSend2(userName,aiokey,channelName1,randVal1, channelName1, randVal2);

function checkAlp(num){
  var n = num -1;
  append(megCon,alphabet[n]);
  megCon.clean(undefined);
  megCon.clean("");

}


function draw() {
  background("#FEF1EC");
  fill(0);
  textSize(50);
  text("The message is ",30,50);
  // text("sensor value: " + inData, 30, 30);

  // var n = inData -1;
  // text("My message is " + alphabet[n], 30,50);

  // console.log(megCon);
  if(megCon.length>0){
    // background("#FEF1EC");
    mySentece = megCon.join("");
    textSize(100);
    text(mySentece , 30,150);
    console.log("Here is the message: " + megCon.join(""));

  }


 //   if(millis()-lastCheck>=pollingRate){
 //  iftttCheck(userName,aiokey,channelName);
 //  lastCheck=millis();
 // }

}

function windowResized() { resizeCanvas(windowWidth, windowHeight); }

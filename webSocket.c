////////////////////////////////////////////// Async web server ///////////////////////////////////////////////////////////////////////
/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-web-server-physical-button/
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

// Import required libraries
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "ELEC302";
const char* password = "elec1234";

const char* PARAM_INPUT_1 = "state";

const int output = 2;
const int buttonPin = 32;

// Variables will change:
int ledState = LOW;          // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
    input:checked+.slider {background-color: #2196F3}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?state=1", true); }
  else { xhr.open("GET", "/update?state=0", true); }
  xhr.send();
}

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var inputChecked;
      var outputStateM;
      if( this.responseText == 1){ 
        inputChecked = true;
        outputStateM = "On";
      }
      else { 
        inputChecked = false;
        outputStateM = "Off";
      }
      document.getElementById("output").checked = inputChecked;
      document.getElementById("outputState").innerHTML = outputStateM;
    }
  };
  xhttp.open("GET", "/state", true);
  xhttp.send();
}, 1000 ) ;
</script>
</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons ="";
    String outputStateValue = outputState();
    buttons+= "<h4>Output - GPIO 2 - State <span id=\"outputState\"></span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"output\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons;
  }
  return String();
}

String outputState(){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
  return "";
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(output, OUTPUT);
  digitalWrite(output, LOW);
  pinMode(buttonPin, INPUT);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?state=<inputMessage>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/update?state=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      digitalWrite(output, inputMessage.toInt());
      ledState = !ledState;
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });

  // Send a GET request to <ESP_IP>/state
  server.on("/state", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(digitalRead(output)).c_str());
  });
  // Start server
  server.begin();
}
  
void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  // set the LED:
  digitalWrite(output, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////     webSocket toggle  /////////////////////////////////////////////////////////////
/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp32-websocket-server-arduino/
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "ELEC302";
const char* password = "elec1234";

bool ledState = 0;
const int ledPin = 2;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 600px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    padding-top:10px;
    padding-bottom:20px;
  }
  .button {
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .state {
     font-size: 1.5rem;
     color:#8c8c8c;
     font-weight: bold;
   }
  </style>
<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="topnav">
    <h1>ESP WebSocket Server</h1>
  </div>
  <div class="content">
    <div class="card">
      <h2>Output - GPIO 2</h2>
      <p class="state">state: <span id="state">%STATE%</span></p>
      <p><button id="button" class="button">Toggle</button></p>
    </div>
  </div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
    var state;
    if (event.data == "1"){
      state = "ON";
    }
    else{
      state = "OFF";
    }
    document.getElementById('state').innerHTML = state;
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  function initButton() {
    document.getElementById('button').addEventListener('click', toggle);
  }
  function toggle(){
    websocket.send('toggle');
  }
</script>
</body>
</html>
)rawliteral";

void notifyClients() {
  ws.textAll(String(ledState));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "toggle") == 0) {
      ledState = !ledState;
      notifyClients();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if (ledState){
      return "ON";
    }
    else{
      return "OFF";
    }
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}

void loop() {
  ws.cleanupClients();
  digitalWrite(ledPin, ledState);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// esp32_websocket_bmp280     index.html   ///////////////////////////////////////////////////////////////////

<!DOCTYPE html>
<html>
    <head>
        <title>ESP IOT DASHBOARD</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="icon" type="image/png" href="favicon.png">
        <link rel="stylesheet" type="text/css" href="style.css">
    </head>
    <body>
        <div class="topnav">
            <h1>SENSOR READINGS (WEBSOCKET)</h1>
        </div>
        <div class="content">
            <div class="card-grid">
                <div class="card">
                    <p class="card-title"><i class="fas fa-thermometer-threequarters" style="color:#059e8a;"></i> Temperature</p>
                    <p class="reading"><span id="temperature"></span> &deg;C</p>
                </div>
                <div class="card">
                    <p class="card-title"> Humidity</p>
                    <p class="reading"><span id="humidity"></span> &percnt;</p>
                </div>
                <div class="card">
                    <p class="card-title"> Pressure</p>
                    <p class="reading"><span id="pressure"></span> hpa</p>
                </div>
            </div>
        </div>
        <script src="script.js"></script>
    </body>
</html>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////// esp32_websocket_bmp280  style.css ////////////////////////////////////////////////////////  
  html {
    font-family: Arial, Helvetica, sans-serif;
    display: inline-block;
    text-align: center;
}
h1 {
    font-size: 1.8rem;
    color: white;
}
.topnav {
    overflow: hidden;
    background-color: #0A1128;
}
body {
    margin: 0;
}
.content {
    padding: 50px;
}
.card-grid {
    max-width: 800px;
    margin: 0 auto;
    display: grid;
    grid-gap: 2rem;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
}
.card {
    background-color: white;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
}
.card-title {
    font-size: 1.2rem;
    font-weight: bold;
    color: #034078
}
.reading {
    font-size: 1.2rem;
    color: #1282A2;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////// esp32_websocket_bmp280  script.js //////////////////////////////////////////


var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
// Init web socket when the page loads
window.addEventListener('load', onload);

function onload(event) {
    initWebSocket();
}

function getReadings(){
    websocket.send("getReadings");
}

function initWebSocket() {
    console.log('Trying to open a WebSocket connection…');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

// When websocket is established, call the getReadings() function
function onOpen(event) {
    console.log('Connection opened');
    getReadings();
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

// Function that receives the message from the ESP32 with the readings
function onMessage(event) {
    console.log(event.data);
    var myObj = JSON.parse(event.data);
    var keys = Object.keys(myObj);

    for (var i = 0; i < keys.length; i++){
        var key = keys[i];
        document.getElementById(key).innerHTML = myObj[key];
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////  esp32_websocket_bmp280_AHT20.ino  //////////////////////////////////////////
/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete instructions at https://RandomNerdTutorials.com/esp32-websocket-server-sensor/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include <Adafruit_BMP280.h>
#include <AHT20.h>
AHT20 aht20;
Adafruit_BMP280 bmp; // I2C

// Replace with your network credentials
const char* ssid = "ELEC302";
const char* password = "elec1234";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create a WebSocket object
AsyncWebSocket ws("/ws");

// Json Variable to Hold Sensor Readings
JSONVar readings;

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;


// Init BMP280
void initBMP_AHT()
{
  unsigned status;
  status = bmp.begin();
  if (!status) 
  {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    //while (1) delay(10);
  }
  
  if (aht20.begin() == false)
  {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    //while (1);
  }

  if (!status&&aht20.begin() == false) 
  {
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

}

// Get Sensor Readings and return JSON object
String getSensorReadings()
{
  readings["temperature"] = String(bmp.readTemperature());
  readings["humidity"] =  String(aht20.getHumidity());
  readings["pressure"] = String(bmp.readPressure()/100.0F);
  String jsonString = JSON.stringify(readings);
  return jsonString;
}

// Initialize LittleFS
void initLittleFS() 
{
  if (!LittleFS.begin(true)) 
  {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  Serial.println("LittleFS mounted successfully");
}

// Initialize WiFi
void initWiFi() 
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void notifyClients(String sensorReadings) 
{
  ws.textAll(sensorReadings);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) 
{
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) 
  {
    //data[len] = 0;
    //String message = (char*)data;
    // Check if the message is "getReadings"
    //if (strcmp((char*)data, "getReadings") == 0) {
      //if it is, send current sensor readings
      String sensorReadings = getSensorReadings();
      Serial.print(sensorReadings);
      notifyClients(sensorReadings);
    //}
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) 
{
  switch (type) 
  {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() 
{
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void setup() 
{
  Serial.begin(115200);
  initBMP_AHT();
  initWiFi();
  initLittleFS();
  initWebSocket();

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) 
  {
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.serveStatic("/", LittleFS, "/");

  // Start server
  server.begin();
}

void loop() 
{
  if ((millis() - lastTime) > timerDelay) 
  {
    String sensorReadings = getSensorReadings();
    Serial.print(sensorReadings);
    notifyClients(sensorReadings);
    lastTime = millis();
  }
  ws.cleanupClients();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// esp32_webSocket_RCbot.ino /////////////////////////////////////////////////////////////////

/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-controls-car-via-web
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include "index.h"

#define CMD_STOP 0
#define CMD_FORWARD 1
#define CMD_BACKWARD 2
#define CMD_LEFT 4
#define CMD_RIGHT 8

#define ENA_PIN 14  // The ESP32 pin GPIO14 connected to the ENA pin L298N
#define IN1_PIN 27  // The ESP32 pin GPIO27 connected to the IN1 pin L298N
#define IN2_PIN 26  // The ESP32 pin GPIO26 connected to the IN2 pin L298N
#define IN3_PIN 25  // The ESP32 pin GPIO25 connected to the IN3 pin L298N
#define IN4_PIN 33  // The ESP32 pin GPIO33 connected to the IN4 pin L298N
#define ENB_PIN 32  // The ESP32 pin GPIO32 connected to the ENB pin L298N

const char* ssid = "YOUR_WIFI_SSID";     // CHANGE IT
const char* password = "YOUR_WIFI_PASSWORD";  // CHANGE IT

AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);  // WebSocket server on port 81

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      }
      break;
    case WStype_TEXT:
      //Serial.printf("[%u] Received text: %s\n", num, payload);
      String angle = String((char*)payload);
      int command = angle.toInt();
      Serial.print("command: ");
      Serial.println(command);

      switch (command) {
        case CMD_STOP:
          Serial.println("Stop");
          CAR_stop();
          break;
        case CMD_FORWARD:
          Serial.println("Move Forward");
          CAR_moveForward();
          break;
        case CMD_BACKWARD:
          Serial.println("Move Backward");
          CAR_moveBackward();
          break;
        case CMD_LEFT:
          Serial.println("Turn Left");
          CAR_turnLeft();
          break;
        case CMD_RIGHT:
          Serial.println("Turn Right");
          CAR_turnRight();
          break;
        default:
          Serial.println("Unknown command");
      }

      break;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);

  digitalWrite(ENA_PIN, HIGH);  // set full speed
  digitalWrite(ENB_PIN, HIGH);  // set full speed

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  // Serve a basic HTML page with JavaScript to create the WebSocket connection
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("Web Server: received a web page request");
    String html = HTML_CONTENT;  // Use the HTML content from the servo_html.h file
    request->send(200, "text/html", html);
  });

  server.begin();
  Serial.print("ESP32 Web Server's IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  webSocket.loop();
  // TO DO: Your code here
}

void CAR_moveForward() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_moveBackward() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}

void CAR_turnLeft() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_turnRight() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_stop() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// esp32_webSocket_RCbot   index.h ////////////////////////////////////////////////////////////
/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-controls-car-via-web
 */

const char *HTML_CONTENT = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>ESP32 Control Car via Web</title>
<meta name="viewport" content="width=device-width, initial-scale=0.7, maximum-scale=1, user-scalable=no">
<style type="text/css">
body { text-align: center; font-size: 24px;}
button { text-align: center; font-size: 24px;}
#container {
    margin-right: auto;
    margin-left: auto;
  width: 400px; 
    height: 400px;
    position: relative;
    margin-bottom: 10px;
}
div[class^='button'] { position: absolute; }
.button_up, .button_down { width:214px; height:104px;}
.button_left, .button_right { width:104px; height:214px;}
.button_stop { width:178px; height:178px;}
.button_up {
    background: url('https://esp32io.com/images/tutorial/up_inactive.png') no-repeat; 
  background-size: contain; 
    left: 200px;
    top: 0px;
  transform: translateX(-50%);
}

.button_down {
    background: url('https://esp32io.com/images/tutorial/down_inactive.png') no-repeat; 
  background-size: contain; 
    left:200px;
    bottom: 0px;
  transform: translateX(-50%);
}

.button_right {
    background: url('https://esp32io.com/images/tutorial/right_inactive.png') no-repeat;
  background-size: contain;   
    right: 0px;
    top: 200px;
  transform: translateY(-50%);
}

.button_left {
    background: url('https://esp32io.com/images/tutorial/left_inactive.png') no-repeat; 
  background-size: contain;
    left:0px;
    top: 200px;
  transform: translateY(-50%);
}

.button_stop {
  background: url('https://esp32io.com/images/tutorial/stop_inactive.png') no-repeat; 
  background-size: contain;
    left:200px;
    top: 200px;
  transform: translate(-50%, -50%);
}
</style>
<script>
var CMD_STOP     = 0;
var CMD_FORWARD  = 1;
var CMD_BACKWARD = 2;
var CMD_LEFT     = 4;
var CMD_RIGHT    = 8;
var img_name_lookup = {
  [CMD_STOP]:     "stop",
  [CMD_FORWARD]:  "up",
  [CMD_BACKWARD]: "down",
  [CMD_LEFT]:     "left",
  [CMD_RIGHT]:    "right"
}
var ws = null;

function init() 
{
  
  var container = document.querySelector("#container");
    container.addEventListener("touchstart", mouse_down);
    container.addEventListener("touchend", mouse_up);
    container.addEventListener("touchcancel", mouse_up);
    container.addEventListener("mousedown", mouse_down);
    container.addEventListener("mouseup", mouse_up);
    container.addEventListener("mouseout", mouse_up);    
}
function ws_onmessage(e_msg)
{
    e_msg = e_msg || window.event; // MessageEvent
 
    //alert("msg : " + e_msg.data);
}
function ws_onopen()
{
  document.getElementById("ws_state").innerHTML = "OPEN";
  document.getElementById("wc_conn").innerHTML = "Disconnect";
}
function ws_onclose()
{
  document.getElementById("ws_state").innerHTML = "CLOSED";
  document.getElementById("wc_conn").innerHTML = "Connect";
  console.log("socket was closed");
  ws.onopen = null;
  ws.onclose = null;
  ws.onmessage = null;
  ws = null;
}
function wc_onclick()
{
  if(ws == null)
  {
    ws = new WebSocket("ws://" + window.location.host + ":81");
    document.getElementById("ws_state").innerHTML = "CONNECTING";
    
    ws.onopen = ws_onopen;
    ws.onclose = ws_onclose;
    ws.onmessage = ws_onmessage; 
  }
  else
    ws.close();
}
function mouse_down(event) 
{
  if (event.target !== event.currentTarget) 
  {
    var id = event.target.id;
    send_command(id);
    event.target.style.backgroundImage = "url('https://esp32io.com/images/tutorial/" + img_name_lookup[id] + "_active.png')";
    }
    event.stopPropagation();    
    event.preventDefault();    
}

function mouse_up(event) 
{
  if (event.target !== event.currentTarget) 
  {
    var id = event.target.id;
    send_command(CMD_STOP);
    event.target.style.backgroundImage = "url('https://esp32io.com/images/tutorial/" + img_name_lookup[id] + "_inactive.png')";
    }
    event.stopPropagation();   
    event.preventDefault();    
}
function send_command(cmd) 
{   
  if(ws != null)
    if(ws.readyState == 1)
      ws.send(cmd + "\r\n");   
}

window.onload = init;
</script>
</head>
<body>
<h2>ESP32 - RC Car via Web</h2>
<div id="container">
  <div id="0" class="button_stop"></div>
    <div id="1" class="button_up"></div>
    <div id="2" class="button_down"></div>
    <div id="8" class="button_right"></div>
    <div id="4" class="button_left"></div>
</div>
<p>
WebSocket : <span id="ws_state" style="color:blue">closed</span><br>
</p>
<button id="wc_conn" type="button" onclick="wc_onclick();">Connect</button>
<br>
<br>
<div class="sponsor">Sponsored by <a href="https://amazon.com/diyables">DIYables</a></div>
</body>
</html>
)=====";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

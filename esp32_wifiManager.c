#include <WiFi.h>
#include <WebServer.h>
#include <time.h>

// Station Mode Credentials
const char* sta_ssid = "ELEC302";
const char* sta_password = "elec1234";

// AP Mode Credentials
const char* ap_ssid = "ESP32_AP";
const char* ap_password = "12345678";

// IP Configurations
IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

bool is_authenticated() {
  if (!server.authenticate("admin", "admin"))
  {
    server.requestAuthentication();
    return false;
  }
  return true;
}

String getPage(String content) {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>ESP32 Web Server</title>";
  html += "<style>";
  html += "body{font-family:Arial,sans-serif;margin:0;padding:20px;background:#f0f2f5;}";
  html += "nav{background:#333;padding:10px;margin-bottom:20px;}";
  html += "nav a{color:white;text-decoration:none;margin-right:15px;}";
  html += ".container{max-width:800px;margin:0 auto;background:white;padding:20px;border-radius:8px;box-shadow:0 2px 4px rgba(0,0,0,0.1);}";
  html += "@keyframes fadeIn{from{opacity:0;}to{opacity:1;}}";
  html += ".animate{animation:fadeIn 1s;}";
  html += "</style></head><body>";
  html += "<nav>";
  html += "<a href='/'>Home</a>";
  html += "<a href='/timer'>Timer</a>";
  html += "<a href='/info'>Info</a>";
  html += "<a href='/goodbye'>Goodbye</a>";
  html += "</nav>";
  html += "<div class='container animate'>";
  html += content;
  html += "</div></body></html>";
  return html;
}

void handleHome() {
  String content = "<h1>Welcome to ESP32 Web Server</h1>";
  content += "<div style='text-align:center;'>";
  content += "<div style='font-size:48px;animation:bounce 1s infinite;'>hello</div>";
  content += "<p>Welcome! Explore our pages using the navigation bar above.</p>";
  content += "<div style='background:#e8f5e9;padding:10px;border-radius:5px;margin-top:20px;'>";
  content += "<h2>Network Information</h2>";
  content += "<p><strong>WiFi Station IP:</strong> ";
  if (WiFi.status() == WL_CONNECTED) {
    content += WiFi.localIP().toString();
  } else {
    content += "Not connected";
  }
  content += "</p>";
  content += "<p><strong>Access Point IP:</strong> ";
  content += WiFi.softAPIP().toString();
  content += "</p>";
  content += "<p><strong>Access Point SSID:</strong> ";
  content += ap_ssid;
  content += "</p>";
  content += "</div>";
  content += "</div>";
  content += "<style>@keyframes bounce{0%,100%{transform:translateY(0);}50%{transform:translateY(-20px);}}</style>";
  server.send(200, "text/html", getPage(content));
}

void handleTimer() {
  String content = "<h1>Current Time</h1>";
  content += "<div id='clock' style='font-size:48px;text-align:center;'>Loading...</div>";
  content += "<script>";
  content += "function updateClock(){";
  content += "const now=new Date();";
  content += "document.getElementById('clock').textContent=now.toLocaleTimeString();}";
  content += "setInterval(updateClock,1000);updateClock();";
  content += "</script>";
  server.send(200, "text/html", getPage(content));
}

void handleInfo() {
  if (!is_authenticated()) {
    return;
  }
  
  String content = "<h1>Detailed Network Information</h1>";
  content += "<div style='background:#e3f2fd;padding:15px;border-radius:5px;'>";
  content += "<h2>Station Mode (Client)</h2>";
  content += "<p><strong>Status:</strong> ";
  content += (WiFi.status() == WL_CONNECTED) ? "Connected" : "Disconnected";
  content += "</p>";
  content += "<p><strong>IP Address:</strong> ";
  content += (WiFi.status() == WL_CONNECTED) ? WiFi.localIP().toString() : "N/A";
  content += "</p>";
  content += "<p><strong>Subnet Mask:</strong> ";
  content += (WiFi.status() == WL_CONNECTED) ? WiFi.subnetMask().toString() : "N/A";
  content += "</p>";
  content += "<p><strong>Gateway IP:</strong> ";
  content += (WiFi.status() == WL_CONNECTED) ? WiFi.gatewayIP().toString() : "N/A";
  content += "</p>";
  content += "<p><strong>MAC Address:</strong> ";
  content += WiFi.macAddress();
  content += "</p>";
  content += "<p><strong>Connected to SSID:</strong> ";
  content += sta_ssid;
  content += "</p>";
  
  content += "<h2>Access Point Mode</h2>";
  content += "<p><strong>AP IP:</strong> ";
  content += WiFi.softAPIP().toString();
  content += "</p>";
  content += "<p><strong>AP MAC Address:</strong> ";
  content += WiFi.softAPmacAddress();
  content += "</p>";
  content += "<p><strong>AP SSID:</strong> ";
  content += ap_ssid;
  content += "</p>";
  content += "<p><strong>Connected Stations:</strong> ";
  content += WiFi.softAPgetStationNum();
  content += "</p>";
  content += "</div>";
  
  server.send(200, "text/html", getPage(content));
}

void handleGoodbye() {
  String content = "<h1>Goodbye!</h1>";
  content += "<div style='text-align:center;'>";
  content += "<div style='font-size:48px;animation:wave 1s infinite;'>👋</div>";
  content += "<p>Thank you for visiting. Come back soon!</p>";
  content += "</div>";
  content += "<style>@keyframes wave{0%,100%{transform:rotate(0deg);}50%{transform:rotate(20deg);}}</style>";
  server.send(200, "text/html", getPage(content));
}

void handleNotFound() {
  String content = "<h1>404: Not Found</h1><p>The requested page was not found.</p>";
  server.send(404, "text/html", getPage(content));
}
void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi network
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ap_ssid, ap_password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  
  WiFi.begin(sta_ssid, sta_password);
  
  Serial.println("Setting up Access Point: ");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  
  Serial.println("Connecting to WiFi network...");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.print("Station IP address: ");
    Serial.println(WiFi.localIP());
    
    // Init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  } else {
    Serial.println("\nFailed to connect to WiFi network");
  }

  server.on("/", handleHome);
  server.on("/timer", handleTimer);
  server.on("/info", handleInfo);
  server.on("/goodbye", handleGoodbye);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  wifi manager "index.html" //////////////////////////////////////////////////////
<!DOCTYPE html>
<html>
  <head>
    <title>ESP WEB SERVER</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" href="style.css">
    <link rel="icon" type="image/png" href="favicon.png">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  </head>
  <body>
    <div class="topnav">
      <h1>ESP WEB SERVER</h1>
    </div>
    <div class="content">
      <div class="card-grid">
        <div class="card">
          <p class="card-title"><i class="fas fa-lightbulb"></i> GPIO 2</p>
          <p>
            <a href="on"><button class="button-on">ON</button></a>
            <a href="off"><button class="button-off">OFF</button></a>
          </p>
          <p class="state">State: %STATE%</p>
        </div>
      </div>
    </div>
  </body>
</html>

  
///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// wifi manager "wifimanager.html" /////////////////////////////////////////
  
<!DOCTYPE html>
<html>
<head>
  <title>ESP Wi-Fi Manager</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
  <div class="topnav">
    <h1>ESP Wi-Fi Manager</h1>
  </div>
  <div class="content">
    <div class="card-grid">
      <div class="card">
        <form action="/" method="POST">
          <p>
            <label for="ssid">SSID</label>
            <input type="text" id ="ssid" name="ssid"><br>
            <label for="pass">Password</label>
            <input type="text" id ="pass" name="pass"><br>
            <label for="ip">IP Address</label>
            <input type="text" id ="ip" name="ip"><br>
            <label for="gateway">Gateway Address</label>
            <input type="text" id ="gateway" name="gateway"><br>
            <input type ="submit" value ="Submit">
          </p>
        </form>
      </div>
    </div>
  </div>
</body>
</html>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// wifi manager "style.css" ////////////////////////////////////////////////////////

html {
  font-family: Arial, Helvetica, sans-serif; 
  display: inline-block; 
  text-align: center;
}

h1 {
  font-size: 1.8rem; 
  color: white;
}

p { 
  font-size: 1.4rem;
}

.topnav { 
  overflow: hidden; 
  background-color: #0A1128;
}

body {  
  margin: 0;
}

.content { 
  padding: 5%;
}

.card-grid { 
  max-width: 800px; 
  margin: 0 auto; 
  display: grid; 
  grid-gap: 2rem; 
  grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
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

input[type=submit] {
  border: none;
  color: #FEFCFB;
  background-color: #034078;
  padding: 15px 15px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  width: 100px;
  margin-right: 10px;
  border-radius: 4px;
  transition-duration: 0.4s;
  }

input[type=submit]:hover {
  background-color: #1282A2;
}

input[type=text], input[type=number], select {
  width: 50%;
  padding: 12px 20px;
  margin: 18px;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
}

label {
  font-size: 1.2rem; 
}
.value{
  font-size: 1.2rem;
  color: #1282A2;  
}
.state {
  font-size: 1.2rem;
  color: #1282A2;
}
button {
  border: none;
  color: #FEFCFB;
  padding: 15px 32px;
  text-align: center;
  font-size: 16px;
  width: 100px;
  border-radius: 4px;
  transition-duration: 0.4s;
}
.button-on {
  background-color: #034078;
}
.button-on:hover {
  background-color: #1282A2;
}
.button-off {
  background-color: #858585;
}
.button-off:hover {
  background-color: #252524;
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// wifi manager " esp32_wifiManager.ino ///////////////////////////////////
/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete instructions at https://RandomNerdTutorials.com/esp32-wi-fi-manager-asyncwebserver/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "LittleFS.h"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_4 = "gateway";

//Variables to save values from HTML form
String ssid;
String pass;
String ip;
String gateway;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";

IPAddress localIP;
//IPAddress localIP(192, 168, 1, 200); // hardcoded

// Set your Gateway IP address
IPAddress localGateway;
//IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 0, 0);

// Timer variables
unsigned long previousMillis = 0;
const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds)

// Set LED GPIO
const int ledPin = 2;
// Stores LED state

String ledState;

// Initialize LittleFS
void initLittleFS() {
  if (!LittleFS.begin(true)) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  Serial.println("LittleFS mounted successfully");
}

// Read File from LittleFS
String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return String();
  }
  
  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;     
  }
  return fileContent;
}

// Write file to LittleFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
}

// Initialize WiFi
bool initWiFi() 
{
  if(ssid=="")
  {
    Serial.println("Undefined SSID.");
    return false;
  }
  
  WiFi.mode(WIFI_STA);
  if(ip!="")
  {
    Serial.println("Assigned IP.");
    localIP.fromString(ip.c_str());
    localGateway.fromString(gateway.c_str());
    if (!WiFi.config(localIP, localGateway, subnet)){
      Serial.println("STA Failed to configure");
      return false;
    }
  }else
  {
    Serial.println("Undefined IP.");
  }



 
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;

  while(WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failed to connect.");
      return false;
    }
  }

  Serial.println(WiFi.localIP());
  return true;
}

// Replaces placeholder with LED state value
String processor(const String& var) {
  if(var == "STATE") {
    if(digitalRead(ledPin)) {
      ledState = "ON";
    }
    else {
      ledState = "OFF";
    }
    return ledState;
  }
  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  initLittleFS();

  // Set GPIO 2 as an OUTPUT
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Load values saved in LittleFS
  ssid = readFile(LittleFS, ssidPath);
  pass = readFile(LittleFS, passPath);
  ip = readFile(LittleFS, ipPath);
  gateway = readFile (LittleFS, gatewayPath);
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(ip);
  Serial.println(gateway);

  if(initWiFi()) {
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(LittleFS, "/index.html", "text/html", false, processor);
    });
    server.serveStatic("/", LittleFS, "/");
    
    // Route to set GPIO state to HIGH
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
      digitalWrite(ledPin, HIGH);
      request->send(LittleFS, "/index.html", "text/html", false, processor);
    });

    // Route to set GPIO state to LOW
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
      digitalWrite(ledPin, LOW);
      request->send(LittleFS, "/index.html", "text/html", false, processor);
    });
    server.begin();
  }
  else {
    // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP); 

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/wifimanager.html", "text/html");
    });
    
    server.serveStatic("/", LittleFS, "/");
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        const AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid value
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            // Write file to save value
            writeFile(LittleFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(LittleFS, passPath, pass.c_str());
          }
          // HTTP POST ip value
          if (p->name() == PARAM_INPUT_3) {
            ip = p->value().c_str();
            Serial.print("IP Address set to: ");
            Serial.println(ip);
            // Write file to save value
            writeFile(LittleFS, ipPath, ip.c_str());
          }
          // HTTP POST gateway value
          if (p->name() == PARAM_INPUT_4) {
            gateway = p->value().c_str();
            Serial.print("Gateway set to: ");
            Serial.println(gateway);
            // Write file to save value
            writeFile(LittleFS, gatewayPath, gateway.c_str());
          }
          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: " + ip);
      delay(3000);
      ESP.restart();
    });
    server.begin();
  }
}

void loop() {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// esp32 basic OTA ////////////////////////////////////////////////////////////////
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "ELEC302";
const char* password = "elec1234";

//variabls for blinking an LED with Millis
const int led = 2; // ESP32 Pin to which onboard LED is connected
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 1000;  // interval at which to blink (milliseconds)
int ledState = LOW;  // ledState used to set the LED

void setup() 
{
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("myesp32_aim");

  // No authentication by default
  ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  ArduinoOTA.handle();

    
//loop to blink without delay
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    ledState = !ledState;
    // set the LED with the ledState of the variable:
    digitalWrite(led,  ledState);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

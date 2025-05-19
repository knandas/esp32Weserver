///////////////////////////////// test weather String ///////////////////////////////////////////////////

{"coord":{"lon":100.4608,"lat":13.7442},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04d"}],"base":"stations","main":{"temp":328.11,"feels_like":314.53,"temp_min":304.12,"temp_max":308.69,"pressure":1007,"humidity":52,"sea_level":1007,"grnd_level":1006},"visibility":10000,"wind":{"speed":1.7,"deg":139,"gust":1.37},"clouds":{"all":99},"dt":1716258967,"sys":{"type":2,"id":2093772,"country":"TH","sunrise":1716245434,"sunset":1716291554},"timezone":25200,"id":1619460,"name":"Bangkok Noi","cod":200}

///////////////////////////////// test weather JSON ///////////////////////////////////////////////////

{
    "coord": {
        "lon": 100.4608,
        "lat": 13.7442
    },
    "weather": [
        {
            "id": 804,
            "main": "Clouds",
            "description": "overcast clouds",
            "icon": "04d"
        }
    ],
    "base": "stations",
    "main": {
        "temp": 328.11,
        "feels_like": 314.53,
        "temp_min": 304.12,
        "temp_max": 308.69,
        "pressure": 1007,
        "humidity": 52,
        "sea_level": 1007,
        "grnd_level": 1006
    },
    "visibility": 10000,
    "wind": {
        "speed": 1.7,
        "deg": 139,
        "gust": 1.37
    },
    "clouds": {
        "all": 99
    },
    "dt": 1716258967,
    "sys": {
        "type": 2,
        "id": 2093772,
        "country": "TH",
        "sunrise": 1716245434,
        "sunset": 1716291554
    },
    "timezone": 25200,
    "id": 1619460,
    "name": "Bangkok Noi",
    "cod": 200
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// F1 ////////////////////////////////////////////////////////////////
var count =  0;
count += 1;
msg.payload = "F1 " + msg.payload + " " + count;
return msg;

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// F2 ///////////////////////////////////////////////////////////

var count = context.get('count') || 0;
count += 1;
msg.payload = "F2 " + msg.payload + " " + count;
context.set('count', count);
return msg;

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// F3 //////////////////////////////////////////////////////////
var local = context.get('data') || {};
if (local.count === undefined)//test exists
{
    local.count = 0;
}
local.count += 1;
msg.payload = "F3 " + msg.payload + " " + local.count;
context.set('data', local);
return msg;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// flow /////////////////////////////////////////////////////////////////

var count = flow.get('count') || 0;
count += 1;
msg.payload = "F1 " + msg.payload + " " + count;
flow.set('count', count);
return msg;


//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

<html>
  <head>
    <title>Node-RED Web sample</title>
  </head>
  <body>
    <h1>Hello Node-RED!!</h1>
    <h2>Menu 1</h2>
    <p>It is Node-RED sample webpage.</p>
    <hr>
    <h2>Menu 2</h2>
    <p>It is Node-RED sample webpage.</p>
  </body>
</html>

 ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
var min=1;
var max=10;
var a = Math.floor(Math.random()*(max+1-min))+min;
msg.payload=a;
return msg;



////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////  example2 4 LEDs //////////////////////////////////////////////////
#include <WiFi.h>
#include <PubSubClient.h>


WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 

const char* ssid = "ELEC302";  //ELEC302_plus
const char* password = "elec1234";

char *mqttServer = "broker.emqx.io";
int mqttPort = 1883;
//const char* mqttUser = "yourInstanceUsername";
//const char* mqttPassword = "yourInstancePassword";

#define out1 4
#define out2 2
#define out3 13
#define out4 12

#define topic1 "mut/iot/light1"
#define topic2 "mut/iot/light2"
#define topic3 "mut/iot/light3"
#define topic4 "mut/iot/light4"

void setupMQTT() 
{
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);
}

void reconnect() 
{
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      //client.connect(clientId.c_str(), mqttUser, mqttPassword
      if (mqttClient.connect(clientId.c_str())) 
      {
        Serial.println("Connected.");
        // subscribe to topic
        mqttClient.subscribe(topic1);   //in topic
        mqttClient.subscribe(topic2);
        mqttClient.subscribe(topic3);
        mqttClient.subscribe(topic4);
      }      
  }
}

void setup() 
{
  Serial.begin(115200);
  pinMode(out1,OUTPUT);
  pinMode(out2,OUTPUT);
  pinMode(out3,OUTPUT);
  pinMode(out4,OUTPUT);
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    } 
    Serial.println("");
    Serial.println("Connected to Wi-Fi");
  setupMQTT();
}


void loop() 
{
  if (!mqttClient.connected()){ reconnect();}
  mqttClient.loop();
  delay(10);
}

void callback(char* topic, byte* message, unsigned int length) 
{
  String messageTemp;
  Serial.print("Callback - ");
  Serial.print("Message:");
  for (int i = 0; i < length; i++) 
  {
    //Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

 if (strcmp(topic, topic1) == 0) 
 {
  if (messageTemp == "true") 
  { 
   digitalWrite(out1, HIGH);  Serial.println("out1: on");
  } else {
   digitalWrite(out1, LOW);  Serial.println("out1: off");
  }
 }else if (strcmp(topic, topic2) == 0) 
 {
  if (messageTemp == "true") { 
   digitalWrite(out2, HIGH); Serial.println("out2: on");
  } else {
   digitalWrite(out2, LOW); Serial.println("out2: off");
  }
 }else if (strcmp(topic, topic3) == 0) 
 {
  if (messageTemp == "true") { 
   digitalWrite(out3, HIGH); Serial.println("out3: on");
  } else {
   digitalWrite(out3, LOW); Serial.println("out3: off");
  }
 }else if (strcmp(topic, topic4) == 0) 
 {
  if (messageTemp == "true") { 
   digitalWrite(out4, HIGH); Serial.println("out4: on");
  } else {
   digitalWrite(out4, LOW); Serial.println("out4: off");
  }
 }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////  example3 4 LEDs + BMP280+AHT20    //////////////////////////////////////////////////
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_BMP280.h>
#include <AHT20.h>
AHT20 aht20;
Adafruit_BMP280 bmp; // I2C
float  temperature= 0;
float  humidity=  0;
float  pressure = 0;
// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 

const char* ssid = "wifi1971_2";  //ELEC302_plus
const char* password = "fedcba9876";

char *mqttServer = "broker.emqx.io";
int mqttPort = 1883;
//const char* mqttUser = "yourInstanceUsername";
//const char* mqttPassword = "yourInstancePassword";

#define out1 4
#define out2 2
#define out3 13
#define out4 12

#define topic1 "mut/iot2/light1"
#define topic2 "mut/iot2/light2"
#define topic3 "mut/iot2/light3"
#define topic4 "mut/iot2/light4"
#define topic5 "mut/iot2/temperature"
#define topic6 "mut/iot2/humidity"
#define topic7 "mut/iot2/pressure"

void setupMQTT() 
{
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);
}

void reconnect() 
{
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      //client.connect(clientId.c_str(), mqttUser, mqttPassword
      if (mqttClient.connect(clientId.c_str())) 
      {
        Serial.println("Connected.");
        // subscribe to topic
        mqttClient.subscribe(topic1);   //in topic
        mqttClient.subscribe(topic2);
        mqttClient.subscribe(topic3);
        mqttClient.subscribe(topic4);
      }      
  }
}

void setup() 
{
  Serial.begin(115200);
  initBMP_AHT(); // Init BMP280 + AHT20
  pinMode(out1,OUTPUT);
  pinMode(out2,OUTPUT);
  pinMode(out3,OUTPUT);
  pinMode(out4,OUTPUT);
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    } 
    Serial.println("");
    Serial.println("Connected to Wi-Fi");
  setupMQTT();
}


void loop() 
{
  if (!mqttClient.connected()){ reconnect();}
  mqttClient.loop();

  if ((millis() - lastTime) > timerDelay) //Send an HTTP POST request every 30 seconds
  {
    readSensor();
    char msg_out[20];
    dtostrf(temperature,3,2,msg_out);
    mqttClient.publish(topic5,msg_out);
    dtostrf(humidity,2,2,msg_out);
    mqttClient.publish(topic6,msg_out);
    dtostrf(pressure,5,2,msg_out);
    mqttClient.publish(topic7,msg_out);
    lastTime=millis();
  }
  delay(10);
}

void callback(char* topic, byte* message, unsigned int length) 
{
  String messageTemp;
  Serial.print("Callback - ");
  Serial.print("Message:");
  for (int i = 0; i < length; i++) 
  {
    //Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();o

 if (strcmp(topic, topic1) == 0) 
 {
  if (messageTemp == "true") 
  { 
   digitalWrite(out1, HIGH);  Serial.println("out1: on");
  } else {
   digitalWrite(out1, LOW);  Serial.println("out1: off");
  }
 }else if (strcmp(topic, topic2) == 0) 
 {
  if (messageTemp == "true") { 
   digitalWrite(out2, HIGH); Serial.println("out2: on");
  } else {
   digitalWrite(out2, LOW); Serial.println("out2: off");
  }
 }else if (strcmp(topic, topic3) == 0) 
 {
  if (messageTemp == "true") { 
   digitalWrite(out3, HIGH); Serial.println("out3: on");
  } else {
   digitalWrite(out3, LOW); Serial.println("out3: off");
  }
 }else if (strcmp(topic, topic4) == 0) 
 {
  if (messageTemp == "true") { 
   digitalWrite(out4, HIGH); Serial.println("out4: on");
  } else {
   digitalWrite(out4, LOW); Serial.println("out4: off");
  }
 }
}



// Init BMP280 + AHT20
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

void readSensor()
{
  temperature= bmp.readTemperature();
  humidity=  aht20.getHumidity();
  pressure = bmp.readPressure()/100.0F;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// mqtt dashboard json ////////////////////////////////////////////////////////

// example3 esp32 JSON+servo
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "myBounce.h"

#include <Adafruit_BMP280.h>
#include <AHT20.h>
AHT20 aht20;
Adafruit_BMP280 bmp; // I2C
float  temperature= 0;
float  humidity=  0;
float  pressure = 0;


WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 

const char* ssid = "ELEC302";  //ELEC302_plus
const char* password = "elec1234";

char *mqttServer = "broker.emqx.io";
int mqttPort = 1883;

#define servo1 25
#define out1 4
#define out2 2
#define out3 13
#define out4 12
#define sw1 34
#define sw2 35
#define sw3 32
#define sw4 33
#define in1 36


unsigned long delayTime1=0,delayTime2=0 ; 
myBounce SW1(sw1);
myBounce SW2(sw2);
myBounce SW3(sw3);
myBounce SW4(sw4);
int state1=1,state2=1,state3=1,state4=1;
unsigned long lastMillis;
unsigned int delayTime=10000;
unsigned int now=0,lastRead=0;
#define thisDevice 1

#define topic1 "MIIX/topic1" ///////send topic///// 
#define topic2 "MIIX/topic2" ///////receive topic///// 

void setup() 
{
  Serial.begin(115200);
  initBMP_AHT(); // Init BMP280 + AHT20
  pinMode(out1,OUTPUT); pinMode(out2,OUTPUT);
  pinMode(out3,OUTPUT); pinMode(out4,OUTPUT);
   WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    } 
    Serial.println("");
    Serial.println("Connected to Wi-Fi");
  setupMQTT();
}

void loop() 
{
  if (!mqttClient.connected()) reconnect();
  mqttClient.loop();
  if(SW1.update()==1)
  { state1=!state1;  sendMQTT(); digitalWrite(out1,state1);}
  if(SW2.update()==1)  
  { state2=!state2;  sendMQTT(); digitalWrite(out2,state2);}
  if(SW3.update()==1)
  { state3=!state3; sendMQTT();  digitalWrite(out3,state3);}
  if(SW4.update()==1)
  { state4=!state4;  sendMQTT(); digitalWrite(out4,state4);}

  
  if ((millis() - lastMillis) > delayTime)
  {
    readSensor();
    sendMQTT();   
    lastMillis=millis();
    delay(10);
  }
  
}

void sendMQTT()
{
  StaticJsonDocument<256> doc;
  doc["device"] = thisDevice;
  doc["Temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["pressure"] = pressure;
  doc["state1"] =state1;
  doc["state2"] =state2;
  doc["state3"] =state3;
  doc["state4"] =state4;

  char out[256];
  int b =serializeJson(doc, out);
  Serial.print("bytes = ");
  Serial.println(b,DEC);
  Serial.println(out);
  mqttClient.publish(topic1, out);
  delay(10);
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char str[length+1];
  int i=0;
  for (i=0;i<length;i++) 
  {
    Serial.print((char)payload[i]);
    str[i]=(char)payload[i];
  }
  str[i] = 0; // Null termination
  String payload2=str;
  Serial.println();

  StaticJsonDocument <256> doc;
  deserializeJson(doc,payload);
  unsigned int device = doc["device"];
  if(device==thisDevice)
  {
    if(payload2.indexOf("state1")>0)
    {
      unsigned int st1 = doc["state1"];
      if(st1==1) state1=1; else state1=0;
    }
    if(payload2.indexOf("state2")>0)
    {
      unsigned int st2 = doc["state2"];
      if(st2==1) state2=1; else state2=0;
    }
    if(payload2.indexOf("state3")>0)
    {
      unsigned int st3 = doc["state3"];
      if(st3==1) state3=1; else state3=0;
    }
    if(payload2.indexOf("state4")>0)
    {
      unsigned int st4 = doc["state4"];
      if(st4==1) state4=1; else state4=0;
    }
    digitalWrite(out1,state1);
    digitalWrite(out2,state2);
    digitalWrite(out3,state3);
    digitalWrite(out4,state4);
    Serial.print("device:");Serial.println(device);
    Serial.print("state =");Serial.print(state1);
    Serial.print(state2); Serial.print(state3);
    Serial.println(state4);
    sendMQTT();
    delay(15);
  }
}

void setupMQTT() 
{
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);
}

void reconnect() 
{
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) 
  {
    Serial.println("Reconnecting to MQTT Broker..");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (mqttClient.connect(clientId.c_str())) 
    {
      Serial.println("Connected.");
      // subscribe to topic
      mqttClient.subscribe(topic2);   //in topic
    }
    delay(1000);      
  }
}


// Init BMP280 + AHT20
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

void readSensor()
{
  temperature= bmp.readTemperature();
  humidity=  aht20.getHumidity();
  pressure = bmp.readPressure()/1000.0F;
}


///////////////////////////////////////////////////////////////////
///////////////////// myBounce.h /////////////////////////////////
/*
 * myBounce.h
 */
#ifndef MYBOUNCE_H
#define MYBOUNCE_H
#include <Arduino.h>

    
class myBounce
{
  public:
   myBounce(byte pin);
   bool update();
  private:
   byte _pin;
   bool _sw_state;
   bool _last_sw_state;
   bool _buttonstate;
   bool _change;
   unsigned long _time; 
};

#endif

//////////////////////////////////////////////////////////////
////////////////// myBounce.cpp /////////////////////////////

/*
 * myBounce.cpp
 */

#include "myBounce.h"

myBounce::myBounce(byte pin)
{
   pinMode(pin, INPUT_PULLUP);
  _pin = pin;
}

bool myBounce::update()
{
  _change=0;
  _sw_state=digitalRead(_pin);
  if(_sw_state!=_last_sw_state)
  {
    _time=millis();
  }
  
  if((millis()-_time)>50)
  {
    if(_sw_state!=_buttonstate)
    {
      _buttonstate=_sw_state;
      if(_buttonstate==HIGH)
      {
        _change=1;
        _buttonstate=_sw_state;
      }
    }
  }
  _last_sw_state=_sw_state;
  return _change;
}

//////////////////////////////////////////////////////////////////////////////////////////

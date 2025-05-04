/////////////////////servo 1 /////////////////////////////////////////////////////
#include <Servo.h>
#define SERVO_PIN 25 // ESP32 pin GIOP25 connected to servo motor

Servo servoMotor;

void setup() 
{
  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
  servoMotor.write(90):
}

void loop() 
{
 sweep();
}	

void sweep()
{
    // rotates from 0 degrees to 180 degrees
  for (int pos = 0; pos <= 180; pos += 1) 
  {
    servoMotor.write(pos); // in steps of 1 degree
    delay(15); // waits 15ms to reach the position
  }

  // rotates from 180 degrees to 0 degrees
  for (int pos = 180; pos >= 0; pos -= 1) 
  {
    servoMotor.write(pos);
    delay(15); // waits 15ms to reach the position
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// servo 2 /////////////////////////////////////////////

#include <Servo.h>
#define SERVO_PIN 25 // ESP32 pin GIOP25 connected to servo motor
#define VR 36
Servo servoMotor;

void setup() 
{
  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
  servoMotor.write(90);
}

void loop() 
{
  int reading =analogRead(VR);
  int pos=map(reading,0,4096,0,180);
  servoMotor.write(pos); 
  delay(15);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////// MQTT example1 ///////////////////////////////////////////////////////////////

#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 

const char* ssid = "ELEC302";
const char* password = "elec1234";

char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

void setupMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);
}

void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // subscribe to topic
        mqttClient.subscribe("mut/secB/light1");   //in topic
      }      
  }
}

void setup() 
{
  Serial.begin(115200);
  pinMode(18,OUTPUT);
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    } 
    Serial.println("");
    Serial.println("Connected to Wi-Fi");
  setupMQTT();
}


void loop() {
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
  delay(50);
}

void callback(char* topic, byte* message, unsigned int length) 
{
  Serial.print("Callback - ");
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
  }
  Serial.println();
   // Switch on the LED if an 1 was received as first character
  if ((char)message[0] == '1') 
  {
    digitalWrite(18, HIGH); 
    Serial.println(" light1 on ");  
  } else 
  {
    digitalWrite(18, LOW); 
    Serial.println(" light1 off ");  
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////  example2 4 LEDs + SW  //////////////////////////////////////////////////
#include <WiFi.h>
#include <PubSubClient.h>
#include "myBounce.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 

const char* ssid = "ELEC302";  //ELEC302_plus
const char* password = "elec1234";

char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;
//const char* mqttUser = "yourInstanceUsername";
//const char* mqttPassword = "yourInstancePassword";

#define out1 4
#define out2 2
#define out3 13
#define out4 12
#define sw1 34
#define sw2 35
#define sw3 32
#define sw4 33

myBounce SW1(sw1);
myBounce SW2(sw2);
myBounce SW3(sw3);
myBounce SW4(sw4);

bool state1=1,state2=1,state3=1,state4=1;

#define topic1 "mut/miia0107/light1"
#define topic2 "mut/miia0107/light2"
#define topic3 "mut/miia0107/light3"
#define topic4 "mut/miia0107/light4"

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
  if (!mqttClient.connected()) reconnect();
  mqttClient.loop();
  if(SW1.update()==1)
  { 
    state1=!state1; digitalWrite(out1,state1); 
    mqttClient.publish(topic1,state1?"1":"0");
  }
  if(SW2.update()==1)  
  { 
    state2=!state2; digitalWrite(out2,state2); 
    mqttClient.publish(topic2,state2?"1":"0");
  }
  if(SW3.update()==1)
  { 
    state3=!state3; digitalWrite(out3,state3); 
    mqttClient.publish(topic3,state3?"1":"0");
  }
  if(SW4.update()==1)
  { 
    state4=!state4; digitalWrite(out4,state4); 
    mqttClient.publish(topic4,state4?"1":"0");
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
  Serial.println();

 if (strcmp(topic, topic1) == 0) 
 {
  // If the relay is on turn it off (and vice-versa)
  if (messageTemp == "1") 
  { 
   digitalWrite(out1, HIGH);  state1=1;
  } else {
   digitalWrite(out1, LOW);  state1=0;
  }
   Serial.print("mqtt out1: ");
   Serial.println(state1?"On":"Off");
 }else if (strcmp(topic, topic2) == 0) 
 {
  // If the relay is on turn it off (and vice-versa)
  if (messageTemp == "1") { 
   digitalWrite(out2, HIGH); state2=1;
  } else {
   digitalWrite(out2, LOW); state2=0;
  }
  Serial.print("mqtt out2: ");
  Serial.println(state2?"On":"Off");
 }else if (strcmp(topic, topic3) == 0) 
 {
  // If the relay is on turn it off (and vice-versa)
  if (messageTemp == "1") { 
   digitalWrite(out3, HIGH); state3=1;
  } else {
   digitalWrite(out3, LOW); state3=0;
  }
  Serial.print("mqtt out3: ");
  Serial.println(state3?"On":"Off");
 }else if (strcmp(topic, topic4) == 0) 
 {
  // If the relay is on turn it off (and vice-versa)
  if (messageTemp == "1") { 
   digitalWrite(out4, HIGH); state4=1;
  } else {
   digitalWrite(out4, LOW); state4=0;
  }
  Serial.print("mqtt out4: ");
  Serial.println(state4?"On":"Off");
 }

}




//////////////////////////////////////////////////////////////////////////////////////
#include <WiFi.h>
#include <PubSubClient.h>
#include "myBounce.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 

const char* ssid = "ELEC302";  //ELEC302_plus
const char* password = "elec1234";

char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;
//const char* mqttUser = "yourInstanceUsername";
//const char* mqttPassword = "yourInstancePassword";

#define out1 4
#define out2 2
#define out3 13
#define out4 12
#define sw1 34
#define sw2 35
#define sw3 32
#define sw4 33

myBounce SW1(sw1);
myBounce SW2(sw2);
myBounce SW3(sw3);
myBounce SW4(sw4);
bool state1=1,state2=1,state3=1,state4=1;
#define topic1 "mut/miia0107/light1"
#define topic2 "mut/miia0107/light2"
#define topic3 "mut/miia0107/light3"
#define topic4 "mut/miia0107/light4"
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
  if (!mqttClient.connected()) reconnect();
  mqttClient.loop();
  if(SW1.update()==1)
  { 
    state1=!state1; digitalWrite(out1,state1); 
    mqttClient.publish(topic1,state1?"1":"0");
  }
  if(SW2.update()==1)  
  { 
    state2=!state2; digitalWrite(out2,state2); 
    mqttClient.publish(topic2,state2?"1":"0");
  }
  if(SW3.update()==1)
  { 
    state3=!state3; digitalWrite(out3,state3); 
    mqttClient.publish(topic3,state3?"1":"0");
  }
  if(SW4.update()==1)
  { 
    state4=!state4; digitalWrite(out4,state4); 
    mqttClient.publish(topic4,state4?"1":"0");
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
  Serial.println();

 if (strcmp(topic, topic1) == 0) 
 {
  // If the relay is on turn it off (and vice-versa)
  if (messageTemp == "1") 
  { 
   digitalWrite(out1, HIGH);  state1=1;
  } else {
   digitalWrite(out1, LOW);  state1=0;
  }
   Serial.print("mqtt out1: ");
   Serial.println(state1?"On":"Off");
 }else if (strcmp(topic, topic2) == 0) 
 {
  // If the relay is on turn it off (and vice-versa)
  if (messageTemp == "1") { 
   digitalWrite(out2, HIGH); state2=1;
  } else {
   digitalWrite(out2, LOW); state2=0;
  }
  Serial.print("mqtt out2: ");
  Serial.println(state2?"On":"Off");
 }else if (strcmp(topic, topic3) == 0) 
 {
  // If the relay is on turn it off (and vice-versa)
  if (messageTemp == "1") { 
   digitalWrite(out3, HIGH); state3=1;
  } else {
   digitalWrite(out3, LOW); state3=0;
  }
  Serial.print("mqtt out3: ");
  Serial.println(state3?"On":"Off");
 }else if (strcmp(topic, topic4) == 0) 
 {
  // If the relay is on turn it off (and vice-versa)
  if (messageTemp == "1") { 
   digitalWrite(out4, HIGH); state4=1;
  } else {
   digitalWrite(out4, LOW); state4=0;
  }
  Serial.print("mqtt out4: ");
  Serial.println(state4?"On":"Off");
 }

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// myBounce.h //////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// myBounce.cpp /////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////
//example3   M2M //////////////////////////////////////////////////////////

#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "myBounce.h"
#include <Servo.h>
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 

//const char* ssid = "wifi1971_2";
//const char* password = "fedcba9876";
//const char* ssid = "ELEC302";  //ELEC302_plus
//const char* password = "elec1234";

char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;
//const char* mqttUser = "yourInstanceUsername";
//const char* mqttPassword = "yourInstancePassword";
#define SERVO_PIN 25
#define out1 4
#define out2 2
#define out3 13
#define out4 12
#define sw1 34
#define sw2 35
#define sw3 32
#define sw4 33
#define in1 36

Servo servoMotor;
myBounce SW1(sw1);
myBounce SW2(sw2);
myBounce SW3(sw3);
myBounce SW4(sw4);
int state1=1,state2=1,state3=1,state4=1;
unsigned long lastMillis;
unsigned int delayTime=1000;
unsigned int now=0,lastRead=0;
#define topic1 "mut/miia0107/group1" 
#define topic2 "mut/miia0107/board2" 
#define thisDevice 1
#define otherDevice 2


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
      
      }      
  }
}

void setup() 
{
  Serial.begin(115200);
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
  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
  servoMotor.write(90);

}


void loop() 
{
  if (!mqttClient.connected()) reconnect();
  mqttClient.loop();
  if(SW1.update()==1)
  { 
    state1=!state1;  sendMQTT(); //digitalWrite(out1,state1);
  }
  if(SW2.update()==1)  
  { 
    state2=!state2;  sendMQTT(); //digitalWrite(out2,state2);
  }
  if(SW3.update()==1)
  { 
    state3=!state3; sendMQTT(); // digitalWrite(out3,state3);
  }
  if(SW4.update()==1)
  { 
    state4=!state4;  sendMQTT(); //digitalWrite(out4,state4);
  }
 
 if ((millis() - lastMillis) > delayTime)
 {
   now = map(analogRead(in1),0,4095,0,180);
   if((now>lastRead+1)||(now<lastRead-1))
   {
     sendMQTT();   
     lastRead=now;
   }
   
   delay(10);
 }

}

void sendMQTT()
{
  StaticJsonDocument<256> doc;
  doc["device"] = otherDevice;
  doc["ADC1"] = map(analogRead(in1),0,4095,0,180);
  JsonArray state = doc.createNestedArray("state");
  state.add(state1);
  state.add(state2);
  state.add(state3);
  state.add(state4);
  
  char out[128];
  int b =serializeJson(doc, out);
  Serial.print("bytes = ");
  Serial.println(b,DEC);
  Serial.println(out);
  mqttClient.publish(topic1, out);
  delay(10);
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  char str[length+1];
  
  int i=0;
  for (i=0;i<length;i++) 
  {
  Serial.print((char)payload[i]);
  str[i]=(char)payload[i];
  }
  str[i] = 0; // Null termination
  Serial.println();
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");
  
  
  StaticJsonDocument <256> doc;
  // deserializeJson(doc,str); can use string instead of payload
  deserializeJson(doc,payload);
  unsigned int device = doc["device"];
  if(device==thisDevice)
  {
    unsigned int ADC1 = doc["ADC1"];
    unsigned int state1 = doc["state"][0]; digitalWrite(out1,state1);
    unsigned int state2 = doc["state"][1]; digitalWrite(out2,state2);
    unsigned int state3 = doc["state"][2]; digitalWrite(out3,state3);
    unsigned int state4 = doc["state"][3]; digitalWrite(out4,state4);

    Serial.print("device:");Serial.println(device);
    Serial.print("ADC1 =");Serial.println(ADC1);
    Serial.print("state =");Serial.print(state1);
    Serial.print(state2); Serial.print(state3);
    Serial.println(state4);
    servoMotor.write(ADC1); 
    delay(15);

  }
}

//สวัสดีครับ

//////////////////// ledc servo //////////////////////////


unsigned long delayTime1=0,delayTime2=0 ; 
#define servo0 26
#define servo1 25
#define freq  50
#define resolution  16

 #define COUNT_LOW 2676
 #define COUNT_HIGH 7553

void setup() 
{
  Serial.begin(115200);
  Serial.println("Start");
  ledcSetup(1, 50, 16);
  ledcAttachPin(26, 1);
  ledcSetup(2, 50, 16);
  ledcAttachPin(25, 1);
}

void loop() 
{
  for(int vol=COUNT_LOW;vol<COUNT_HIGH;vol=vol+10)
  {
   ledcWrite(1, vol);
   ledcWrite(2, vol);
   Serial.println(vol);
   delay(10);
  }

  for(int vol=COUNT_HIGH;vol>COUNT_LOW;vol=vol-10)
  {
   ledcWrite(1, vol);
   ledcWrite(2, vol);
   Serial.println(vol);
   delay(10);
  }
}





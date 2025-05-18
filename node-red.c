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

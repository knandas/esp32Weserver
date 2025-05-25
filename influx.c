// influxDB
#include <InfluxDbClient.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define WIFI_SSID  "ELEC302"  //ELEC302_plus
#define WIFI_PASSWORD "elec1234"


#define led 2
int value = 0;
unsigned long lastMillis=0;
unsigned int delayTime =1000; 
bool dir=0;

#define INFLUXDB_URL "http://192.168.1.xxx:8086"
#define INFLUXDB_TOKEN "p0-3eqHuzE226jz535jyY6kqI7zCXk96dCUSC__sWMA=="
#define INFLUXDB_ORG "mii"
#define INFLUXDB_BUCKET "ESP32"
#define DEVICE "ESP32_1"

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
// Data point
Point sensor("test_esp32");

void setup() 
{
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  while (wifiMulti.run() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Connected to Wi-Fi");

  // Add constant tags - only once
  sensor.addTag("device", DEVICE);
  sensor.addTag("count", "count_value");

    // Check server connection
  if (client.validateConnection()) 
  {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else 
  {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void loop() 
{
 if(millis()-lastMillis>delayTime)
 {
  if(dir==0)
  {
    value++;
    if(value==100) dir=1;
    Serial.println(value);
  }else
  {
    value--;
    if(value==0) dir=0;
    Serial.println(value);
  }
  sensor.clearFields();
  sensor.addField("count_value", value);
  //sensor.addField("value_div2", value/2); 
  // Print what are we exactly writing
  Serial.print("Writing: ");
  Serial.println(client.pointToLineProtocol(sensor));
  // If no Wifi signal, try to reconnect it
  if (wifiMulti.run() != WL_CONNECTED) 
  {
    Serial.println("Wifi connection lost");
  }
  // Write point
  if (!client.writePoint(sensor)) 
  {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }


  digitalWrite(led,HIGH); delay(100); digitalWrite(led,LOW);
  lastMillis=millis();
 }  
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////// grafana.html ///////////////////////////////////////////////////////////

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Grafana Dashboard</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            background-color: #f4f4f4;
        }
        iframe {
            width: 50%;
            height: 350px;
            border: none;
        }
    </style>
</head>
<body>
    <h1>Grafana Graph Display</h1>
    <iframe src="http://your-grafana-server.com/d-solo/your-dashboard-id?orgId=1&panelId=2" allowfullscreen></iframe>
</body>
</html>

///////////////////////////////////////////////////////////////////////////////////////////////////

/*
 esp32-https-request json httpbin.org
*/


#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>

const char WIFI_SSID[] = "ELEC302";            
const char WIFI_PASSWORD[] = "elec1234"; 

const char*  host =  "www.httpbin.org"; 
String PATH_NAME   = "/post";  
String queryString = "temperature=26.5&humidity=70.1";     


const char* test_root_ca= \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----\n";


WiFiClientSecure client;

void setup() 
{
  Serial.begin(115200); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  

   client.setCACert(test_root_ca);
  //client.setCertificate(test_client_cert); // for client verification
  //client.setPrivateKey(test_client_key);	// for client verification

  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, 443))
    Serial.println("Connection failed!");
  else 
  {
    Serial.println("Connected to server!");
    // Make a HTTP request:
     client.print(String("POST ") + PATH_NAME + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Content-Type: application/x-www-form-urlencoded\r\n" +
                 "Content-Length: " + queryString.length() + "\r\n" +
                 "\r\n" + // This is the extra CR+LF pair to signify the start of a body
                 queryString + "\n");


   Serial.println("request sent");
   while (client.connected()) 
   {
    String payload = client.readStringUntil('\n');
    if (payload == "\r") 
    {
      Serial.println("headers received");
      break;
    }
   }
   String payload=""; //= client.readStringUntil('\n');
   while (client.available()) 
    {
      char c = client.read();
      Serial.write(c);
      payload=payload+c;
    }
   client.stop();
    
    Serial.println(payload);

    Serial.println("parse");
    Serial.println("=====");
    JSONVar myObject = JSON.parse(payload);

    // JSON.typeof(jsonVar) can be used to get the type of the variable
    if (JSON.typeof(myObject) == "undefined") 
    {
      Serial.println("Parsing input failed!");
      return;
    }
    
      Serial.print("\"temperature\" : ");
      Serial.println(myObject["form"]["temperature"]);
      //Serial.println(JSON.typeof(myObject["form"]["temperature"]));
      String conv = myObject["form"]["temperature"];
      //Serial.println(conv);
      float C =conv.toFloat();
      Serial.print("temperature = ");
      Serial.println(C);

      Serial.print("\"humidity\" : ");
      Serial.println(myObject["form"]["humidity"]);
      //Serial.println(JSON.typeof(myObject["form"]["humidity"]));
      String conv2 = myObject["form"]["humidity"];
      //Serial.println(conv);
      float H =conv2.toFloat();
      Serial.print("humidity = ");
      Serial.println(H);
     
  }
}


void loop() 
{

}




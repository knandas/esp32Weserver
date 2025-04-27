/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////    esp32-http-request get   /////////////////////////////////////////////////////
/*
 esp32-http-request
*/

#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "ELEC302";            
const char WIFI_PASSWORD[] = "elec1234"; 

String HOST_NAME   = "http://httpbin.org/get"; 
String PATH_NAME   = "?temp=34.56";      

void setup() 
{
  Serial.begin(115200); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME); //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) 
    {
      Serial.println("Payload:");
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop() 
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////    esp32-http-request get json   /////////////////////////////////////////////////////
/*
 esp32-http-request json
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char WIFI_SSID[] = "ELEC302";            
const char WIFI_PASSWORD[] = "elec1234"; 

String HOST_NAME   = "http://httpbin.org/get"; 
String PATH_NAME   = "?temp=34.56";      

void setup() 
{
  Serial.begin(115200); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME); //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) 
  {
    // file found at server
    if(httpCode == HTTP_CODE_OK) 
    {
      Serial.println("Payload:");
      String payload = http.getString();
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
      
      
      //if (myObject.hasOwn("temp"))
      {
        Serial.print("\"temp\" = ");
        Serial.println(myObject["args"]["temp"]);
        String conv = myObject["args"]["temp"];
        Serial.println(conv);
        float C =conv.toFloat();
        Serial.println(C);

      }

    } else 
    {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } 
  else 
  {
   Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop() 
{

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////  esp32-http-request post json  ///////////////////////////////////////////////
/*
 esp32-http-request post json
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char WIFI_SSID[] = "POCO F5";            
const char WIFI_PASSWORD[] = "fedcba9876"; 

String HOST_NAME   = "http://httpbin.org"; 
String PATH_NAME   = "/post";  
String queryString = "temperature=26.5&humidity=70.1";     

void setup() 
{
  Serial.begin(115200); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME); //HTTP

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(queryString);
 
  // httpCode will be negative on error
  if(httpCode > 0) 
  {
    // file found at server
    if(httpCode == HTTP_CODE_OK) 
    {
      Serial.println("Payload:");
      String payload = http.getString();
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
      
      
      //if (myObject.hasOwn("temp"))
      {
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

    } else 
    {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } 
  else 
  {
   Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop() 
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
///////////////////////////// openWeather json 1 /////////////////////////////////////////////////////////////

/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-open-weather-map-thingspeak-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "ELEC302";
const char* password = "elec1234";

// Your Domain name with URL path or IP address with path
String openWeatherMapApiKey = "REPLACE_WITH_YOUR_OPEN_WEATHER_MAP_API_KEY";
// Example:
//String openWeatherMapApiKey = "11d3988c265263deffff50b";

// Replace with your country code and city
String city = "bangkok";
String countryCode = "TH";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

String jsonBuffer;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}

void loop() {
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey + "&units=metric";
      
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
  
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.print("JSON object = ");
      Serial.println(myObject);
      Serial.print("Temperature: ");
      Serial.println(myObject["main"]["temp"]);
      Serial.print("Pressure: ");
      Serial.println(myObject["main"]["pressure"]);
      Serial.print("Humidity: ");
      Serial.println(myObject["main"]["humidity"]);
      Serial.print("Wind Speed: ");
      Serial.println(myObject["wind"]["speed"]);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// esp32_thingspeak.ino ///////////////////////////////////////////////////////////////////
/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-open-weather-map-thingspeak-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ELEC302";
const char* password = "elec1234";

// REPLACE WITH THINGSPEAK.COM API KEY
String serverName = "http://api.thingspeak.com/update?api_key=SFNDJAF9NM";
// EXAMPLE:
//String serverName = "http://api.thingspeak.com/update?api_key=7HQJM49R8JAPR";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
  
  // Random seed is a number used to initialize a pseudorandom number generator
  randomSeed(analogRead(33));
}

void loop() {
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName + "&field1=" + String(random(40));
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

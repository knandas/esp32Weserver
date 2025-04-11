 
////////////////////////////code 0 Blink ////////////////////////////////

/*
  Blink
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() 
{    
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

/////////////////////////////blink2.ino/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

#define led4 12
#define led3 13

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  digitalWrite(led3, LOW);   
  digitalWrite(led4, HIGH);
  delay(1000);                       
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);
  delay(1000);                      
}

///////////////////////////////////////////////////////////////////////////
///////////// files->example -> basic -> digitalreadserial /////////////
/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 32;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(112500);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.println(buttonState);
  delay(10);        // delay in between reads for stability
}

//////////////////////////////////////////////////////////////////////////
///////////////////  digitalReadSerial to led ////////////////////////


int pushButton = 32;
int Led3 = 13;

void setup() 
{
  Serial.begin(115200);
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(Led3, OUTPUT);
}


void loop() 
{
  int buttonState = digitalRead(pushButton);
  Serial.println(buttonState);
  digitalWrite(Led3,buttonState);
  delay(10);       
}



////////////////////////////////////////////////////////////////////////////
//////////////////////////////// code 1 digital input basic /////////////////

const int buttonPin = 2;     
const int ledPin =  13;      

int buttonState = 0;        

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() 
{
 
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) 
  {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else 
  {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}

/////////////////////////////////////////////////////////////////////////
//////////////////////////////// code 2 digital input pullup ///////////
const int buttonPin = 32;     
const int led3 =  13;      
const int led4 =  12;  
int buttonState = 0;        

void setup() 
{
  Serial.begin(115200);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() 
{
 
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) 
  {
    // turn LED on:
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  } else 
  {
    // turn LED off:
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  }
delay(1000);
} 

////////////////////////////////////////////////////////////////////////////
///// code 3 jamm sw toggle ///////

const int buttonPin = 32;     
const int led3 =  13;      
const int led4 =  12;  
bool swState=0,buttonState = 0;        

void setup() 
{
  Serial.begin(115200);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() 
{
 
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  if(buttonState==0) swState= !swState;

  if (swState == HIGH) 
  {
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  } else 
  {
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  }
delay(100);
}  
/////////////////////////////////////////////////////////////
//////////////////////////////// code 4 sw debounce///////////

int led1 = 13;
int led2 = 12;
int sw1 = 32;
bool sw_state=0,last_sw_state,buttonstate=1;
int state=0;
unsigned long time1;
int debounceDelay=40;

void setup() 
{
  pinMode(led1,OUTPUT);  
  pinMode(led2,OUTPUT); 
  pinMode(sw1,INPUT_PULLUP);  
}

void loop() 
{
  sw_state=digitalRead(sw1);
  if(sw_state!= last_sw_state)
  {
    time1=millis();
  }
  if((millis()-time1)>debounceDelay)
  {
    buttonstate=sw_state;        
  }

  
  if(buttonstate==0)
  {
    state=!state; 
    buttonstate=1;
    if(state==0){digitalWrite(led1,HIGH); digitalWrite(led2,LOW);} 
    if(state==1){digitalWrite(led1,LOW); digitalWrite(led2,HIGH);}
    while(!digitalRead(sw1));
    delay(10);
  }
    
  last_sw_state=sw_state;
}





//////////////////////////////////////////////////////////////
//////////////////////////////// code 5 sw debounce fn///////////
int led3 = 13;
int led4 = 12;
int sw1 = 32;
bool sw_state=0,last_sw_state,buttonstate=1,change=0;
bool state=0;
unsigned long time1;
int debounceDelay=40;

void setup() 
{
  pinMode(led3,OUTPUT);  
  pinMode(led4,OUTPUT); 
  pinMode(sw1,INPUT_PULLUP);  
}

void loop() 
{
  checkSW();

  if(state==0){ digitalWrite(led3,LOW);} 
  else{ digitalWrite(led3,HIGH);}
    
}


void checkSW()
{
  sw_state=digitalRead(sw1);
  if((sw_state==0)&&(last_sw_state==1))
  {
    time1=millis();
    change=1;
  }
  last_sw_state=sw_state;
  if(((millis()-time1)>debounceDelay)&&(change==1))
  {
    if(sw_state==0)
    {
      state= !state;
    }
    change=0;
  }
}  

///////////////////////////////////////////////////////
//////////////////////////////// code 5b double sw debounce fn///////////
int led3 = 13;
int led4 = 12;
int sw1 = 32;
int sw2 = 33;
bool sw_state1=0,last_sw_state1,buttonstate1=1,change1=0;
bool sw_state2=0,last_sw_state2,buttonstate2=1,change2=0;
bool state1=0;
bool state2=0;
unsigned long time1,time2;
int debounceDelay=40;

void setup() 
{
  pinMode(led3,OUTPUT);  
  pinMode(led4,OUTPUT); 
  pinMode(sw1,INPUT_PULLUP);  
  pinMode(sw2,INPUT_PULLUP);
}

void loop() 
{
  checkSW1();
  if(state1==0){ digitalWrite(led3,LOW);} 
  else{ digitalWrite(led3,HIGH);}

  checkSW2();
  if(state2==0){ digitalWrite(led4,LOW);} 
  else{ digitalWrite(led4,HIGH);}
    
}


void checkSW1()
{
  sw_state1=digitalRead(sw1);
  if((sw_state1==0)&&(last_sw_state1==1))
  {
    time1=millis();
    change1=1;
  }
  last_sw_state1=sw_state1;
  if(((millis()-time1)>debounceDelay)&&(change1==1))
  {
    if(sw_state1==0)
    {
      state1= !state1;
    }
    change1=0;
  }
}  

void checkSW2()
{
  sw_state2=digitalRead(sw2);
  if((sw_state2==0)&&(last_sw_state2==1))
  {
    time2=millis();
    change2=1;
  }
  last_sw_state2=sw_state2;
  if(((millis()-time2)>debounceDelay)&&(change2==1))
  {
    if(sw_state2==0)
    {
      state2= !state2;
    }
    change2=0;
  }
}  

///////////////////////////////////////////////////////////////////////
//////////////////////////////// code 5c sw debounce lib .ino///////////
#include "myBounce.h"

#define led1 4
#define led2 2
#define led3 13
#define led4 12
#define sw1 34
#define sw2 35
#define sw3 32
#define sw4 33

bool state1=1,state2=1,state3=1,state4=1;

myBounce SW1(sw1);
myBounce SW2(sw2);
myBounce SW3(sw3);
myBounce SW4(sw4);

void setup() 
{
  
  pinMode(led1,OUTPUT);  
  pinMode(led2,OUTPUT); 
  pinMode(led3,OUTPUT);  
  pinMode(led4,OUTPUT); 

}

void loop() 
{
 if(SW1.update()==1){ state1=!state1; digitalWrite(led1,state1); }
 if(SW2.update()==1){ state2=!state2; digitalWrite(led2,state2); }
 if(SW3.update()==1){ state3=!state3; digitalWrite(led3,state3); }
 if(SW4.update()==1){ state4=!state4; digitalWrite(led4,state4); }
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




////////////////////////////////////////////////////////
//////////////////////////////// code 5c sw debounce lib block .ino///////////
#include "myBounce.h"

#define led1 4
#define led2 2
#define led3 13
#define led4 12
#define sw1 34
#define sw2 35
#define sw3 32
#define sw4 33

bool state1=1,state2=1,state3=1,state4=1;

myBounce SW1(sw1);
myBounce SW2(sw2);
myBounce SW3(sw3);
myBounce SW4(sw4);

void setup() 
{
  
  pinMode(led1,OUTPUT);  
  pinMode(led2,OUTPUT); 
  pinMode(led3,OUTPUT);  
  pinMode(led4,OUTPUT); 

}

void loop() 
{
 if(SW1.update()==1){ state1=!state1; digitalWrite(led1,state1); }
 if(SW2.update()==1){ state2=!state2; digitalWrite(led2,state2); }
 if(SW3.update()==1){ state3=!state3; digitalWrite(led3,state3); }
 if(SW4.update()==1){ state4=!state4; digitalWrite(led4,state4); }

 digitalWrite(led1,HIGH);
 delay(1000);
 digitalWrite(led1,LOW);
 delay(1000);
}

//////////////////////////////////////////////////////////////////////////////////////////////
// code5d sw debounce lib noblock i am sorry<3 //
  
#include "myBounce.h"

#define led1 4
#define led2 2
#define led3 13
#define led4 12
#define sw1 34
#define sw2 35
#define sw3 32
#define sw4 33

bool state1=1,state2=1,state3=1,state4=1;
unsigned long delayTime1;

myBounce SW1(sw1);
myBounce SW2(sw2);
myBounce SW3(sw3);
myBounce SW4(sw4);

void setup() 
{
  
  pinMode(led1,OUTPUT);  
  pinMode(led2,OUTPUT); 
  pinMode(led3,OUTPUT);  
  pinMode(led4,OUTPUT); 

}

void loop() 
{
 //if(SW1.update()==1){ state1=!state1; digitalWrite(led1,state1); }
 if(SW2.update()==1){ state2=!state2; digitalWrite(led2,state2); }
 if(SW3.update()==1){ state3=!state3; digitalWrite(led3,state3); }
 if(SW4.update()==1){ state4=!state4; digitalWrite(led4,state4); }

  if ((millis() - delayTime1) > 1000)
  {
   state1=!state1;
   digitalWrite(led1, state1);
   delayTime1=millis();
  }
}



//////////////////////////////////////////////////////////////////////
//////////////////////////////// code 7 sw debounce lib noBlock ADC.ino///////////
#include "myBounce.h"
#define led1 4
#define led2 2
#define led3 13
#define led4 12
#define sw1 34
#define sw2 35
#define sw3 32
#define sw4 33
#define Ain1 36

bool state1=1,state2=1,state3=1,state4=1;
unsigned long delayTime1;

myBounce SW1(sw1);
myBounce SW2(sw2);
myBounce SW3(sw3);
myBounce SW4(sw4);

void setup() 
{
  Serial.begin(115200);
  pinMode(led1,OUTPUT);  
  pinMode(led2,OUTPUT); 
  pinMode(led3,OUTPUT);  
  pinMode(led4,OUTPUT); 
}

void loop() 
{
 if(SW1.update()==1){ state1=!state1; digitalWrite(led1,state1); }
 if(SW2.update()==1){ state2=!state2; digitalWrite(led2,state2); }
 if(SW3.update()==1){ state3=!state3; digitalWrite(led3,state3); }
 if(SW4.update()==1){ state4=!state4; digitalWrite(led4,state4); }

 if ((millis() - delayTime1) > 500)
 {
  int sensorValue = analogRead(Ain1);
  float volt = sensorValue*3.3/4095;
  Serial.print("ADC:");
  Serial.print(sensorValue);
  Serial.print(" volt:");
  Serial.println(volt);
  delayTime1=millis();
 }
}
                                      
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// File > Examples > WiFi > WiFiScan.ino ///////////////////////////// 
/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is based on the Arduino WiFi Shield library, but has significant changes as newer WiFi functions are supported.
 *  E.g. the return value of `encryptionType()` different because more modern encryption is supported.
 */
#include "WiFi.h"

void setup()
{
    Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected.
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
}

void loop()
{
    Serial.println("Scan start");

    // WiFi.scanNetworks will return the number of networks found.
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.printf("%2d",i + 1);
            Serial.print(" | ");
            Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
            Serial.print(" | ");
            Serial.printf("%4d", WiFi.RSSI(i));
            Serial.print(" | ");
            Serial.printf("%2d", WiFi.channel(i));
            Serial.print(" | ");
            switch (WiFi.encryptionType(i))
            {
            case WIFI_AUTH_OPEN:
                Serial.print("open");
                break;
            case WIFI_AUTH_WEP:
                Serial.print("WEP");
                break;
            case WIFI_AUTH_WPA_PSK:
                Serial.print("WPA");
                break;
            case WIFI_AUTH_WPA2_PSK:
                Serial.print("WPA2");
                break;
            case WIFI_AUTH_WPA_WPA2_PSK:
                Serial.print("WPA+WPA2");
                break;
            case WIFI_AUTH_WPA2_ENTERPRISE:
                Serial.print("WPA2-EAP");
                break;
            case WIFI_AUTH_WPA3_PSK:
                Serial.print("WPA3");
                break;
            case WIFI_AUTH_WPA2_WPA3_PSK:
                Serial.print("WPA2+WPA3");
                break;
            case WIFI_AUTH_WAPI_PSK:
                Serial.print("WAPI");
                break;
            default:
                Serial.print("unknown");
            }
            Serial.println();
            delay(10);
        }
    }
    Serial.println("");

    // Delete the scan result to free memory for code below.
    WiFi.scanDelete();

    // Wait a bit before scanning again.
    delay(5000);
}





////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////// ESP32 wifi ///////////////////////////////////////////////////////////////

#include <WiFi.h>

#define led_pin 2

char* ssid = "ELEC302";  //ELEC302_plus
char* password ="elec1234"; 

void setup() 
{
  pinMode(led_pin,OUTPUT);
  Serial.begin(115200);
  Serial.println("");
  WiFi.begin(ssid,password);
  Serial.println("initailizing WiFi connection");                                   
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());

}

void loop() 
{
  ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////// wifi esp deep sleep /////////////////////////////////////////////////////
// wifi esp deep sleep
#include <WiFi.h>
//Time in seconds
#define CONNECTION_TIMEOUT 5
#define DEEP_SLEEP_DURATION 10

const char* ssid = "ELEC302";
const char* password = "elec124";

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");
    int timeout_counter = 0;

    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
        timeout_counter++;
            if(timeout_counter >= CONNECTION_TIMEOUT*10)
            {
                Serial.println("\nCan't establish WiFi connection");
                //Setup timer
                esp_sleep_enable_timer_wakeup(DEEP_SLEEP_DURATION * 1000000);
                //Start deep sleep
                esp_deep_sleep_start();
            }
    }
    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop(){}

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////// auto reconnect //////////////////////////////////////////////////////////

#include <WiFi.h>

// Replace with your network credentials (STATION)
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

unsigned long previousMillis = 0;
unsigned long interval = 30000;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  initWiFi();
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
}

void loop() {
  unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// wifi event reconect /////////////////////////////////////////////////////
#include <WiFi.h> 
const char* ssid = "REPLACE_WITH_YOUR_SSID"; 
const char* password = "REPLACE_WITH_YOUR_PASSWORD"; 
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{ 
 Serial.println("Connected to AP successfully!"); 
} 

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
{ 
 Serial.println("WiFi connected"); 
 Serial.println("IP address: "); 
 Serial.println(WiFi.localIP()); 
} 

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{ 
 Serial.println("Disconnected from WiFi access point"); 
 Serial.print("WiFi lost connection. Reason: "); 
 Serial.println(info.wifi_sta_disconnected.reason); 
 Serial.println("Trying to Reconnect"); 
 WiFi.begin(ssid, password); 
} 

void setup()
{ 
 Serial.begin(115200); // delete old config 
 WiFi.disconnect(true); 
 delay(1000); 
 WiFi.onEvent(WiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED); 
 WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP); 
 WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED); 

/* //Remove WiFi event 
 Serial.print("WiFi Event ID: "); 
 Serial.println(eventID); 
 WiFi.removeEvent(eventID);
*/ 

 WiFi.begin(ssid, password); 
 Serial.println(); 
 Serial.println(); 
 Serial.println("Wait for WiFi... "); 
} 

void loop()
{ 
 delay(1000); 
} 

/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////// wifiMulti auto reconnect ////////////////////////////////////////////////
//wifiMulti auto reconnect
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

// WiFi connect timeout per AP. Increase when connecting takes longer.
const uint32_t connectTimeoutMs = 10000;

void setup()
{
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_STA);
  
  // Add list of wifi networks
  wifiMulti.addAP("ELEC302", "elec1234");
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) 
  {
      Serial.println("no networks found");
  } 
  else 
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) 
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
  }

  // Connect to Wi-Fi using wifiMulti (connects to the SSID with strongest connection)
  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) 
  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop()
{
  //if the connection to the stongest hotstop is lost, it will connect to the next network on the list
  if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) 
  {
    Serial.print("WiFi connected: ");
    Serial.print(WiFi.SSID());
    Serial.print(" ");
    Serial.println(WiFi.RSSI());
  }
  else 
  {
    Serial.println("WiFi not connected!");
  }
  delay(1000);
}
    
///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////// esp webserver basic ///////////////////////////////////////////////////

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "ELEC302";
const char* password = "elec1234";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output4State = "off";
String output2State = "off";

// Assign output variables to GPIO pins
const int output4 = 4;
const int output2 = 2;

// Set your Static IP address
//IPAddress local_IP(192, 168, 1, 184);
// Set your Gateway IP address
//IPAddress gateway(192, 168, 1, 1);

//IPAddress subnet(255, 255, 0, 0);
//IPAddress primaryDNS(8, 8, 8, 8);   //optional
//IPAddress secondaryDNS(8, 8, 4, 4); //optional

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output4, OUTPUT);
  pinMode(output2, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output4, LOW);
  digitalWrite(output2, LOW);

  // Configures static IP address
  //if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
  //  Serial.println("STA Failed to configure");
  //}
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) 
  {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) 
    {            // loop while the client's connected
      if (client.available()) 
      {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') 
        {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) 
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /4/on") >= 0) 
            {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) 
            {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) 
            {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) 
            {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>GPIO 4 - State " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 2  
            client.println("<p>GPIO 2 - State " + output2State + "</p>");
            // If the output2State is off, it displays the ON button       
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// esp32 webserver2 ////////////////////////////////////////////////////////////

//esp32 wifi webserver


#include <WiFi.h>
#include <WebServer.h>

#define led_pin1 13
#define led_pin2 12
bool out1=0;
bool out2=0;
const char* ssid = "ELEC302";
const char* password = "elec1234";

WebServer server;

void setup() 
{
  pinMode(led_pin1,OUTPUT);
  pinMode(led_pin2,OUTPUT);
  Serial.begin(115200);
  Serial.println("");
  WiFi.begin(ssid,password);
  Serial.println("initailizing WiFi connection");                                   
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


  server.on("/",[](){server.send(200,"text/plain","Hello from ESP32!");});  
  server.on("/toggle1",toggleLED1); 
  server.on("/toggle2",toggleLED2);           
  server.begin();
}

void loop() 
{
  server.handleClient();
}

void toggleLED1()
{
  out1=!out1;
  digitalWrite(led_pin1,out1);
  server.send(200,"text/plain",out1?"out1:On":"out1:Off");
  server.send(204," "); 
  Serial.print("out1: ");
  Serial.println(out1?"On":"Off");
}

void toggleLED2()
{
  out2=!out2;
  digitalWrite(led_pin2,out2);
  server.send(200,"text/plain",out2?"out2:On":"out2:Off");
  server.send(204," "); 
  Serial.print("out2: ");
  Serial.println(out2?"On":"Off");
}



/////////////////////////////////////////////////////////////////////////////////////////////
/*
esp32 wifi webserver2
*/

#include <WiFi.h>
#include <WebServer.h>

#define led_pin1 13
#define led_pin2 12
bool out1=0;
bool out2=0;
const char* ssid = "ELEC302_plus";
const char* password = "elec1234";

WebServer server;

void setup() 
{
  pinMode(led_pin1,OUTPUT);
  pinMode(led_pin2,OUTPUT);
  Serial.begin(115200);
  Serial.println("");
  WiFi.begin(ssid,password);
  Serial.println("initailizing WiFi connection");                                   
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


  server.on("/",[](){server.send(200,"text/plain","Hello from ESP32!");});  
  server.on("/toggle1",toggleLED1); 
  server.on("/toggle2",toggleLED2);
  server.on("/on1",on1);  
  server.on("/on2",on2);   
  server.on("/off1",off1);   
  server.on("/off2",off2);               
  server.begin();
}

void loop() 
{
  server.handleClient();
}

void toggleLED1()
{
  out1=!out1;
  digitalWrite(led_pin1,out1);
  server.send(200,"text/plain",out1?"out1:On":"out1:Off");
  server.send(204," "); 
  Serial.print("out1: ");
  Serial.println(out1?"On":"Off");
}

void toggleLED2()
{
  out2=!out2;
  digitalWrite(led_pin2,out2);
  server.send(200,"text/plain",out2?"out2:On":"out2:Off");
  server.send(204," "); 
  Serial.print("out2: ");
  Serial.println(out2?"On":"Off");
}

void on1()
{
  out1=1;
  digitalWrite(led_pin1,out1);
  server.send(200,"text/plain",out1?"out1:On":"out1:Off");
  server.send(204," "); 
  Serial.print("out1: ");
  Serial.println(out1?"On":"Off");
}

void on2()
{
  out2=1;
  digitalWrite(led_pin2,out2);
  server.send(200,"text/plain",out2?"out2:On":"out2:Off");
  server.send(204," "); 
  Serial.print("out2: ");
  Serial.println(out2?"On":"Off");
}

void off1()
{
  out1=0;
  digitalWrite(led_pin1,out1);
  server.send(200,"text/plain",out1?"out1:On":"out1:Off");
  server.send(204," "); 
  Serial.print("out1: ");
  Serial.println(out1?"On":"Off");
}

void off2()
{
  out2=0;
  digitalWrite(led_pin2,out2);
  server.send(200,"text/plain",out2?"out2:On":"out2:Off");
  server.send(204," "); 
  Serial.print("out2: ");
  Serial.println(out2?"On":"Off");
}
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////esp32_ web on off ///////////////////////////////////////////////////////////////////////////

// Load Wi-Fi library
#include <WiFi.h>
#include <WebServer.h>

#define out1_pin 13
#define out2_pin 12
bool out1=0;
bool out2=0;

// Replace with your network credentials
const char* ssid = "ELEC302";
const char* password = "elec1234";

WebServer server;

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String out1_State = "off";
String out2_State = "off";

void setup() 
{
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(out1_pin, OUTPUT);
  pinMode(out2_pin, OUTPUT);
  // Set outputs to LOW
  digitalWrite(out1_pin, LOW);
  digitalWrite(out2_pin, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.println("");
  WiFi.begin(ssid,password);
  Serial.println("initailizing WiFi connection");                                   
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);  
  server.on("/1/on",on1); 
  server.on("/1/off",off1); 
  server.on("/2/on",on2); 
  server.on("/2/off",off2); 

  server.begin();
  Serial.println("HTTP server started");  
}

void handleRoot()
{
  server.send(200,"text/html",getHtmlPage());
}

String getHtmlPage()
{
            String strHtml = "<!DOCTYPE html><html>";
            strHtml += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
            strHtml += "<link rel=\"icon\" href=\"data:,\">";
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            strHtml += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
            strHtml += ".button { background-color: #555555; border: none; color: white; padding: 16px 40px;";
            strHtml += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
            strHtml += ".button2 {background-color: #4CAF50;}</style></head>";
            
            // Web Page Heading
            strHtml += "<body><h1>ESP32 Web Server</h1>";
            
            // Display current state, and ON/OFF buttons for out1
            strHtml += "<p>output1 - State " + out1_State + "</p>";
            // If the out1_State is off, it displays the ON button       
            if (out1_State=="off") 
            {
              strHtml += "<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>";
            } else 
            {
              strHtml += "<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>";
            } 
               
            // Display current state, and ON/OFF buttons for out2  
            strHtml += "<p>output2 - State " + out2_State + "</p>";
            // If the out2_State is off, it displays the ON button       
            if (out2_State=="off") {
              strHtml += "<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>";
            } else 
            {
              strHtml += "<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>";
            }
            strHtml += "</body></html>";

            return strHtml;
}


void loop()
{
 server.handleClient();
}

void on1()
{
  out1=1;
  digitalWrite(out1_pin,out1);
  Serial.print("out1: ");
  Serial.println(out1?"On":"Off");
  out1_State="on";
  server.send(200, "text/html",getHtmlPage());
}

void on2()
{
  out2=1;
  digitalWrite(out2_pin,out2);
  Serial.print("out2: ");
  Serial.println(out2?"On":"Off");
  out2_State="on";
  server.send(200, "text/html",getHtmlPage());
}

void off1()
{
  out1=0;
  digitalWrite(out1_pin,out1);
  Serial.print("out1: ");
  Serial.println(out1?"On":"Off");
  out1_State="off";
  server.send(200, "text/html",getHtmlPage());
}

void off2()
{
  out2=0;
  digitalWrite(out2_pin,out2);
  Serial.print("out2: ");
  Serial.println(out2?"On":"Off");
  out2_State="off";
  server.send(200, "text/html",getHtmlPage());
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////esp32_ web on off async////////////////////////////////////////////////////////////



/*
esp32 web onoff async
*/

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include "myBounce.h"
//******Enter your network credentials************
const char* ssid = "ELEC302";
const char* password = "elec1234";
//************************************************
 
//Define Status
const char* PARAM_INPUT_1 = "state";
const char* PARAM_INPUT_2 = "state2";

int threshold = 60;

int timeout=700;
#define sw3 32
#define sw4 33
 
//**********Pin Assignments***********
const int relay1 = 13; // D0 Pin of NodeMcu, change it if you are using ESP32
const int relay2 = 12; // D1 Pin of NodeMcu, change it if you are using ESP32
//************************************
 
//*********************Variables declaration**********************
int relay_1_status = LOW; // the current status of relay1
int relay_2_status = LOW; // the current status of relay2
//****************************************************************

myBounce SW3(sw3);
myBounce SW4(sw4); 
 
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//html
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>z
<head>
<title>NodeMCU based Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
html {font-family: Arial; display: inline-block; text-align: center;}
h2 {font-size: 3.0rem;}
p {font-size: 3.0rem;}
body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
.switch {position: relative; display: inline-block; width: 120px; height: 68px}
.switch input {display: none}
.slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #F63E36; border-radius: 34px}
.slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
input:checked+.slider {background-color: #3CC33C}
input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
</style>
</head>
<body>
<h2>ESP32 based Web Server</h2>
%BUTTONPLACEHOLDER%
%BUTTONPLACEHOLDER2%
<script>
function toggleCheckbox(element)
{
var xhr = new XMLHttpRequest();
if(element.checked)
{
xhr.open("GET", "/update?state=1", true);
}
else
{
xhr.open("GET", "/update?state=0", true);
}
xhr.send();
}
 
function toggleCheckbox2(element)
{
var xhr2 = new XMLHttpRequest();
if(element.checked)
{
xhr2.open("GET", "/update?state2=1", true);
}
else
{
xhr2.open("GET", "/update?state2=0", true);
}
xhr2.send();
}
 
setInterval(function ( )
{
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked;
var outputStateM;
 
if( this.responseText == 1)
{
inputChecked = true;
outputStateM = "ON";
}
else
{
inputChecked = false;
outputStateM = "OFF";
}
document.getElementById("output").checked = inputChecked;
document.getElementById("outputState").innerHTML = outputStateM;
}
}
xhttp.open("GET", "/state", true);
xhttp.send();
 
var xhttp2 = new XMLHttpRequest();
xhttp2.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked2;
var outputStateM2;
 
if( this.responseText == 1)
{
inputChecked2 = true;
outputStateM2 = "ON";
}
else
{
inputChecked2 = false;
outputStateM2 = "OFF";
}
document.getElementById("output2").checked = inputChecked2;
document.getElementById("outputState2").innerHTML = outputStateM2;
}
};
xhttp2.open("GET", "/state2", true);
xhttp2.send();
 
}, 1000 ) ;
</script>
</body>
</html>
)rawliteral";
//end html
 
// Replaces placeholder with button section in your web page
String processor(const String& var)
{
 //Serial.println(var);
 if(var == "BUTTONPLACEHOLDER")
 {
  String buttons1 ="";
  String outputStateValue = outputState();
  buttons1+= "<h4>Device 1 - Status <span id=\"outputState\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"output\" " + outputStateValue + "><span class=\"slider\"></span></label>";
  return buttons1;
 }
 
 if(var == "BUTTONPLACEHOLDER2")
 {
  String buttons2 ="";
  String outputStateValue2 = outputState2();
  buttons2+= "<h4>Device 2 - Status <span id=\"outputState2\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox2(this)\" id=\"output2\" " + outputStateValue2 + "><span class=\"slider\"></span></label>";
  return buttons2;
 }
 return String();
}
 
String outputState()
{
 if(digitalRead(relay1))
 {
  return "checked";
 }
 else
 {
  return "";
 }
 return "";
}

String outputState2()
{
 if(digitalRead(relay2))
 {
  return "checked";
 }
 else
 {
  return "";
 }
 return "";
}


 
void setup()
{ 
 // Serial port for debugging purposes
 delay(2000);
 Serial.begin(115200);
 
 pinMode(relay1, OUTPUT);
 digitalWrite(relay1, LOW);
 //pinMode(switch1, INPUT);
 
 pinMode(relay2, OUTPUT);
 digitalWrite(relay2, LOW);
 //pinMode(switch2, INPUT);

  // Connect to Wi-Fi network with SSID and password
  Serial.println("");
  WiFi.begin(ssid,password);
  Serial.println("initailizing WiFi connection");                                   
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
 
// Route for root / web page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
{
request->send_P(200, "text/html", index_html, processor);
});
 
// Send a GET request
server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request)
{
String inputMessage;
String inputParam;
 
// GET input1 value on <ESP_IP>/update?state=<inputMessage>
if (request->hasParam(PARAM_INPUT_1))
{
inputMessage = request->getParam(PARAM_INPUT_1)->value();
inputParam = PARAM_INPUT_1;
digitalWrite(relay1, inputMessage.toInt());
relay_1_status = !relay_1_status;
}
else
{
inputMessage = "No message sent";
inputParam = "none";
}
Serial.print("Relay1: ");
Serial.println(inputMessage);
request->send(200, "text/plain", "OK");
 
String inputMessage2;
String inputParam2;
 
if (request->hasParam(PARAM_INPUT_2))
{
inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
inputParam2 = PARAM_INPUT_2;
digitalWrite(relay2, inputMessage2.toInt());
relay_2_status = !relay_2_status;
}
else
{
inputMessage2 = "No message sent";
inputParam2 = "none";
}
Serial.print("Relay2: ");
Serial.println(inputMessage2);
request->send(200, "text/plain", "OK");
});
 
// Send a GET request to <ESP_IP>/state
server.on("/state", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay1)).c_str());
});
 
server.on("/state2", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay2)).c_str());
});
// Start server
server.begin();

delay(2000);
}
 
void loop()
{
  if(SW3.update()==1){ relay_1_status=!relay_1_status; }
  if(SW4.update()==1){ relay_2_status=!relay_2_status; }


  // set the LED:
  digitalWrite(relay1, relay_1_status);
  digitalWrite(relay2, relay_2_status);
}  



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-async-web-server-espasyncwebserver-library/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  ESPAsyncWebServer by ESP32Async
  AsyncTCP by ESP32Async
*********/

// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "ELEC302";
const char* password = "elec1234";

const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Output - GPIO 4</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"4\" " + outputState(4) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Output - GPIO 2</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState(2) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Output - GPIO 13</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"13\" " + outputState(13) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Output - GPIO 12</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"12\" " + outputState(12) + "><span class=\"slider\"></span></label>";
    
    return buttons;
  }
  return String();
}

String outputState(int output){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });

  // Start server
  server.begin();
}

void loop() {

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

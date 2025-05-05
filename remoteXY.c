
/////////////////////12-bits analog input /////////////////////////////////
/*
  ReadAnalogVoltage
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/

// the setup routine runs once when you press reset:
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() 
{
  int sensorValue = analogRead(36);   // pin 36
  int percent=map(sensorValue,0,4095,0,100); // 0-100
  //Convert the analog reading from 0 - 4095 to a voltage 0 - 3.3V:
  float voltage = sensorValue * (3.3 / 4095.0);
  // print out the value you read:
  Serial.print("sensor: ");
  Serial.print(sensorValue);
  Serial.print(" output: ");
  Serial.print(percent);
  Serial.print(" Volt: ");
  Serial.println(voltage);
  delay(100);
}


/////////////////////////////////////////////////////////////
///////12-bits analog input serial plotter  ///////////////


void setup() 
{
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() 
{
  int sensorValue = analogRead(36);   // pin 36
  int percent=map(sensorValue,0,4095,0,100); // 0-100
  //Convert the analog reading from 0 - 4095 to a voltage 0 - 3.3V:
  float voltage = sensorValue * (3.3 / 4095.0);
  //print out the value you read:
  //Serial.print("sensor:");
  //Serial.print(sensorValue);
  //Serial.print(" output:");
  //Serial.print(percent);
  Serial.print("Volt:");
  Serial.println(voltage);
  
  //Serial.print("min:");
  //Serial.println(0);
  //Serial.print("max:");
  //Serial.println(3.3);
  delay(100);
}

//////////////////////////////////////////////////////////////////
/////////////// code for remoteXY ///////////////////////////

#define analogInPin 36
unsigned long lastTime=0; 
void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_BUTTON_01, (RemoteXY.button_01==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_01, (RemoteXY.pushSwitch_01==0)?LOW:HIGH);
  digitalWrite(PIN_SWITCH_01, (RemoteXY.switch_01==0)?LOW:HIGH);
  

  if(millis()>lastTime+1000)
  {
   float sensorValue = analogRead(analogInPin);
   int percent= sensorValue *(100/4096.0);
   float volt= sensorValue *(3.3/4096.0);
   RemoteXY.level_01=percent;
   //snprintf (RemoteXY.text_01, 5, "%f.2", volt);
   dtostrf(volt, 1, 2, RemoteXY.text_01);
   lastTime=millis();
  } 
}


///////////////////////////////////////////////////////////////
////////////////////////////// myBounce.h ////////

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
   bool _change;
   unsigned long _time; 
};

#endif


//////////////////////////////////////////////////////////////
////////////////////myBounce.cpp //////////////////////////////

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
  bool ret=0;
  _sw_state=digitalRead(_pin);
  if((_sw_state==0)&&(_last_sw_state==1))
  {
    _time=millis();
    _change=1;
  }
  _last_sw_state=_sw_state;

  if(((millis()-_time)>50)&&(_change==1))
  {
    _sw_state=digitalRead(_pin);
    if(_sw_state==0)
    {
      ret=1;
    }else
    {
      ret=0;
    }
    _change=0;
  }
 return ret;
}

/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include "myBounce.h"
#define pinSw1 34  //external R-pullUP
#define LED1 4
#define analogInPin 36
unsigned long lastTime=0, lastTimeXY=0;
myBounce SW1(pinSw1);
uint8_t state1=0,state2=0;

void setup() 
{
  RemoteXY_Init (); 
  pinMode (pinSw1, INPUT);
  pinMode (LED1, OUTPUT);
  RemoteXY.led_01=state1;  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  if(SW1.update()==1)
  { 
    state1=!state1; 
    digitalWrite(LED1,state1); 
    //RemoteXY.led_01=state1;
  }

  if((RemoteXY.button_01==1)&&(state2==0))
  {
    state1=!state1; 
    digitalWrite(LED1,state1); 
    RemoteXY.led_01=state1;
    lastTimeXY=millis();
    state2=1;
  }
 
  if(millis()>lastTimeXY+2000){ state2=0;}  

  if(millis()>lastTime+1000)
  {
    float sensorValue = analogRead(analogInPin);
    int percent= sensorValue *(100/4096.0);
    float volt= sensorValue *(3.3/4096.0);
    RemoteXY.onlineGraph_01_var1=volt;
    dtostrf(volt, 1, 2, RemoteXY.text_01);
    RemoteXY.led_01=state1;
    lastTime=millis();
  }

  RemoteXY_delay(100); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////  BMP280  + aht20 ///////////////////////////////////////////////////////

/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP280 Breakout
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
 /**************************************************************************
   Tests the getTemperature and getHumidity functions of the aht20 library
 **************************************************************************/

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <AHT20.h>
AHT20 aht20;
Adafruit_BMP280 bmp; // I2C

void setup() 
{
  Serial.begin(115200);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 & AHT20 test"));
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

void loop() 
{   
  Serial.print(F("BMP280: "));
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.print(" *C  ");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.print(" Pa  ");


  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.println(" m");



  //Get the new temperature and humidity value
  Serial.print(F("AHT20: "));
  float temperature = aht20.getTemperature();
  float humidity = aht20.getHumidity();
  //Print the results
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.print(" C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity, 2);
  Serial.println("% RH");
  Serial.println();
  
  delay(10000);
}

/////////////////////////////////////////////////////////////////////////////////////////////

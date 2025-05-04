
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

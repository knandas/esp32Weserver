https://randomnerdtutorials.com/installing-esp32-arduino-ide-2-0/

https://www.silabs.com/documents/public/software/CP210x_Windows_Drivers.zip

/////////////////////////////////////////////////////////////////////////////

// esp32_adc_LDR.ino //
const int LdrPin = 39;  
int sensorValue = 0;  

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  sensorValue = analogRead(LdrPin);
  Serial.println(sensorValue);
  delay(100);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////// esp32_adc_LDR_2.ino ///////////////////////////

const int LdrPin = 39;  	
int sensorValue = 0;  
#define relay1 4
int compare=2000;
bool light=0;

void setup() 
{
  Serial.begin(115200);
  pinMode(relay1,OUTPUT);
}

void loop() 
{
  sensorValue = analogRead(LdrPin);
  if(sensorValue>compare) light=1; else light=0;
  
  Serial.print(sensorValue);
  Serial.println(light?"\tLight on":"\tLight off");
  digitalWrite(relay1,light);

  delay(100);
}


///////////////////////////////////////////////////////////////////////////////////////////
////////////// esp32_adc_LDR_3.ino  Hysteresis /////////////////////////////////////////////

const int LdrPin = 39;  
int sensorValue = 0;  
#define relay1 4
int compare=2000;
bool light=0;

void setup() 
{
  Serial.begin(115200);
  pinMode(relay1,OUTPUT);
}

void loop() 
{
  sensorValue = analogRead(LdrPin);

  //Hysteresis loop
  if(sensorValue>compare+400) light=1; 
  if(sensorValue<compare-400) light=0; 
  
  Serial.print(sensorValue);
  Serial.println(light?"\tLight on":"\tLight off");
  digitalWrite(relay1,light);
  delay(100);
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////// esp32_adc_LDR_4_motion .ino  motion sensor /////////////////////////////

const int LdrPin = 39;  
int sensorValue = 0;  
#define relay1 4
bool light=0;
float avg1=analogRead(LdrPin);
unsigned long delayTime1=0;

void setup() 
{
  Serial.begin(115200);
  pinMode(relay1,OUTPUT);
}

void loop() 
{
  
 if ((millis() - delayTime1) > 100)
 {
  sensorValue = analogRead(LdrPin);
  avg1=(((avg1*29)+sensorValue)/30); //moving avg 30

  //motion detect
  if(sensorValue>avg1+400) light=1; else light=0;
  
  Serial.print(avg1);
  Serial.print(" ");
  Serial.print(sensorValue);
  Serial.println(light?"\tLight on":"\tLight off");
  digitalWrite(relay1,light);
  delayTime1=millis();
 }
}

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////Google Script  to find LINE Group ID//////////////////////////////////////
var sheet_id = "YOUR SHEET ID";
var sheet_name = "NAME OF YOUR SHEET";
var accessToken =  "YOUR ACCESS TOKEN"; //จาก https://developers.line.biz

function doPost(e) {
  try {
    // ตรวจสอบว่ามีข้อมูลใน e.postData หรือไม่
    if (!e || !e.postData || !e.postData.contents) {
      throw new Error("ไม่มีข้อมูล postData หรือเนื้อหาไม่สมบูรณ์");
    }
 
    // อ่านข้อมูลจาก Webhook
    let contents = JSON.parse(e.postData.contents);
    var userMessage = contents.events[0].message.text;
    var replyToken = contents.events[0].replyToken;
 
    // ตรวจสอบว่ามี groupId หรือไม่
    if (!contents.events || contents.events.length === 0 || !contents.events[0].source.groupId) {
      throw new Error("ไม่มี groupId ในข้อมูลที่ได้รับ");
    }
 
    let groupId = contents.events[0].source.groupId; // ดึง groupId
 
    // Log groupId เพื่อตรวจสอบ
    Logger.log("Group ID: " + groupId);


    if (userMessage === "!groupid") 
    {
      // บันทึก groupId ใน Spreadsheet ให้ใส่ไอดีของ google sheet และชื่อชีต ที่ต้องการให้เอาข้อมูลไปวางไว้
      let sheet = SpreadsheetApp.openById(sheet_id).getSheetByName("Sheet1");
      sheet.appendRow([new Date(), groupId]);

      var url = "https://api.line.me/v2/bot/message/reply";
      var payload = JSON.stringify({
        "replyToken": replyToken,
        "messages": [{
          "type": "text",
          "text": "Group ID ของคุณคือ: " + groupId
        }]
      });

      var headers = {
        "Content-Type": "application/json",
        "Authorization": "Bearer " + accessToken
      };

      UrlFetchApp.fetch(url, {
        "method": "post",
        "headers": headers,
        "payload": payload
      });
    }
 
    // ส่งคำตอบกลับให้ LINE เพื่อยืนยันการรับ
    return ContentService.createTextOutput(JSON.stringify({ status: "success" })).setMimeType(ContentService.MimeType.JSON);
  } catch (error) {
    // Log ข้อผิดพลาด
    Logger.log("Error: " + error.message);
    return ContentService.createTextOutput(JSON.stringify({ status: "error", message: error.message })).setMimeType(ContentService.MimeType.JSON);
  }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

var sheet_id = "YOUR SHEET ID";
var sheet_name = "NAME OF YOUR SHEET";
var accessToken =  "YOUR ACCESS TOKEN"; //จาก https://developers.line.biz
var Id = "Your groupID"; 
//var Id = "Your userID"; 

function doGet(e)
{
  var ss = SpreadsheetApp.openById(sheet_id);
  var sheet = ss.getSheetByName(sheet_name); 
  var sensor = Number(e.parameter.sensor);
  //Logger.log('old2: '+oldRow);
  //var sensor =1234;
  sheet.appendRow([new Date(),sensor]);

  sendLineMessageAPI();
 
}




function sendLineMessageAPI() 
{
  var ss = SpreadsheetApp.openById(sheet_id);
  var sheet = ss.getSheetByName(sheet_name);
  var lastRow = sheet.getLastRow();
  var message = sheet.getRange(lastRow, 2).getValue(); // ข้อความอยู่ที่คอลัมน์ B
  // หากต้องการเปลี่ยนเป็นข้อความแจ้งเตือน สามารถแก้ไขด้านที่ message
  //var message = "พบการเคลื่อนไหว";

  var url = "https://api.line.me/v2/bot/message/push";
  var payload = JSON.stringify({
    //---------------------------text-----------  
      "to": Id,
      "messages": [{
      "type": "text",
      "text": message
     }]
     //----------------------end-----text-----------
     //---------------------------Sticker-----------    
     // "to": Id,
     // "messages": [{
     //   "type": "sticker",
     //   "packageId": "446",
     //   "stickerId": "1988"
     // }]
      //----------------------end-----Sticker-----------  
  });

  var options = {
    "method": "post",
    "headers": {
      "Content-Type": "application/json",
      "Authorization": "Bearer " + accessToken
    },
    "payload": payload
  };

  UrlFetchApp.fetch(url, options);
  Logger.log(payload);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
// esp32 +ldr motion detect -> line Bot
#include "WiFi.h"
#include <HTTPClient.h>

const int LdrPin = 32;  
int sensorValue = 0;
bool detect=0,lastDetect=0;
float avg1=analogRead(LdrPin);
unsigned long delayTime1=0, delayTime2=0;

char ssid[] = "ELEC302";   //ELEC302_plus
char pass[] = "elec1234";
String GOOGLE_SCRIPT_ID = "AKfycbwNmecLQUfy8g7IisKfvlIhXTVeOMi9h-UnLd6e";

void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, pass);
  Serial.print("WiFi Connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

}

void loop() 
{

 if ((millis() - delayTime1) > 100)
 {
  lastDetect=detect;
  sensorValue = analogRead(LdrPin);
  avg1=(((avg1*29)+sensorValue)/30); //moving avg 30

  //motion detect
  if(sensorValue>avg1+400) detect=1;
  if(lastDetect==0&&detect==1)
  {
    Serial.print(avg1);
    Serial.print(" ");
    Serial.print(sensorValue);
    Serial.println(detect?"\tSomebody is in this area!":" ");
    sendData();
  }
  delayTime1=millis();
 }

  if ((millis() - delayTime2) > 30000)
 {
   detect=0;
   delayTime2=millis();
   //Serial.println("clear");
 }


}


void sendData()
{
  if (WiFi.status() == WL_CONNECTED) 
  {
    String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"
    + "sensor=" + String(sensorValue);
    Serial.print("POST data to spreadsheet: ");
    Serial.println(urlFinal);
    HTTPClient http;
    http.begin(urlFinal.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET(); 
    Serial.print("HTTP Status Code: ");
    Serial.println(httpCode);
    //---------------------------------------------------------------------
    //getting response from google sheet
    String payload;
    if (httpCode > 0) 
    {
      payload = http.getString();
      Serial.println(httpCode); 
      Serial.println(payload);
      if(payload=="0")digitalWrite(LED_BUILTIN, LOW);
      if(payload=="1")digitalWrite(LED_BUILTIN, HIGH);    
    }
    else 
    {
      Serial.println("Error on HTTP request");
    }
    //---------------------------------------------------------------------
    http.end();
  }  
}

////////////////////////////////////////end ////////////////////////////////////////////////



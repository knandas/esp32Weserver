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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ArtronShop LineMessging 1 ///////////////////////////////////////////////////////////////////////
#include <WiFi.h> // นำเข้าไลบรารี่ WiFi
#include <ArtronShop_LineMessaging.h> // นำเข้าไลบารี่ ArtronShop_LineMessaging

const char* ssid = "ELEC302"; // ชื่อ WiFi
const char* password = "elec1234"; // รหัสผ่าน WiFi
#define LINE_TOKEN "LINE Token" // Channel access token

void setup() 
{
  Serial.begin(115200); // เริ่มต้นใช้ Serial ที่ความเร็ว 115200
  while (!Serial) { delay(100); }

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println("******************************************************");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // เริ่มต้นเชื่อมต่อ WiFi

  while (WiFi.status() != WL_CONNECTED) { // วนลูปหากยังเชื่อมต่อ WiFi ไม่สำเร็จ
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  LINE.begin(LINE_TOKEN); // เริ่มต้นใช้ LINE Notify

  if (LINE.send("User ID/Group ID", "รถโดนขโมย")) {  // ถ้าส่งข้อความ "รถโดนขโมย" ไปที่ LINE สำเร็จ
    Serial.println("Send notify successful"); // ส่งข้อความ "Send notify successful" ไปที่ Serial Monitor
  } else { // ถ้าส่งไม่สำเร็จ
    Serial.printf("Send notify fail. check your token (code: %d)\n", LINE.status_code); // ส่งข้อความ "Send notify fail" ไปที่ Serial Monitor
  }
}

void loop() {

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
https://developers.line.biz/en/docs/messaging-api/sticker-list/#sticker-definitions     link sticker
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// ArtronShop LineMessging 2 sticker ////////////////////////////////////////////////////////////
#include <WiFi.h> 
#include <ArtronShop_LineMessaging.h> 
const char* ssid = "ELEC302"; 
const char* password = "elec1234"; 
#define LINE_TOKEN "LINE Token" 

void setup() {
  Serial.begin(115200); 
  while (!Serial) { delay(100); }
  Serial.println();
  Serial.println("******************************************************");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  LINE.begin(LINE_TOKEN); 

  LINE_Messaging_Massage_Option_t option; // สร้างตัวแปร option

  // https://developers.line.biz/en/docs/messaging-api/sticker-list/
  option.sticker.package_id = 446; // sticker Package ID
  option.sticker.id = 1988; // sticker ID

  if (LINE.send("User ID/Group ID", "รถโดยขโมย", &option)) { 
    Serial.println("Send notify successful"); 
  } else { 
    Serial.printf("Send notify fail. check your token (code: %d)\n", LINE.status_code); 
  }
}

void loop() {

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////  https://pic.in.th/  ///////////////////////////////////////////////////////

LINE_Messaging_Massage_Option_t option; // สร้างตัวแปร option

  // https://developers.line.biz/en/docs/messaging-api/sticker-list/
  //option.sticker.package_id = 446; // sticker Package ID
  //option.sticker.id = 1988; // sticker ID
  option.image.url = "https://img2.pic.in.th/pic/557160.jpg";

  if (LINE.send("User ID/Group ID", "pop pop", &option)) { 
    Serial.println("Send notify successful"); 
  } else { 
    Serial.printf("Send notify fail. check your token (code: %d)\n", LINE.status_code); 
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// map ///////////////////////////////////////////////////////////////

LINE_Messaging_Massage_Option_t option; // สร้างตัวแปร option

  // https://developers.line.biz/en/docs/messaging-api/sticker-list/
  //option.sticker.package_id = 446; // sticker Package ID
  //option.sticker.id = 1988; // sticker ID
  //option.image.url = "https://img2.pic.in.th/pic/557160.jpg";
  option.map.service = LONGDO_MAP; // ใช้แผนที่จาก Longdo Map
  // option.map.service = GOOGLE_MAP; // ใช้แผนที่จาก Google Map
  option.map.lat = 13.84250; // ละติจูด
  option.map.lng = 100.85547; // ลองจิจูด
  option.map.zoom = 20; // ระยะซูม กำหนดได้ 1 - 20
  // option.map.api_key = "Google Map API Key"; // กรอก API Key หากใช้ Google Map

  if (LINE.send("User ID/Group ID", "pop pop", &option)) { 
    Serial.println("Send notify successful"); 
  } else { 
    Serial.printf("Send notify fail. check your token (code: %d)\n", LINE.status_code); 
  }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Gscript for lineMessging ///////////////////////////////////////////////////

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
/////////////////////////////////// line LDR .ino ////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  flex message //////////////////////////////////////////////////////////////

"{
  ""type"": ""bubble"",
  ""body"": {
    ""type"": ""box"",
    ""layout"": ""vertical"",
    ""contents"": [
      {
        ""type"": ""text"",
        ""text"": ""{{message}}"",
        ""weight"": ""bold"",
        ""color"": ""#1DB446"",
        ""size"": ""sm""
      },
      {
        ""type"": ""text"",
        ""text"": ""MUT"",
        ""weight"": ""bold"",
        ""size"": ""xxl"",
        ""margin"": ""md""
      },
      {
        ""type"": ""text"",
        ""text"": ""140 ถ.เชื่อมสัมพันธ์ หนองจอก กทม 10530"",
        ""size"": ""xs"",
        ""color"": ""#aaaaaa"",
        ""wrap"": true
      },
      {
        ""type"": ""separator"",
        ""margin"": ""xxl""
      },
      {
        ""type"": ""box"",
        ""layout"": ""vertical"",
        ""margin"": ""xxl"",
        ""spacing"": ""sm"",
        ""contents"": [
          {
            ""type"": ""box"",
            ""layout"": ""horizontal"",
            ""contents"": [
              {
                ""type"": ""text"",
                ""text"": ""sensor"",
                ""size"": ""sm"",
                ""color"": ""#555555"",
                ""flex"": 0
              },
              {
                ""type"": ""text"",
                ""text"": ""{{sensor}}"",
                ""size"": ""sm"",
                ""color"": ""#111111"",
                ""align"": ""end""
              }
            ]
          },
          {
            ""type"": ""separator"",
            ""margin"": ""xxl""
          },
          {
            ""type"": ""box"",
            ""layout"": ""horizontal"",
            ""contents"": [
              {
                ""type"": ""image"",
                ""url"": ""https://scdn.line-apps.com/n/channel_devcenter/img/fx/01_1_cafe.png"",
                ""backgroundColor"": ""#ffffff""
              }
            ]
          }
        ]
      },
      {
        ""type"": ""separator"",
        ""margin"": ""xxl""
      },
      {
        ""type"": ""box"",
        ""layout"": ""horizontal"",
        ""margin"": ""md"",
        ""contents"": [
          {
            ""type"": ""text"",
            ""text"": ""digital & embedded"",
            ""size"": ""xs"",
            ""color"": ""#aaaaaa"",
            ""flex"": 0
          },
          {
            ""type"": ""text"",
            ""text"": ""671111xxxx"",
            ""color"": ""#aaaaaa"",
            ""size"": ""xs"",
            ""align"": ""end""
          }
        ]
      }
    ]
  },
  ""styles"": {
    ""footer"": {
      ""separator"": true
    }
  }
}"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////  line take4  GScript ///////////////////////////////////////////////////////////////

var sheet_id = "17CY9HCEs75kBF-VMxLE89Srg";
var sheet_data = "data";
var sheet_config = "config";
//var sheet_id = "id";

//var accessToken =  "lvoiWlK5pc+TdbL9fV7sFwPgC2e/1PrIU0MgUxGGxi5ZhVMcDN/PBn+5OZCuBA9wdB04t89/1O/w1cDnyilFU=";

//var groupId = "C26f91799dbe8f63fa6f73";
//var groupId = "U7e22c2897d5741755b0e7";


//var sheet = SpreadsheetApp.openById(sheet_id).getSheetByName(sheet_data);
//var config = SpreadsheetApp.openById(sheet_id).getSheetByName(sheet_config);
//var accessToken = config.getRange('B1').getValue();


function doGet(e)
{
  var ss = SpreadsheetApp.openById(sheet_id);
  var sheet = ss.getSheetByName(sheet_data); 
  var sensor = Number(e.parameter.sensor);
  //Logger.log('old2: '+oldRow);
  //var sensor =1234;
  sheet.appendRow([new Date(),sensor]);
  sheet.
  var sheet2 = ss.getSheetByName(sheet_config); 
  var uid= sheet2.getRange('B2').getValue();
  
  sendLineMessageAPI(uid);
 
}

var dataReport = {
    date: " ",
    message: " ",
    sensor: " "
};


function sendLineMessageAPI()
{
  var ss = SpreadsheetApp.openById(sheet_id);
  var sheet = ss.getSheetByName(sheet_config);
  var accessToken = sheet.getRange('B1').getValue();
  var uid = sheet.getRange('B2').getValue();
  var sheet2 = ss.getSheetByName(sheet_data);
  var lastRow = sheet2.getLastRow();
  dataReport.date = DateConvert(sheet2.getRange(lastRow,1).getValue()); // ข้อความอยู่ที่คอลัมน์ A
  dataReport.sensor = sheet2.getRange(lastRow,2 ).getValue(); // ข้อความอยู่ที่คอลัมน์ B
  // หากต้องการเปลี่ยนเป็นข้อความแจ้งเตือน สามารถแก้ไขด้านที่ message
  dataReport.message = sheet.getRange('B4').getValue();

  var flexMessage = JSON.parse(sheet.getRange("B6").getValue());
  replaceVariables(flexMessage,dataReport);
  Logger.log(JSON.stringify(flexMessage));
  var lineHeader = {
    "Content-Type": "application/json",
    "Authorization" : "Bearer " + accessToken
  };

  var url = "https://api.line.me/v2/bot/message/push";

  var payload = {
    to: uid,
    messages: [
      {
        "type": "flex",
        "altText": "This is a Flex Message",
        "contents": flexMessage,
      },
    ],
  };
  Logger.log(JSON.stringify(payload));

  var options = {
    "method": "post",
    "headers": lineHeader,
    "payload": JSON.stringify(payload),
  };

  var response = UrlFetchApp.fetch(url, options);
  Logger.log(response.getContentText());
}


function replaceVariables(obj, variables) {
  for (var key in obj) {
    if (typeof obj[key] === "string") {
      // Replace variables in strings
      obj[key] = replaceVariablesInString(obj[key], variables);
    } else if (typeof obj[key] === "object") {
      // Recursively replace variables in nested objects
      replaceVariables(obj[key], variables);
    }
  }
}

function replaceVariablesInString(str, variables) {
  for (var key in variables) {
    var placeholder = "{{" + key + "}}";
    if (str.includes(placeholder)) {
      str = str.replace(placeholder, variables[key]);
    }
  }
  return str;
}


function formatNumber(number) {
  return number.toLocaleString();
}

function DateConvert(date) {

    var yyyy = date.getFullYear().toString();
    var mm = (date.getMonth()+1).toString(); // getMonth() is zero-based
    var dd  = date.getDate().toString();

    return (dd[1]?dd:"0"+dd[0]) + '-' + (mm[1]?mm:"0"+mm[0]) + '-' + yyyy;
}




////////////////////////////////////////end ////////////////////////////////////////////////



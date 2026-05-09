////////////////////////////////////////  BLE server  ////////////////////////////////////////////////////////
/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("Long name works now");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Hello World says Neil");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();  
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// BLE_scan ///////////////////////////////////////////////////////////////////

/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; //In seconds
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(2000);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////// esp32 BLE server AHT20 //////////////////////////////////////////////////////////////

/*********
  knandas
  esp32 BLE server + AHT20
*********/
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Wire.h>
#include <AHT20.h>
AHT20 aht20;

#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  2

//Default Temperature is in Celsius
//Comment the next line for Temperature in Fahrenheit
#define temperatureCelsius

//BLE server name
#define bleServerName "AHT20_ESP32"


float temp;
float tempF;
float hum;

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

bool deviceConnected = false;
bool disConDet = false;
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "91bad492-b950-4226-aa2b-4ede9fa42f59"

// Temperature Characteristic and Descriptor
#ifdef temperatureCelsius
  BLECharacteristic ahtTemperatureCelsiusCharacteristics("cba1d466-344c-4be3-ab3f-189f80dd7518", BLECharacteristic::PROPERTY_NOTIFY);
  BLEDescriptor ahtTemperatureCelsiusDescriptor(BLEUUID((uint16_t)0x2902));
#else
  BLECharacteristic ahtTemperatureFahrenheitCharacteristics("f78ebbff-c8b7-4107-93de-889a6a06d408", BLECharacteristic::PROPERTY_NOTIFY);
  BLEDescriptor ahtTemperatureFahrenheitDescriptor(BLEUUID((uint16_t)0x2902));
#endif

// Humidity Characteristic and Descriptor
BLECharacteristic ahtHumidityCharacteristics("ca73b3ba-39f6-4ab3-91ae-186dc9577d99", BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor ahtHumidityDescriptor(BLEUUID((uint16_t)0x2903));

//Setup callbacks onConnect and onDisconnect
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Connected");
  };
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Disconnected");
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println("Going to sleep now");
    esp_deep_sleep_start();
  };
};

void initAHT()
{
  if (!aht20.begin()) 
  {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    while (1);
  }
  Serial.println("AHT20 acknowledged.");
}

void setup() 
{
  // Start serial communication 
  Serial.begin(115200);

  // Init AHT Sensor
  initAHT();

  // Create the BLE Device
  BLEDevice::init(bleServerName);

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *ahtService = pServer->createService(SERVICE_UUID);

  // Create BLE Characteristics and Create a BLE Descriptor
  // Temperature
  #ifdef temperatureCelsius
    ahtService->addCharacteristic(&ahtTemperatureCelsiusCharacteristics);
    ahtTemperatureCelsiusDescriptor.setValue("AHT20 temperature Celsius");
    ahtTemperatureCelsiusCharacteristics.addDescriptor(&ahtTemperatureCelsiusDescriptor);
  #else
    ahtService->addCharacteristic(&bahtTemperatureFahrenheitCharacteristics);
    ahtTemperatureFahrenheitDescriptor.setValue("AHT20 temperature Fahrenheit");
    ahtTemperatureFahrenheitCharacteristics.addDescriptor(&ahtTemperatureFahrenheitDescriptor);
  #endif  

  // Humidity
  ahtService->addCharacteristic(&ahtHumidityCharacteristics);
  ahtHumidityDescriptor.setValue("AHT20 humidity");
  ahtHumidityCharacteristics.addDescriptor(new BLE2902());
  
  // Start the service
  ahtService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");

}

void loop() 
{
  if (deviceConnected) 
  {
    if ((millis() - lastTime) > timerDelay) 
    {
      // Read temperature as Celsius (the default)
      temp = aht20.getTemperature();
      //temp = random(1,20);
      // Fahrenheit
      tempF = 1.8*temp +32;
      // Read humidity
      hum = aht20.getHumidity();
      //hum = random(1,100);
  
      //Notify temperature reading from AHT20 sensor
      #ifdef temperatureCelsius
        static char temperatureCTemp[6];
        dtostrf(temp, 6, 2, temperatureCTemp);
        //Set temperature Characteristic value and notify connected client
        ahtTemperatureCelsiusCharacteristics.setValue(temperatureCTemp);
        ahtTemperatureCelsiusCharacteristics.notify();
        Serial.print("Temperature Celsius: ");
        Serial.print(temp);
        Serial.print(" ºC");
      #else
        static char temperatureFTemp[6];
        dtostrf(tempF, 6, 2, temperatureFTemp);
        //Set temperature Characteristic value and notify connected client
        ahtTemperatureFahrenheitCharacteristics.setValue(temperatureFTemp);
        ahtTemperatureFahrenheitCharacteristics.notify();
        Serial.print("Temperature Fahrenheit: ");
        Serial.print(tempF);
        Serial.print(" ºF");
      #endif
      
      //Notify humidity reading from AHT20
      static char humidityTemp[6];
      dtostrf(hum, 6, 2, humidityTemp);
      //Set humidity Characteristic value and notify connected client
      ahtHumidityCharacteristics.setValue(humidityTemp);
      ahtHumidityCharacteristics.notify();   
      Serial.print(" - Humidity: ");
      Serial.print(hum);
      Serial.println(" %");
      
      lastTime = millis();
    }
  }else
  {
    if(disConDet==0) 
    {
      lastTime=millis();
      disConDet=1;
    }  
    
    if(disConDet==1&&millis()-lastTime>5000)
    {
      esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
      Serial.println("Going to sleep now");
      esp_deep_sleep_start();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////// esp32 client AHT20 //////////////////////////////////////////////////////////////
/*********
 knandas
 esp32_BLE_client AHT20
*********/

#include "BLEDevice.h"


//Default Temperature is in Celsius
//Comment the next line for Temperature in Fahrenheit
#define temperatureCelsius

//BLE Server name (the other ESP32 name running the server sketch)
#define bleServerName "AHT20_ESP32"

/* UUID's of the service, characteristic that we want to read*/
// BLE Service
static BLEUUID ahtServiceUUID("91bad492-b950-4226-aa2b-4ede9fa42f59");

// BLE Characteristics
#ifdef temperatureCelsius
  //Temperature Celsius Characteristic
  static BLEUUID temperatureCharacteristicUUID("cba1d466-344c-4be3-ab3f-189f80dd7518");
#else
  //Temperature Fahrenheit Characteristic
  static BLEUUID temperatureCharacteristicUUID("f78ebbff-c8b7-4107-93de-889a6a06d408");
#endif

// Humidity Characteristic
static BLEUUID humidityCharacteristicUUID("ca73b3ba-39f6-4ab3-91ae-186dc9577d99");

//Flags stating if should begin connecting and if the connection is up
static boolean doConnect = false;
static boolean connected = false;

//Address of the peripheral device. Address will be found during scanning...
static BLEAddress *pServerAddress;
 
//Characteristicd that we want to read
static BLERemoteCharacteristic* temperatureCharacteristic;
static BLERemoteCharacteristic* humidityCharacteristic;

//Activate notify
const uint8_t notificationOn[] = {0x1, 0x0};
const uint8_t notificationOff[] = {0x0, 0x0};

//Variables to store temperature and humidity
char* temperatureChar;
char* humidityChar;

//Flags to check whether new temperature and humidity readings are available
boolean newTemperature = false;
boolean newHumidity = false;

//Connect to the BLE Server that has the name, Service, and Characteristics
bool connectToServer(BLEAddress pAddress) {
   BLEClient* pClient = BLEDevice::createClient();
 
  // Connect to the remove BLE Server.
  pClient->connect(pAddress);
  Serial.println(" - Connected to server");
 
  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(ahtServiceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(ahtServiceUUID.toString().c_str());
    return (false);
  }
 
  // Obtain a reference to the characteristics in the service of the remote BLE server.
  temperatureCharacteristic = pRemoteService->getCharacteristic(temperatureCharacteristicUUID);
  humidityCharacteristic = pRemoteService->getCharacteristic(humidityCharacteristicUUID);

  if (temperatureCharacteristic == nullptr || humidityCharacteristic == nullptr) {
    Serial.print("Failed to find our characteristic UUID");
    return false;
  }
  Serial.println(" - Found our characteristics");
 
  //Assign callback functions for the Characteristics
  temperatureCharacteristic->registerForNotify(temperatureNotifyCallback);
  humidityCharacteristic->registerForNotify(humidityNotifyCallback);
  return true;
}

//Callback function that gets called, when another device's advertisement has been received
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks 
{
  void onResult(BLEAdvertisedDevice advertisedDevice) 
  {
    if (advertisedDevice.getName() == bleServerName) 
    { //Check if the name of the advertiser matches
      advertisedDevice.getScan()->stop(); //Scan can be stopped, we found what we are looking for
      pServerAddress = new BLEAddress(advertisedDevice.getAddress()); //Address of advertiser is the one we need
      doConnect = true; //Set indicator, stating that we are ready to connect
      Serial.println("Device found. Connecting!");
    }
  }
};
 
//When the BLE Server sends a new temperature reading with the notify property
static void temperatureNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, 
                                        uint8_t* pData, size_t length, bool isNotify) {
  //store temperature value
  temperatureChar = (char*)pData;
  newTemperature = true;
}

//When the BLE Server sends a new humidity reading with the notify property
static void humidityNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, 
                                    uint8_t* pData, size_t length, bool isNotify) {
  //store humidity value
  humidityChar = (char*)pData;
  newHumidity = true;
}


void printReadings()
{
  Serial.print("Temperature:");
  Serial.print(temperatureChar);
  #ifdef temperatureCelsius
    //Temperature Celsius
    Serial.print("C");
  #else
    //Temperature Fahrenheit
    Serial.print("F");
  #endif
  Serial.print(" Humidity:");
  Serial.print(humidityChar); 
  Serial.println("%");
}

void setup() 
{
  //Start serial communication
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");

  //Init BLE device
  BLEDevice::init("");
 
  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 30 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);
}

void loop() 
{
  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
  // connected we set the connected flag to be true.
  if (doConnect == true) 
  {
    if (connectToServer(*pServerAddress)) 
    {
      Serial.println("We are now connected to the BLE Server.");
      //Activate the Notify property of each Characteristic
      temperatureCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);
      humidityCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);
      connected = true;
    } else 
    {
      Serial.println("We have failed to connect to the server; Restart your device to scan for nearby BLE server again.");
    }
    doConnect = false;
  }
  //if new temperature readings are available, 
  if (newTemperature && newHumidity){
    newTemperature = false;
    newHumidity = false;
    printReadings();
  }
  delay(1000); // Delay a second between loops.
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// esp32 BLE server two-way UART ////////////////////////////////
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic *pCharacteristic;
BLEDescriptor *pDescriptor;
BLEServer *pServer;
BLEService *pService;
bool deviceConnected = false;
bool deviceNotifying = false;
uint32_t txValue = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

/* 
 *  BLE Server Callbacks
 */
class MyServerCallbacks: public BLEServerCallbacks 
{
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
        Serial.println("device connected");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
        Serial.println("device disconnected");
    }
};

/* 
 *  BLE Characteristic Callbacks
 */
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      String strValue;

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
          strValue += rxValue[i];
        }
          //Serial.print(" ");
          //Serial.print(strValue.substring(0,5));
        Serial.println();
        // if (strValue.substring(0,5)=="value") {
        //   storeValue(strValue.substring(5));
        // }

        Serial.println("*********");
      }
    }
};





/* 
 *  BLE Descriptor Callbacks
 */
class MyDisCallbacks: public BLEDescriptorCallbacks 
{
    void onWrite(BLEDescriptor *pDescriptor) 
    {
      uint8_t* rxValue = pDescriptor->getValue();

      if (pDescriptor->getLength() > 0) {
        if (rxValue[0]==1) 
        {
          deviceNotifying=true;
        } else 
        {
          deviceNotifying=false;
        }
        Serial.println("*********");
        Serial.print("Received Descriptor Value: ");
        for (int i = 0; i < pDescriptor->getLength(); i++)
          Serial.print(rxValue[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};


/* 
  *  Activate BLE and start advertising
 */
void Prepare_BLE() 
{
  // Create the BLE Device
  BLEDevice::init("UART Service");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pDescriptor = new BLE2902();
  pCharacteristic->addDescriptor(pDescriptor);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pDescriptor->setCallbacks(new MyDisCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
  

}

void setup() 
{
 Serial.begin(115200);
 Prepare_BLE();

}  

void loop() 
{
  Serial.print("deviceConnect=");
  Serial.print(deviceConnected);
  Serial.print(" deviceNotifying=");
  Serial.println(deviceNotifying);
  if (deviceConnected && deviceNotifying) 
  {
    String TxTemp=String(txValue);
    //dtostrf(txValue,6,2,TxTemp);
    Serial.printf("*** Sent Value: %d ***\n", txValue);
    pCharacteristic->setValue(TxTemp.c_str());
    pCharacteristic->notify();
    txValue++;
  }
  delay(1000);


}  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// esp32 BLE client two-way UART  ////////////////////////////////////////

/*
 * Video: https://www.youtube.com/watch?v=oCMOYS71NIU
 * Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
 * Ported to Arduino ESP32 by Evandro Copercini, with some additional code by pcbreflux
 * 
 * A BLE client example that is rich in capabilities.
 */

#include "BLEDevice.h"
//#include "BLEScan.h"

// The remote service we wish to connect to.
static BLEUUID serviceUUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
// The characteristic of the remote service we are interested in.
static BLEUUID charUUID_TX("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
static BLEUUID charUUID_RX("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");

static BLEAddress *pServerAddress;
static boolean doConnect = false;
static boolean connected = false;
static BLERemoteCharacteristic* pRemoteCharacteristic_TX;
static BLERemoteCharacteristic* pRemoteCharacteristic_RX;

#define BLE_SERVER_SERVICE_NAME "UART Service"
#define GPIO_DEEP_SLEEP_DURATION     60  // sleep 1 seconds and then wake up
char* rxValue;
/* 
 *  BLE Callbacks
 */
static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) 
  {
    Serial.print("Notify callback:");
    Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print(" of data length ");
    Serial.print(length);
    Serial.print(" : ");
    String rxStr = (char*)pData;
      //String strValue;
      Serial.println(rxStr.substring(0, length));
  }

/* 
 *  BLE Connect to Server and Characteristic named in charUUID
 */
bool connectToServer(BLEAddress pAddress) {
    Serial.print("Forming a connection to ");
    Serial.println(pAddress.toString().c_str());
    
    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    // Connect to the remove BLE Server.
    pClient->connect(pAddress);
    Serial.println(" - Connected to server");

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) 
    {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      return false;
    }
    Serial.println(" - Found our service");


    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic_TX = pRemoteService->getCharacteristic(charUUID_TX);
    if (pRemoteCharacteristic_TX == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID_TX.toString().c_str());
      return false;
    }
    Serial.println(" - Found our characteristic");

    // Read the value of the characteristic.
    std::string value = pRemoteCharacteristic_TX->readValue();
    Serial.print("The characteristic TX value was: ");
    Serial.println(value.c_str());

    //pRemoteCharacteristic_TX->registerForNotify(notifyCallback);

    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic_RX = pRemoteService->getCharacteristic(charUUID_RX);
    if (pRemoteCharacteristic_RX == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID_RX.toString().c_str());
      return false;
    }
    Serial.println(" - Found our characteristic");

    // Read the value of the characteristic.
    value = pRemoteCharacteristic_RX->readValue();
    Serial.print("The characteristic RX value was: ");
    Serial.println(value.c_str());

    pRemoteCharacteristic_RX->registerForNotify(notifyCallback);

  return true;
}

/**
 * Scan for BLE servers Named in BLE_SERVER_SERVICE_NAME 
 * and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
 /**
   * Called for each advertising BLE server.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());
    if (advertisedDevice.haveServiceUUID()) {
      Serial.println(advertisedDevice.getServiceUUID().toString().c_str());
    }
    if (advertisedDevice.haveName()) {
      Serial.println(advertisedDevice.getName().c_str());
    }

    // We have found a device, let us now see if it contains the service we are looking for.
    //if (advertisedDevice.haveServiceUUID() && advertisedDevice.getServiceUUID().equals(serviceUUID)) {
    if (advertisedDevice.getName()==BLE_SERVER_SERVICE_NAME) 
    {
      // 
      Serial.print("Found our device!  address: "); 
      advertisedDevice.getScan()->stop();

      pServerAddress = new BLEAddress(advertisedDevice.getAddress());
      doConnect = true;

    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks


void setup() {
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 10 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(10);
} // End of setup.

static uint32_t pos=0;

// This is the Arduino main loop function.
void loop() 
{

  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
  // connected we set the connected flag to be true.
  if (doConnect == true) 
  {
    if (connectToServer(*pServerAddress)) 
    {
      Serial.println("We are now connected to the BLE Server.");
      connected = true;
    } else 
    {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }

  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.
  if (connected) 
  {
    String newValue = "value" + String(random(0,101));
    Serial.println("Setting new characteristic value to \"" + newValue + "\"");
    
    // Set the characteristic's value to be the array of bytes that is actually a string.
    pRemoteCharacteristic_TX->writeValue(newValue.c_str(), newValue.length());
    // Serial.println("enter deep sleep");
    // Serial.flush();
    // esp_deep_sleep(1000000LL * GPIO_DEEP_SLEEP_DURATION);
    // Serial.println("in deep sleep");
    // Serial.flush();
    //delay(1000);
  }
  
  Serial.println(pos++);
  delay(1000); // Delay a second between loops.
  if (pos>=60) {
    pos=0;
    // Serial.println("enter deep sleep");
    // Serial.flush();
    // esp_deep_sleep(1000000LL * GPIO_DEEP_SLEEP_DURATION);
    // Serial.println("in deep sleep");
    // Serial.flush();
  }
} // End of loop


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// esp32 BLE server academy ////////////////////////////////////////

/*
  TODO

    [x] Create a BLE Device
        [x] Import BLEDevice Library
        [x] Name Device
        [x] Initialize Device

    [x] Create Server
        [x] Import BLEServer library
        [x] Create BLEServer

    [x] Create Server Callbacks
        [x] OnConnect
            [x] Turn on LED
        [x] OnDisconnect
            [x] Turn off LED
    
    [x] Create Service
        [x] Define a Service UUID
        [x] Create a Service
        [x] Start the Service

    [x] Create Characteristic
        [x] Define a Characteristic UUID
        [x] Create a Characteristic
        [x] Add Characteristic to Service

    [x] Create a Characteristic Callback
        [x] create sub-class to override BLECharacteristicCallbacks
        [x] Send millis value every time request comes in

    [x] Create a Descriptor
        [x] Add a Descriptor (2901)

    [] Advertise the Service
        [x] Get the Advertising object from Device
        [x] Create and set Advertisement Data
        [x] Create and set Scan Data
        [x] Add Advertisement and Scan Data to Advertising Object
        [x] Add Service UUID
        [x] Start Advertising

*/

/** Includes ***********************************/
#include <BLEDevice.h>
#include <BLE2901.h>

/** Defines ***********************************/
#define DEVICE_NAME "CIA Monitoring Device"
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_1_UUID "d9b4049b-c663-446c-9211-71754d930811"
#define CHARACTERISTIC_1A_UUID "596d9fe5-baf0-472b-89ee-bbb3ce27165a"
#define CHARACTERISTIC_1B_UUID "fd52c152-7b33-4059-80c6-090143a3d2f8"

/** Callbacks ***********************************/
class MyServerCallbacks : public BLEServerCallbacks {

  void onConnect(BLEServer *pServer) {
    digitalWrite(2, HIGH);
    Serial.println("Client Connected");
  }

  void onDisconnect(BLEServer *pServer) {
    digitalWrite(2, LOW);
    Serial.println("Client Disconnected");
    BLEDevice::startAdvertising();
  }
};

class MyCharacteristic_1A_Callbacks : public BLECharacteristicCallbacks {

  void onRead(BLECharacteristic *pCharacteristic) {
    uint32_t currentMillis = millis() / 1000;
    pCharacteristic->setValue(currentMillis);
  }
};



void setup() {

  Serial.begin(9600);
  Serial.println("ESP32 BLE Server setup beginning...");

  // Pin modes
  pinMode(2, OUTPUT);

  //Initialize Device
  BLEDevice::init(DEVICE_NAME);

  // Create Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Services
  BLEService *pService = pServer->createService(SERVICE_1_UUID);

  // Characteristics
  BLECharacteristic *pCharacteristic_1A = pService->createCharacteristic(
    CHARACTERISTIC_1A_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

  pCharacteristic_1A->setCallbacks(new MyCharacteristic_1A_Callbacks());

  // Descriptors
  BLE2901 *pDescriptor_2901 = new BLE2901();
  pDescriptor_2901->setDescription("Time");
  pCharacteristic_1A->addDescriptor(pDescriptor_2901);

  pService->start();

  // Advertising
  // Get the Advertising object
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  /*
  // Advertisement Data
  BLEAdvertisementData advertisementData;
  advertisementData.setFlags(ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT);
  advertisementData.setName(DEVICE_NAME);
  advertisementData.setCompleteServices(BLEUUID(SERVICE_1_UUID));
  advertisementData.setPartialServices(BLEUUID(SERVICE_1_UUID));
  advertisementData.setServiceData(BLEUUID(SERVICE_1_UUID), "some data");
  
  // // Scan Response Data
  BLEAdvertisementData scanResponseData;
  scanResponseData.setName(DEVICE_NAME);
  
  // Add advertising data and scan response data to advertising
  pAdvertising->setAdvertisementData(advertisementData);
  pAdvertising->setScanResponseData(scanResponseData);
  */
  
  // Adertising settings
  pAdvertising->addServiceUUID(SERVICE_1_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue

  BLEDevice::startAdvertising();
}

void loop() {
  // put your main dog chow here, to run repeatedly:
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// esp32 BLE client academy ////////////////////////////////////////

//  BLE Client Example Sketch
//
//  Programming Electronics Academy
//

#include <BLEDevice.h>            // sets up BLE device constructs

// The remote service we wish to connect to.
static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");

// The characteristic of the remote service we are interested in.
static BLEUUID    charUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");
static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;

static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLEAdvertisedDevice* myDevice;
static void notifyCallback(

  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {

    Serial.print("Notify callback for characteristic ");
    Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print(" of data length ");
    Serial.println(length);
    Serial.print("data: ");
    Serial.println((char*)pData);

}

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {

  }

  void onDisconnect(BLEClient* pclient) {
    connected = false;

    Serial.println("onDisconnect");

  }

};

bool connectToServer() {
    Serial.print("Forming a connection to ");
    Serial.println(myDevice->getAddress().toString().c_str());
    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");
    pClient->setClientCallbacks(new MyClientCallback());

    // Connect to the remove BLE Server.
    pClient->connect(myDevice);
    Serial.println(" - Connected to server");

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) {

      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      pClient->disconnect();

      return false;

    }

    Serial.println(" - Found our service");

    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);

    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
      pClient->disconnect();

      return false;

    }

    Serial.println(" - Found our characteristic");
    // Read the value of the characteristic.
    if(pRemoteCharacteristic->canRead()) {

      String value = pRemoteCharacteristic->readValue();

      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());

    }

    if(pRemoteCharacteristic->canNotify())
      pRemoteCharacteristic->registerForNotify(notifyCallback);
    connected = true;
    return true;

}

// Scan for BLE servers and find the first one that advertises the service we are looking for.
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {

  // Called for each advertising BLE server.
  void onResult(BLEAdvertisedDevice advertisedDevice) {

    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;

    } // Found our server

  } // onResult

}; // MyAdvertisedDeviceCallbacks

void setup() {

  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 5 seconds.

  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);

} // End of setup.

// This is the Arduino main loop function that runs repeatedly.

void loop() {

  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
  // connected we set the connected flag to be true.

  if (doConnect == true) {

    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
    } else {

      Serial.println("We have failed to connect to the server; there is nothin more we will do.");

    }

    doConnect = false;

  }

  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.

  if (connected) {

    String newValue = "Time since boot: " + String(millis()/1000);
    Serial.println("Setting new characteristic value to \"" + newValue + "\"");

    // Set the characteristic's value to be the array of bytes that is actually a string.
    pRemoteCharacteristic->writeValue(newValue.c_str(), newValue.length());

  }else if(doScan){

    BLEDevice::getScan()->start(0);  // this is just an example to re-start the scan after disconnect

  }

  delay(1000); // Delay a second between loops.

}

/////////////////////////////////////////////end ////////////////////////////////////////////////////

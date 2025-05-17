https://www.apachefriends.org/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CREATE TABLE sensordata 
(
    id BIGINT(10) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    sensor VARCHAR(30) NOT NULL,
    location VARCHAR(30) NOT NULL,
    value1 VARCHAR(10),
    value2 VARCHAR(10),
    value3 VARCHAR(10),
    reading_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
)

/////////////////////////////////////////////////////////////////////////////////////////////////

INSERT INTO `sensordata` (`id`, `sensor`, `location`, `value1`, `value2`, `value3`, `reading_time`) VALUES ('1', 'aaa', 'bbb', '1', '2', '3', CURRENT_TIMESTAMP()) 
  
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  esp-data.php ////////////////////////////////////////////////////////////////////////////////////
  
<!DOCTYPE html>
<html>
<body>
<center>
<?php

$servername = "localhost";

// REPLACE with your Database name
$dbname = "testuser";
// REPLACE with Database user
$username = "testUSER";
// REPLACE with Database user password
$password = "HewPpUu*r26V9EUg";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT id, sensor, location, value1, value2, value3, reading_time FROM sensordata ORDER BY id ASC";



  echo '<table cellspacing="5" cellpadding="5">
      <tr> 
      <td>No.</td> 
        <td>ID</td> 
        <td>Sensor</td> 
        <td>Location</td> 
        <td>Value 1</td> 
        <td>Value 2</td>
        <td>Value 3</td> 
        <td>Timestamp</td> 
      </tr>';
 $num = isset($num) ? $num : '';
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
    $num++;
        $row_id = $row["id"];
        $row_sensor = $row["sensor"];
        $row_location = $row["location"];
        $row_value1 = $row["value1"];
        $row_value2 = $row["value2"]; 
        $row_value3 = $row["value3"]; 
        $row_reading_time = $row["reading_time"];
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
      
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        $row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 7 hours"));
      
        echo '<tr> 
        <td>' . $num .    '</td>
                <td>' . $row_id . '</td> 
                <td>' . $row_sensor . '</td> 
                <td>' . $row_location . '</td> 
                <td>' . $row_value1 . '</td> 
                <td>' . $row_value2 . '</td>
                <td>' . $row_value3 . '</td> 
                <td>' . $row_reading_time . '</td> 
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</center>
</body>
</html>



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////  post-esp-data.php  ///////////////////////////////////////////////////////////////////////////

<?php
declare(strict_types=1);
$servername = "localhost";
// REPLACE with your Database name
$dbname = "testuser";
// REPLACE with Database user
$username = "testUSER";
// REPLACE with Database user password
$password = "HewPpUu*r26V9EUg";

// Keep this API Key value to be compatible with the ESP32 code provided in the project page. If you change this value, the ESP32 sketch needs to match
$api_key_value = "tPmAT5Ab3j7F9";

$api_key = $id = $sensor = $location= $value1 = $value2 = $value3 = "";
// Set response content type to JSON
header("Content-Type: application/json");

// Check if the request method is POST
if ($_SERVER["REQUEST_METHOD"] === "POST") 
{
    // Retrieve and sanitize POST data
    $data = [];
	//$api_key = test_input($_POST["api_key"]);
    
	
	foreach ($_POST as $key => $value) {
        $data[$key] = htmlspecialchars(trim($value), ENT_QUOTES | ENT_HTML401);
    }

    // Return the sanitized data to the client
    echo json_encode([
        "status" => "success",
        "received_data" => $data
    ], JSON_PRETTY_PRINT);
    
    if($data["api_key"] == $api_key_value) 
	{	
	 $sensor=$data["sensor"]; 
	 $location=$data["location"]; 
	 $value1=$data["value1"]; 
	 $value2=$data["value2"]; 
	 $value3=$data["value3"]; 
	
     $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) 
        {
            //file_put_contents('debug.log', print_r("connect_error",true), FILE_APPEND);
            die("Connection failed: " . $conn->connect_error);
        } 
        

  
      //    $sql = "INSERT INTO 'sensordata' ('sensor', location, value1, value2, value3)
      //    VALUES ('" . $sensor . "', '" . $location . "', '" . $value1 . "', '" . $value2 . "', '" . $value3 . "')";
      
     $sql = "INSERT INTO `sensordata` ( `sensor`, `location`, `value1`, `value2`, `value3`, `reading_time`) VALUES ('$sensor', '$location', '$value1', '$value2', '$value2', CURRENT_TIMESTAMP())";
        
        
        if ($conn->query($sql) === TRUE) 
        {
            //file_put_contents('debug.log', print_r("New record created successfully",true), FILE_APPEND);
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else 
    {
        echo "Wrong API Key provided.";
    }

} else {
    // Return an error message if the request is not POST
    echo json_encode([
        "status" => "error",
        "message" => "Please send a POST request with x-www-form-urlencoded data."
    ], JSON_PRETTY_PRINT);
}
?>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////  esp_mysql.ino ///////////////////////////////////////////////////////////////////////////////////

#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
char* ssid     = "ELEC302";  //ELEC302_plus
char* password = "elec1234";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.1.xxx/post-esp-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9"; //tPmAT5Ab3j7F9
//String id = "52";
String sensorName = "volt1";    //any
String sensorLocation = "Office";  

void setup() 
{
  delay(1000);
  Serial.begin(115200);
  Serial.println("start");
  delay(1000);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{  
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue +"&sensor=" + sensorName
                          + "&location=" + sensorLocation + "&value1=" + String(analogRead(39))
                          + "&value2=" + String(map(analogRead(36),0,4095,0,100)) + "&value3=" + String("3") + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
         
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println("Server Response:");
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
  //Send an HTTP POST request every 30 seconds
  delay(30000);  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// esp_mysql_bmp280_aht20.ino ////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_BMP280.h>
#include <AHT20.h>
AHT20 aht20;
Adafruit_BMP280 bmp; // I2C
float  temperature= 0;
float  humidity=  0;
float  pressure = 0;
// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Replace with your network credentials
char* ssid     = "ELEC302";  //ELEC302_plus
char* password = "elec1234";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.1.xxx/post-esp-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9"; //tPmAT5Ab3j7F9
//String id = "52";
String sensorName = "BMP280+AHT20";    //any
String sensorLocation = "Office";  

void setup() 
{
  delay(1000);
  Serial.begin(115200);
  Serial.println("start");
  delay(1000);
  initBMP_AHT(); // Init BMP280 + AHT20
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{  
  if ((millis() - lastTime) > timerDelay) //Send an HTTP POST request every 30 seconds
  {
    readSensor();
    if(WiFi.status()== WL_CONNECTED)
    {
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      
      // Prepare your HTTP POST request data
      String httpRequestData = "api_key=" + apiKeyValue +"&sensor=" + sensorName
                            + "&location=" + sensorLocation + "&value1=" + String(temperature)
                            + "&value2=" + String(humidity) + "&value3=" + String(pressure) + "";
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);
      
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
          
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println("Server Response:");
        Serial.println(payload);

      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else 
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime=millis();
  } 
  
  delay(10);  
}


// Init BMP280 + AHT20
void initBMP_AHT()
{
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

void readSensor()
{
  temperature= bmp.readTemperature();
  humidity=  aht20.getHumidity();
  pressure = bmp.readPressure()/100.0F;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////  esp-chart.php /////////////////////////////////////////////////////////////////

<?php

$servername = "localhost";


// REPLACE with your Database name
$dbname = "testuser";
// REPLACE with Database user
$username = "testUSER";
// REPLACE with Database user password
$password = "HewPpUu*r26V9EUg";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT id, value1, value2, value3, reading_time FROM sensordata order by reading_time desc limit 40";

$result = $conn->query($sql);

while ($data = $result->fetch_assoc()){
    $sensor_data[] = $data;
}

$readings_time = array_column($sensor_data, 'reading_time');

// ******* Uncomment to convert readings time array to your timezone ********
/*$i = 0;
foreach ($readings_time as $reading){
    // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
    $readings_time[$i] = date("Y-m-d H:i:s", strtotime("$reading - 1 hours"));
    // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
    //$readings_time[$i] = date("Y-m-d H:i:s", strtotime("$reading + 4 hours"));
    $i += 1;
}*/

$value1 = json_encode(array_reverse(array_column($sensor_data, 'value1')), JSON_NUMERIC_CHECK);
$value2 = json_encode(array_reverse(array_column($sensor_data, 'value2')), JSON_NUMERIC_CHECK);
$value3 = json_encode(array_reverse(array_column($sensor_data, 'value3')), JSON_NUMERIC_CHECK);
$reading_time = json_encode(array_reverse($readings_time), JSON_NUMERIC_CHECK);

/*echo $value1;
echo $value2;
echo $value3;
echo $reading_time;*/

$result->free();
$conn->close();
?>

<!DOCTYPE html>
<html>
<meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://code.highcharts.com/highcharts.js"></script>
  <style>
    body {
      min-width: 310px;
      max-width: 1280px;
      height: 500px;
      margin: 0 auto;
    }
    h2 {
      font-family: Arial;
      font-size: 2.5rem;
      text-align: center;
    }
  </style>
  <body>
    <h2>ESP Embedded MII</h2>
    <div id="chart-temperature" class="container"></div>
    <div id="chart-humidity" class="container"></div>
    <div id="chart-pressure" class="container"></div>
<script>

var value1 = <?php echo $value1; ?>;
var value2 = <?php echo $value2; ?>;
var value3 = <?php echo $value3; ?>;
var reading_time = <?php echo $reading_time; ?>;

var chartT = new Highcharts.Chart({
  chart:{ renderTo : 'chart-temperature' },
  title: { text: 'Temperature' },
  series: [{
    showInLegend: false,
    data: value1
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    },
    series: { color: '#059e8a' }
  },
  xAxis: { 
    type: 'datetime',
    categories: reading_time
  },
  yAxis: {
    title: { text: 'Temperature (Celsius)' }
    //title: { text: 'Temperature (Fahrenheit)' }
  },
  credits: { enabled: false }
});

var chartH = new Highcharts.Chart({
  chart:{ renderTo:'chart-humidity' },
  title: { text: 'humidity' },
  series: [{
    showInLegend: false,
    data: value2
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    }
  },
  xAxis: {
    type: 'datetime',
    //dateTimeLabelFormats: { second: '%H:%M:%S' },
    categories: reading_time
  },
  yAxis: {
    title: { text: '%humidity' }
  },
  credits: { enabled: false }
});


var chartP = new Highcharts.Chart({
  chart:{ renderTo:'chart-pressure' },
  title: { text: 'Pressure' },
  series: [{
    showInLegend: false,
    data: value3
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    },
    series: { color: '#18009c' }
  },
  xAxis: {
    type: 'datetime',
    categories: reading_time
  },
  yAxis: {
    title: { text: 'Pressure (hPa)' }
  },
  credits: { enabled: false }
});

</script>
</body>
</html>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

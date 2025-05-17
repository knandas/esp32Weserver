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

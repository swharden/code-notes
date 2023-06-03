# SQLite in PHP

```php
<?php

header("Content-Type: text/plain");

include "../../key.php";

function get_post_data()
{
    if ($_SERVER["REQUEST_METHOD"] != "POST") {
        echo "ERROR: POST required";
        die();
    }

    $data = json_decode(file_get_contents('php://input'), true);

    if (empty($data)) {
        echo "ERROR invalid JSON";
        die();
    }

    if ($data['key'] != get_api_key()) {
        echo "ERROR 'key' is invalid";
        die();
    }

    return $data;
}

function store_csv($timestamp, $sensor, $temperature, $pressure)
{
    $file = '../log.txt';
    $line = "$timestamp,$sensor,$temperature,$pressure\n";
    file_put_contents($file, $line, FILE_APPEND | LOCK_EX);
}

function store_db($timestamp, $sensor, $temperature, $pressure)
{
	
	// connect
	$db = new SQLite3('weather.db');

	// setup table
	$query = "CREATE TABLE IF NOT EXISTS readings (
		id INTEGER PRIMARY KEY AUTOINCREMENT,
		timestamp INTEGER,
		sensor INTEGER,
		temperature INTEGER,
		pressure INTEGER
	)";
	$db->exec($query);

	// make record
    $timestamp = time();
	$sensor = intval($sensor);
	$temperature = intval($temperature * 100);
	$pressure = intval($pressure);
	$query = "INSERT INTO readings (timestamp, sensor, temperature, pressure) " . 
		"VALUES ($timestamp, $sensor, $temperature, $pressure)";
	$db->exec($query);

	// disconnect
	$db->close();	
}

$data = get_post_data();
$timestamp = time();
$sensor = $data['sensor'];
$temperature = $data['temperature'];
$pressure = $data['pressure'];

store_csv($timestamp, $sensor, $temperature, $pressure);
store_db($timestamp, $sensor, $temperature, $pressure);

echo "[$timestamp] Success";
```

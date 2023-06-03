# SQLite in PHP

```php
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
```

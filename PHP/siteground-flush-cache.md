# SiteGround: Console Command to Flush Dynamic Cache

This command executed on the surver will purge the dynamic cache:

```sh
curl -X PURGE http://127.0.0.1/ -H "Host: example.com"
```

### purge.php
```php
<?php
header("Cache-Control: no-cache");
if ($_POST['key'] == "PASSWORD123"){
	exec('curl -X PURGE http://127.0.0.1/ -H "Host: swharden.com"');
	echo "Purge: Successful";
} else {
	echo "ERROR: Invalid Key";
}
```

### Request
```
curl --data "key=PASSWORD123" https://swharden.com/purge/
```

### .htaccess
```
Header set Cache-Control "private"
```

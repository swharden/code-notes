# SiteGround: Console Command to Flush Dynamic Cache

```bash
curl -s -k -X PURGE -L https://example.com/*
```

## Clear Cache with PHP

### clear-cache.php
```php
<?php

// This page won't work if it's cached
header("Cache-Control: no-cache");

// NOTE: see .htaccess to enable PHP_AUTH_PW
if (empty($_SERVER['PHP_AUTH_PW'])) {
    echo "ERROR: Password Required";
} else if ($_SERVER['PHP_AUTH_PW'] == 'P4SSW0RD') {
	exec('curl -s -k -X PURGE -L https://maui.graphics/*');
	echo("Purge: Successful");
} else {
    echo "ERROR: Incorrect Password";
}
```

### .htaccess
```
SetEnvIf Authorization .+ HTTP_AUTHORIZATION=$0
```

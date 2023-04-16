# SiteGround: Console Command to Flush Dynamic Cache

This command executed on the surver will purge the dynamic cache:

```sh
curl -X PURGE http://127.0.0.1/ -H "Host: example.com"
```

### purge.php
```php
<?php
header("Cache-Control: no-cache");
exec('curl -X PURGE http://127.0.0.1/ -H "Host: example.com"');
echo("Purge: Successful");
```

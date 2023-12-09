# SiteGround: Console Command to Flush Dynamic Cache

## Login with SSH
* Use web interface to create SSH key
* Copy private key into key.txt locally
* Load key.txt into bitvise client key manager
* Configure bitvise to use publickey+password

## Purge Cache over SSH
```sh
site-tools-client domain update id=1 flush_cache=1
```

Domain IDs can be listed using:
```sh
site-tools-client domain list -f id,name
```

## Purge Cache from another host
```sh
ssh example.com@gcam1098.siteground.biz -p 18765 "site-tools-client domain update id=1 flush_cache=1"
```

## Purge Cache with PHP

```php
<?php
header("Cache-Control: no-cache");
header("Content-Type: text/plain");
exec("site-tools-client domain update id=1 flush_cache=1");
echo("Purged " . time());
```

### .htaccess
not sure if this works
```
Header set Cache-Control "private"
```

# PHP Request Information

```php
$info = array(
    "url" => (isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] === 'on' ? "https" : "http") . "://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]",
    "code" => http_response_code(),
    "utc" => (new DateTime())->format("c"),
    "ref" => $_SERVER['HTTP_REFERER'],
    "ip" => $_SERVER['REMOTE_ADDR'],
    "agent" => $_SERVER['HTTP_USER_AGENT'],
);

echo "<pre>";
print_r($info);
echo "</pre>";
```

```
Array
(
    [url] => http://localhost:8080/my/bad/url.html
    [code] => 404
    [utc] => 2021-09-28T23:04:30+00:00
    [ref] => http://localhost:8080/
    [ip] => 172.18.0.1
    [agent] => Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36
)
```

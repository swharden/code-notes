# PHP Redirect

* 301 - permanent redirect
* 302 - temporary redirect

```cs
<?php

function Redirect(string $url, bool $permanent = false): void
{
    header('Location: ' . $url, true, $permanent ? 301 : 302);
    die();
}

Redirect('https://scottplot.net/cookbook/4.1/colors/', true);
```

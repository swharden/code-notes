# Enable all requests in Apache

When developing locally I found Hugo and NPM/React servers cannot request JSON files served by Apache due to CORS restrictions.

To disable cors in Apache you must edit `httpd.conf` file and un-comment this line:

```
LoadModule headers_module modules/mod_headers.so
```

Then you can add this in `.htaccess` or inside the `Directory` element in `httpd.conf`

```
Header set Access-Control-Allow-Origin *
```

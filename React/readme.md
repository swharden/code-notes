# React JS Notes

## Setup
* https://nodejs.org/en/download/
* `npm install -g create-react-app`
* `npx create-react-app appname -template typescript`
* `cd appname`
* `npm audit fix`
* `npm start`

## Run Once On Load

```js
import React, { useState, useEffect } from 'react';

function MyComponent() {

  const [timeNow, setTimeNow] = useState("first");

  useEffect(() => {
    doOnce();
  }, []);

  const doOnce = () => {
      timeNow = new Date().toISOString());
  }

  return (<div>{timeNow}</div>);
}

export default MyComponent;
```

## Routing in Apache

### .htaccess

```
Options -MultiViews
RewriteEngine On
RewriteCond %{REQUEST_FILENAME} !-f
RewriteRule ^ index.html [QSA,L]
```

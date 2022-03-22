# React JS Notes

## Setup
* https://nodejs.org/en/download/
* `npm install -g create-react-app`
* `npx create-react-app abf-browser -template typescript`

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

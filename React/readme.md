# React JS Notes

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
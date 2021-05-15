import React, { useState } from 'react';

import Alpha from "./components/Alpha";
import Beta from "./components/Beta";

function App() {

  const [message, setMessage] = useState('not set yet');

  const buttonAction = () => {
    console.log("clicked");
    setMessage("clicked " + new Date().toISOString());
  };

  return (
    <div className="container">
      <div className="my-5">

        <ul>
          <li>A top-level function is defined in <code>App</code></li>
          <li>The function is passed into the <code>Alpha</code> component and executed on a button click</li>
          <li>Execution of the top-level function changes state in the <code>Beta</code> component</li>
        </ul>

        <Alpha action={buttonAction} />
        <Beta message={message} />
      </div>
    </div>
  );
}

export default App;

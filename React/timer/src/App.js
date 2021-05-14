import React from "react";
import TimerClass from "./TimerClass";
import TimerFunctional from "./TimerFunctional";

class App extends React.Component {

  render() {
    return (
      <div className="container" >
        <TimerClass />
        <TimerFunctional />
      </div>
    );
  }
}

export default App;

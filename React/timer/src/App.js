import React from "react";
import Child from "./Child";

class App extends React.Component {

  constructor(props) {
    super(props);
    this.state = {
      numbers: []
    }
  }

  componentDidMount() {
    setInterval(() => this.tick(), 1000);
  }

  tick() {
    const countMin = 5;
    const countMax = 20;
    const count = Math.floor(Math.random() * (countMax - countMin)) + countMin;
    const numbers = Array.apply(null, Array(count)).map(x => Math.floor(Math.random() * 100));
    this.setState({ numbers: numbers });
  }

  render() {
    return (
      <div className="container" >
        <h1>React Timer</h1>

        <p>
          This example shows how to create a timer that does something every second using class components.
        </p>
        <p>
          It also demonstrates how to pass data into child components easily.
        </p>

        {
          this.state.numbers.map(item => {
            return <Child message={item} />
          })
        }

      </div>
    );
  }
}

export default App;

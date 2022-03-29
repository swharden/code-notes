# Managing Component State
  
This example shows how to manage state within a component using modern class components and hooks

* [Function and Class Components](https://reactjs.org/docs/components-and-props.html#function-and-class-components)
* Official API documentation: [setState()](https://reactjs.org/docs/react-component.html#setstate)

```jsx
import React from 'react';

class Counter extends React.Component {

    state = {
        count: 123
    };

    changeCount(delta) {
        this.setState({ count: this.state.count + delta });
    }

    setCount(newValue) {
        this.setState({ count: newValue });
    }

    render() {
        return (
            <div>
                Count: {this.state.count}
                <button onClick={() => this.changeCount(1)}>increment</button>
                <button onClick={() => this.setCount(0)}>reset</button>
                <button onClick={() => this.changeCount(-1)}>decrement</button>
            </div>
        );
    }
}

export default Counter;
```

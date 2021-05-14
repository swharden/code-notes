import React from "react";
import Child from "./Child";

class TimerClass extends React.Component {
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
            <div className="border bg-light rounded p-3 m-5 shadow">
                <h1>Timer (Class Model)</h1>
                {
                    this.state.numbers.map(item => {
                        return <Child message={item} />
                    })
                }
            </div>
        );
    }
}

export default TimerClass;
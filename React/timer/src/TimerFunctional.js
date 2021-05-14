import React, { useState, useEffect } from 'react';
import Child from "./Child";

const TimerFunctional = () => {

    const [myValue, setMyValue] = useState('initial');
    const [numbers, setNumbers] = useState([]);

    useEffect(() => {

        const tick = () => {
            const countMin = 5;
            const countMax = 20;
            const count = Math.floor(Math.random() * (countMax - countMin)) + countMin;
            const numbers = Array.apply(null, Array(count)).map(x => Math.floor(Math.random() * 100));
            setNumbers(numbers);
        };

        const interval = setInterval(() => { tick(); }, 1000);
        return () => clearInterval(interval);
    }, []);

    return (
        <div className="border bg-light rounded p-3 m-5 shadow">
            <h1>Timer (Functional Style)</h1>
            {
                numbers.map(item => {
                    return <Child message={item} />
                })
            }
        </div>
    )
}

export default TimerFunctional;
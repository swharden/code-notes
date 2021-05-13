import React from 'react';

class Child extends React.Component {
    render() {
        return (
            <div>
                I'm just a kid! <code>{this.props.message}</code>
            </div>
        )
    }
}

export default Child;

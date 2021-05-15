function Alpha(props) {

    const action = props.action

    return (
        <div className="m-5 border rounded bg-light p-3">
            <h1>Alpha</h1>
            <button className="btn btn-primary" onClick={action}>do the thing!</button>
        </div>
    );
}

export default Alpha;

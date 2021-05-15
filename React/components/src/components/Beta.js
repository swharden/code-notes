function Beta(props) {

    const message = props.message;

    return (
        <div className="m-5 border rounded bg-light p-3">
            <h1>Beta</h1>
            {message}
        </div>
    );
}

export default Beta;

function App() {

  const getView = () => {
    const urlParams = new URLSearchParams(window.location.search);
    switch (urlParams.get('view')) {
      case "mobile":
        return "mobile"
      default:
        return "desktop"
    }
  }

  return (
    <div className="container">
      <h1>Routing Tests</h1>
      <code>{getView()}</code>
    </div>
  );
}

export default App;

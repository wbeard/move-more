let component = ReasonReact.statelessComponent("App");

let make = (~route, _children) => {
  ...component,
  render: (_self) => {
    let page =
      switch route {
      | Routing.Home => <Home />
      | Routing.Settings => <Settings />
      };
    <div className="App">
      <Header />
      page
    </div>
  }
};
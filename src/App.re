open Utils;

let component = ReasonReact.statelessComponent("App");

let make = (~route, _children) => {
  ...component,
  render: _self => {
    let settings = getSettings();
    let page =
      switch route {
      | Routing.Home =>
        <Home duration=settings##duration time=settings##time />
      | Routing.Meditation => <Meditation duration=settings##duration />
      | Routing.Settings =>
        <Settings duration=settings##duration time=settings##time />
      };
    <div className="App"> <Header /> page </div>;
  }
};
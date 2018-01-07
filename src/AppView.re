open Utils;

open Types.Routing;

let component = ReasonReact.statelessComponent("AppView");

let make = (~route, _children) => {
  ...component,
  render: _self => {
    let settings = PersistenceUtils.get();
    let page =
      switch route {
      | Home => <HomeView duration=settings##duration time=settings##time />
      | Meditation => <MeditationView duration=settings##duration />
      | Setting(setting) =>
        <SettingsView
          duration=settings##duration
          time=settings##time
          setting
        />
      };
    <div className="App"> <Header /> page </div>;
  }
};
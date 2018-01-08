open Utils;

open Utils.JsInterop;

open Types.Routing;

open Utils.ReactUtils;

require("./app.css");

type s = {
  duration: int,
  time: string
};

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
          calendared=settings##calendared
          setting
        />
      };
    let className = "App" ++ (route === Meditation ? " App-dark" : "");
    <div className>
      (route === Meditation ? ReasonReact.nullElement : <Header />)
      page
      (
        route === Meditation ?
          ReasonReact.nullElement :
          <p className="Home-attribution">
            ("Photo by " |> str)
            <a
              className="Home-attributionLink"
              href="https://unsplash.com/photos/mkdI8JN6sDU?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">
              ("Matheus Bandoch" |> str)
            </a>
            (" on " |> str)
            <a
              className="Home-attributionLink"
              href="https://unsplash.com/?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText">
              ("Unsplash" |> str)
            </a>
          </p>
      )
    </div>;
  }
};
open Utils.JsInterop;

open Types;

registerServiceWorker();

require("./index.css");

let renderForRoute = route =>
  ReactDOMRe.renderToElementWithId(<AppView route />, "root");

let router =
  DirectorRe.makeRouter({
    "/": () => Routing.Home |> renderForRoute,
    "/meditation": () => Routing.Meditation |> renderForRoute,
    "/settings": () => Routing.Setting(Time) |> renderForRoute,
    "/settings/:setting": setting =>
      Routing.Setting(Settings.fromStringToType(setting)) |> renderForRoute
  });

DirectorRe.init(router, "/");
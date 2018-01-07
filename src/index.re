open Utils.JsInterop;

open Types;

registerServiceWorker();

require("./index.css");

let renderForRoute = route =>
  ReactDOMRe.renderToElementWithId(<AppView route />, "root");

let router =
  DirectorRe.makeRouter({
    "/": () => renderForRoute(Routing.Home),
    "/meditation": () => renderForRoute(Routing.Meditation),
    "/settings": () => renderForRoute(Routing.Setting(Time)),
    "/settings/:setting": setting =>
      renderForRoute(Routing.Setting(Settings.fromStringToType(setting)))
  });

DirectorRe.init(router, "/");
open Utils;

registerServiceWorker();

require("./index.css");

let renderForRoute = route =>
  ReactDOMRe.renderToElementWithId(<App route />, "root");

let router =
  DirectorRe.makeRouter({
    "/": () => renderForRoute(Routing.Home),
    "/meditation": () => renderForRoute(Routing.Meditation),
    "/settings": () => renderForRoute(Routing.Settings)
  });

DirectorRe.init(router, "/");
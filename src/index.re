open Utils;
registerServiceWorker();
requireCSS("./index.css");

let renderForRoute = (route) =>
  ReactDOMRe.renderToElementWithId(<App route />, "root");

let router =
  DirectorRe.makeRouter({
    "/": () => renderForRoute(Routing.Home),
    "/settings": () => renderForRoute(Routing.Settings)
  });

DirectorRe.init(router, "/");

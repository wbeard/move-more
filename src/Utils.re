[@bs.val] external require : string => unit = "require";

[@bs.val] external requireAudio : string => string = "require";

[@bs.module]
external registerServiceWorker : unit => unit = "./registerServiceWorker";

[@bs.new] external createDate : unit => Js.Date.t = "Date";

[@bs.val] external unsafeJsonParse : string => 'a = "JSON.parse";

let valueFromEvent = evt : string => (
                                       evt
                                       |> ReactEventRe.Form.target
                                       |> ReactDOMRe.domElementToObj
                                     )##value;

let str = ReasonReact.stringToElement;

let namespace = "move-more-settings";

let saveLocally = settings =>
  Dom.Storage.(
    localStorage |> setItem(namespace, Js.Json.stringify(settings))
  );

let getSettings = () =>
  switch Dom.Storage.(localStorage |> getItem(namespace)) {
  | None => {"duration": 10, "time": "07:00"}
  | Some(settings) => unsafeJsonParse(settings)
  };
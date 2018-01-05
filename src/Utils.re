[@bs.val] external requireCSS : string => unit = "require";

[@bs.module] external registerServiceWorker : unit => unit = "./registerServiceWorker";

[@bs.new] external createDate : unit => Js.Date.t = "Date";

let namespace = "move-more-settings";

[@bs.val] external unsafeJsonParse : string => 'a = "JSON.parse";

let valueFromEvent = (evt) : string => (
  evt
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;

let str = ReasonReact.stringToElement;
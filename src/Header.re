open Utils.JsInterop;

open Utils.ReactUtils;

require("./header.css");

let component = ReasonReact.statelessComponent("Header");

let make = (_) => {
  ...component,
  render: (_) =>
    <div className="Header">
      <div className="Logo">
        <a className="Navigation-button" href="#/"> ("MoveMore" |> str) </a>
      </div>
      <div className="Navigation">
        <a className="Navigation-button" href="#/settings">
          ("Settings" |> str)
        </a>
      </div>
    </div>
};
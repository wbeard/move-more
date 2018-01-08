open Utils.JsInterop;

open Utils.ReactUtils;

open Utils.TimeUtils;

require("./summary.css");

let component = ReasonReact.statelessComponent("Summary");

let make = (~duration, ~time, _children) => {
  ...component,
  render: (_) =>
    <div className="Summary">
      (str("You will meditate at "))
      <a className="Summary-link" href="#/settings/time">
        (time |> twentyFourClockToTwelveClock |> str)
      </a>
      (str(" for "))
      <a className="Summary-link" href="#/settings/duration">
        (duration |> string_of_int |> str)
      </a>
      (str(" minutes."))
    </div>
};
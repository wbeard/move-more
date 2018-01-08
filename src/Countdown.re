open Utils.JsInterop;

open Utils.ReactUtils;

open Utils.TimeUtils;

require("./countdown.css");

let component = ReasonReact.statelessComponent("Coundown");

let make = (~duration, ~time, ~until, ~units, _children) => {
  ...component,
  render: (_) =>
    <div className="Countdown">
      <div className="Row">
        <p className="Count">
          (until |> int_of_float |> string_of_int |> str)
        </p>
      </div>
      <div className="Row">
        <p className="Description">
          (
            units
            ++ " until your "
            ++ (duration |> string_of_int)
            ++ " minute meditation session at "
            ++ (time |> twentyFourClockToTwelveClock)
            |> str
          )
        </p>
      </div>
    </div>
};
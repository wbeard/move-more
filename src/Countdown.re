open Utils.JsInterop;

open Utils.ReactUtils;

require("./countdown.css");

let component = ReasonReact.statelessComponent("Coundown");

let make = (~duration, ~until, ~units, _children) => {
  ...component,
  render: (_) =>
    <div className="Countdown">
      <div className="Row">
        <p className="Count"> (str(string_of_int(int_of_float(until)))) </p>
      </div>
      <div className="Row">
        <p className="Description">
          (
            str(
              units
              ++ " until your "
              ++ string_of_int(duration)
              ++ " minute meditation session."
            )
          )
        </p>
      </div>
    </div>
};
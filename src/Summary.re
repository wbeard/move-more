open Utils.JsInterop;

open Utils.ReactUtils;

open Utils.TimeUtils;

require("./summary.css");

let component = ReasonReact.statelessComponent("Summary");

let make = (~duration, ~time, _children) => {
  ...component,
  render: (_) =>
    <div className="Summary">
      (
        str(
          "You will meditate at "
          ++ (time |> twentyFourClockToTwelveClock)
          ++ " "
        )
      )
      (str("for " ++ string_of_int(duration) ++ " minutes."))
    </div>
};
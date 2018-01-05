open Utils;

requireCSS("./summary.css");

let component = ReasonReact.statelessComponent("Summary");
let make = (~duration, ~location, ~time, _children) => {
  ...component,
  render: (_) => {
    <div className="Summary">
      (str("You will meditate at " ++ time ++ " "))
      (str("for " ++ string_of_int(duration) ++ " minutes "))
      (str("in " ++ location))
    </div>
  }
}
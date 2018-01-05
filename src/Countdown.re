open Utils;

requireCSS("./countdown.css");

let component = ReasonReact.statelessComponent("Coundown");

let make = (~duration, ~location, ~until, ~units, _children) => {
  ...component,
  render: (_) =>
    <div className="Countdown">
      <p className="Count"> (str(string_of_int(int_of_float(until)))) </p>
      <p className="Description">
        (
          str(
            units
            ++ " until your "
            ++ duration
            ++ " minute meditation session in "
            ++ location
            ++ "."
          )
        )
      </p>
    </div>
};
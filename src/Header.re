open Utils;

requireCSS("./header.css");

let component = ReasonReact.statelessComponent("Header");
let make = (_) => {
  ...component,
  render: (_) => {
    <div className="Header">
      <div className="Logo">(str("MoveMore"))</div>
    </div>
  }
}
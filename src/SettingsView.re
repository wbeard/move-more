open Utils;

open Utils.DomUtils;

open Utils.ReactUtils;

open Utils.JsInterop;

open Json.Encode;

open Types;

require("./settings.css");

require("./setting.css");

type action =
  | ShowSummary
  | UpdateDuration(int)
  | UpdateTime(string);

type state = {
  duration: int,
  showSummary: bool,
  time: string
};

let component = ReasonReact.reducerComponent("SettingsView");

let make = (~duration, ~setting, ~time, _) => {
  ...component,
  initialState: () => {duration, showSummary: false, time},
  reducer: (action, state) =>
    switch action {
    | ShowSummary => ReasonReact.Update({...state, showSummary: true})
    | UpdateDuration(value) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, duration: value},
        (
          ({state}) =>
            PersistenceUtils.save(
              object_([
                ("duration", value |> int),
                ("time", state.time |> string)
              ])
            )
        )
      )
    | UpdateTime(value) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, time: value},
        (
          ({state}) =>
            PersistenceUtils.save(
              object_([
                ("duration", state.duration |> int),
                ("time", value |> string)
              ])
            )
        )
      )
    },
  render: ({state, reduce}) =>
    <div className="Settings">
      (
        state.showSummary ?
          <Summary duration=state.duration time=state.time /> :
          ReasonReact.nullElement
      )
      (
        switch setting {
        | Settings.Time =>
          <div className="Setting">
            <div className="Row">
              <label className="Label" htmlFor="meditation-time">
                (str("What time do you want to meditate?"))
              </label>
            </div>
            <div className="Row">
              <input
                className="Input"
                id="meditation-time"
                _type="time"
                value=state.time
                onChange=(reduce(evt => UpdateTime(valueFromEvent(evt))))
              />
            </div>
            <div className="Row">
              <a
                className="Button"
                onClick=(reduce((_) => ShowSummary))
                href="#/settings/duration">
                (str("Set time"))
              </a>
            </div>
          </div>
        | Settings.Duration =>
          <div className="Setting">
            <div className="Row">
              <label className="Label" htmlFor="meditation-duration">
                (str("How long do you want to meditate?"))
              </label>
            </div>
            <div className="Row">
              <input
                className="Input"
                id="meditation-duration"
                _type="number"
                value=(string_of_int(state.duration))
                step=1.0
                onChange=(
                  reduce(evt =>
                    UpdateDuration(int_of_string(valueFromEvent(evt)))
                  )
                )
              />
            </div>
            <div className="Row">
              <a className="Button" href="#/"> (str("Set duration")) </a>
            </div>
          </div>
        }
      )
    </div>
};
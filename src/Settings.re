open Utils;

open Json.Encode;

require("./settings.css");

require("./setting.css");

type settings =
  | Time
  | Duration;

type action =
  | SetActiveSetting(settings)
  | UpdateDuration(int)
  | UpdateTime(string);

type state = {
  activeSetting: settings,
  duration: int,
  showSummary: bool,
  time: string
};

let component = ReasonReact.reducerComponent("Settings");

let make = (~duration, ~time, _) => {
  ...component,
  initialState: () => {activeSetting: Time, duration, showSummary: false, time},
  reducer: (action, state) =>
    switch action {
    | SetActiveSetting(value) =>
      ReasonReact.Update({...state, activeSetting: value, showSummary: true})
    | UpdateDuration(value) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, duration: value},
        (
          ({state}) =>
            saveLocally(
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
            saveLocally(
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
        switch state.activeSetting {
        | Time =>
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
              <button
                className="Button"
                onClick=(reduce((_) => SetActiveSetting(Duration)))>
                (str("Set time"))
              </button>
            </div>
          </div>
        | Duration =>
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
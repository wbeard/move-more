open Utils;

open Utils.DomUtils;

open Utils.ReactUtils;

open Utils.JsInterop;

open Json.Encode;

open Utils.TimeUtils;

open Types;

require("./settings.css");

require("./setting.css");

type action =
  | Calendared
  | UpdateDuration(int)
  | UpdateTime(string);

type state = {
  calendared: bool,
  duration: int,
  time: string
};

let component = ReasonReact.reducerComponent("SettingsView");

let make = (~duration, ~setting, ~calendared, ~time, _) => {
  ...component,
  initialState: () => {duration, time, calendared},
  reducer: (action, state) =>
    switch action {
    | Calendared =>
      ReasonReact.UpdateWithSideEffects(
        {...state, calendared: true},
        (
          ({state}) =>
            PersistenceUtils.save(
              object_([
                ("duration", state.duration |> int),
                ("time", state.time |> string),
                ("calendared", true |> bool)
              ])
            )
        )
      )
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
      <Summary duration=state.duration time=state.time />
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
              <a className="Button" href="#/settings/duration">
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
              (
                state.calendared ?
                  <a className="Button" href="#/"> (str("Set duration")) </a> :
                  <a className="Button" href="#/settings/calendar">
                    (str("Set duration"))
                  </a>
              )
            </div>
          </div>
        | Settings.Calendar =>
          let nextMeditation =
            DateFns.addDays(1.0, resolveDateFromTime(time, createDate()))
            |> Js.Date.toISOString;
          <div className="Setting">
            <div className="Row">
              <label className="Label" htmlFor="meditation-duration">
                (str("Add your meditations to your Google calendar."))
              </label>
            </div>
            <div className="Row">
              <a
                onClick=(reduce((_) => Calendared))
                className="Button"
                href=(
                  "https://www.google.com/calendar/render?action=TEMPLATE&text=Meditate&dates="
                  ++ nextMeditation
                  ++ "/"
                  ++ nextMeditation
                  ++ "&details=Meditation+scheduled+with+MoveMore,+link+here:+http://www.example.com&location=Your+favorite+place+to+sit&sf=true&output=xml+trp=true"
                )
                target="_blank"
                rel="nofollow">
                (str("Add to Google calendar"))
              </a>
              <a className="Button" href="#/"> (str("Skip")) </a>
            </div>
          </div>;
        | Settings.GoHome =>
          <div className="Setting">
            <div className="Row">
              <a className="Button" href="#/"> (str("Go home")) </a>
            </div>
          </div>
        }
      )
    </div>
};
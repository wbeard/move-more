open Utils.JsInterop;

open Utils.ReactUtils;

open Utils.TimeUtils;

require("./meditation.css");

require("./setting.css");

let audio = requireAudio("./resources/ocean.mp3");

type state = {
  muted: bool,
  endTime: Js.Date.t,
  finished: bool,
  time: int,
  timerId: ref(option(Js.Global.intervalId))
};

type action =
  | Mute
  | Unmute
  | Tick;

let interval = 1000;

let component = ReasonReact.reducerComponent("MeditationView");

let make = (~duration, _children) => {
  ...component,
  initialState: () => {
    let now = createDate();
    {
      muted: false,
      endTime: DateFns.addMinutes(float_of_int(duration), now),
      time: 0,
      timerId: ref(None),
      finished: false
    };
  },
  reducer: (action, state) =>
    switch action {
    | Mute => ReasonReact.Update({...state, muted: true})
    | Unmute => ReasonReact.Update({...state, muted: false})
    | Tick =>
      let newTime = state.time + interval;
      let finished = state.time >= duration * 60 * 1000;
      ReasonReact.Update({...state, time: newTime, finished});
    },
  didMount: self => {
    self.state.timerId :=
      Some(Js.Global.setInterval(self.reduce((_) => Tick), interval));
    ReasonReact.NoUpdate;
  },
  render: ({state, reduce}) => {
    let now = createDate();
    let yes = Js.Boolean.to_js_boolean(true);
    <div className="Meditation">
      <div className="Row">
        <p className="Meditation-text">
          (str(countdownClock(state.endTime, now)))
        </p>
      </div>
      (
        state.finished ?
          <div className="Row">
            <a className="Button" href="#/"> (str("Go home")) </a>
          </div> :
          <div className="Row">
            <a
              className="Button Button-meditation"
              onClick=(reduce((_) => state.muted ? Unmute : Mute))>
              (state.muted ? str("Unmute") : str("Mute"))
            </a>
            <a className="Button Button-meditation" href="#/">
              ("Stop" |> str)
            </a>
          </div>
      )
      <audio
        muted=(Js.Boolean.to_js_boolean(state.muted))
        key="loop"
        loop=yes
        autoPlay=yes
        src=audio
      />
    </div>;
  }
};
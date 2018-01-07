open Utils.JsInterop;

open Utils.ReactUtils;

require("./meditation.css");

let audio = requireAudio("./resources/ocean.mp3");

type state = {
  finished: bool,
  time: int,
  timerId: ref(option(Js.Global.intervalId))
};

type action =
  | Tick;

let interval = 1000;

let component = ReasonReact.reducerComponent("MeditationView");

let make = (~duration, _children) => {
  ...component,
  initialState: () => {time: 0, timerId: ref(None), finished: false},
  reducer: (action, state) =>
    switch action {
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
  render: ({state}) => {
    let yes = Js.Boolean.to_js_boolean(true);
    <div className="Meditation">
      <p className="Meditation-text"> (str("Welcome to your meditation")) </p>
      (
        switch state.finished {
        | false => <audio key="loop" loop=yes autoPlay=yes src=audio />
        | true => <a className="Button" href="#/"> (str("Go home")) </a>
        }
      )
    </div>;
  }
};
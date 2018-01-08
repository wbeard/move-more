open Utils.JsInterop;

open Utils.ReactUtils;

open Utils.TimeUtils;

require("./home.css");

type countdown = {
  until: float,
  units: string,
  showStartButton: bool
};

let calculateUntil = time => {
  let currentDate = createDate();
  let nextDate = resolveDateFromTime(time, currentDate);
  if (DateFns.differenceInHours(nextDate, currentDate) != 0.0) {
    {
      until: DateFns.differenceInHours(nextDate, currentDate),
      units: "hours",
      showStartButton: false
    };
  } else if (DateFns.differenceInMinutes(nextDate, currentDate) != 0.0) {
    {
      until: DateFns.differenceInMinutes(nextDate, currentDate),
      units: "minutes",
      showStartButton: false
    };
  } else {
    let showStartButton =
      DateFns.differenceInSeconds(nextDate, currentDate) <= 60.0;
    {
      until: DateFns.differenceInSeconds(nextDate, currentDate),
      units: "seconds",
      showStartButton
    };
  };
};

type action =
  | Tick;

type state = {
  until: float,
  units: string,
  showStartButton: bool,
  timerId: ref(option(Js.Global.intervalId))
};

let component = ReasonReact.reducerComponent("HomeView");

let make = (~duration, ~time, _children) => {
  ...component,
  reducer: (action, state) =>
    switch action {
    | Tick =>
      let result = time |> calculateUntil;
      ReasonReact.Update({
        ...state,
        until: result.until,
        units: result.units,
        showStartButton: result.showStartButton
      });
    },
  initialState: () => {
    let result = time |> calculateUntil;
    {
      showStartButton: result.showStartButton,
      timerId: ref(None),
      units: result.units,
      until: result.until
    };
  },
  didMount: self => {
    self.state.timerId :=
      Some(Js.Global.setInterval(self.reduce((_) => Tick), 1000));
    ReasonReact.NoUpdate;
  },
  render: ({state}) =>
    <div className="Home">
      <Countdown time until=state.until units=state.units duration />
      (
        state.showStartButton ?
          <div className="Row">
            <a className="Button" href="#/meditation">
              ("Begin Meditation" |> str)
            </a>
          </div> :
          ReasonReact.nullElement
      )
    </div>
};
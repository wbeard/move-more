open Utils;

require("./home.css");

let resolveDateFromTime = (time, date) => {
  let currentHour = DateFns.getHours(date);
  let currentMinute = DateFns.getMinutes(date);
  let appointmentHour = float_of_string(Js.String.split(":", time)[0]);
  let appointmentMinute = float_of_string(Js.String.split(":", time)[1]);
  let beginningDate =
    if (appointmentHour > currentHour) {
      date;
    } else if (appointmentHour < currentHour) {
      DateFns.addDays(1.0, date);
    } else if (appointmentMinute > currentMinute) {
      date;
    } else {
      DateFns.addDays(1.0, date);
    };
  beginningDate
  |> DateFns.setHours(appointmentHour)
  |> DateFns.setMinutes(appointmentMinute)
  |> DateFns.setSeconds(0.0);
};

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

let component = ReasonReact.reducerComponent("Home");

let make = (~duration, ~time, _children) => {
  ...component,
  reducer: (action, state) =>
    switch action {
    | Tick =>
      let result = calculateUntil(time);
      ReasonReact.Update({
        ...state,
        until: result.until,
        units: result.units,
        showStartButton: result.showStartButton
      });
    },
  initialState: () => {
    let result = calculateUntil(time);
    {
      until: result.until,
      timerId: ref(None),
      units: result.units,
      showStartButton: result.showStartButton
    };
  },
  didMount: self => {
    self.state.timerId :=
      Some(Js.Global.setInterval(self.reduce((_) => Tick), 1000));
    ReasonReact.NoUpdate;
  },
  render: ({state}) =>
    <div className="Home">
      <Countdown until=state.until units=state.units duration />
      (
        if (state.showStartButton === true) {
          <div className="Row">
            <a className="Button" href="#/meditation">
              (str("Begin Meditation"))
            </a>
          </div>;
        } else {
          ReasonReact.nullElement;
        }
      )
    </div>
};
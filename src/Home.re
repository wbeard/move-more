open Utils;

requireCSS("./home.css");

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
let calculateUntil = time => {
  let currentDate = createDate();
  let nextDate = resolveDateFromTime(time, currentDate);
  DateFns.differenceInHours(nextDate, currentDate);
};

type action =
  | Tick;

type state = {
  until: float,
  units: string,
  timerId: ref(option(Js.Global.intervalId))
};

let component = ReasonReact.reducerComponent("Home");

let make =
    (~duration="15", ~location="the living room", ~time="06:30", _children) => {
  ...component,
  reducer: (action, state) =>
    switch action {
    | Tick => ReasonReact.Update({...state, until: calculateUntil(time)})
    },
  initialState: () => {until: calculateUntil(time), timerId: ref(None), units: "hours"},
  didMount: self => {
    self.state.timerId :=
      Some(Js.Global.setInterval(self.reduce((_) => Tick), 60000));
    ReasonReact.NoUpdate;
  },
  render: ({state}) =>
    <div className="Home">
      {
        switch state.until {
        | 0.0 => <div />
        | _ => <Countdown until={state.until} units={state.units} duration={duration} location={location} />
        }
      }
    </div>
};
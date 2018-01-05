open Utils;

requireCSS("./home.css");

let calculateUntil = (time) => {
  let currentDate = createDate();
  let currentHour = DateFns.getHours(currentDate);
  let currentMinute = DateFns.getMinutes(currentDate);
  let appointmentHour = float_of_string(Js.String.split(":", time)[0]);
  let appointmentMinute = float_of_string(Js.String.split(":", time)[1]);
  let beginningDate = if (appointmentHour > currentHour) {
    currentDate
  } else if (appointmentHour < currentHour ) {
    DateFns.addDays(1.0, currentDate);
  } else {
    if (appointmentMinute > currentMinute) {
      currentDate
    } else {
    DateFns.addDays(1.0, currentDate);
      
    }
  };
  let nextDate = beginningDate |> DateFns.setHours(appointmentHour) |> DateFns.setMinutes(appointmentMinute);
  
  DateFns.differenceInHours(nextDate, currentDate);
};
type action = 
  | Tick;
type state = {
  until: float,
  timerId: ref(option(Js.Global.intervalId))
};
let component = ReasonReact.reducerComponent("Home");
let make = (~duration="15", ~location="the living room", ~time="06:30", _children) => {
  ...component,
  reducer: (action, state) =>
    switch action {
    | Tick => {
      ReasonReact.Update({
        ...state, 
        until: calculateUntil(time)
      })
    }
    },
  initialState: () => {
    until: calculateUntil(time),
    timerId: ref(None)
  },
  didMount: (self) => {
    self.state.timerId := Some(
      Js.Global.setInterval(
        self.reduce((_) => Tick), 60000
      )
    );
    ReasonReact.NoUpdate
  },
  render: ({state}) => 
    <div className="Home">
      <p className="Countdown">(str(string_of_int(int_of_float(state.until))))</p>
      <p className="Description">(str("hours until your " ++ duration ++ " minute meditation session in " ++ location ++ "."))</p>
    </div>
}
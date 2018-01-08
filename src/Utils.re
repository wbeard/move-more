module JsInterop = {
  [@bs.val] external require : string => unit = "require";
  [@bs.val] external requireAudio : string => string = "require";
  [@bs.module]
  external registerServiceWorker : unit => unit = "./registerServiceWorker";
  [@bs.new] external createDate : unit => Js.Date.t = "Date";
  [@bs.val] external unsafeJsonParse : string => 'a = "JSON.parse";
};

module DomUtils = {
  let valueFromEvent = evt : string => (
                                         evt
                                         |> ReactEventRe.Form.target
                                         |> ReactDOMRe.domElementToObj
                                       )##value;
};

module ReactUtils = {
  let str = ReasonReact.stringToElement;
};

module PersistenceUtils = {
  let namespace = "move-more-settings";
  let get = () =>
    switch Dom.Storage.(localStorage |> getItem(namespace)) {
    | None => {"duration": 10, "time": "07:00"}
    | Some(settings) => JsInterop.unsafeJsonParse(settings)
    };
  let save = settings =>
    Dom.Storage.(
      localStorage |> setItem(namespace, Js.Json.stringify(settings))
    );
};

module TimeUtils = {
  let secondsToHours = seconds => seconds / 60 / 60;
  let hoursToSeconds = hours => hours * 60 * 60;
  let secondsToMinutes = seconds => seconds / 60;
  let minutesToSeconds = seconds => seconds * 60;
  let resolveDateFromTime = (time, date) => {
    let currentHour = DateFns.getHours(date);
    let currentMinute = DateFns.getMinutes(date);
    let appointmentHour = Js.String.split(":", time)[0] |> float_of_string;
    let appointmentMinute = Js.String.split(":", time)[1] |> float_of_string;
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
  let countdownClock = (from, to_) => {
    let seconds = to_ |> DateFns.differenceInSeconds(from) |> int_of_float;
    let hours = seconds |> secondsToHours;
    let remaining = hours > 0 ? seconds - hours |> hoursToSeconds : seconds;
    let minutes = remaining |> secondsToMinutes;
    let remainingSeconds =
      minutes > 0 ? remaining - (minutes |> minutesToSeconds) : seconds;
    hours != 0 ?
      (hours |> string_of_int) ++ ":" :
      ""
      ++ (minutes |> string_of_int)
      ++ ":"
      ++ (remainingSeconds == 0 ? "00" : string_of_int(remainingSeconds));
  };
  let twentyFourClockToTwelveClock = time => {
    let hour = Js.String.split(":", time)[0];
    let minute = Js.String.split(":", time)[1];
    let intHour = hour |> int_of_string;
    if (intHour - 12 > 0) {
      string_of_int(intHour - 12) ++ ":" ++ minute ++ " PM";
    } else {
      hour ++ ":" ++ minute ++ " AM";
    };
  };
};
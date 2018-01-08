module Settings = {
  type t =
    | Calendar
    | GoHome
    | Time
    | Duration;
  let fromStringToType = str =>
    switch str {
    | "time" => Time
    | "duration" => Duration
    | "calendar" => Calendar
    | _ => Time
    };
};

module Routing = {
  type t =
    | Home
    | Meditation
    | Setting(Settings.t);
};
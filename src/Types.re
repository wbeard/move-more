module Settings = {
  type t =
    | Time
    | Duration;
  let fromStringToType = str =>
    switch str {
    | "time" => Time
    | "duration" => Duration
    | _ => Time
    };
};

module Routing = {
  type t =
    | Home
    | Meditation
    | Setting(Settings.t);
};
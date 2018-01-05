open Utils;

requireCSS("./settings.css");
requireCSS("./setting.css");

let saveLocally = (settings) =>
  switch (Js.Json.stringifyAny(settings)) {
  | None => ()
  | Some(stringifiedSettings) => Dom.Storage.(localStorage |> setItem(namespace, stringifiedSettings))
  };

type settings = 
  | Time
  | Duration
  | Location
  | Finish;

type action = 
  | SetActiveSetting(settings)
  | UpdateDuration(int)
  | UpdateLocation(string)
  | UpdateTime(string);

type state = {
  activeSetting: settings,
  duration: int,
  location: string,
  showSummary: bool,
  time: string
};

let component = ReasonReact.reducerComponent("Settings");

let make = (_) => {
  ...component,
  initialState: () => {
    activeSetting: Time,
    duration: 15,
    location: "the living room",
    showSummary: false,
    time: "06:00"
  },
  reducer: (action, state) => 
    switch action {
    | SetActiveSetting(value) => ReasonReact.Update({ ...state, activeSetting: value, showSummary: true })
    | UpdateLocation(value) => ReasonReact.Update({ ...state, location: value }) 
    | UpdateDuration(value) => ReasonReact.Update({ ...state, duration: value })
    | UpdateTime(value) => ReasonReact.Update({ ...state, time: value })
    },
  render: ({ state, reduce }) => {
    <div className="Settings">
      {
        switch state.showSummary {
        | true => <Summary
                    duration={state.duration} 
                    location={state.location} 
                    time={state.time}
                  />
        | false => ReasonReact.nullElement
        }
      }
      {
        switch state.activeSetting {
        | Time =>
          <div className="Setting">
            <label className="Label" htmlFor="meditation-time">
              (str("What time do you want to meditate?"))
            </label>
            <input 
              className="Input" 
              id="meditation-time" 
              _type="time" 
              value={ state.time }
              onChange=(reduce((evt) => UpdateTime(valueFromEvent(evt))))
            />
            <button 
              className="Button" 
              onClick=(reduce(
                (_) => {
                  SetActiveSetting(Duration);
                }
              ))>
                (str("Set time"))
            </button>
          </div>
        | Duration => 
          <div className="Setting">
            <label className="Label" htmlFor="meditation-duration">
              (str("How long do you want to meditate?"))
            </label>
            <input 
              className="Input" 
              id="meditation-duration" 
              _type="number"
              value={ string_of_int(state.duration) }                
              step={1.0}
              onChange=(reduce((evt) => UpdateDuration(int_of_string(valueFromEvent(evt)))))
            />
            <button 
              className="Button" 
              onClick=(reduce(
                (_) => SetActiveSetting(Location)
              ))>
                (str("Set duration"))
            </button>
          </div>
        | Location => 
          <div className="Setting">
            <label className="Label" htmlFor="meditation-location">
              (str("Where will you meditate?"))
            </label>
            <input 
              className="Input" 
              id="meditation-location" 
              value={ state.location }
              onChange=(reduce((evt) => UpdateLocation(valueFromEvent(evt))))           
            />
            <button 
              className="Button" 
              onClick=(reduce(
                (_) => SetActiveSetting(Finish)
              ))>
                (str("Set location"))
            </button>
          </div>
        | Finish => ReasonReact.nullElement
        }
      }
    </div>
  }
};

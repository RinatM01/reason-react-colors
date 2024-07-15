[@mel.module "rc-slider"] [@react.component]
external make:
  (
    ~defaultValue: int=?,
    ~min: int=?,
    ~max: int=?,
    ~step: int=?,
    ~onChangeComplete: int => unit=?,
    ~trackStyle: Js.Json.t=?,
    ~railStyle: Js.Json.t=?,
    ~handleStyle: Js.Json.t=?
  ) =>
  React.element =
  "default";

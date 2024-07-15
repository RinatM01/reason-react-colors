module Select = {
  [@mel.module "@mui/material/Select"] [@react.component]
  external make:
    (
      ~value: 'a=?,
      ~onChange: React.Event.Selection.t => unit=?,
      ~label: string=?,
      ~labelId: string=?,
      ~id: string=?,
      ~children: React.element=?,
      ~defaultValue: 'a=?,
      ~className: string=?,
      ~variant: string=?
    ) =>
    React.element =
    "default";
};

module FormControl = {
  [@mel.module "@mui/material/FormControl"] [@react.component]
  external make:
    (~variant: string=?, ~fullWidth: bool=?, ~children: React.element=?) =>
    React.element =
    "default";
};

module MenuItem = {
  [@mel.module "@mui/material/MenuItem"] [@react.component]
  external make: (~value: 'a=?, ~children: React.element=?) => React.element =
    "default";
};

module InputLabel = {
  [@mel.module "@mui/material/InputLabel"] [@react.component]
  external make: (~id: string=?, ~children: React.element=?) => React.element =
    "default";
};

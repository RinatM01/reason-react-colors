[%%mel.raw {|import "rc-slider/assets/index.css"|}];
module Style = {
  let navbar = [%cx
    {|
        height: 6vh;
        display: flex;
        justify-content: flex-start;
        align-items: center;
    |}
  ];
  let logo = [%cx
    {
      {|
    margin-right: 15px;
	padding: 0 13px;
	font-size: 22px;
	background-color: #eceff1;
	height: 100%;
	display: flex;
	align-items: center;
    & a {
        text-decoration: none;
	    color: black;
    }
  |};
    }
  ];
  let sliderContainer = [%cx
    {|
    margin-right: 1rem;
	margin-left: 1rem;
  |}
  ];
  let slider = [%cx
    {|
    width: 340px;
    margin: 0 10px;
    display: inline-block;
  |}
  ];
  let selectContainer = [%cx {|

  |}];
  //open ReactDOM.Style;
  let track =
    CssJs.toJson([|[%css {|
    background-color: transparent;
  |}]|]);
  //let rail = make(~height="8px", ());
  let rail = CssJs.toJson([|[%css {|
    height: 8px;
  |}]|]);
  let handle =
    CssJs.toJson([|
      [%css {| background-color: green; |}],
      [%css {| outline: none; |}],
      [%css {| border: 2px solid green;|}],
      [%css {| box-shadow: none;|}],
      [%css {| width: 13px;|}],
      [%css {| height: 13px;|}],
      [%css {| margin-left: -7px;|}],
      [%css {| margin-top: -3px;|}],
    |]);
};

[@react.component]
let make = (~lightLevel, ~setLightLevel, ~format, ~setFormat) => {
  <nav className=Style.navbar>
    <div className=Style.logo>
      <a href="#"> {"reasoncolorpicker" |> RR.s} </a>
    </div>
    <div className=Style.sliderContainer>
      <span> {RR.s("Level: " ++ string_of_int(lightLevel))} </span>
      <div className=Style.slider>
        <RcSlider
          defaultValue=lightLevel
          min=100
          max=900
          step=100
          onChangeComplete={newLevel => setLightLevel(_ => newLevel)}
          trackStyle=Style.track
          railStyle=Style.rail
          handleStyle=Style.handle
        />
      </div>
    </div>
    <div className=Style.selectContainer>
      <MUI.Select
        labelId="color-format-label"
        id="color-format"
        value=format
        variant="standard"
        onChange={evt => {
          let value = React.Event.Selection.target(evt)##value;
          setFormat(_ => value);
        }}
        label="Format">
        <MUI.MenuItem value=ColorUtility.HexFormat>
          {RR.s("Hex")}
        </MUI.MenuItem>
        <MUI.MenuItem value=ColorUtility.RgbFormat>
          {RR.s("Rgb")}
        </MUI.MenuItem>
        <MUI.MenuItem value=ColorUtility.RgbaFormat>
          {RR.s("Rgba")}
        </MUI.MenuItem>
      </MUI.Select>
    </div>
  </nav>;
};

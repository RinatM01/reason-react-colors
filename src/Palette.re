module Style = {
  let palette = [%cx {|
    height: 100vh;
    overflow: hidden;
  |}];

  let paletteColors = [%cx {|
    height: 90%;
  |}];
};

[@react.component]
let make = (~palette: ColorUtility.extendedPalette) => {
  let (lightLevel, setLightLevel) = React.useState(_ => 400);
  let (format, setFormat) = React.useState(_ => ColorUtility.HexFormat);

  let currColors =
    palette.colors |> Array.map(colorArrays => colorArrays[lightLevel / 100]);

  //Js.log(currColors[0].rgba |> ColorUtility.toRgba);
  <div className=Style.palette>
    <Navbar lightLevel setLightLevel format setFormat />
    <div className=Style.paletteColors>
      {currColors
       |> Array.map((color: ColorUtility.exntededColor) => {
            let code = ColorUtility.getCorrectFormat(color, format);
            switch (code) {
            | None => React.null
            | Some(code) =>
              <ColorBox key={color.name} code name={color.name} />
            };
          })
       |> React.array}
    </div>
  </div>;
};

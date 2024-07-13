module Style = {
  let palette = [%cx {|
    height: 100vh;
    overflow: hidden;
  |}];

  let paletteColors = [%cx {|
    height: 90%;
  |}];
};

// module Color = {
//   type t = {
//     name: string,
//     [@mel.as "color"]
//     code: string,
//   };
// };

// type t = {
//   [@mel.as "paletteName"]
//   name: string,
//   id: string,
//   emoji: string,
//   colors: array(Color.t),
// };

[@react.component]
let make = (~palette: ColorUtility.pallete) => {
  let newPal = ColorUtility.generatePalettes(palette);
  Js.log(newPal);
  <div className=Style.palette>
    <div className=Style.paletteColors>
      {palette.colors
       |> Array.map((color: ColorUtility.color) =>
            <ColorBox key={color.code} code={color.code} name={color.name} />
          )
       |> React.array}
    </div>
  </div>;
};

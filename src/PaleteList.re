[@mel.module "./seededColors.js"]
external seedPalettes: array(ColorUtility.pallete) = "default";

[@react.component]
let make = () => {
  //Js.log(seedPalettes[0]);
  let material = ColorUtility.generatePalettes(seedPalettes[0]);
  <Palette palette=material />;
};

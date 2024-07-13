[@mel.module "./seededColors.js"]
external seedPalettes: array(ColorUtility.pallete) = "default";

[@react.component]
let make = () => {
  //Js.log(seedPalettes[0]);
  let material = seedPalettes[3];
  <Palette palette=material />;
};

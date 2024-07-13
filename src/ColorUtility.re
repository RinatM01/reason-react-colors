// [@mel.module "chroma-js"]
// external
module Chroma = {
  type t;
  type scale;
  type mode;
  [@mel.module "chroma-js"] [@mel.new]
  external chroma: string => t = "default";
  [@mel.send.pipe: t] external darken: float => t = "darken";
  [@mel.send] external hex: t => string = "hex";
  [@mel.send] external css: t => string = "css";
  [@mel.module "chroma-js"] external scale: array(string) => scale = "scale";
  [@mel.send.pipe: scale] external mode: string => mode = "mode";
  [@mel.send.pipe: mode] external colors: int => array(string) = "colors";
};

open Chroma;
//let levels = [|50, 100, 200, 300, 400, 500, 600, 700, 800, 900|];

type color = {
  name: string,
  [@mel.as "color"]
  code: string,
};

type pallete = {
  [@mel.as "paletteName"]
  name: string,
  id: string,
  emoji: string,
  colors: array(color),
};

type exntededColor = {
  name: string,
  id: string,
  hex: string,
  rgb: string,
  rgba: string,
};

type extendedPalette = {
  [@mel.as "paletteName"]
  name: string,
  id: string,
  emoji: string,
  colors: array(array(exntededColor)),
};

let getRange = hexColor => {
  let endColor = "#fff";
  [|hexColor |> chroma |> darken(1.4) |> hex, hexColor, endColor|];
};

let generateScale = (hexColor, numOfColors) => {
  hexColor |> getRange |> scale |> mode("lab") |> colors(numOfColors);
};
let generatePalettes = (pal: pallete) => {
  let starterPallete = {
    name: pal.name,
    id: pal.id,
    emoji: pal.emoji,
    colors:
      pal.colors
      |> Array.map((color: color) => {
           generateScale(color.code, 10)
           |> Js.Array.reverseInPlace
           |> Array.mapi((idx, scaledColor) => {
                let lvl = idx == 0 ? "50" : string_of_int(idx) ++ "00";
                {
                  name: Printf.sprintf("%s %s", color.name, lvl),
                  id:
                    color.name
                    |> String.lowercase_ascii
                    |> Js.String.replace(~search=" ", ~replacement="-"),
                  hex: scaledColor,
                  rgb: scaledColor |> chroma |> css,
                  rgba:
                    scaledColor
                    |> chroma
                    |> css
                    |> Js.String.replace(~search="rgb", ~replacement="rgba")
                    |> Js.String.replace(~search=")", ~replacement=",1.0)"),
                };
              })
         }),
  };
  starterPallete;
};

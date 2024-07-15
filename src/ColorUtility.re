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

type colorFormat =
  | HexFormat
  | RgbFormat
  | RgbaFormat;

type colorCode =
  | Hex(string)
  | Rgb(string, string, string)
  | Rgba(string, string, string, string);

[@deriving getSet]
type exntededColor = {
  name: string,
  id: string,
  hex: option(colorCode),
  rgb: option(colorCode),
  rgba: option(colorCode),
};

type extendedPalette = {
  [@mel.as "paletteName"]
  name: string,
  id: string,
  emoji: string,
  colors: array(array(exntededColor)),
};

let getCorrectFormat: (exntededColor, colorFormat) => option(colorCode) =
  (color, format) =>
    switch (format) {
    | HexFormat => color.hex
    | RgbFormat => color.rgb
    | RgbaFormat => color.rgba
    };

let toCss =
  fun
  | Hex(str) => Css.hex(str)
  | Rgb(red, green, blue) =>
    Css.rgb(int_of_string(red), int_of_string(green), int_of_string(blue))
  | Rgba(red, green, blue, alpha) =>
    Css.rgba(
      int_of_string(red),
      int_of_string(green),
      int_of_string(blue),
      `num(float_of_string(alpha)),
    );
let toString =
  fun
  | Hex(str) => Printf.sprintf("#%s", str)
  | Rgb(red, green, blue) =>
    Printf.sprintf("rgb(%s,%s,%s)", red, green, blue)
  | Rgba(red, green, blue, alpha) =>
    Printf.sprintf("rgba(%s,%s,%s,%s)", red, green, blue, alpha);

let toHex = s => {
  let arg = s |> Js.String.slice(~start=1);
  switch (arg) {
  | arg when String.length(arg) == 6 => Some(Hex(arg))
  | _ => None
  };
};
let toRgb = s => {
  let args =
    s
    |> chroma
    |> css
    |> Js.String.slice(~start=4)
    |> Js.String.slice(~end_=-1)
    |> Js.String.split(~sep=",");
  switch (args) {
  | [|red, green, blue|] => Some(Rgb(red, green, blue))
  | _ => None
  };
};

let toRgba = s => {
  let args =
    s
    |> chroma
    |> css
    |> Js.String.slice(~start=4)
    |> Js.String.slice(~end_=-1)
    |> Js.String.split(~sep=",");
  switch (args) {
  | [|red, green, blue|] => Some(Rgba(red, green, blue, "1.0"))
  | _ => None
  };
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
                  hex: scaledColor |> toHex,
                  rgb: scaledColor |> toRgb,
                  rgba: scaledColor |> toRgba,
                };
              })
         }),
  };
  starterPallete;
};

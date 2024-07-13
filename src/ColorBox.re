module Style = {
  let copyBtn = [%cx
    {|
    width: 100px;
    height: 30px;
    position: absolute;
    display: inline-block;
    top: 50%;
    left: 50%;
    margin-left: -50px;
    margin-top: -15px;
    text-align: center;
    outline: none;
    background: rgba(255,255,255,0.3);
    font-size: 1rem;
    line-height: 30px;
    color: white;
    border: none;
    opacity: 0;
    cursor: pointer;
  |}
  ];
  let colorBox = color => {
    let hexy = color |> Js.String.slice(~start=1) |> CssJs.hex;

    [%cx
     {j|
        background-color: $(hexy);
        width: 20%;
        height: 25%;
        display: inline-block;
        position: relative;
        cursor: pointer;
        vertical-align: top;
        &:hover .$(copyBtn) {
          opacity: 1;
          transition: 0.5s;
        }
    |j}];
  };
  let boxContent = [%cx
    {|
      position: absolute;
      width: auto;
      left: 0px;
      bottom: 0px;
      margin: 10px;
      color: black;
      letter-spacing: 1px;
      text-transform: uppercase;
      font-size: 12px;
  |}
  ];
  let seeMore = [%cx
    {|
    background-color: rgba(255,255,255,0.3);
    position: absolute;
    border: none;
    right: 0px;
    bottom: 0px;
    color: white;
    width: 60px;
    height: 30px;
    text-align: center;
    line-height: 30px;
  |}
  ];
  let copyOverlay = color => {
    let hexy = color |> Js.String.slice(~start=1) |> CssJs.hex;
    [%cx
     {j|
    background-color: $(hexy);
    opacity:0;
    z-index: 0;
    width: 100%;
    height: 100%;
    transition: transform 0.5s ease-in-out;
    transform: scale(0.1);
    /* &:hover {
      opacity: 1;
      transform: scale(50);
      z-index: 10;
      position: absolute;
    } */
  |j}];
  };
  let show = [%cx
    {|
      opacity: 1 !important;
      transform: scale(10) !important;
      z-index: 10 !important;
      position: absolute !important;
  |}
  ];
  let showCopyMsg = [%cx
    {|
      opacity: 1 !important;
      transform: scale(1) !important;
      z-index: 25 !important;
      transition: 0.4s ease-in-out !important;
  |}
  ];
  let copyMsg = [%cx
    {|
    position: fixed;
    top: 0;
    bottom: 0;
    left: 0;
    right: 0;
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: 4rem;
    flex-direction: column;
    opacity: 0;
    transform: scale(0.1);
    color: white;
    & h1 {
      font-weight: 400;
      text-shadow: 1px 2px 0px black;
      background: rgba(255,255,255, 0.2);
      width: 100%;
      text-align: center;
      margin-bottom: 0;
      padding: 1rem;
    }
    & p {
      font-weight: 100;
      font-size: 2rem;
    }
  |}
  ];
};

[@mel.module "./ColorBox.module.css"] external css: Js.t({..}) = "default";
[@react.component]
let make = (~code, ~name) => {
  let (copied, setCopied) = React.useState(_ => false);
  let toggleCopyState = () => {
    setCopied(_ => true);
    Js.Global.setTimeout(~f=_ => setCopied(_ => false), 800) |> ignore;
  };
  // let hexy = code |> ColorUtility.generateScale(_, 5);
  // Js.log(hexy);
  <CopyToClipBoard text=code onCopy=toggleCopyState>
    <div className={Style.colorBox(code)}>
      <div
        className={
          (copied ? Style.show : "") ++ " " ++ Style.copyOverlay(code)
        }
      />
      <div
        className={(copied ? Style.showCopyMsg : "") ++ " " ++ Style.copyMsg}>
        <h1> {RR.s("copied!")} </h1>
        <p> {RR.s(code)} </p>
      </div>
      <div>
        <div className=Style.boxContent> <span> {RR.s(name)} </span> </div>
        <button className=Style.copyBtn> {RR.s("COPY")} </button>
      </div>
      <span className=Style.seeMore> {RR.s("MORE")} </span>
    </div>
  </CopyToClipBoard>;
};

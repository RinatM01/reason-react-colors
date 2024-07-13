module App = {
  [@react.component]
  let make = () => <PaleteList />;
  //let make = () => <ColorBox code={color.code} name={color.name} />;
};

let node = ReactDOM.querySelector("#root");
switch (node) {
| None =>
  Js.Console.error("Failed to start React: couldn't find the #root element")
| Some(root) =>
  let root = ReactDOM.Client.createRoot(root);
  ReactDOM.Client.render(root, <App />);
};
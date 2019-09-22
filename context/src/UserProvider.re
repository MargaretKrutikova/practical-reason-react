// Create a provider component
let make = React.Context.provider(UserContext.context);

// Tell bucklescript how to translate props into JS
let makeProps = (~value, ~children, ()) => {
  "value": value,
  "children": children,
};

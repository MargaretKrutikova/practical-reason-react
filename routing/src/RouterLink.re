let shouldPreventDefault = e =>
  !ReactEvent.Mouse.metaKey(e) && !ReactEvent.Mouse.ctrlKey(e);

[@react.component]
let make = (~href, ~className=?, ~children) => {
  let handleClick = event =>
    if (!ReactEvent.Mouse.defaultPrevented(event)
        && shouldPreventDefault(event)) {
      ReactEvent.Mouse.preventDefault(event);
      ReasonReact.Router.push(href);
    };

  <a href ?className onClick=handleClick> children </a>;
};

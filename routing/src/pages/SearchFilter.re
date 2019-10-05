let str = React.string;
let checked = e => ReactEvent.Form.target(e)##checked;

[@react.component]
let make = (~name, ~values, ~selectedValues, ~onChange) => {
  let isChecked = value =>
    selectedValues->Belt.Array.keep(v => v == value)->Belt.Array.length > 0;

  <div className="filter-row">
    <h3 className="filter-name"> {str(name ++ ":")} </h3>
    {values->Belt.Array.map(value =>
       <label key=value>
         <input
           type_="checkbox"
           checked={isChecked(value)}
           onChange={e => onChange(value, checked(e))}
         />
         {str(value)}
       </label>
     )
     |> React.array}
  </div>;
};

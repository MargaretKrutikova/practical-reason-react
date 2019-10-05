let str = React.string;
open Routing;

let priceRanges = [|"< 100$", "100-1000$", ">1000$"|];

let updateFilter = (currentValues, value, checked) => {
  checked
    ? currentValues->Belt.Array.concat([|value|])
    : currentValues->Belt.Array.keep(val_ => val_ !== value);
};

type state = SearchParams.t;

type action =
  | ColorFilterChanged(string, bool)
  | SizeFilterChanged(string, bool)
  | BrandFilterChanged(string, bool);

let reducer = (state: state, action): state => {
  switch (action) {
  | ColorFilterChanged(value, checked) =>
    let colors = updateFilter(state.colors, value, checked);
    {...state, colors};

  | SizeFilterChanged(value, checked) =>
    let sizes = updateFilter(state.sizes, value, checked);
    {...state, sizes};

  | BrandFilterChanged(value, checked) =>
    let brands = updateFilter(state.brands, value, checked);
    {...state, brands};
  };
};

let initialState: state = {
  query: "",
  colors: [||],
  sizes: [||],
  brands: [||],
};

[@react.component]
let make = (~searchParams) => {
  Js.log(searchParams);
  let (searchQuery, dispatch) =
    React.useReducerWithMapState(reducer, initialState, init =>
      searchParams->Belt.Option.getWithDefault(init)
    );
  React.useEffect1(
    () => {
      Routing.pushRoute(Search(Some(searchQuery)));
      None;
    },
    [|searchQuery|],
  );

  <>
    <h1> {React.string("Search")} </h1>
    <form className="search-form">
      <div className="inputs">
        <input type_="search" />
        <select>
          <option value="" hidden=true> {str("Price range")} </option>
          {priceRanges->Belt.Array.map(range =>
             <option key=range> {str(range)} </option>
           )
           |> React.array}
        </select>
      </div>
      <div className="filters">
        <SearchFilter
          name="Color"
          selectedValues={searchQuery.colors}
          values=ProductFilter.colors
          onChange={(value, checked) =>
            dispatch(ColorFilterChanged(value, checked))
          }
        />
        <SearchFilter
          name="Sizes"
          selectedValues={searchQuery.sizes}
          values=ProductFilter.sizes
          onChange={(value, checked) =>
            dispatch(SizeFilterChanged(value, checked))
          }
        />
        <SearchFilter
          name="Brands"
          selectedValues={searchQuery.brands}
          values=ProductFilter.brands
          onChange={(value, checked) =>
            dispatch(BrandFilterChanged(value, checked))
          }
        />
      </div>
    </form>
  </>;
};

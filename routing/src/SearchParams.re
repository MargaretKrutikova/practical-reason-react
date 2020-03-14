type t = {
  query: string,
  colors: array(string),
  sizes: array(string),
  brands: array(string),
};

let fromQs = (qs: string): t => {
  let map = BsQueryString.Parse.toQueryObj(qs);
  BsQueryString.Parse.{
    query: map |> (item("q", string) |> withDefault("")),
    colors: map |> (item("color", array) |> withDefault([||])),
    sizes: map |> (item("size", array) |> withDefault([||])),
    brands: map |> (item("brand", array) |> withDefault([||])),
  };
};

let toOptionalQuery = query => query != "" ? Some(query) : None;

let toQs = params =>
  BsQueryString.Stringify.(
    toQs([|
      ("query", optional(params.query |> toOptionalQuery, string)),
      ("color", item(params.colors, array)),
      ("size", item(params.sizes, array)),
      ("brand", item(params.brands, array)),
    |])
  );

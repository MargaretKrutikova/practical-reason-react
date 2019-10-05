type t = {
  query: string,
  colors: array(string),
  sizes: array(string),
  brands: array(string),
};

let fromQs = (qs: string): t => {
  let map = BsQueryString.Parse.toQueryObj(qs);
  BsQueryString.Parse.{
    query: map |> string("q") |> default(""),
    colors: map |> array("color") |> default([||]),
    sizes: map |> array("size") |> default([||]),
    brands: map |> array("brand") |> default([||]),
  };
};

let hasQuery = params => params.query != "";

let toQs = params =>
  BsQueryString.Stringify.(
    toQs(
      [|
        ("color", array(params.colors)),
        ("size", array(params.sizes)),
        ("brand", array(params.brands)),
      |]
      |> addOptional("q", string(params.query), ~skip=hasQuery(params)),
    )
  );

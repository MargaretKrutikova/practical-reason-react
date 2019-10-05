module Paths = {
  let searchPage = "search";
  let productPage = "page";
  let homePage = "home";
};

type route =
  | Search(option(SearchParams.t))
  | Product(string)
  | Home
  | NotFound;

let useAppUrl = () => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path) {
  | [path] when path == Paths.searchPage =>
    switch (url.search) {
    | "" => Search(None)
    | search =>
      let searchPageParams = SearchParams.fromQs(search);
      Search(Some(searchPageParams));
    }
  | [path, id] when path == Paths.productPage => Product(id)
  | [path] when path == Paths.homePage => Home
  | _ => NotFound
  };
};

let ensureForwardSlash = path => {
  path |> Js.String.slice(~from=0, ~to_=1) == "/" ? path : "/" ++ path;
};

let routeToUrl = route => {
  switch (route) {
  | Search(Some(params)) =>
    let qs = SearchParams.toQs(params);
    let path = Paths.searchPage |> ensureForwardSlash;

    BsQueryString.Utils.addToPath(~path, ~qs);
  | Search(None) => Paths.searchPage |> ensureForwardSlash
  | Product(id) => Paths.productPage ++ id |> ensureForwardSlash
  | Home => Paths.homePage |> ensureForwardSlash
  | _ => "/"
  };
};

let pushRoute = route => {
  route |> routeToUrl |> ReasonReactRouter.replace;
};

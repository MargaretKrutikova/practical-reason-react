type route =
  | Search
  | Product(string)
  | Home
  | NotFound;

let routeToPath = route =>
  switch (route) {
  | Search => "search"
  | Product(_) => "product"
  | Home => "home"
  | _ => ""
  };

let routeToUrl = route =>
  switch (route) {
  | Search => "/search"
  | Product(id) => "/product/" ++ id
  | Home => "/home"
  | _ => "/"
  };

let useAppUrl = () => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path) {
  | ["search"] => Search
  | ["product", id] => Product(id)
  | ["home"]
  | [] => Home
  | _ => NotFound
  };
};

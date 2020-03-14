[@react.component]
let make = () => {
  let route = Routing.useAppUrl();

  let activePage =
    React.useMemo1(
      () =>
        switch (route) {
        | Search(searchParams) => <SearchPage searchParams />
        | Product(_) => <ProductPage />
        | Home => <HomePage />
        | NotFound => <NotFoundPage />
        },
      [|route|],
    );
  <>
    <header>
      <RouterLink href={Routing.routeToUrl(Home)} className="nav-link">
        {React.string("Home")}
      </RouterLink>
      <RouterLink
        href={Routing.routeToUrl(Search(None))} className="nav-link">
        {React.string("Search")}
      </RouterLink>
    </header>
    <main> activePage </main>
  </>;
};

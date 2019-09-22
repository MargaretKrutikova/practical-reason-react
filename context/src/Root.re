open Types;

type state = {user};
let initialState = {user: Anonymous};

let reducer = (_, action) =>
  switch (action) {
  | UserLoggedIn(userName) => {user: LoggedIn(userName)}
  | UserLoggedOut => {user: Anonymous}
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  // if needed, could be optimized with useMemo, or split into two context
  // providers for user and dispatch separately
  <UserProvider value=(state.user, dispatch)>
    <> <Header /> <main> <Page /> </main> </>
  </UserProvider>;
};

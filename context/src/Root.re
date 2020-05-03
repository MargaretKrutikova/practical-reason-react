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

  let context =
    React.useMemo2(() => (state.user, dispatch), (state.user, dispatch));

  // if needed, could be optimized with useMemo, or split into two context
  // providers for user and dispatch separately
  <UserProvider value=context>
    <> <Header /> <main> <Page /> </main> </>
  </UserProvider>;
};

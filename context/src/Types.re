type user =
  | Anonymous
  | LoggedIn(string);

type userAction =
  | UserLoggedIn(string)
  | UserLoggedOut;

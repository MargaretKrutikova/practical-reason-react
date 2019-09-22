[@react.component]
let make = () => {
  let (user, _) = UserContext.useUser();

  <>
    <h1> {React.string("A page")} </h1>
    {switch (user) {
     | Anonymous =>
       <span className="user-message">
         {React.string("Sneaky, you are browsing anonymously!")}
       </span>
     | LoggedIn(userName) =>
       <span className="user-message">
         {React.string("Welcome, " ++ userName ++ "!")}
       </span>
     }}
  </>;
};

[@react.component]
let make = () => {
  let (user, _) = UserContext.useUser();

  <div>
    <h1> {React.string("A page")} </h1>
    {switch (user) {
     | Anonymous =>
       <span> {React.string("Sneaky, you are browsing anonymously!")} </span>
     | LoggedIn(userName) =>
       <span> {React.string("Welcome, " ++ userName ++ "!")} </span>
     }}
  </div>;
};

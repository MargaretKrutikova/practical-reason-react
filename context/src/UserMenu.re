open Types;
let str = React.string;

[@react.component]
let make = () => {
  let (user, dispatch) = UserContext.useUser();
  let (userName, setUserName) = React.useState(() => "");

  switch (user) {
  | Anonymous =>
    <form
      className="user-form"
      onSubmit={e => {
        ReactEvent.Form.preventDefault(e);
        dispatch(UserLoggedIn(userName));
      }}>
      <input
        className="login-input"
        placeholder="User name"
        value=userName
        onChange={e => {
          let value = ReactEvent.Form.target(e)##value;
          setUserName(_ => value);
        }}
      />
      <button type_="submit"> {str("Log in")} </button>
    </form>
  | LoggedIn(userName) =>
    <div className="user-form">
      <span className="logged-in">
        {str("Logged in as: ")}
        <b> {str(userName)} </b>
      </span>
      <button onClick={_ => dispatch(UserLoggedOut)}>
        {str("Log out")}
      </button>
    </div>
  };
};

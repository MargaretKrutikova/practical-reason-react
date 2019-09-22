// Define the type of the value we will put in context - pair of user and dispatch
type dispatch = Types.userAction => unit;
type contextValue = (Types.user, dispatch);

let initValue: contextValue = (Anonymous, _ => ignore());

// Create the context that will hold the valuer
let context = React.createContext(initValue);

// Create hooks for ease of access to the context value
let useUser = () => React.useContext(context);

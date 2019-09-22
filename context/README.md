# Reason-React context explained in action

Originally published on [dev.to](https://dev.to/margaretkrutikova/reason-react-context-explained-in-action-5eki).

---

[`Context`](https://reactjs.org/docs/context.html) in `react` is designed for sharing some global data between your components located at different levels of the component tree. It allows to avoid passing `props` all the way down to those components ("prop-drilling") while still updating them whenever the value in `context` changes.

It is recommended to use `context` for low-frequent updates ([quote by Sebastian Markbåge](https://github.com/facebook/react/issues/14110#issuecomment-448074060)), due to a possible performance impact because of to the way `react` finds subscribers to the context value. This topic would require it is own article (or perhaps a book?), and I will not touch upon it here and instead focus on a practical example of using `context` for seldom updates in a `react` application with `reasonml`.

## What are we building

We are going to build a feature with log in/log out, where we will put information about the user in `context`, so that we can access it from anywhere in our app and customize it depending on whether the user is browsing anonymously or not. The source code in the article is in [this repo](https://github.com/MargaretKrutikova/practical-reason-react/tree/master/context).

There are many bits and pieces that have to be wired up together in order to get benefits and all the convenience react context provides, especially in a strongly-typed environment with `ReasonML`, but it is definitely worth.

I will go through the steps needed to connect everything together and we will end up with a simple hook that allows to read the user data from context and dispatch and action to update it from any component, like this:

```reason
let (user, dispatch) = UserContext.useUser();
let handleLogIn = () => dispatch(UserLoggedIn(userName));

switch (user) {
  | Anonymous => // display login form
  | LoggedIn(userName) => // say hi to the user!
};
```

Scroll down to learn how 👇

## Create provider and context

We will start with these steps:

1. Create context,
2. Create provider component,
3. Create reusable hook to access context value.

We need to know whether the user using our app is anonymous or logged in, and what actions can change this, so let's start with a few types:

```reason
// Types.re
type user =
  | Anonymous
  | LoggedIn(string);

type userAction =
  | UserLoggedIn(string)
  | UserLoggedOut;
```

`LoggedIn` will hold user name, but can be any other type with more user data. We will use `userAction` when implementing a reducer for our user state.

Now let's create context and reusable hook to access the context value, in a file `UserContext.re`:

```reason
// initial value is Anonymous
let context = React.createContext(Anonymous);

// hook to easily access context value
let useUser = () => React.useContext(context);
```

This is very similar to how you would do it in JS. Now let's create context provider in a file `UserProvider.re`

```reason
// UserProvider.re
let make = React.Context.provider(UserContext.context);

// Tell bucklescript how to translate props into JS
let makeProps = (~value, ~children, ()) => {
  "value": value,
  "children": children,
};
```

What is that `makeProps` for and why can't we just create a normal component with `[@react.component]` and `make`? The question I asked myself many times until I got tired and dug into it and found out 🤦‍♀️🙃

Remember how we always have named arguments for `props` in our `reason` components, like `~id` or `~className`? JS doesn't have such a feature, and all regular JS components just want to have `props` as an object. So how does it compile to valid `react` components in JS?

That's what the attribute [`[@react.component]`](https://reasonml.github.io/reason-react/docs/en/components#reactcomponent) is for. It will generate a function called `makeProps`, that transforms those named arguments into a JS object to be used as `props` in the JS compiled component.

`React.Context.provider` already generates a react component, that uses `props` as a JS object, but we want to use it as a `reason` component with named args. That's why we create `makeProps` by hand and it will tell bucklescript how to translate our named args into a JS object, consumed as `props` by the JS component. And in order to create an object that will compile cleanly to a JS object, we use bucklescript [`Object 2`](https://bucklescript.github.io/docs/en/object-2) bindings, that look like this:

```reason
{
  "value": value,
  "children": children,
}
```

So we are basically doing the job of `[@react.component]`, but luckily it is not much, since the provider just needs a value and children 😅.

We can now use our provider component like `<UserProvider...>` since we followed the [`convention`](https://reasonml.github.io/reason-react/docs/en/components#component-naming) of having two functions `make` and `makeProps` in a file `UserProvider`.

## Update value in context

Now, we want to use our `Provider` component and give it the user info, that we can update when the user logs in or logs out.

The important thing to understand here, is that if we want to **update** the value in `context` and **propagate** the update to subscriber-components, the value needs to be on the state of some component. This component needs to render the provider component with the value from its own state.

Let's call it `Root` component:

```reason
// Root.re
type state = {user};

// user and userAction defined in Types.re
let reducer = (_, action) =>
  switch (action) {
  | UserLoggedIn(userName) => {user: LoggedIn(userName)}
  | UserLoggedOut => {user: Anonymous}
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, {user: Anonymous});

  <UserProvider value=state.user>
    <Page />
  </UserProvider>;
};
```

Cool, now whenever the value in context changes, components using `useUser` will be updated with the new value! Wait, the value actually never changes.. oh no! 😯

Let's give our components possibility to update user data via context. We could pass the update function down as `props`, which will be back to prop-drilling approach, but a more fun way is to include `dispatch` in the context value itself.

## Pass dispatch in context

Let's pass our `dispatch` along with `user` as context value. Knowing that `dispatch` accepts `userAction` and returns `unit`, we can modify the type of context value in `UserContext.re`:

```reason
// UserContext.re
type dispatch = userAction => unit;
type contextValue = (user, dispatch);

let initValue: contextValue = (Anonymous, _ => ignore());
// no changes when creating context
```

and the root component:

```reason
// Root.re
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, {user: Anonymous});

  <UserProvider value=(state.user, dispatch)>
    <Page />
  </UserProvider>;
}
```

## Use context value via hook

And now the reward I promised in the beginning, an easy to use and convenient hook. I will just repeat it here once more, because it is cool:

```reason
let (user, dispatch) = UserContext.useUser();
let handleLogIn = () => dispatch(UserLoggedIn(userName));

switch (user) {
  | Anonymous => // display login form
  | LoggedIn(userName) => // say hi to the user!
};
```

Done!

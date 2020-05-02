open Jest;
open TaskStatus;

describe("Task status transitions", () => {
  open Expect;

  testAll(
    "Transition works correctly for valid state transitions",
    [
      (NotStarted, Start, Running(0.0)),
      (Running(10.0), Pause, Paused(10.0)),
      (Running(10.0), Finish, Done(10.0)),
      (Paused(10.0), Resume, Running(10.0)),
      (Paused(10.0), Finish, Done(10.0)),
      (Running(10.0), Tick(15.0), Running(25.0)),
    ],
    ((currentState, input, nextState)) =>
    expect(currentState |> transition(input)) |> toEqual(nextState)
  );

  testAll(
    "Transition returns current state for invalid state transitions",
    [
      ([|Running(5.0), Paused(5.0), Done(5.0)|], Start, " when started"),
      ([|NotStarted, Paused(10.0), Done(10.0)|], Pause, " when paused"),
      ([|NotStarted, Running(10.0), Done(10.0)|], Resume, " when resumed"),
      ([|NotStarted, Done(10.0)|], Finish, " when finished"),
      ([|NotStarted, Paused(5.0), Done(5.0)|], Tick(1.0), " when ticked"),
    ],
    ((states, input, _)) =>
    expect(states->Belt.Array.map(state => state |> transition(input)))
    |> toEqual(states)
  );
});

describe("Task status utility functions", () => {
  open Expect;

  test("isRunning returns true if Running", () => {
    expect(Running(20.8) |> isRunning) |> toEqual(true)
  });

  testAll(
    "isRunning returns false if not Running",
    [NotStarted, Paused(10.0), Done(10.0)],
    status => {
    expect(status |> isRunning) |> toEqual(false)
  });
});

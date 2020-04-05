open Jest;
open TaskStatus;

describe("Task status transitions", () => {
  open Expect;

  test("start transition returns Running state from NotStarted", () =>
    expect(NotStarted |> start) |> toEqual(Running(0.0))
  );

  testAll(
    "start transition returns the same state if not NotStarted",
    [Running(10.0), Paused(10.0), Done(10.0)],
    status =>
    expect(status |> start) |> toEqual(status)
  );

  test(
    "pause transition returns Paused state from Running with the same elapsed",
    () => {
    expect(Running(42.2) |> pause) |> toEqual(Paused(42.2))
  });

  testAll(
    "pause transition returns the same state if not Running",
    [NotStarted, Paused(10.0), Done(10.0)],
    status => {
    expect(status |> pause) |> toEqual(status)
  });

  test(
    "resume transition returns Running state from Paused with the same elapsed",
    () => {
    expect(Paused(42.2) |> resume) |> toEqual(Running(42.2))
  });

  testAll(
    "resume transition returns the same state if not Paused",
    [NotStarted, Running(10.0), Done(10.0)],
    status => {
    expect(status |> resume) |> toEqual(status)
  });

  test(
    "done transition returns Done state from Running with the same elapsed", () => {
    expect(Running(42.2) |> finish) |> toEqual(Done(42.2))
  });

  test(
    "done transition returns Done state from Paused with the same elapsed", () => {
    expect(Paused(42.2) |> finish) |> toEqual(Done(42.2))
  });

  testAll(
    "done transition returns the same state if not Running or Paused",
    [NotStarted, Done(10.0)],
    status => {
    expect(status |> finish) |> toEqual(status)
  });

  test("tick transition adds tick to the elapsed time if Running", () => {
    expect(Running(20.8) |> tick(21.2)) |> toEqual(Running(42.0))
  });

  testAll(
    "tick transition returns the same state if not Running",
    [NotStarted, Paused(10.0), Done(10.0)],
    status => {
    expect(status |> tick(21.2)) |> toEqual(status)
  });
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

type elapsed = float;

type t =
  | NotStarted
  | Running(elapsed)
  | Paused(elapsed)
  | Done(elapsed);

/* function per each state transition */
let start = status =>
  switch (status) {
  | NotStarted => Running(0.0)
  | other => other
  };

let pause =
  fun
  | Running(time) => Paused(time)
  | other => other;

let resume =
  fun
  | Paused(time) => Running(time)
  | other => other;

/* encode business rules inside state transitions:
      1. Running and paused tasks can be finished
      2. Not started tasks can't be finished
   */
let finish =
  fun
  | Running(time)
  | Paused(time) => Done(time)
  | other => other;

let tick = (elapsed, status) =>
  switch (status) {
  | Running(time) => Running(time +. elapsed)
  | other => other
  };

/* utility functions */
let isRunning =
  fun
  | Running(_) => true
  | _ => false;

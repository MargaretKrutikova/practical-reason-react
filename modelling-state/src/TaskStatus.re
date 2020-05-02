type elapsed = float;

type t =
  | NotStarted
  | Running(elapsed)
  | Paused(elapsed)
  | Done(elapsed);

type input =
  | Start
  | Pause
  | Resume
  | Finish
  | Tick(elapsed);

/* encode business rules inside state transitions:
     1. Running and paused tasks can be finished
     2. Not started tasks can't be finished
   */
let transition = (input, state) =>
  switch (state, input) {
  | (NotStarted, Start) => Running(0.0)
  | (Running(elapsed), Pause) => Paused(elapsed)
  | (Running(elapsed), Finish) => Done(elapsed)
  | (Paused(elapsed), Resume) => Running(elapsed)
  | (Paused(elapsed), Finish) => Done(elapsed)
  | (Running(elapsed), Tick(tick)) => Running(elapsed +. tick)
  | _ => state
  };

/* utility functions */
let isRunning =
  fun
  | Running(_) => true
  | _ => false;

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
  switch (state) {
  | NotStarted =>
    switch (input) {
    | Start => Running(0.0)
    | Pause
    | Finish
    | Tick(_)
    | Resume => state
    }
  | Running(elapsed) =>
    switch (input) {
    | Pause => Paused(elapsed)
    | Finish => Done(elapsed)
    | Tick(tick) => Running(elapsed +. tick)
    | Start
    | Resume => state
    }
  | Paused(elapsed) =>
    switch (input) {
    | Resume => Running(elapsed)
    | Finish => Done(elapsed)
    | Tick(_)
    | Start
    | Pause => state
    }
  | Done(_) => state
  };

/* utility functions */
let isRunning =
  fun
  | Running(_) => true
  | _ => false;

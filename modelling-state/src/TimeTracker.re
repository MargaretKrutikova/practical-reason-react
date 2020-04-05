type state = {tasks: array(Task.t)};

let init = () => {tasks: [||]};

type action =
  | TaskAdded(string, string)
  | Tick(float)
  /* action for each task status transition */
  | TaskStarted(string)
  | TaskPaused(string)
  | TaskResumed(string)
  | TaskDone(string)
  | TaskRemoved(string);

/* utility functions */

let updateTaskById = (id, update, tasks: array(Task.t)) =>
  tasks->Belt.Array.map(task => task.id == id ? update(task) : task);

let updateTaskStatus = (id, updateStatusFn, state) => {
  let updateTaskFn = updateStatusFn |> Task.withStatus;
  {tasks: state.tasks |> updateTaskById(id, updateTaskFn)};
};

let removeTask = (id, state) => {
  tasks: state.tasks->Belt.Array.keep(task => task.id != id),
};

let addTask = (id, name, state) => {
  let task = Task.make(~id, ~name);
  {tasks: state.tasks->Belt.Array.concat([|task|])};
};

let getRunningTask = state =>
  state.tasks->Belt.Array.getBy(task => task.status |> TaskStatus.isRunning);

let updateRunningTask = (updateFn, state) =>
  switch (state |> getRunningTask) {
  | None => state
  | Some(runningTask) => state |> updateTaskStatus(runningTask.id, updateFn)
  };

let pauseRunningTask = state => state |> updateRunningTask(TaskStatus.pause);

let reducer = (action, state) => {
  switch (action) {
  | TaskStarted(id) =>
    state |> pauseRunningTask |> updateTaskStatus(id, TaskStatus.start)
  | TaskPaused(id) => state |> updateTaskStatus(id, TaskStatus.pause)
  | TaskResumed(id) =>
    state |> pauseRunningTask |> updateTaskStatus(id, TaskStatus.resume)
  | TaskDone(id) => state |> updateTaskStatus(id, TaskStatus.finish)
  | TaskRemoved(id) => state |> removeTask(id)
  | Tick(elapsed) => state |> updateRunningTask(TaskStatus.tick(elapsed))
  | TaskAdded(id, name) => state |> addTask(id, name)
  };
};

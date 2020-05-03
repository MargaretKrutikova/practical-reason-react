type t = {
  id: string,
  name: string,
  status: TaskStatus.t,
};

// always begin in status NotStarted
let make = (~name, ~id) => {id, name, status: NotStarted};

let withStatus = (taskStatusInput: TaskStatus.input, task) => {
  let nextStatus = TaskStatus.transition(taskStatusInput, task.status);

  {...task, status: nextStatus};
};

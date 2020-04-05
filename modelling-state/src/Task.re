// module TaskId: {
//   type t;
//   let make: unit => t;
// } = {
//   type t = string;
//   let make = () => {

//   }
// };

type t = {
  id: string,
  name: string,
  status: TaskStatus.t,
};

// always begin in status NotStarted
let make = (~name, ~id) => {id, name, status: NotStarted};

let withStatus = (updateStatus, task) => {
  ...task,
  status: updateStatus(task.status),
};

type t = {
  name: string,
  displayName: string,
  values: array(string),
};

let colors = [|"Grey", "Silver", "White", "Black"|];
let sizes = [|"XS", "S", "M", "L"|];
let brands = [|"Ralph Lauren", "Prada", "Burberry", "H&M"|];

let filters = [|
  {displayName: "Color", name: "color", values: colors},
  {displayName: "Size", name: "size", values: sizes},
  {displayName: "Brand", name: "brand", values: brands},
|];

qi:`qinv 2:(`inv;2)
qinv:{[m]
  if[not all first[b]=b:count each m;:"Not a square matrix"];
  if[count[m]~count raze m;:"Not a square matrix"];
  if[not count[m]~count flip m;:"Not a square matrix"];
  if[not all 9h=type each m;:"Invalid type. Requires all floats"];
  m:qi[raze flip m;d:count m];
  $[m~0i;"Error: Matrix is singular";(d;d)#m]
 }

qi:`qinv 2:(`inv;2)
qinv:{[m]
  if[count[m]~count raze m;:"Not a square matrix"];
  if[not count[m]~count flip m;:"Not a square matrix"];
  d:count m;
  m:qi[raze flip m;d];
  $[m=0;"Error: Matrix is singular";(d;d)#m]
 }

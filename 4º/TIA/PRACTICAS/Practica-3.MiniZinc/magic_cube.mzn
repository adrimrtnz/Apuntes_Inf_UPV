int: n = 5;
var int: p;
array [1..n, 1..n] of var 1..n*n: Z;

include "alldifferent.mzn";

constraint p=(n*(pow(n,2) + 1))/2;
constraint alldifferent(Z);
constraint forall (j in 1..n) (sum (i in 1..n) (Z[i,j]) == p);
constraint forall (i in 1..n) (sum (j in 1..n) (Z[i,j]) == p);
constraint sum (i,j in 1..n where i=j) (Z[j, i]) == p;

%output [show(p), " ", show (Z)];
output [show(p), "\n" ] ++
 [show(Z[i,j]) ++
 if j = n then "\n" else " " endif % Nueva linea en cada fila
 | i,j in 1..n ];

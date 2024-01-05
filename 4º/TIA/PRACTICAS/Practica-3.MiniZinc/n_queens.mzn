int: n;
array [1..n] of var 1..n: q; % queen in column i is in row q[i]

include "alldifferent.mzn";

% No es la misma columna
constraint forall (i,j in 1..n where i!=j) (q[i] != q[j]);

% No es la misma diagonal SE
constraint forall (i,j in 1..n where i!=j) ((q[i]-q[j]) != (i-j));

% No en misma diagonal SO
constraint forall (i,j in 1..n where i!=j) ((q[j]-q[i]) != (i-j));

% search
solve satisfy;

output [(show (q[i]) ++ " ") | i in 1..n];
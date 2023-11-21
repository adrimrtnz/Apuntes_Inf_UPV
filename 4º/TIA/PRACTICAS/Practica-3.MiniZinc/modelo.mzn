include "datos.dzn";

int: S;
int: C;
int: min_u_computo;

array[1..S] of int: oferta;
array[1..C] of int: demanda;
array[1..C] of int: max_u_computo_clientes;

% Declaracion de matriz CxS
array[1..C, 1..S] of var 0..100: matriz;

% No negatividad
constraint forall (i in 1..C, j in 1..S) (matriz[i,j] > 0);

% Los servisores no pueden sobrepasar su oferta
constraint forall (j in 1..S) (sum (i in 1..C) (matriz[i,j]) <= oferta[j]);

% minimo de unidades de computo por servidor
constraint forall (j in 1..S) (sum (i in 1..C) (matriz[i,j]) >= min_u_computo);

% de un servidor S un cliente C no puede tener más del max
constraint forall (i in 1..C, j in 1..S) (matriz[i,j] <= max_u_computo_clientes[i]);

% la suma del consumo del servidor S de un cliente C 
% tiene que satisfacer su demanda
constraint forall (i in 1..C) (sum (j in 1..S) (matriz[i,j]) == demanda[i]);


solve satisfy;
% output [show(matriz)];
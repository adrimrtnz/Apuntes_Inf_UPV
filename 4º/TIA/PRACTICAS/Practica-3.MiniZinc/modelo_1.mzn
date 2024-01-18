include "datos_1.dzn";

int: S;
int: C;
int: min_u_computo;
int: server_viejo;

array[1..S] of int: oferta;
array[1..C] of int: demanda;
array[1..C] of int: max_u_computo_clientes;

% Declaracion de matriz CxS
array[1..C, 1..S] of var 0..100: matriz;

% Los servisores no pueden sobrepasar su oferta
constraint forall (j in 1..S) (sum (i in 1..C) (matriz[i,j]) <= oferta[j]);

% minimo de unidades de computo por servidor
constraint forall (j in 1..S) (sum (i in 1..C) (matriz[i,j]) >= min_u_computo);

% de un servidor S un cliente C no puede tener más del max
constraint forall (i in 1..C, j in 1..S) (matriz[i,j] <= max_u_computo_clientes[i]);

% la suma del consumo del servidor S de un cliente C 
% tiene que satisfacer su demanda
constraint forall (i in 1..C) (sum (j in 1..S) (matriz[i,j]) >= demanda[i]);

% Restricciones de software: clientes 1 y 2 solo en servers 1..3
constraint forall (i in 1..2, j in 4..S) (matriz[i,j] == 0);

% Servidor 2 no puede atender simultaneamente a cliente 1 y 2
constraint (matriz[1,2]>0) -> (matriz[2,2]=0);
constraint (matriz[2,2]>0) -> (matriz[1,2]=0);

% Restricción del ejercicio 1: el servidor 9 no puede atender al cliente 8 y 9 a la vez
constraint (matriz[8,9]>0) xor (matriz[9,9]>0);

% minimizar el uso del servidor 8
solve minimize (sum (i in 1..C) (matriz[i,server_viejo]));
%solve satisfy;

output [
 if show(matriz[i, j]) != show(0) then
    "Servidor " ++ show(j) ++ " atiende a cliente " ++ show(i) ++
    " la cantidad " ++ show(matriz[i, j]) ++ " / " ++ show(demanda[i]) ++ "\n"

endif
    | j in 1..S, i in 1..C];
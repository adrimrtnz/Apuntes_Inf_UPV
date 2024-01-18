include "datos_3.dzn";

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
%constraint forall (i in 1..C) (sum (j in 1..S) (matriz[i,j]) >= demanda[i]);

% Restricciones de software: clientes 1 y 2 solo en servers 1..3
constraint forall (i in 1..2, j in 4..S) (matriz[i,j] == 0);

% Servidor 2 no puede atender simultaneamente a cliente 1 y 2
constraint (matriz[1,2]>0) -> (matriz[2,2]=0);
constraint (matriz[2,2]>0) -> (matriz[1,2]=0);
%constraint (matriz[2,2]>0) xor (matriz[1,2]>0);

% Restricciones del Ejercicio 3 ==================================
% Cliente 8 integro en Servidor 1
constraint forall (j in 2..S) (matriz[8,j] == 0);

% Cliente 7 integro en servers 4 y 5
constraint forall (j in 1..3) (matriz[7, j] == 0);
constraint forall (j in 4..5) (matriz[7, j] > 0);
constraint forall (j in 6..S) (matriz[7, j] == 0);


% minimizar el uso del servidor 8
%solve minimize (sum (i in 1..C) (matriz[i,server_viejo]));
solve maximize (sum (i in 1..C, j in 1..S) (matriz[i,j]));

output [
 if show(matriz[i, j]) != show(0) then
    "Servidor " ++ show(j) ++ " atiende a cliente " ++ show(i) ++
    " la cantidad " ++ show(matriz[i, j]) ++ " / " ++ show(demanda[i]) ++ 
    " | Demanda: " ++ 
    show((sum (i2 in 1..C, j2 in 1..S) (matriz[i2,j2])))
     ++ "\n"

endif
    | j in 1..S, i in 1..C];
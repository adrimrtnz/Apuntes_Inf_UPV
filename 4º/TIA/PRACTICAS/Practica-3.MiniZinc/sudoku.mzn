% Modelo de un Sudoku N x N

include "alldifferent.mzn";
include "datos_sudoku.dzn";

% Declaración de la dimensión (N) del Sudoku como parámetro, para se un modelo general para cualquier tamaño;
% La matriz está compuesta de submatrices S x S;
par int: S;    % Un valor=3 indica un dusoku 9x9
int: N = S*S;

% Declaración de un vector N x N
array[1..N, 1..N] of var 1..N: celda;  % Podemos acceder a cada celda[i,j]

% Todas las celdas en una fila son diferentes
constraint forall (i in 1..N) ( alldifferent (j in 1..N) ( celda[i,j] ));

% Todas las celdas en una columna son diferentes
constraint forall (j in 1..N) ( alldifferent (i in 1..N) ( celda[i,j] ));

% Todas las celdas de una submatriz son diferentes
constraint forall (i,j in 1..S) ( alldifferent (p, q in 1..S) ( celda[S*(i-1)+p, S*(j-1) + q] ));

solve satisfy; % solo requerimos satisfactibilidad

output["sudoku:\n"] ++ 
      [ show(celda[i,j]) ++
      
      % Establecemos blancos separadores de submatrices
      if j = N then
        if i mod S = 0 /\ i < N then "\n\n" else "\n" endif
      else
        if j mod S = 0 then "  " else " " endif
      endif
      | i,j in 1..N];
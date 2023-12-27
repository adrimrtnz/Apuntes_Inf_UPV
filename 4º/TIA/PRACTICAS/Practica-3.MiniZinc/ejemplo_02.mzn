include "datos_ejemplo_02.dzn";

% Parámetros cuyo valor será adquirido por fichero externo
int: flour;    % no. grams of flour available
int: banana;   % no. of bananas available
int: sugar;    % no. grams of sugar available
int: butter;   % no. grams of butter available
int: cocoa;    % no. grams of cocoa available

var 0..100: b; % no. of banana cackes
var 0..100: c; % no. of chocolate cakes

% flour
constraint 250*b + 200*c <= flour;

% bananas
constraint 2*b <= banana;

% butter
constraint 100*b + 150*c <= butter;

% cocoa
constraint 75*c <= cocoa;

% maximize our profit
solve maximize 400*b + 450*c;

output ["banana cakes = ", show(b), "\n",
        "chocolate cakes = ", show(c), "\n"];
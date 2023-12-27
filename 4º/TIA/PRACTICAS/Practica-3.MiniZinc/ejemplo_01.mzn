% Modelo para determinar número de pasteles de plátano y chocolate

var 0..100: b; % número de pasteles de plátano
var 0..100: c; % número de pasteles de chocolate

% gramos de harina
constraint 250*b + 200*c <= 4000;

% número de platanos
constraint 2*b <= 6;

% gramos de azucar
constraint 75*b + 150*c <= 2000;

% gramos de mantequilla
constraint 100*b + 150*c <= 500;

% gramos de cacao
constraint 75*c <= 500;

% maximizar cantidad ponderada de pasteles
solve maximize 400*b + 450*c;

output ["no. of banana cackes = ", show(b), "\n",
        "no. of chocolate cakes = ", show(c), "\n"];
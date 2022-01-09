rufian(bertoldo).
rufian(bartolo).

noble(romeo).
noble(bertoldo).

plebeyo(bartolo).

dama(julieta).
dama(gertrudis).

hermosa(julieta).

desea(X,Y) :- plebeyo(X), dama(Y).
desea(X,Y) :- noble(X), hermosa(Y).

rapta(X,Y) :- rufian(X), desea(X,Y).

/*

?- noble(X), rufian(X). -> {bertoldo}
?- rapta(romeo, Y). -> false
?- rapta(X, julieta). -> {bertoldo, bartolo}
?- rapta(X,Y). -> {bertoldo -> julieta, bartolo -> julieta, gertrudis}
?- desea(bartolo, Y). -> {julieta, gertrudis}
?- desea(romeo, Y). -> {julieta}
?- desea(bartolo, Y), dama(Y), hermosa(Y). -> {julieta}

*/
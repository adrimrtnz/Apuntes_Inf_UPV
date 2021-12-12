/* Facts */
male(adrian).
male(miguel).

female(juani).
female(alba).

father(miguel,adrian).
father(miguel, alba).
father(elias, juani).
mother(juani, adrian).
mother(juani, alba).

/* Rules */
is_mother(X) :- 
    mother(X, _).

is_father(X) :- 
    father(X, _).

is_son(X) :- 
    male(X),
    (father(_,X);mother(_,X)).

is_daughter(X) :- 
    female(X),
    (father(_,X);mother(_,X)).

sister_of(X,Y) :-
    female(X),
    father(F, X),
    father(F, Y),
    mother(M, X),
    mother(M, Y),
    X \== Y.

aunt(X, Y) :-
    sister_of(X, Z),
    parent(Z, Y).

sibling(X, Y) :-
    father(F, X),
    father(F, Y),
    mother(M, X),
    mother(M, Y),
    X \== Y.

grandpa_of(X, Y) :-
    (mother(M, Y),father(X,M));
    (father(F, Y),father(X,F)).
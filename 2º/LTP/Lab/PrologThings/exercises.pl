% devuelve el mayor elemento de una lista
mayor([X],X).
mayor([X,Y|T],Z) :- X>=Y, mayor([X|T], Z).
mayor([X,Y|T],Z) :- X<Y, mayor([Y|T], Z).

% divide una lista respecto a un umbral U.
split(_,[],[],[]).
split(U,[X|T],[X|Z],V) :- X>=U, split(U,T,Z,V). 
split(U,[X|T],Z,[X|V]) :- X<U, split(U,T,Z,V).

% suma los elementos de una lista de enteros.
suma([],0).
suma([X|T],N) :- suma(T,N1), N is X+N1. 
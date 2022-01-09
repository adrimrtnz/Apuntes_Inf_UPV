remove(X,[],[]).
remove(X,[X|L], Z) :- remove(X,L,Z).
remove(X,[Y|L],[Y|Z]) :- remove(X,L,Z).

remove_rep([],[]).
remove_rep([X],[X]).
remove_rep([X|L], [X|Z]) :- member(X,L), remove(X,L,M), remove_rep(M,Z).
remove_rep([X|L], [X|Z]) :- not (member(X,L)), remove_rep(L,Z).

repeated(X,[],0).
repeated(X,[X],1).
repeated(X, [X|T],N) :- repeated(X,T,N1), N is N1 + 1.
repeated(X, [Y|T],N) :- X\=Y, repeated(X,T,N).
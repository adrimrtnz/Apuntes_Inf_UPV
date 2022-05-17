% Ejercicio 1
trabaja(empleado(antonio,boix),renfe,1200).
trabaja(empleado(carmen,sanchez),endesa,1600).
trabaja(empleado(lana,rey),polydor,4000).
trabaja(empleado(lana,rey),sonymusic,6000).
trabaja(empleado(pablo,sanchez),bayer,2600).
trabaja(empleado(pablo,sanchez),endesa,4000).

pluriempleado(P,E) :-   trabaja(P,E,_), 
                        trabaja(P,F,_), 
                        E \= F.

% Ejercicio 2
comparables(X,Y) :- trabaja(X,E1,S), 
                    trabaja(Y,E2,S), 
                    X \= Y, E1 \= E2.

% Ejercicio 3
colegas(P1,P2) :- trabaja(P1,E,_),
                  trabaja(P2,E,_),
                  P1\=P2.
colegas(P1,P2) :- trabaja(P1,_,S),
                  trabaja(P2,_,S),
                  P1\=P2.

% Ejercicio A y B Examen 2019
/* movie(M, Y), M is a movie released in the year Y */
movie(barton_fink, 1991).
movie(the_big_lebowski, 1998).
movie(fargo, 1996).
movie(lick_the_star, 1998).
movie(mission_impossible, 1996).
movie(fall, 1997).
/* director(M, D), M is a movie directed by D */
director(the_big_lebowski, joel_coen).
director(barton_fink, ethan_coen).
director(barton_fink, joel_coen).
director(fargo, ethan_coen).
director(fargo, joel_coen).
director(lick_the_star, sofia_coppola).
director(mission_impossible, brian_de_palma).
/* actor(M, A, R), the actor A played the role of R in the movie M */
actor(mission_impossible, tom_cruise, ethan_hunt).
actor(mission_impossible, jon_voight, jim_phelps).
actor(barton_fink, john_turturro, barton_fink).
actor(barton_fink, john_goodman, charlie_meadows).
actor(the_big_lebowski, jeff_bridges, jeffrey_lebowski__the_dude).
actor(the_big_lebowski, john_goodman, walter_sobchak).
actor(the_big_lebowski, philip_seymour_hoffman, brandt).
actor(the_big_lebowski, john_turturro, jesus_quintana).

moviesTwoDirectors(M) :-
    director(M,D1),
    director(M,D2),
    D1 @< D2.

moviesAfter(M,A) :- movie(M,Y), A < Y.

moviesTwoActors(M, Actor1, Actor2) :-
    actor(M, Actor1,_),
    actor(M, Actor2,_),
    Actor1 \== Actor2.

moviesYear(M1,M2,Y) :-
    movie(M1,Y),
    movie(M2,Y),
    M1 @< M2.
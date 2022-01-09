personas(0, []) :- !.
personas(N, [((_Hombre,_Color,_Bebida,_Fuma,_Mascota))|T]) :- N1 is N-1, personas(N1, T).

persona(1, [H|_], H) :- !.
persona(N, [_|T], R) :- N1 is N-1, persona(N1, T, R).

/* 1. el británico vive en la casa roja*/
pista1([(britanico, roja,_,_,_)|_]).
pista1([_|T]) :- pista1(T).

/* 2. el sueco tiene un perro como mascota */
pista2([(sueco,_,_,_, perro)|_]).
pista2([_|T]) :- pista2(T).

/* 3. el danés toma té */
pista3([(danes,_,te,_,_)|_]).
pista3([_|T]) :- pista3(T).

/* 4. el noruego vive en la primera casa */
pista4(Personas) :- persona(1, Personas, (noruego,_,_,_,_)).

/* 5. el alemán fuma Prince */
pista5([(aleman,_,_, prince,_)|_]).
pista5([_|T]) :- pista5(T).

/* 6. la casa verde está a la junto y a la izquierda de la blanca */
pista6([(_,verde,_,_,_),(_,blanca,_,_,_)|_]).
pista6([_|T]) :- pista6(T).

/* 7. el dueño de la casa verde bebe café*/
pista7([(_, verde, cafe,_,_)|_]).
pista7([_|T]) :- pista7(T).

/* 8. el que fuma Pall Mall cría pájaros */
pista8([(_, _,_, pallmall, pajaro)|_]).
pista8([_|T]) :- pista8(T).

/* 9. el duño de la casa amarilla fuma Dunhill */
pista9([(_, amarilla,_, dunhill, _)|_]).
pista9([_|T]) :- pista9(T).

/* 10. el hombre en la casa del centro bebe leche */
pista10(Personas) :- persona(3, Personas, (_,_, leche,_,_)).

/* 11. el que fuma Blends vive al lado del que tiene un gato */
pista11([(_, _,_, blends,_), (_,_,_,_, gato)|_]).
pista11([(_, _,_,_, gato), (_,_,_,blends,_)|_]) ).
pista11([_|T]) :- pista11(T).

/* 12. el que tiene un caballo vive al lado del que fuma Dunhill */
pista12([(_, _,_, dunhill,_), (_,_,_,_, caballo)|_]).
pista12([(_, _,_,_, caballo), (_,_,_,dunhill,_)|_]).
pista12([_|T]) :- pista12(T).

/* 13. El que fuma Bluemaster toma cerveza */
pista13([(_, _, cerveza, bluemaster,_)|_]).
pista13([_|T]) :- pista13(T).

/* 14. El que fuma Blends vive al lado del que toma agua */
pista14([(_,_,_,blends,_), (_,_,agua,_,_)|_]).
pista14([(_,_,agua,_,_), (_,_,_,blends,_)|_]).
pista14([_|T]) :- pista14(T).

/* 15. El noruego vive al lado de la casa azul */
pista15([(noruego,_,_,_,_), (_, azul,_,_,_)|_]).
pista15([(_, azul,_,_,_), (noruego,_,_,_,_)|_]).
pista15([_|T]) :- pista15(T).

/* Pregunta: ¿quién tiene el pez? */
pregunta([(_,_,_,_, pez)|[]]).
pregunta([_|T]) :- pregunta(T).

solucion(Personas) :-
    personas(5, Personas),
    pista1(Personas),
    pista2(Personas),
    pista3(Personas),
    pista4(Personas),
    pista5(Personas),
    pista6(Personas),
    pista7(Personas),
    pista8(Personas),
    pista9(Personas),
    pista10(Personas),
    pista11(Personas),
    pista12(Personas),
    pista13(Personas),
    pista14(Personas),
    pista15(Personas),
    pregunta(Personas).
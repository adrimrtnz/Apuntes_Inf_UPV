persona(britanico).
persona(sueco).
persona(danes).
persona(noruego).
persona(aleman).

casa(roja).
casa(verde).
casa(blanca).
casa(amarilla).

orden(primera).
orden(segunda).
orden(tercera).

posicion(izquierza).
posicion(centro).
posicion(derecha).

animal(perro).
animal(gato).
animal(pajaros).
animal(caballo).

bebida(te).
bebida(cafe).
bebida(leche).
bebida(cerveza).
bebida(agua).

tabaco('Prince').
tabaco('Pall Mall').
tabaco('Dunhill').
tabaco('Blends').
tabaco('Bluemaster').

/* persona A vive en casa de color B */
encasacolor(britanico, roja).

/* persona A vive en casa posicion B */
encasaposicion(noruego, primera).

/* personas casa A y B son vecinas*/
vecino(primera, segunda).
vecino(segunda, primera).
vecino(segunda, tercera).
vecino(tercera, segunda).

vecino(izquierda, centro).
vecino(centro, izquierda).
vecino(centro, derecha).
vecino(derecha, centro).


/* casa A está a la X de la casa B */
posicioncasa(verde, izquierda, blanca).
posicioncasa(X, centro, leche) :- persona(X). bebe(X, leche).

/* animal A es mascota de B */
mascotade(perro, sueco).
mascotade(caballo, X) :-
    ( encasaposicion(X, Y) ; encasacolor(X, Y) ).
    vecino(Y, Z).
    encasaposicion(W, Z).
    fuma(W, 'Dunhill').
mascota(gato, X) :- bebe(X, agua).

/* persona A bebe B */
bebe(danes, te).
bebe(X, cafe) :- encasacolor(X, verde).

/* persona A fuma B */
fuma(aleman, 'Prince').
fuma(X, 'Pall Mall') :- mascota(pajaros, X).
fuma(X, 'Dunhill') :- encasacolor(X, amarilla).
fuma(X, 'Blends') :- 
    ( 
        (
            encasaposicion(X, Y) 
        )
        ;
        (
            encasacolor(X, Y) 
        }
    ).
    vecino(Y, Z). 
    encasaposicion(W, Z).
    mascotade(gato, W).

fuma(X, 'Bluemaster') :- bebe(X, cerveza)
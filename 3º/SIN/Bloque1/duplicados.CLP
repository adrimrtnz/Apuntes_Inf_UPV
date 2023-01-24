(defacts Ej2 (lista 1 3 4 5 6 7 4 6 4 4 3 4 5 6 4 5 6 4 8 5 7 3 2 4 4 4 1 5 6 7 1 2 3 2 3 4 6 5 3 4 5 1 4 3))

(defrule R1
	?f1<-(lista $?x ?y $?z ?y $?w)
=>
	(retract ?f1)
	(assert (lista $?x ?y $?z $?w))
)
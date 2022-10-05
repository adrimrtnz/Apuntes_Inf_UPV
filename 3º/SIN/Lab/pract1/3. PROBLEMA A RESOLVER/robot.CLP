(defglobal ?*height* = 5)
(defglobal ?*width* = 5)

;; =========================================================
;; ===                      FUNCIONES                   ====
;; =========================================================

(deffunction inicio ()
        (reset)
	(printout t "Profundidad Maxima:= " )
	(bind ?prof (read))
	(printout t "Tipo de Busqueda " crlf "    1.- Anchura" crlf "    2.- Profundidad" crlf )
	(bind ?a (read))
	(if (= ?a 1)
	       then   (set-strategy breadth)
	       else   (set-strategy depth))

        (printout t " Ejecuta (run) para poner en marcha el programa " crlf)
	(assert (profundidad-maxima ?prof))

	(assert (altura-maxima ?*height*))
	(assert (anchura-maxima ?*width*))
	(assert (robot 1 1))
	(assert (almacen 2 3))
	(assert (farola 3 5 1))	;; (farola X Y BOMBILLAS_ROTAS)
	(assert (farola 4 3 2))
	(assert (farola 5 5 3))
	(assert (farola 2 1 3))
	(assert (necesito 0))
	(assert (tengo 0))
)


;; =========================================================
;; ===                       REGLAS                     ====
;; =========================================================

(defrule arriba
	?robot <- (robot ?x0 ?y0)
	?farola <- (farola ?x1 ?y1 ?b)
	(test (or 
		(neq (+ ?y0 1) ?y1)
		(neq ?x0 ?x1)
		(eq ?b 0)
	))
	(test (< ?y0 ?*height*))
=>
	(retract ?robot)
	(assert (robot ?x0 (+ ?y0 1)))
)

(defrule derecha
	?robot <- (robot ?x0 ?y0)
	?farola <- (farola ?x1 ?y1 ?b)
	(test (or 
		(neq (+ ?x0 1) ?x1) 
		(neq ?y0 ?y1)
		(eq ?b 0)
	))
	(test (< ?x0 ?*width*))
=>
	(retract ?robot)
	(assert (robot (+ ?x0 1) ?y0))
)

(defrule abajo
	?robot <- (robot ?x0 ?y0)
	?farola <- (farola ?x1 ?y1 ?b)
	(test (or 
		(neq (- ?y0 1) ?y1) 
		(neq ?x0 ?x1)
		(eq ?b 0)
	))
	(test (> ?y0 1))
=>
	(retract ?robot)
	(assert (robot ?x0 (- ?y0 1)))
)

(defrule izquierda
	?robot <- (robot ?x0 ?y0)
	?farola <- (farola ?x1 ?y1 ?b)
	(test (or 
		(neq (- ?x0 1) ?x1) 
		(neq ?y0 ?y1)
		(eq ?b 0)
	))
	(test (> ?x0 1))
=>
	(retract ?robot)
	(assert (robot (- ?x0 1) ?y0))
)

(defrule farola_estropeada(declare (salience 10))
	?robot <- (robot ?x ?y)
	?farola <- (farola ?xf ?yf ?b)
	?tengo <- (tengo ?t)

	(test (or 
		(eq (+ ?x 1) ?xf)
		(eq (- ?x 1) ?xf)
		(eq (+ ?y 1) ?yf)
		(eq (- ?y 1) ?yf)
	))
	
	(test (> ?b 0))
	(test (= ?b ?t))
=>
	(retract ?farola))
	(retract ?tengo))
	(assert (tengo 0))
	(assert (farola ?xf ?yf 0))
)

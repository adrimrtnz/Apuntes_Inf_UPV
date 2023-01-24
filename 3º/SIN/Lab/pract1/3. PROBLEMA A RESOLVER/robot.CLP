(defglobal ?*height* = 5)
(defglobal ?*width* = 5)
(defglobal ?*max_bombillas* = 3)
(defglobal ?*nodos_gen* = 0)

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
	(assert (bombillas-maximas ?*max_bombillas*))
	(assert (ALMACENES almacen 2 3))
	(assert (capacidad 1 2 3))

	; ESTADO INICIAL DEL PROBLEMA
	(assert (robot 1 1 0 farola 3 5 2 farola 4 3 3 farola 5 5 2 nivel 0))
)


;; =========================================================
;; ===                       REGLAS                     ====
;; =========================================================

(defrule recoger
	?f1 <- (robot ?x ?y ?t $?farolas nivel ?n)
	?f2 <- (ALMACENES $? almacen ?xa ?ya $?)
	(capacidad $? ?b $?)

	(profundidad-maxima ?prof)
	
	(test (<= (+ ?t ?b) 3))
	(test (and 
		(= ?x ?xa)
		(= ?y ?ya)
	))

	(test (< ?n ?prof))	
=>
	(assert (robot ?x ?y (+ ?t ?b) $?farolas nivel (+ ?n 1)))
	(bind ?*nodos_gen* (+ ?*nodos_gen* 1))
)


(defrule derecha
	?f1 <- (robot ?x ?y ?b $?farolas nivel ?n)
	(profundidad-maxima ?prof)

	; COMPROBAR QUE SI SE MUEVE NO ESTÁ EN LA MISMA POSICIÓN QUE UNA FAROLA CON BOMBILLAS POR REPARAR
	(test (not
		(member$ (create$ farola (+ ?x 1) ?y) $?farolas)	
	))
	
	; COMPROBAR QUE NO SE SALE DE LA CUADRÍCULA
	(test (< ?x ?*width*))

	(test (< ?n ?prof))
=>
	(assert (robot (+ ?x 1) ?y ?b ?farolas nivel (+ ?n 1)))
	(bind ?*nodos_gen* (+ ?*nodos_gen* 1))
)

(defrule izquierda
	?f1 <- (robot ?x ?y ?b $?farolas nivel ?n)
	(profundidad-maxima ?prof)

	; COMPROBAR QUE SI SE MUEVE NO ESTÁ EN LA MISMA POSICIÓN QUE UNA FAROLA CON BOMBILLAS POR REPARAR
	(test (not
		(member$ (create$ farola (- ?x 1) ?y) $?farolas)	
	))

	; COMPROBAR QUE NO SE SALE DE LA CUADRÍCULA
	(test (> ?x 1))

	(test (< ?n ?prof))
=>
	(assert (robot (- ?x 1) ?y ?b ?farolas nivel (+ ?n 1)))
	(bind ?*nodos_gen* (+ ?*nodos_gen* 1))
)


(defrule abajo
	?f1 <- (robot ?x ?y ?b $?farolas nivel ?n)
	(profundidad-maxima ?prof)

	; COMPROBAR QUE SI SE MUEVE NO ESTÁ EN LA MISMA POSICIÓN QUE UNA FAROLA CON BOMBILLAS POR REPARAR
	(test (not
		(member$ (create$ farola ?x (- ?y 1)) $?farolas)	
	))
	
	; COMPROBAR QUE NO SE SALE DE LA CUADRÍCULA
	(test (> ?y 1))

	(test (< ?n ?prof))
=>
	(assert (robot ?x (- ?y 1) ?b ?farolas nivel (+ ?n 1)))
	(bind ?*nodos_gen* (+ ?*nodos_gen* 1))	
)


(defrule arriba
	?f1 <- (robot ?x ?y ?b $?farolas nivel ?n)
	(profundidad-maxima ?prof)
	
	; COMPROBAR QUE SI SE MUEVE NO ESTÁ EN LA MISMA POSICIÓN QUE UNA FAROLA CON BOMBILLAS POR REPARAR
	(test (not
		(member$ (create$ farola ?x (+ ?y 1)) $?farolas)	
	))
	
	; COMPROBAR QUE NO SE SALE DE LA CUADRÍCULA
	(test (< ?y ?*height*))
	
	(test (< ?n ?prof))
=>
	(assert (robot ?x (+ ?y 1) ?b ?farolas nivel (+ ?n 1)))
	(bind ?*nodos_gen* (+ ?*nodos_gen* 1))
)


(defrule arreglar
	?f1 <- (robot ?x ?y ?br $?antes farola ?xf ?yf ?bf $?despues nivel ?n)
	(profundidad-maxima ?prof)

	(test (or
		(and (= (+ ?x 1) ?xf) (= ?y ?yf))
		(and (= (- ?x 1) ?xf) (= ?y ?yf))
		(and (= ?x ?xf) (= (+ ?y 1) ?yf))
		(and (= ?x ?xf) (= (- ?y 1) ?yf))	
	))
	(test (>= ?br ?bf))

	(test (< ?n ?prof))
	
=>
	(assert (robot ?x ?y (- ?br ?bf) $?antes $?despues nivel (+ ?n 1)))
	(bind ?*nodos_gen* (+ ?*nodos_gen* 1))
)


(defrule objetivo 
	(declare (salience 100))
	
	?f1 <- (robot ? ? ?t $?farolas nivel ?n $?)

	(test (= (length$ $?farolas) 0))
	(test (= ?t 0))
=>
	(printout t "SOLUCIÓN ENCONTRADA EN EL NIVEL " ?n crlf)
	(printout t "- NODOS GENERADOS:" ?*nodos_gen* crlf)
	(printout t "- HECHO OBJETIVO:" ?f1 crlf)
	(halt)
)

(defrule no_solucion
	(declare (salience -100))
	?f1 <- (robot ?x ?y ?br $?antes farola ?xf ?yf ?bf nivel ?n $?)
	?f2 <- (profundidad-maxima ?p)
=>
	(printout t "SIN SOLUCIÓN EN EL NIVEL " ?n crlf)
	(printout t "- NODOS GENERADOS:" ?*nodos_gen* crlf)
	(halt)
)

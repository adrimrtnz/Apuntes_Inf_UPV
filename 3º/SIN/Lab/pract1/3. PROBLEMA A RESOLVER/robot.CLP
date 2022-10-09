(defglobal ?*height* = 5)
(defglobal ?*width* = 5)
(defglobal ?*max_bombillas* = 3)

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

	(assert (robot 1 1 almacen 2 3 farola 3 5 2 farola 4 3 3 farola 5 5 2 tengo 0 necesito 0 nivel 0))
)


;; =========================================================
;; ===                       REGLAS                     ====
;; =========================================================

(defrule arriba
	?f1 <- (robot ?x ?y $?r1 farola ?xf ?yf $?r2 nivel ?n)

	; COMPROBAR QUE SI SE MUEVE NO ESTÉ EN LA MISMA POSICIÓN QUE UNA FAROLA CON BOMBILLAS POR REPARAR
	(test (not
		(and (= (+ ?y 1) ?yf) (= ?x ?xf))	
	))
	
	; COMPROBAR QUE NO SE SALE DE LA CUADRÍCULA
	(test (< ?y ?*height*))
=>
	(assert (robot ?x (+ ?y 1) $?r1 farola ?xf ?yf $?r2 nivel (+ ?n 1)))
)


(defrule derecha

=>

)


(defrule abajo

=>
	
)


(defrule izquierda

=>

)


(defrule objetivo 
	(declare (salience 100))
	
	?f1 <- ($? almacen ? ? $?r tengo ?t $? nivel ?n)

	(test (= (length$ $?r) 0))
	(test (= ?t 0))
=>
	(printout t "SOLUCIÓN ENCONTRADA EN EL NIVEL " ?n crlf)
	(halt)
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(deffunction fuzzify (?fztemplate ?value ?delta)

    (bind ?low (get-u-from ?fztemplate))
    (bind ?hi  (get-u-to   ?fztemplate))

    (if (<= ?value ?low)
        then
        (assert-string
            (format nil "(%s (%g 1.0) (%g 0.0))" ?fztemplate ?low ?delta))
        else
        (if (>= ?value ?hi)
            then
            (assert-string
                (format nil "(%s (%g 0.0) (%g 1.0))"
                            ?fztemplate (- ?hi ?delta) ?hi))
            else
            (assert-string
                (format nil "(%s (%g 0.0) (%g 1.0) (%g 0.0))"
                            ?fztemplate (max ?low (- ?value ?delta))
                            ?value (min ?hi (+ ?value ?delta)) ))
        )
    )
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(deftemplate peso
	0 10 kilos
	((bajo (3 1) (5 0))
	(medio (3 0) (4 1) (7 1) (10 0))
	(alto (8 0) (9 1))))


(deftemplate humedad
	0 50 porcentage
	((seco (5 1) (10 0))
	(humedo (5 0) (15 1) (30 1) (40 0))
	(mojado (35 0) (40 1))))


(deftemplate temperatura
	20 110 grados					; MODIFICACION EJERCICIO 2
	((baja (30 1) (50 0))
	(media (30 0) (50 1) (60 1) (80 0))
	(alta (60 0) (80 1))
	(vapor (s 80 105))				; MODIFICACION EJERCICIO 2
	(supervapor (pi 10 100))))		; MODIFICACION EJERCICIO 2

; VELOCIDAD CENTRIFUGADO
(deftemplate velocidad
	0 1000 rmp
	((baja (300 1) (500 0))
	(media (400 0) (500 1) (700 1) (800 0))
	(alta (700 0) (800 1))))

(deftemplate duracion-secado
	20 120 min
	((corta (30 1) (40 0))
	(media (30 0) (50 1) (70 1) (80 0))
	(larga (70 0) (80 1) (90 1) (110 0))
	(extralarga (80 0) (100 1))))

(deftemplate Secado
	;;inputs
	(slot peso-crisp (type FLOAT))
	(slot humedad-crisp (type FLOAT))
	(slot modo (type SYMBOL))

	;;outputs
	(slot mom-temperatura-crisp (type FLOAT))
	(slot max-temperatura-crisp (type FLOAT))
	(slot mom-duracion-secado-crisp (type FLOAT))
	(slot max-duracion-secado-crisp (type FLOAT)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;								REGLAS									 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defrule leerconsola ;lee de consola un valor crisp y aserta su valor fusificado
    (initial-fact)
=>
    (printout t "Introduzca el peso en kg" crlf)
    (bind ?Rpeso (read))
    (printout t "Introduzca la humedad en %" crlf)
    (bind ?Rhumedad (read))
	(printout t "Introduzca el modo [EST, HIEST]:" crlf)
	(bind ?Rmodo (read))
    (fuzzify peso ?Rpeso 0)
    (fuzzify humedad ?Rhumedad 0)
	(assert (Secado (peso-crisp ?Rpeso) (humedad-crisp ?Rhumedad) (modo ?Rmodo))))


(defrule defusificar
	(declare (salience -1))
	(temperatura ?t)
	(duracion-secado ?d)
	(velocidad ?v)
	?s <- (Secado (peso-crisp ?p) (humedad-crisp ?h))
=>
    (bind ?tmom (moment-defuzzify ?t))
    (bind ?tmax (maximum-defuzzify ?t))
    (bind ?dmom (moment-defuzzify ?d))
    (bind ?dmax (maximum-defuzzify ?d))

	(bind ?vmom (moment-defuzzify ?v))
	(bind ?vmax (maximum-defuzzify ?v))

	(modify ?s 
		(mom-temperatura-crisp ?tmom) 
		(max-temperatura-crisp ?tmax) 
		(mom-duracion-secado-crisp ?dmom) 
		(max-duracion-secado-crisp ?dmax))
	(printout t "Temperatura (mom): " ?tmom crlf)
    (printout t "Temperatura (max): " ?tmax crlf)
    (printout t "Duracion (mom): " ?dmom crlf)
    (printout t "Duracion (max): " ?dmax crlf)
	(printout t "Velocidad (mom): " ?vmom crlf)
    (printout t "Velocidad (max): " ?vmax crlf)
	(halt))

;; REGLAS ADICIONALES EJERCICIO 2
(defrule esterilizar
	(Secado (peso-crisp ?p) (humedad-crisp ?h) (modo EST))
=>
	(fuzzify temperatura 100 0))

(defrule HIEST
	(Secado (peso-crisp ?p) (humedad-crisp ?h) (modo HIEST))
=>
	(fuzzify temperatura 110 0))


;; TEMPERATURA DE SECADO
(defrule temp-secado-extremely-baja
	(peso bajo)
	(humedad seco)
	=>
	(assert (temperatura extremely baja)))

(defrule temp-secado-media
	(peso bajo)
	(humedad humedo)
	=>
	(assert (temperatura media)))

(defrule temp-secado-alta
	(peso bajo)
	(humedad mojado)
	=>
	(assert (temperatura alta)))

(defrule temp-secado-very-baja
	(peso medio)
	(humedad seco)
	=>
	(assert (temperatura very baja)))

(defrule temp-secado-more-or-less-media
	(peso medio)
	(humedad humedo)
	=>
	(assert (temperatura more-or-less media)))

(defrule temp-secado-modificacion-ej1 	; MODIFICACION EJERCICIO 1
	(peso medio)
	(humedad mojado)
	=>
	(assert (temperatura more-or-less alta)))

(defrule temp-secado-more-or-less-baja
	(peso alto)
	(humedad seco)
	=>
	(assert (temperatura more-or-less baja)))

(defrule temp-secado-alta-2
	(peso alto)
	(humedad humedo)
	=>
	(assert (temperatura alta)))

(defrule temp-secado-extremely-alta
	(peso alto)
	(humedad mojado)
	=>
	(assert (temperatura extremely alta)))

;; DURACIÓN SECADO
(defrule duracion-modificacion-ej1		; MODIFICACION EJERCICIO 1
	(peso bajo)
	(humedad seco)
	=>
	(assert (duracion-secado corta)))

(defrule duracion-somewhat-corta
	(peso bajo)
	(humedad humedo)
	=>
	(assert (duracion-secado somewhat corta)))

(defrule duracion-media
	(peso bajo)
	(humedad mojado)
	=>
	(assert (duracion-secado media)))

(defrule duracion-very-corta
	(peso medio)
	(humedad seco)
	=>
	(assert (duracion-secado very corta)))

(defrule duracion-somewhat-media
	(peso medio)
	(humedad humedo)
	=>
	(assert (duracion-secado somewhat media)))

(defrule duracion-larga
	(peso medio)
	(humedad mojado)
	=>
	(assert (duracion-secado larga)))

(defrule duracion-more-or-less-corta
	(peso alto)
	(humedad seco)
	=>
	(assert (duracion-secado more-or-less corta)))

(defrule duracion-larga-2
	(peso alto)
	(humedad humedo)
	=>
	(assert (duracion-secado larga)))

(defrule duracion-extralarga
	(peso alto)
	(humedad mojado)
	=>
	(assert (duracion-secado extralarga)))

;; CENTRIFUGADO
(defrule centrifugado1
	(peso bajo)
	(temperatura more-or-less vapor)
	=>
	(assert (velocidad alta)))

(defrule centrifugado2
	(peso medio)
	(temperatura vapor)
	=>
	(assert (velocidad media)))

(defrule centrifugado3
	(peso alto)
	(temperatura supervapor)
	=>
	(assert (velocidad very baja)))
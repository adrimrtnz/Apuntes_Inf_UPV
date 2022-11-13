;; Grupo 3ºD, Adrian Martínez Martínez y Marcial Carreras Arencibia

;; =================================================
;; ===     TERMINOLOGIA DE ANALISIS DE HECHOS   ====
;; =================================================
;; 
;; ?rx  posicion x del robot
;; ?ry  posicion y del robot
;; ?rb  cantidad de bombillas que lleva el robot
;; ?fx  posicion x de la farola
;; ?fy  posicion y de la farola
;; ?fb  cantidad de bombillas fundidas en la farola
;; ?nivel nivel del hecho
;; 
;; ?farolas array de farolas 

;; ===================================
;; ===     DEFINICION DE HECHOS   ====
;; ===================================

(deffacts datos
    (dim 6 6); dimensiones de la cuadricula x y
    (alm1 2 5); posicion del almacen    x y
    (maxc 3); capacidad maxima de la cesta del robot
    (capacidad 1 2 3); posibles cantidades de bombillas que el robot podria coger del almacen
    (basurero 5 5)
)

(defglobal ?*nod-gen* = 0); cantidad de nodos generados


;; =====================================
;; ===     REGLAS COGER Y REPARAR   ====
;; =====================================

(defrule vaciar
    ?f1 <- (robot $?rp ?rb ff $?farolas nivel ?nivel)
    ?f2 <- (basurero $?pos)
    (profundidad-maxima ?prof)

    (test (< ?nivel ?prof))
    (test (= (length$ $?farolas) 0))
    (test (member$ $?rp $?pos))
    =>
    (assert (robot $?rp 0 ff ?farolas nivel (+ ?nivel 1)))
)

(defrule cogeB
    ?f1 <- (robot $?rp ?rb ff $?farolas nivel ?nivel)
    ?f2 <- (alm1 $?ap); posicion del almacen
    ?f3 <- (maxc ?maxb); capacidad maxima de la cesta del robot
    ?f4 <- (capacidad $?a ?b $?c)
    (profundidad-maxima ?prof)
;; comprueba que no se supere el limite de profundidad
    (test (< ?nivel ?prof))
;; comprobar que este en un almacen
    (test (member$ ?rp ?ap))
;; comprobar que no lleve la cesta llena
    (test (neq ?rb ?maxb))
;; comprobar si puede recoger esa cantidad de bombillas
    (test (>= ?maxb (+ ?rb ?b)))
    =>
    (assert (robot $?rp (+ ?rb ?b) ff ?farolas nivel (+ ?nivel 1)))
    (bind ?*nod-gen* (+ ?*nod-gen* 1))
)


(defrule reparar
    ?f1 <- (robot ?rx ?ry ?rb ff $?fantes farola ?fx ?fy ?fb $?fdespues nivel ?nivel)
    ?f2 <- (dim ?maxX ?maxY)
    (profundidad-maxima ?prof)
;; comprueba que no se supere el limite de profundidad
    (test (< ?nivel ?prof))
;; comprobar que tenga suficientes bombillas
    (test (>= ?rb ?fb))
;; comprobar que haya una farola cerca
    (test (or
        (eq (create$ (+ ?rx 1) ?ry) (create$ ?fx ?fy))
        (eq (create$ (- ?rx 1) ?ry) (create$ ?fx ?fy))
        (eq (create$ ?rx (+ ?ry 1)) (create$ ?fx ?fy))
        (eq (create$ ?rx (- ?ry 1)) (create$ ?fx ?fy))
    ))
    =>
    (assert (robot ?rx ?ry (- ?rb ?fb) ff ?fantes ?fdespues nivel (+ ?nivel 1)))
    (bind ?*nod-gen* (+ ?*nod-gen* 1))
)




;; ===================================
;; ===     REGLAS DE MOVIMIENTO   ====
;; ===================================


(defrule derecha
    ?f1 <- (robot ?rx ?ry ?rb ff $?farolas nivel ?nivel)
    ?f2 <- (dim ?maxX ?maxY)
    (profundidad-maxima ?prof)
;; comprueba que el robot no este en la ultima columna
    (test (neq ?rx ?maxX))
;; comprueba si el robot tiene una farola a la derecha
    (test (not (member$ (create$ farola (+ ?rx 1) ?ry) ?farolas)))
;; comprueba que no se supere el limite de profundidad
    (test (< ?nivel ?prof))
    =>
    (assert (robot (+ ?rx 1) ?ry ?rb ff ?farolas nivel (+ ?nivel 1)))
    (bind ?*nod-gen* (+ ?*nod-gen* 1)))


(defrule izquierda
    ?f1 <- (robot ?rx ?ry ?rb ff $?farolas nivel ?nivel)
    ?f2 <- (dim ?maxX ?maxY)
    (profundidad-maxima ?prof)
;; comprueba que el robot no este en la primera columna
    (test (neq ?rx 1))
;; comprueba si el robot tiene una farola a la izquierda
    (test (not (member$ (create$ farola (- ?rx 1) ?ry) ?farolas)))
;; comprueba que no se supere el limite de profundidad
    (test (< ?nivel ?prof))
    =>
    (assert (robot (- ?rx 1) ?ry ?rb ff ?farolas nivel (+ ?nivel 1)))
    (bind ?*nod-gen* (+ ?*nod-gen* 1)))

(defrule abajo
    ?f1 <- (robot ?rx ?ry ?rb ff $?farolas nivel ?nivel)
    ?f2 <- (dim ?maxX ?maxY)
    (profundidad-maxima ?prof)
;; comprueba que el robot no este en la primera fila
    (test (neq ?ry 1))
;; comprueba si el robot tiene una farola abajo
    (test (not (member$ (create$ farola ?rx (- ?ry 1)) ?farolas)))
;; comprueba que no se supere el limite de profundidad
    (test (< ?nivel ?prof))
    =>
    (assert (robot ?rx (- ?ry 1) ?rb ff ?farolas nivel (+ ?nivel 1)))
    (bind ?*nod-gen* (+ ?*nod-gen* 1)))

(defrule arriba
  ?f1 <- (robot ?rx ?ry ?rb ff $?farolas nivel ?nivel)
  ?f2 <- (dim ?maxX ?maxY)
  (profundidad-maxima ?prof)
;; comprueba que el robot no este en la ultima fila
  (test (neq ?ry ?maxY))
;; comprueba si el robot tiene una farola arriba
  (test (not (member$ (create$ farola ?rx (+ ?ry 1)) ?farolas)))
;; comprueba que no se supere el limite de profundidad
    (test (< ?nivel ?prof))
  =>
  (assert (robot ?rx (+ ?ry 1) ?rb ff ?farolas nivel (+ ?nivel 1)))
  (bind ?*nod-gen* (+ ?*nod-gen* 1)))


;; ============================================================
;; =========      ESTRATEGIA DE CONTROL DE BUSQUEDA    ========
;; ============================================================
;; La regla 'objetivo' se utiliza para detectar cuando se ha alcanzado el estado objetivo

(defrule objetivo
    (declare (salience 100))
    ?f<-(robot ?rx ?ry 0  ff nivel ?n)

   =>
    (printout t "SOLUCION ENCONTRADA EN EL NIVEL " ?n crlf)
    (printout t "NUMERO DE NODOS EXPANDIDOS O REGLAS DISPARADAS " ?*nod-gen* crlf)
    (printout t "HECHO OBJETIVO " ?f crlf)
    
    (halt))

(defrule no_solucion
    (declare (salience -99))
    (robot $? nivel ?n $?)
=>
    (printout t "SOLUCION NO ENCONTRADA" crlf)
    (printout t "NUMERO DE NODOS EXPANDIDOS O REGLAS DISPARADAS " ?*nod-gen* crlf)
    (halt))		


(deffunction inicio ()
        (reset)
	(printout t "Profundidad Maxima:= " )
	(bind ?prof (read))
	(printout t "Tipo de Busqueda " crlf "    1.- Anchura" crlf "    2.- Profundidad" crlf )
	(bind ?a (read))
	(if (= ?a 1)
	       then    (set-strategy breadth)
	       else   (set-strategy depth))
        (printout t " Ejecuta run para poner en marcha el programa " crlf)

    (assert (robot 3 2 0 ff farola 1 1 2 farola 6 2 3 farola 2 3 3 nivel 0))
;;---------------------------------
;;      DEFINICION DE HECHOS DINAMICOS
;; robot x y b      x=columna en la que esta el robot   y=fila en la que esta el robot  b=cantidad de bombillas que lleva el robot
;; ff               inicio lista de farolas
;; farola x y b     definicion de farola, x,y = posicion de la farola       b = cantidad de bombillas fundidad en la farola
;; nivel x          nivel del nodo
;; -------------------------------------
	(assert (profundidad-maxima ?prof))
	
)
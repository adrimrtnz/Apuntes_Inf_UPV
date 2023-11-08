(define (domain drones)
    (:requirements :durative-actions :typing :fluents)
    (:types Light_Drone Heavy_Drone Light_Pkg Heavy_Pkg Waypoint - object)
    (:predicates 
        (at ?x - (either Light_Drone Heavy_Drone Light_Pkg Heavy_Pkg) ?w - Waypoint)
        (in ?p - (either Light_Pkg Heavy_Pkg) ?d - (either Light_Drone Heavy_Drone))
        (empty ?d - (either Light_Drone Heavy_Drone))
        (recharge-point ?w - Waypoint)
        (zvr ?w - Waypoint)
        (recharge-point-free ?w - Waypoint)
        (taller ?w - Waypoint)
        (taller-libre ?w - Waypoint)
        (cargando ?d - (either Light_Drone Heavy_Drone))
        (reparando ?d - (either Light_Drone Heavy_Drone))
        )
    (:functions 
        (battery ?d - (either Light_Drone Heavy_Drone))
        (max-battery ?d - (either Light_Drone Heavy_Drone))
        (fly-speed ?d - (either Light_Drone Heavy_Drone))
        (recharge-delay ?d - (either Light_Drone Heavy_Drone))
        (recharge-cost ?d - (either Light_Drone Heavy_Drone))
        (distance ?w1 - Waypoint ?w2 - Waypoint)
        (coste-recargas)
        (coste-mantenimiento)
        (flight-control ?d - (either Light_Drone Heavy_Drone)) ;; MODIFICACION EJ2
        )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                         RECOGER                                   ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    (:durative-action pick-up-heavy
    :parameters (?p - Heavy_Pkg ?d - Heavy_Drone ?w - Waypoint)
    :duration (= ?duration 2)
    :condition (and   
                    (at start (at ?p ?w))
                    (at start (at ?d ?w))
                    (over all (at ?p ?w))
                    (over all (at ?d ?w))
                    (over all (empty ?d)))
    :effect (and 
                (at end (not (at ?p ?w)))
                (at end (in ?p ?d))
                (at end (not (empty ?d))))
    )

    (:durative-action pick-up-light
    :parameters (?p - Light_Pkg ?d - (either Light_Drone Heavy_Drone) ?w - Waypoint)
    :duration (= ?duration 1)
    :condition (and   
                    (at start (at ?p ?w))
                    (at start (at ?d ?w))
                    (over all (at ?p ?w))
                    (over all (at ?d ?w))
                    (over all (empty ?d)))
    :effect (and 
                (at end (not (at ?p ?w)))
                (at end (in ?p ?d))
                (at end (not (empty ?d))))
    )


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                         ENTREGAR                                  ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ;; Pongo dos casos para que no tenga tanta casuistica y bifurque menos
    (:durative-action deliver-light
    :parameters (?p - Light_Pkg ?d - Light_Drone ?w - Waypoint)
    :duration (= ?duration 2)
    :condition (and   
                    (at start (at ?d ?w))
                    (over all (in ?p ?d))
                    (over all (at ?d ?w))
                    (over all (not (empty ?d))))
    :effect (and 
                (at end (not (in ?p ?d)))
                (at end (at ?p ?w))
                (at end (empty ?d)))
    )

    (:durative-action deliver-heavy
    :parameters (?p - (either Light_Pkg Heavy_Pkg) ?d - Heavy_Drone ?w - Waypoint)
    :duration (= ?duration 2)
    :condition (and  
                    (at start (at ?d ?w))
                    (over all (in ?p ?d))
                    (over all (at ?d ?w))
                    (over all (not (empty ?d))))
    :effect (and 
                (at end (not (in ?p ?d)))
                (at end (at ?p ?w))
                (at end (empty ?d)))
    )



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                            VOLAR                                  ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    (:durative-action fly-light
    :parameters (?d - Light_Drone ?w1 ?w2 - Waypoint)
    :duration (= ?duration (/ (distance ?w1 ?w2) (fly-speed ?d)))
    :condition (and
                (at start (> (flight-control ?d) 0)) ;; MODIFICACION EJ2
                (at start (>= (battery ?d) (distance ?w1 ?w2)))
                (at start (at ?d ?w1)))
    :effect (and
            (at end (not (at ?d ?w1)))
            (at end (at ?d ?w2))
            (at end (decrease (flight-control ?d) 1)) ;; MODIFICACION EJ2
            (at end (decrease (battery ?d) (distance ?w1 ?w2))))
    )

    (:durative-action fly-heavy
    :parameters (?d - Heavy_Drone ?w1 ?w2 - Waypoint)
    :duration (= ?duration (/ (distance ?w1 ?w2) (fly-speed ?d)))
    :condition (and
                (at start (> (flight-control ?d) 0)) ;; MODIFICACION EJ2
                (at start (>= (battery ?d) (distance ?w1 ?w2)))
                (over all (not (zvr ?w1)))
                (over all (not (zvr ?w2)))
                (at start (at ?d ?w1)))
    :effect (and
            (at end (not (at ?d ?w1)))
            (at end (at ?d ?w2))
            (at end (decrease (flight-control ?d) 1)) ;; MODIFICACION EJ2
            (at end (decrease (battery ?d) (distance ?w1 ?w2))))
    )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                         RECARGAR                                  ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    (:durative-action recharge
    :parameters (?d - (either Light_Drone Heavy_Drone) ?w - Waypoint)
    :duration (= ?duration (recharge-delay ?d))
    :condition (and 
                    (at start (recharge-point-free ?w))
                    (over all (recharge-point ?w))
                    (over all (not (reparando ?d)))
                    (over all (empty ?d))
                    (over all (at ?d ?w)))
    :effect (and
                (at start (not (recharge-point-free ?w)))
                (at end (increase (coste-recargas) (recharge-cost ?d)))
                (at end (assign (battery ?d) (max-battery ?d)))
                (at end (recharge-point-free ?w)))
    )
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                         MANTENIMIENTO                             ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    (:durative-action reparar-unico
    :parameters (?d - (either Light_Drone Heavy_Drone) ?w - Waypoint)
    :duration (= ?duration 5)
    :condition (and 
                    (at start (taller-libre ?w))
                    (over all (not (cargando ?d)))
                    (over all (taller ?w)))
    :effect (and
                (at start (not (taller-libre ?w)))
                (at start (reparando ?d))
                (at end (increase (coste-mantenimiento) 9))
                (at end (assign (flight-control ?d) 2))
                (at end (taller-libre ?w))
                (at end (not (reparando ?d))))
    )

    (:durative-action reparar-doble
    :parameters (?d1 ?d2 - (either Light_Drone Heavy_Drone) ?w - Waypoint)
    :duration (= ?duration 8)
    :condition (and 
                    (at start (taller-libre ?w))
                    (over all (not (cargando ?d1)))
                    (over all (not (cargando ?d2)))
                    (over all (not (= ?d1 ?d2)))
                    (over all (taller ?w)))
    :effect (and
                (at start (not (taller-libre ?w)))
                (at start (reparando ?d1))
                (at start (reparando ?d2))
                (at end (increase (coste-mantenimiento) 9))
                (at end (assign (flight-control ?d1) 2))
                (at end (assign (flight-control ?d2) 2))
                (at end (taller-libre ?w))
                (at end (not (reparando ?d1)))
                (at end (not (reparando ?d2))))
    )
)


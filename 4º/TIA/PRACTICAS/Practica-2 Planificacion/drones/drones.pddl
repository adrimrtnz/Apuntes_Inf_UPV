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
        )
    (:functions 
        (battery ?d - (either Light_Drone Heavy_Drone))
        (max-battery ?d - (either Light_Drone Heavy_Drone))
        (fly-speed ?d - (either Light_Drone Heavy_Drone))
        (recharge-delay ?d - (either Light_Drone Heavy_Drone))
        (recharge-cost ?d - (either Light_Drone Heavy_Drone))
        (distance ?w1 - Waypoint ?w2 - Waypoint)
        (coste-recargas)
        )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                         RECOGER                                   ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    (:durative-action pick-up-heavy
    :parameters (?p - (either Light_Pkg Heavy_Pkg) ?d - Heavy_Drone ?w - Waypoint)
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
    :parameters (?p - Light_Pkg ?d - Light_Drone ?w - Waypoint)
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
                (at start (>= (battery ?d) (distance ?w1 ?w2)))
                (at start (at ?d ?w1)))
    :effect (and
            (at end (not (at ?d ?w1)))
            (at end (at ?d ?w2))
            (at end (decrease (battery ?d) (distance ?w1 ?w2))))
    )

    (:durative-action fly-heavy
    :parameters (?d - Heavy_Drone ?w1 ?w2 - Waypoint)
    :duration (= ?duration (/ (distance ?w1 ?w2) (fly-speed ?d)))
    :condition (and
                (at start (>= (battery ?d) (distance ?w1 ?w2)))
                (over all (not (zvr ?w1)))
                (over all (not (zvr ?w2)))
                (at start (at ?d ?w1)))
    :effect (and
            (at end (not (at ?d ?w1)))
            (at end (at ?d ?w2))
            (at end (decrease (battery ?d) (distance ?w1 ?w2))))
    )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                         RECARGAR                                  ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    (:durative-action recharge-light
    :parameters (?d - Light_Drone ?w - Waypoint)
    :duration (= ?duration (recharge-delay ?d))
    :condition (and 
                    (at start (at ?d ?w))
                    (at start (recharge-point-free ?w))
                    (over all (recharge-point ?w))
                    (over all (empty ?d))
                    (over all (at ?d ?w)))
    :effect (and
                (at start (not (recharge-point-free ?w)))
                (at end (increase (coste-recargas) (recharge-cost ?d)))
                (at end (assign (battery ?d) (max-battery ?d)))
                (at end (recharge-point-free ?w)))
    )

    (:durative-action recharge-heavy
    :parameters (?d - Heavy_Drone ?w - Waypoint)
    :duration (= ?duration (recharge-delay ?d))
    :condition (and 
                    (at start (at ?d ?w))
                    (at start (recharge-point-free ?w))
                    (over all (recharge-point ?w))
                    (over all (empty ?d))
                    (over all (at ?d ?w)))
    :effect (and
                (at start (not (recharge-point-free ?w)))
                (at end (increase (coste-recargas) (recharge-cost ?d)))
                (at end (assign (battery ?d) (max-battery ?d)))
                (at end (recharge-point-free ?w)))
    )

)


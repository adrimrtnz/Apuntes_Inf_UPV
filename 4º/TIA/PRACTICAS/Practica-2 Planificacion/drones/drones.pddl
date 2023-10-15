(define (domain drones)
(:requirements :durative-actions :typing :fluents)
(:types Light_Drone Heavy_Drone Light_Pkg Heavy_Pkg Waypoint - object)
(:predicates 
    (at ?x - (either Light_Drone Heavy_Drone Light_Pkg Heavy_Pkg) ?w Waypoint)
    (in ?p - (either Light_Pkg Heavy_Pkg) ?d - (either Light_Drone Heavy_Drone))
    )
(:functions 
    (battery ?d - (either Light_Drone Heavy_Drone))
    (max-battery ?d - (either Light_Drone Heavy_Drone))
    (fly-speed ?d - (either Light_Drone Heavy_Drone))
    (recharge-delay ?d - (either Light_Drone Heavy_Drone))
    (recharge-cost ?d - (either Light_Drone Heavy_Drone))
    (distance ?w1 - Waypoint ?w2 Waypoint)
    )

(:durative-action pick-up
 :parameters (?p - (either Light_Pkg Heavy_Pkg) ?d - (either Light_Drone Heavy_Drone) ?w Waypoint)
 :condition (and    (or
                    (and
                    (at start (at ?p - Light_Pkg ?w))
                    (at start (at ?d - Light_Drone ?w)))
                    
                    (and
                    (at start (at ?p ?w))
                    (at start ((at ?d ?w)))
                (over all (at ?p ?w))
                (over all (at ?d ?w))
            )))
)

(:durative-action fly)

(:durative-action recharge)

)

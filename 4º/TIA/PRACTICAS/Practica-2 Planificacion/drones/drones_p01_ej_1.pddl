(define (problem drones-01)
(:domain drones)
(:objects
    A - Waypoint
    B - Waypoint
    C - Waypoint
    D - Waypoint
    D - Waypoint
    E - Waypoint
    F - Waypoint
    G - Waypoint

    dronL1 - Light_Drone
    dronL2 - Light_Drone
    dronL3 - Light_Drone
    dronP1 - Heavy_Drone
    dronP2 - Heavy_Drone

    paqueteL1 - Light_Pkg
    paqueteL2 - Light_Pkg
    paqueteL3 - Light_Pkg
    paqueteL4 - Light_Pkg       ; MODIFICACION 1
    paqueteP1 - Heavy_Pkg
    paqueteP2 - Heavy_Pkg
    paqueteP3 - Heavy_Pkg       ; MODIFICACION 1
    )
(:init
    (= (coste-recargas) 0)

    (at dronL1 A)
        (= (max-battery dronL1) 100)
        (= (battery dronL1) 5)
        (= (fly-speed dronL1) 2)
        (= (recharge-delay dronL1) 8)
        (= (recharge-cost dronL1) 8)
        (empty dronL1)
    (at dronL2 A)
        (= (max-battery dronL2) 100)
        (= (battery dronL2) 10)
        (= (fly-speed dronL2) 4)
        (= (recharge-delay dronL2) 9)
        (= (recharge-cost dronL2) 10)
        (empty dronL2)
    (at dronL3 C)
        (= (max-battery dronL3) 150)
        (= (battery dronL3) 40)
        (= (fly-speed dronL3) 4)
        (= (recharge-delay dronL3) 10)
        (= (recharge-cost dronL3) 8)
        (empty dronL3)
    (at dronP1 E)
        (= (max-battery dronP1) 200)
        (= (battery dronP1) 40)
        (= (fly-speed dronP1) 1)
        (= (recharge-delay dronP1) 20)
        (= (recharge-cost dronP1) 9)
        (empty dronP1)
    (at dronP2 D)
        (= (max-battery dronP2) 220)
        (= (battery dronP2) 120)
        (= (fly-speed dronP2) 2)
        (= (recharge-delay dronP2) 25)
        (= (recharge-cost dronP2) 12)
        (empty dronP2)

    (at paqueteL1 B)
    (at paqueteL2 A)
    (at paqueteL3 F)
    (at paqueteL4 B)         ; MODIFICACION 1
    (at paqueteP1 D)
    (at paqueteP2 F)
    (at paqueteP3 D)         ; MODIFICACION 1

    (= (distance A A) 0)
    (= (distance A B) 16)
    (= (distance B A) 16)
    (= (distance A C) 20)
    (= (distance C A) 20)
    (= (distance A D) 28)
    (= (distance D A) 28)
    (= (distance A E) 60)
    (= (distance E A) 60)
    (= (distance A F) 84)
    (= (distance F A) 84)
    (= (distance A G) 60)   ; MODIFICACION 1
    (= (distance G A) 70)   ; MODIFICACION 1
    (= (distance B B) 0)
    (= (distance B C) 40)
    (= (distance C B) 40)
    (= (distance B D) 16)
    (= (distance D B) 16)
    (= (distance B E) 24)
    (= (distance E B) 24)
    (= (distance B F) 58)
    (= (distance F B) 58)
    (= (distance B G) 60)   ; MODIFICACION 1
    (= (distance G B) 70)   ; MODIFICACION 1
    (= (distance C C) 0)
    (= (distance C D) 32)
    (= (distance D C) 32)
    (= (distance C E) 56)
    (= (distance E C) 56)
    (= (distance C F) 32)
    (= (distance F C) 32)
    (= (distance C G) 60)   ; MODIFICACION 1
    (= (distance G C) 70)   ; MODIFICACION 1
    (= (distance D D) 0)
    (= (distance D E) 42)
    (= (distance E D) 42)
    (= (distance D F) 40)
    (= (distance F D) 40)
    (= (distance D G) 60)   ; MODIFICACION 1
    (= (distance G D) 70)   ; MODIFICACION 1
    (= (distance E E) 0)
    (= (distance E F) 100)
    (= (distance F E) 100)
    (= (distance E G) 60)   ; MODIFICACION 1
    (= (distance G E) 70)   ; MODIFICACION 1
    (= (distance F F) 0)
    (= (distance F G) 60)   ; MODIFICACION 1
    (= (distance G F) 70)   ; MODIFICACION 1
    (= (distance G G) 0)

    (recharge-point A)
    (recharge-point B)
    (recharge-point C)
    (recharge-point F)
    (recharge-point G)      ; MODIFICACION 1

    (recharge-point-free A)
    (recharge-point-free B)
    (recharge-point-free C)
    (recharge-point-free F)
    (recharge-point-free G) ; MODIFICACION 1

    (zvr A)
    (zvr B)
    (zvr C)
    (zvr G)                 ; MODIFICACION 1
)
(:goal (and
    (at paqueteL1 C)
    (at paqueteL2 B)
    (at paqueteL3 D)
    (at paqueteL4 G)        ; MODIFICACION 1
    (at paqueteP1 F)
    (at paqueteP2 E)
    (at paqueteP3 F)        ; MODIFICACION 1

    (at dronL1 B)
    (at dronL2 B)
    (at dronL3 B)
    (at dronP1 E)
    (at dronP2 E)
    ))

(:metric minimize (+(*0.5 (total-time)) (*0.7 (coste-recargas)))))  ; MODIFICACION 1
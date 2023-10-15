(deftemplate edad
    0 100 anyos
    (
        (joven (10 0) (15 1) (25 1) (30 0))
        (adulta (20 0) (30 1) (60 1) (60 0.7) (70 0))
        (madura (60 0) (70 1))
    )
)

(deftemplate estatura
    0 250 cm
    (
        (bajo (0 1) (100 1) (150 0))
        (medio (100 0) (150 1) (170 1) (180 0))
        (alto (170 0) (180 1))
    )
)

(deftemplate aptitud
    0 10 unidades
    (
        (baja (0 1) (5 0))
        (media (3 0) (4 1) (6 1) (10 0))
        (alta (5 0) (10 1))
    )
)

(defrule ejemplo
    (edad joven)
    (estatura alto)
    =>
    (assert (aptitud alta))
)

(defrule defusificar
    ?f <- (aptitud ?)
    =>
    (bind ?e (maximum-defuzzify ?f))
    (printout t "Aptitud es " ?e crlf)
)

(deffacts fuzzy-fact
    (edad adulta)
    (estatura very alto)
)
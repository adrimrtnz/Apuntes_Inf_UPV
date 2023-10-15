(deftemplate edad   ; variable difusa
    0 120 anos      ; universo
    (
        (infantil (12 1) (20 0))
        (joven (10 0) (15 1) (25 1) (30 0))
        (veinticinco (25 0) (25 1) (25 0))
        (adulta (20 0) (30 1) (60 1) (70 0))
        (mayor (60 0) (70 1))
    )
)

(deftemplate estatura
    0 250 cm
    (
        (bajo (0 1) (100 1) (150 0))
        (muybajito extremely bajo)
        (medio (100 0) (150 1) (170 1) (180 0))
        (alto (170 0) (180 1))
        (muy-alto very alto)
    )
)


(defrule edades
    (edad adulta)
=>
    (printout t "Los adultos son altos" crlf)
    (assert (estatura alto))
)

(deffacts ejemplo (edad veinticinco))
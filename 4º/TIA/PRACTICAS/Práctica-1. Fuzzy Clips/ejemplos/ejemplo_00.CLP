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

(deftemplate edad   ; variable difusa
    0 120 anos      ; universo
    (
        (infantil (12 1) (20 0))
        (joven (10 0) (15 1) (25 1) (30 0))
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

(deftemplate singleton
    0 10 unit
    (
        (tres (3 0) (3 1) (3 0))
        (cinco (5 0) (5 1) (5 0))
    )
)

(deftemplate temperatura
    30 50 grados
    (
        (bajo (35 1) (37 0))
        (medio (35 0) (36 1) (37 0))
        (alto (36 0) (37 1))
    )
)

(deftemplate necesidad-reasfaltado
    0 100 unidades
    (
        (baja (z 10 25))
        (media (pi 15 60))
        (urgente (s 55 90))
    )
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(deffacts ejemplo1
    (edad adulta)
    (estatura very alto)
)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(plot-fuzzy-value t "-*+" 30 50
    (create-fuzzy-value temperatura bajo)
    (create-fuzzy-value temperatura medio)
    (create-fuzzy-value temperatura alto)
)

(plot-fuzzy-value t "-*+" 10 100
    (create-fuzzy-value necesidad-reasfaltado baja)
    (create-fuzzy-value necesidad-reasfaltado media)
    (create-fuzzy-value necesidad-reasfaltado urgente)
)
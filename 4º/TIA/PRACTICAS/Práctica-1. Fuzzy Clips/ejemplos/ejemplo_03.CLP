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


(deftemplate Temp
    5 50 Celsius
    (
        (frio (z 10 20))
        (templado (pi 5 25))
        (calor (s 30 40))
    )
)

(deftemplate valvula
    0 90 grados-apertura
    (
        (poco (z 10 30))
        (medio (pi 30 45))
        (mucho (s 70 80))
    )
)

(defrule hace_frio
    (Temp frio)
=>
    (assert (valvula mucho))
)

(defrule temperatura_buena
    (Temp templado)
=>
    (assert (valvula medio))
)

(defrule hace_calor
    (Temp calor)
=>
    (assert (valvula poco))
)

(deffacts ejemplo
    (Temp very templado)
)

(defrule defuzzificar
    (valvula ?val)
=>
    (printout T "Apertura Valvula por moment: " (moment-defuzzify ?val) crlf)
    (printout T "Apertura Valvula por maximum: " (maximum-defuzzify ?val) crlf)
)
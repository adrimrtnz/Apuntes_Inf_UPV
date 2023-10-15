; lee de consola un valor difuso y lo aserta
(deferule leerconsola
    (initial-fact)
=>
    (printout t "Introduzca la edad: joven, adulta, madura" crlf)
    (bind ?Redad (read))
    (assert-string (format nil "(edad %s)" ?Redad))
)

; lee de consola un valor crisp y aserta su valor fusificado
(defrule leerconsola
    (initial-fact)
=>
    (printout t "Introduzca la edad en anyos" crlf)
    (bind ?Read (read))
    (fuzzify edad ?Redad 0.1)
)

; lee de consola un valor crisp y aserta su valor fusificado con singleton
(defrule leerconsola
    (initial-fact)
=>
    (printout t "Introduzca la edad en anyos" crlf)
    (bind ?Read (read))
    (asert (edad (?Redad 0) (?Redad 1) (?Redad 0)))
)
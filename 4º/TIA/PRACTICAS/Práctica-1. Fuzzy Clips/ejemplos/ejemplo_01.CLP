(deftemplate tanque
    0 80 litros
    (
        (bajo (10 1) (30 0))
        (medio (20 0) (35 1) (45 1) (60 0))
        (alto (50 0) (70 1))
    )
)


(defrule danger
    (tanque extremely alto)
=>
    (printout t "El tanque puede desbordarse. PELIGRO!" crlf)
    (assert (alarma))
)

(assert (tanque plus alto))
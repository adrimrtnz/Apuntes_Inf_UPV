(deftemplate persona
    (slot nombre (type SYMBOL))
    (slot altura (type INTEGER))
    (slot peso (type INTEGER))
    (slot seleccion (type SYMBOL) (default nil))
    (slot vive (type SYMBOL)))


(deffacts
    (persona (nombre david) (altura 184) (vive Valencia))
    (persona (nombre juan) (altura 164) (peso 70) (vive Sevilla))
    (persona (nombre maria) (altura 174) (vive Madrid)))

(defrule seleccion
    ?f <- (persona (nombre ?n) (altura ?a) (vive ?v) (seleccion (nil)))
    (test (> ?a) 175)
    =>
    (printout t "seleccionado " ?n crlf)
    (modify ?f (seleccion si))
)
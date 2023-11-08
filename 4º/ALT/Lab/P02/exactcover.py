# AUTORES:
# Adrián Martínez Martínez - amarmar4

def exact_cover(listaConjuntos, U=None):

    # permitimos que nos pasen U, si no lo hacen lo calculamos:
    if U is None:
        U = set().union(*listaConjuntos) 
    
    def backtracking(sol, cjtAcumulado):
        if len(sol) == len(listaConjuntos):     # Si es completo
            if cjtAcumulado == U:               # Si es factible 
                yield sol
        else:
            cjt = listaConjuntos[len(sol)]
            if cjt.isdisjoint(cjtAcumulado):
                sol.append(1)
                yield from backtracking(sol, cjtAcumulado | cjt)
                sol.pop()
            sol.append(0)
            yield from backtracking(sol, cjtAcumulado)
            sol.pop()  
    yield from backtracking([], set())

if __name__ == "__main__":
    listaConjuntos = [{"casa","coche","gato"},
                      {"casa","bici"},
                      {"bici","perro"},
                      {"boli","gato"},
                      {"coche","gato","bici"},
                      {"casa", "moto"},
                      {"perro", "boli"},
                      {"coche","moto"},
                      {"casa"}]
    for solucion in exact_cover(listaConjuntos):
        print(solucion)

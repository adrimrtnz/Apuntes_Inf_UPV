# AUTORES:
# Adrián Martínez Martínez

listaConjuntos = [{"casa", "coche", "gato"},
                  {"casa", "bici"},
                  {"bici", "perro"},
                  {"boli", "gato"},
                  {"coche", "gato", "bici"},
                  {"casa", "moto"},
                  {"perro", "boli"},
                  {"coche", "moto"},
                  {"casa"}]

def variacionesRepeticion(elementos, cantidad):
    
    def backtracking(sol):
        if len(sol) == cantidad:
            yield sol.copy()
        else:
            for opcion in elementos:
                sol.append(opcion)
                yield from backtracking(sol)
                sol.pop()
                
    yield from backtracking([])

# COMPLETAR las actividades 1 y 2 para permutaciones y combinaciones
def permutaciones(elementos):

    def backtracking(sol):
        if len(sol) == len(elementos):
            yield sol.copy()
        else:
            for opcion in elementos:
                if opcion not in sol:
                    sol.append(opcion)
                    yield from backtracking(sol)
                    sol.pop()
                
    yield from backtracking([])

def combinaciones(elementos, cantidad):

    def backtracking(sol, last_index):
        if len(sol) == cantidad:
            yield sol.copy()
        else:
            for i in range(last_index, len(elementos)):
                opcion = elementos[i]
                if opcion not in sol:
                    sol.append(opcion)
                    yield from backtracking(sol, i+1)
                    sol.pop()
                
    yield from backtracking([], 0)


def exact_cover(lista_conjuntos: list[set], U=None):
    if U is None:
        U = set().union(*lista_conjuntos)

    def backtracking(sol, cjtAcumulado):
        if len(sol) == len(lista_conjuntos):    # Si es completo
            if cjtAcumulado == U:               # Si es factible 
                yield sol
        else:
            cjt = lista_conjuntos[len(sol)]
            if cjt.isdisjoint(cjtAcumulado):
                sol.append(1)
                yield from backtracking(sol, cjtAcumulado | cjt)
                sol.pop()
            sol.append(0)
            yield from backtracking(sol, cjtAcumulado)
            sol.pop()  
    yield from backtracking([], set())


def langford(N: int):
    seq = [0] * 2 * N
    
    def backtracking(num):
        if num <= 0:    # Si es completo
            yield "-".join(map(str, seq))
        else:
            for i in range(len(seq)):
                if seq[i] == 0 and i+1+num <= len(seq)-1 and seq[i+1+num] == 0:
                    seq[i] = num
                    seq[i+1+num] = num
                    yield from backtracking(num-1)
                    seq[i] = 0
                    seq[i+1+num] = 0

    if N%4 in (0, 3):
        yield from backtracking(N)

    
if __name__ == "__main__":
    for n in (1,2,3):
        print('Variaciones con repeticion n =',n)
        for x in variacionesRepeticion(['tomate','queso','anchoas'],n):
            print(x)

        print('\nPermutaciones:')
        for x in permutaciones(['tomate','queso','anchoas']):
            print(x)

        print('\nCombinaciones:')
        for x in combinaciones(['tomate','queso','anchoas', 'aceitunas'], 3):
            print(x)

        print('\nExact Cover:')
        for solucion in exact_cover(listaConjuntos):
            print(solucion)

        print('\nSecuencias de Langford:')
        for i, solucion in enumerate(langford(4)):
            print(f'{1} -> {solucion}')
            # print(solucion)

    # probar las actividades 1 y 2 para permutaciones y combinaciones

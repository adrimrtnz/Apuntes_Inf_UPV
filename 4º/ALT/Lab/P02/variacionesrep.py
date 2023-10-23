# AUTORES:
# (poner aquí el nombre o 2 nombres del equipo de prácticas

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

    # probar las actividades 1 y 2 para permutaciones y combinaciones

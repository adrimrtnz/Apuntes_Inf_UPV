def ejercicio(v, k, W):

    def backtracking(sol, acumulado, ultimo, unos):
        if len(sol) == len(v):
            yield sol.copy(), acumulado
        else:
            if v[ultimo] + acumulado > W or unos >= k:
                sol.append(0)
                yield from backtracking(sol, acumulado, ultimo + 1, unos)
                sol.pop()
            else:
                sol.append(0)
                yield from backtracking(sol, acumulado, ultimo + 1, unos)
                sol.pop()
                sol.append(1)
                acumulado += v[ultimo]
                yield from backtracking(sol, acumulado, ultimo + 1, unos + 1)
                sol.pop()
    yield from backtracking([], 0, 0, 0)

for solucion in ejercicio([10, 3, 12, 3], k=2, W=16):
    print(solucion)
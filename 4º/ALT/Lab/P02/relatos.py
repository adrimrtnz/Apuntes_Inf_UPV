palabras = ["obviamente", "el", "acaso", "lienzo", "oculta", "ese", "entero", "otro"]

def relatos(lista_palabra):

    def backtracking(solucion):
        if len(solucion) == len(lista_palabra):
            yield solucion
        else:
            for palabra in lista_palabra:
                if len(solucion) == 0 or \
                        (palabra not in solucion and palabra[0] == solucion[-1][-1]):
                    solucion.append(palabra)
                    yield from backtracking(solucion)
                    solucion.pop()

    yield from backtracking([])

if __name__ == '__main__':
    for solucion in relatos(palabras):
        print(' '. join(solucion))
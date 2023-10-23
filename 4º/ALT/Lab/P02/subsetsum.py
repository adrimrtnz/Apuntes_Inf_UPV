def subsetSum(valores, obj):
  
  def es_completo(sol):
    return len(sol) == len(valores)
  
  def selecciona(sol):
      return (v for v,s in zip(valores,sol) if s==1)
    
  def es_prometedor(sol):
    known = sum(selecciona(sol))
    return known <= obj and known+sum(valores[len(sol):]) >= obj
  
  def ramificar(sol):
    for opcion in [1,0]:
      yield sol+[opcion]
      
  def backtracking(sol):
    if es_completo(sol):
      yield sol.copy(),list(selecciona(sol))
    else: # es nodo interno, vamos a RAMIFICAR
      for child in ramificar(sol):
        if es_prometedor(child):
          yield from backtracking(child)
          
  yield from backtracking([])

if __name__ == "__main__":    
    valores = [5, 7, 12, 30, 40, 15, 20, 9]
    objetivo = 49
    for x,y in subsetSum(valores, objetivo):
        print(x,y)


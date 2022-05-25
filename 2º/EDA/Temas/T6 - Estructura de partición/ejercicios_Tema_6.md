Todo lo que tenga que ver con **componentes conexas** lo hacemos con **exploración en profundidad** (DFS).

Si es de hayar  **caminos** (más cortos) con **exploración en anchura** (BFS).

Casi todo se hace como una modificación de los métodos `toArrayDFS()`  o del `toArrayBFS()`.



```java
// Ejercicio 4
public boolean esConexo() {
    visitados = new int[numVertices()];
    esConexo(0);
    for(int v = 1; v < numVertices(); v++) {
        if (visitados[i]) == 0) { return false; }
    } 
    return true;
}
protected void esConexo(int v) {
    visitados[v] = 1;
    ListaConPI<Adyacente> l = adyacentesDe(v);

    for(l.inicio(); !l.esFin(); l.siguiente()) {
        int w = l.recuperar().getDestino();     
        if (visitados[w] == 0) { esConexo(w); }  
    }    
}


/* 
 * La siguiente implementación estaría prohibida en el examen por:
 *     1. No es la implementación más óptima
 *     2. Se nos pide implementar el código de la exploración
 */
public boolean esConexo() {
    Arista[] a = prim();
    return a != null;
}
```

```java
// Ejercicio 5
public String toStringCC() {
    visitados = new int[numVertices()];
    String res = "";
    int componentes = 0;    

    for(int v = 1; v < numVertices(); v++) {
        if (visitados[i]) == 0) {
            res += "[" + toStringCC(v) + "]"; 
            componentes++;
        }
    } 
    return cc + " " + res;
}

protected String toStringCC(int v) {
    visitados[v] = 1;
    String res = "" + v;
    ListaConPI<Adyacente> l = adyacentesDe(v);

    for(l.inicio(); !l.esFin(); l.siguiente()) {
        int w = l.recuperar().getDestino();     
        if (visitados[w] == 0) {
            res += " " + toStringCC(w); 
        }  
    }
    return res;
}
```

```java
// Ejercicio 6 mediante DFS
public String spanningTree() {
    visitados = new int[numVertices()];
    ordenVisita = 0;
    String[] res = new String[numVertices() - 1];
    
    spaningTree(0, res);
    
    if (ordenVisita == numVertices() - 1) { return res; }
    return null;
}

protected void spanningTree(int v, String[] res) {
    visitados[v] = 1;
    ListaConPi<Adyacentes> l = adyacentesDe(v);

    for(l.inicio(); !l.esFin(); l.siguiente()) {
        int w = l.recuperar().getDestino();     
        if (visitados[w] == 0) {
            res[ordenVista++] = "(" + v + ", " + w +")"; 
            spanningTree(w, res);
        }  
    }
}
```



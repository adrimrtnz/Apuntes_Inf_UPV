package librerias.grafos;

import librerias.estructurasDeDatos.modelos.ListaConPI; 
import librerias.estructurasDeDatos.lineales.LEGListaConPI;
import librerias.estructurasDeDatos.modelos.Cola;
import librerias.estructurasDeDatos.lineales.ArrayCola;
import librerias.estructurasDeDatos.modelos.ColaPrioridad;
import librerias.estructurasDeDatos.jerarquicos.MonticuloBinario;

/** 
 *  Clase GrafoDirigido
 *  
 *  implementacion de un grafo Dirigido (Ponderado o no) 
 *  mediante Listas de Adyacencia
 */

public class GrafoDirigido extends Grafo {     
    protected int numV; 
    protected int numA;
    protected ListaConPI<Adyacente>[] elArray;
    
    /** Construye un grafo Dirigido vacio con numVertices. 
     *  @param numVertices  Numero de vertices del grafo vacio
     */
    @SuppressWarnings("unchecked")
    public GrafoDirigido(int numVertices) {
        super(true);
        numV = numVertices; 
        numA = 0;
        elArray = new ListaConPI[numVertices]; 
        for (int i = 0; i < numV; i++) 
            elArray[i] = new LEGListaConPI<Adyacente>();
    }
    
    /**
     *  Devuelve el numero de vertices de un grafo. 
     *  @return  int Numero de vertices de un grafo
     */
    public int numVertices() { return numV; }
     
    /**
     *  Devuelve el numero de aristas de un grafo.
     *  @return  int Numero de aristas de un grafo
     */
    public int numAristas() { return numA; }
    
    /** Devuelve una Lista Con PI que contiene 
     *  los adyacentes al vertice i de un grafo.
     *  @param i Vertice del que se obtienen los adyacentes
     *  @return ListaConPI con los vertices adyacentes a i
     */
    public ListaConPI<Adyacente> adyacentesDe(int i) { 
        return elArray[i]; 
    }
    
    /** Comprueba si la arista (i,j) esta en un grafo.
     *  @param i    Vertice origen
     *  @param j    Vertice destino
     *  @return boolean true si (i,j) esta y false en caso contrario
     */
    public boolean existeArista(int i, int j) {
        ListaConPI<Adyacente> l = elArray[i]; 
        for (l.inicio(); !l.esFin(); l.siguiente()) {
            if (l.recuperar().getDestino() == j) { return true; }
        } 
		return false;   
    }
    
    /** Devuelve el peso de la arista (i,j) de un grafo, 
     *  0 si dicha arista no esta en el grafo.
     *  @param i    Vertice origen
     *  @param j    Vertice destino
     *  @return double Peso de la arista (i,j), 0 si no existe.
     */
    public double pesoArista(int i, int j) {
        ListaConPI<Adyacente> l = elArray[i];
        for (l.inicio(); !l.esFin(); l.siguiente()) {
            if (l.recuperar().getDestino() == j) {
                return l.recuperar().getPeso();
            }
        }
        return 0.0;
    }
    
    /** Si no esta, inserta la arista (i, j) en un grafo no Ponderado 
     *  (al principio de la Lista de adyacentes a i).
     *  @param i    Vertice origen
     *  @param j    Vertice destino
     */    
    public void insertarArista(int i, int j) {
        insertarArista(i, j, 1);
    }

    /** Si no esta, inserta la arista (i, j) de peso p en un grafo Ponderado 
     *  (al principio de la Lista de adyacentes a i).
     *  @param i    Vertice origen
     *  @param j    Vertice destino
     *  @param p    Peso de (i, j)
     */ 
    public void insertarArista(int i, int j, double p) {
        if (!existeArista(i, j)) { 
            elArray[i].insertar(new Adyacente(j, p)); 
            numA++; 
        }
    }

    /** Ejemplo 1, pagina 11, tema 6 */
    public int gradoSalida(int i) { 
        return elArray[i].talla(); 
    }

    /** Ejemplo 2, pagina 11, tema 6 */
    public int gradoSalida() { 
        int gradoMax = gradoSalida(0);
        for (int i = 1; i < numV; i++) { 
            int grado = gradoSalida(i); 
            if (grado > gradoMax) gradoMax = grado;
        }
        return gradoMax;
    }

    /** Ejemplo 3, pagina 12, tema 6 */
    public int gradoEntrada(int i) { 
        int grado = 0;
        for (int j = 0;  j < numV;  j++) 
            if (existeArista(j, i)) grado++;  
        return grado;
    }
    
    /** Ejemplo 4, pagina 15, tema 6 */    
    private int[] getArrayGradosEntrada() {
        // crear e inicializar el array de contadores
        int[] gradoEntrada = new int[numV];
        for (int i = 0; i < numV; i++) {
            // actualizar el contador del grado de Entrada
            // de cada vertice de la Lista adyacentesDe(i) 
            ListaConPI<Adyacente> l = elArray[i];
            for ( l.inicio(); !l.esFin(); l.siguiente()) {
                gradoEntrada[l.recuperar().getDestino()]++;
            }
        }
        return gradoEntrada;
    }
    
    public int gradoEntrada() { 
        int[] gradoEntrada = getArrayGradosEntrada();
        // para todo i : 0 <= i < numV : 
        // gradoEntrada[i] es el grado de Entrada de i
        int gradoMax = gradoEntrada[0];
        for (int i = 1; i < numV; i++) { 
            int grado = gradoEntrada[i]; 
            if (grado > gradoMax) gradoMax = grado; 
        }
        return gradoMax;
    }
	
	/** paginas 28 y 29, tema 6 */
    public int[] toArrayDFS() {
        int[] res = new int[numVertices()]; 
        ordenVisita = 0;
        visitados = new int[numVertices()];
        for (int v = 0; v < numVertices(); v++) {  
            if (visitados[v] == 0) toArrayDFS(v, res);
        }
        return res;
    } 
    
    protected void toArrayDFS(int v, int[] res) { 
        res[ordenVisita] = v; 
        ordenVisita++; 
        visitados[v] = 1;
        ListaConPI<Adyacente> l = adyacentesDe(v);
        for (l.inicio(); !l.esFin(); l.siguiente()) {
            int w = l.recuperar().getDestino();
            if (visitados[w] == 0) toArrayDFS(w, res);
        }
    }  
	
	/** paginas 34 y 35, tema 6 */
    public int[] toArrayBFS() {
        int[] res = new int[numVertices()]; 
        visitados = new int[numVertices()];
        ordenVisita = 0; 
        q = new ArrayCola<Integer>(); 
        for (int v = 0; v < numVertices(); v++) { 
            if (visitados[v] == 0) toArrayBFS(v, res); 
        }
        return res;
    }  
    
    protected void toArrayBFS(int v, int[] res) { 
        visitados[v] = 1; 
        res[ordenVisita++] = v; 
        q.encolar(v);
        while (!q.esVacia()) {
            int u = q.desencolar(); 
            ListaConPI<Adyacente> l = adyacentesDe(u);
            for (l.inicio(); !l.esFin(); l.siguiente()) {
                int w = l.recuperar().getDestino();
                if (visitados[w] == 0) { 
                    visitados[w] = 1; 
                    res[ordenVisita++] = w; 
                    q.encolar(w);
                }
            } 
        }
    }
	
	/** paginas 40, 41 y 42, tema 6 */
    // atributos "auxiliares"
    protected double[] distanciaMin; 
    protected int[] caminoMin; 
    protected static final double INFINITO = Double.POSITIVE_INFINITY; 
    
    public void caminosMinimosSinPesos(int v) {
        caminoMin = new int[numVertices()]; 
        distanciaMin = new double[numVertices()];
        for (int i = 0; i < numVertices(); i++) { 
            distanciaMin[i] = INFINITO;
            caminoMin[i] = -1;        
        } 
        distanciaMin[v] = 0;
        q = new ArrayCola<Integer>(); 
        q.encolar(v);
        while (!q.esVacia()) {
            int u = q.desencolar(); 
            ListaConPI<Adyacente> l = adyacentesDe(u);
            for (l.inicio(); !l.esFin(); l.siguiente()) {
                int w = l.recuperar().getDestino();
                if (distanciaMin[w] == INFINITO) { 
                    distanciaMin[w] = distanciaMin[u] + 1; 
                    caminoMin[w] = u; 
                    q.encolar(w);
                }
            }
        }
    }  

    /** paginas 45 y 46, tema 6 */
    
    /** SII v != w AND 0 <= v < numVertices() AND  0 <= w < numVertices() 
     *  devuelve una ListaConPI con los vértices del camino mínimo 
     *  SIN pesos entre v y w, o una lista vacía si tal camino no existe 
     */
    public ListaConPI<Integer> caminoMinimoSinPesos(int v, int w) { 
        caminosMinimosSinPesos(v);
        return decodificarCaminoHasta(w);
    }
    
    // SII 0 <= w < numVertices()
    // devuelve una ListaConPI con los vértices del camino hasta w 
    protected ListaConPI<Integer> decodificarCaminoHasta(int w) {
        ListaConPI<Integer> res = new LEGListaConPI<Integer>();
        if (distanciaMin[w] != INFINITO) {
            res.insertar(w);
            for (int v = caminoMin[w]; v != -1; v = caminoMin[v]) {
                res.inicio();
                res.insertar(v);
            }
        }        
        return res;
    }

    /** paginas 47, 53 y 54, tema 6 */
    
    /** SII v != w AND 0 <= v < numVertices() AND  0 <= w < numVertices() 
     *  devuelve una ListaConPI con los vértices del camino 
     *  mínimo CON pesos entre v y w, o una lista vacía si
     *  tal camino no existe */
    public ListaConPI<Integer> caminoMinimo(int v, int w) { 
        dijkstra(v);
        return decodificarCaminoHasta(w);
    }
    
    public void dijkstra(int u) {
        distanciaMin = new double[numVertices()]; 
        caminoMin = new int[numVertices()];        
        for (int i = 0; i < numVertices(); i++) {
            distanciaMin[i] = INFINITO; 
            caminoMin[i] = -1; 
        }
        distanciaMin[u] = 0;
        visitados = new int[numVertices()];
        ColaPrioridad<VerticeCoste> qP;
        qP = new MonticuloBinario<VerticeCoste>(); 
        qP.insertar(new VerticeCoste(u, 0));
        // mientras haya vertices por explorar
        while (!qP.esVacia()) { 
            // siguiente vertice a explorar es el de menor distancia
            int v = qP.eliminarMin().codigo;
            if (visitados[v] == 0) { // evitar repeticiones
                visitados[v] = 1; 
                // recorrer vertices adyacentes de v
                ListaConPI<Adyacente> l = adyacentesDe(v);
                for (l.inicio(); !l.esFin(); l.siguiente()) {
                    int  w = l.recuperar().destino;
                    double costeW = l.recuperar().peso;
                    // ¿ mejor forma de alcanzar w es a traves de v ?
                    if (distanciaMin[w] > distanciaMin[v] + costeW) {
                        distanciaMin[w] = distanciaMin[v] + costeW; 
                        caminoMin[w] = v;
                        qP.insertar(new VerticeCoste(w, distanciaMin[w]));  
                    }
                }
            }
        }
    }
	
	/** pagina 60, tema 6 */
    /* SII el Grafo es un DAG */
    public int[] ordenTopologicoDFS() {
        int[] res = new int[numVertices()]; 
        ordenVisita = 0;
        visitados = new int[numVertices()];
        for (int v = 0; v < numVertices(); v++) {
            if (visitados[v] == 0) ordenTopologicoDFS(v, res);  
        }
        return res;
    }
    
    protected void ordenTopologicoDFS(int v, int[] res) { 
        visitados[v] = 1;
        ListaConPI<Adyacente> l = adyacentesDe(v);
        for (l.inicio(); !l.esFin(); l.siguiente()) {
            int w = l.recuperar().getDestino();
            if (visitados[w] == 0) ordenTopologicoDFS(w, res);         
        }
        visitados[v] = 2;
        res[numVertices() - 1 - ordenVisita] = v; 
        ordenVisita++;
    }  

    /** pagina 64, tema 6 */
    // SII el Grafo es un Digrafo ...
    public boolean hayCicloDFS() {
        boolean ciclo = false; 
        visitados = new int[numVertices()];
        for (int v = 0; v < numVertices() && !ciclo; v++) 
            if (visitados[v] == 0) ciclo = hayAristaHADFS(v); 
        return ciclo;
    }
    
    protected boolean hayAristaHADFS(int v) { 
        boolean aristaHA = false; 
        visitados[v] = 1;
        ListaConPI<Adyacente> l = adyacentesDe(v);
        for (l.inicio(); !l.esFin() && !aristaHA; l.siguiente()) {
            int w = l.recuperar().getDestino();
            if (visitados[w] == 0) aristaHA = hayAristaHADFS(w); 
            else if (visitados[w] == 1) aristaHA = true;          
        }
        visitados[v] = 2;
        return aristaHA;
    }  

    /** paginas 65 y 66, tema 6 */
    // SII el Grafo es Dirigido ...
    public int[] hayCicloyOrdenTopologicoDFS() {
        int[] res = new int[numVertices()]; 
        ordenVisita = 0; 
        visitados = new int[numVertices()]; 
        boolean ciclo = false; 
        for (int v = 0; v < numVertices() && !ciclo; v++) {
            if (visitados[v] == 0) ciclo = hayCicloyOrdenTopologicoDFS(v, res); 
        }
        if (!ciclo) return res; 
        return null; 
    }
    
    protected boolean hayCicloyOrdenTopologicoDFS(int v, int[] res) { 
        boolean aristaHA = false; 
        visitados[v] = 1; 
        ListaConPI<Adyacente> l = adyacentesDe(v);
        for (l.inicio(); !l.esFin() && !aristaHA; l.siguiente()) {
            int w = l.recuperar().getDestino();
            if (visitados[w] == 0) {
                aristaHA = hayCicloyOrdenTopologicoDFS(w, res);
            }
            else if (visitados[w] == 1) {
                aristaHA = true;
            }
        }
        visitados[v] = 2;
        res[numVertices() - 1 - ordenVisita] = v; 
        ordenVisita++;
        return aristaHA;
    }	
}
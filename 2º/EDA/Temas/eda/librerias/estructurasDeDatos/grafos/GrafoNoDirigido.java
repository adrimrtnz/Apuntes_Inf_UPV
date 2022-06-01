package librerias.estructurasDeDatos.grafos;

import librerias.estructurasDeDatos.modelos.ListaConPI; 

/** 
 *  Clase GrafoNoDirigido
 *  
 *  implementacion de un grafo No Dirigido (Ponderado o no) 
 *  mediante Listas de Adyacencia
 *  
 *  un grafo No Dirigido ES UN Grafo Dirigido tal que 
 *  si la Arista (i, j) está presente en la Lista de Adyacencia de i 
 *  entonces también lo está la Arista (j, i) en la de j
 */

public class GrafoNoDirigido extends GrafoDirigido {
    
    /** Construye un grafo No Dirigido vacio con numVertices. 
     *  @param numVertices  Numero de vertices del grafo vacio
     */
    public GrafoNoDirigido(int numVertices) { 
        super(numVertices); 
        esDirigido = false;
    }
    
    /** Si no esta, inserta la arista (i, j) en un grafo 
     *  No Dirigido y No Ponderado; 
     *  por tanto, tambien inserta la arista (j, i).
     *  @param i    Vertice origen
     *  @param j    Vertice destino
     */ 
    public void insertarArista(int i, int j) {
        insertarArista(i, j, 1);
    }
    
    /** Si no esta, inserta la arista (i, j) de peso p en un grafo 
     *  No Dirigido y Ponderado; 
     *  por tanto, tambien inserta la arista (j, i) de peso p.
     *  @param i    Vertice origen
     *  @param j    Vertice destino
     *  @param p    Peso de (i, j)
     */ 
    public void insertarArista(int i, int j, int p) {
        if (!existeArista(i, j)) { 
            elArray[i].insertar(new Adyacente(j, p)); 
            elArray[j].insertar(new Adyacente(i, p));
            numA++; 
        }
    }
    
    /** Ejemplo 3, pagina 12, tema 6 */
    public int gradoEntrada(int i) {
        return gradoSalida(i);
    }
    
    ////////////////////////////////////////////////////////////////////
    //                         EJERCICIOS                             //
    ////////////////////////////////////////////////////////////////////
    
    public int getVerticeReceptivo() {
        for (int i = 0; i < numV; i++) {
            if (elArray[i].talla() == numV - 1) { return i; }
        }
        
        return -1;
    }
    
    public boolean esSumidero(int i) { return false; }
    public int getSumideroU() { return -1; }
    
    public boolean esCompleto() {
        return 2 * numA == numV * (numV - 1);   
    }
    
    public boolean esConexo() {
        visitados = new int[numVertices()];
        ordenVisita = 0;
        
        recorridoDFS(0);
        
        /* // Versión menos eficiente
        for (int i = 0; i < numVertices(); i++) {
            if (visitados[i] == 0) { return false; }
        }
        */
        
        return ordenVisita == numVertices();
    }
    
    protected void recorridoDFS(int v) {
        visitados[v] = 1;
        ordenVisita++;
        ListaConPI<Adyacente> l = adyacentesDe(v);
        
        for (l.inicio(); !l.esFin(); l.siguiente()) {
            int w = l.recuperar().getDestino();
            
            if (visitados[w] == 0) {
                recorridoDFS(w);
            }
        }
    }
    
    public String toStringCC() {
        String res = "";
        int cc = 0;
        visitados = new int[numVertices()];
        
        for (int v = 0; v < numVertices(); v++) {
            if (visitados[v] == 0) {
                cc++;
                res += "[" + toStringCC(v) + "] ";
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
                res += " " + toStringCC(w);;
            }
        }
        
        return res;
    }
    
    public String[] spanningTree() {
        String[] sTree = new String[numVertices() - 1];
        visitados = new int[numVertices()];
        ordenVisita = 0;
        
        spanningTree(0, sTree);
        
        if (ordenVisita != numVertices() - 1) { return null; }
        return sTree;
    }
    
    protected void spanningTree(int v, String[] sTree) {
        visitados[v] = 1;
        ListaConPI<Adyacente> l = adyacentesDe(v);
        
        for (l.inicio(); !l.esFin(); l.siguiente()) {
            int w = l.recuperar().getDestino();
            
            if (visitados[w] == 0) {
                sTree[ordenVisita++] = "(" + v + ", " + w + ")";
                spanningTree(w, sTree);
            }
        }
    }
}
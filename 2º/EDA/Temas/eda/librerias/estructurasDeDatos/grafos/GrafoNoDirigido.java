package librerias.estructurasDeDatos.grafos;

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
}
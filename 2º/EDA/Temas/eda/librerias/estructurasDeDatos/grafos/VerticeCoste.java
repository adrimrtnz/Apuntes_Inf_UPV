package librerias.estructurasDeDatos.grafos;

/**
 *  Clase VerticeCoste
 * 
 *  Clase auxiliar, usada en el algoritmo de Dijkstra (pagina 53, tema 6)
 *  Entradas para la cola de prioridad: pares (codigo vertice, coste)
 */

class VerticeCoste implements Comparable<VerticeCoste> {
    protected int codigo;   // Codigo del vertice
    protected double coste; // Coste minimo para alcanzar dicho vertice
  
    // Constructor
    public VerticeCoste(int cod, double cost) { 
        codigo = cod; 
        coste = cost; 
    }
  
    // Establece la prioridad: un vertice es mas prioritario que otro
    // si el coste de alcanzarlo es menor
    public int compareTo(VerticeCoste v) {
        if (coste < v.coste) { return -1; }
        if (coste > v.coste) { return 1; }
        return 0;
    }
}
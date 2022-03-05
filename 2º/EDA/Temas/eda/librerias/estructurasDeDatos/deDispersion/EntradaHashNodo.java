package librerias.estructurasDeDatos.deDispersion;

/**
 * Nodo de una Lista Enlazada Directa 
 * con la que se implementa una cubeta de una TablaHash: 
 * TIENE la clave y el valor de una Entrada 
 * y TIENE una referencia al siguiente nodo
 */

class EntradaHashNodo<C, V> {    
    protected C clave;
    protected V valor;
    protected EntradaHashNodo<C, V> siguiente;
    
    public EntradaHashNodo(C c, V v, EntradaHashNodo<C, V> s) {
        clave = c;
        valor = v;
        siguiente = s;
    }
    
    public String toString() { 
        return "(" + clave + ", " + valor + ")"; 
    }
} 
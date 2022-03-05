package librerias.estructurasDeDatos.deDispersion;

/**
 * Nodo de una Lista con PI 
 * con la que se implementa una cubeta de una TablaHash: 
 * TIENE la clave y el valor de una Entrada
 */

class EntradaHash<C, V> {    
    protected C clave;
    protected V valor;

    EntradaHash(C c, V v) {
        clave = c;
        valor = v;
    }
    
    public String toString() { 
        return "(" + clave + ", " + valor + ")"; 
    }
}
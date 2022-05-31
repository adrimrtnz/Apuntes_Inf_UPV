package librerias.estructurasDeDatos.modelos;

/**
 * Modelo Diccionario Ordenado SIN claves repetidas, o Map Ordenado:  
 * Busqueda Dinamica de una Entrada de Clave dada, para recuperar el 
 * Valor asociado a esta. 
 * @param <C>, el tipo de sus claves
 * @param <V>, el tipo de sus valores
 * @version Abril 2016
 */

public interface MapOrdenado<C extends Comparable<C>, V> extends Map<C, V> {
    
    /** SII !esVacio(): 
     *  recupera la Entrada de Clave minima de un Map Ordenado */
    EntradaMap<C, V> recuperarEntradaMin();
    /** SII !esVacio(): recupera la Clave minima de un Map Ordenado */
    C recuperarMin();   
   
    /** SII !esVacio(): 
     *  recupera la Entrada de Clave maxima de un Map Ordenado */
    EntradaMap<C, V> recuperarEntradaMax();
    /** SII !esVacio(): recupera la Clave maxima de un Map Ordenado */
    C recuperarMax(); 

    /** SII !esVacio(): recupera la Entrada siguiente a c
     *  segun el orden establecido entre claves */
    EntradaMap<C, V> sucesorEntrada(C c);  
    /** SII !esVacio(): recupera la clave siguiente a c
     *  segun el orden establecido entre claves */
    C sucesor(C c); 
    
    /** SII !esVacio(): recupera la Entrada anterior a c
     *  segun el orden establecido entre claves */
    EntradaMap<C, V> predecesorEntrada(C c);  
    /** SII !esVacio(): recupera la clave anterior a c
     *  segun el orden establecido entre claves */
    C predecesor(C c); 
    
    /** SII !esVacio(): 
     * elimina y devuelve la Entrada de Clave minima de un Map Ordenado */
    EntradaMap<C, V> eliminarEntradaMin();
    /** SII !esVacio(): 
     *  elimina y devuelve la Clave minima de un Map Ordenado */
    C eliminarMin();
}
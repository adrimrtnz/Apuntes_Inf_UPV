package librerias.estructurasDeDatos.modelos;

/** Representa una Entrada de un MapOrdenado:
 * @param <C>, el tipo de sus claves: cualquier tipo que implemente Comparable 
 * @param <V>, el tipo de sus valores
 * @version Abril 2016
 */

public class EntradaMap<C extends Comparable<C>, V>  
    implements Comparable<EntradaMap<C, V>> {
    
    // Una entrada de un Map Ordenado TIENE UNA
    private C clave;
    // Una entrada de un Map Ordenado TIENE UN 
    private V valor;
   
    /** crea una Entrada (c, v) de un Map Ordenado */
    public EntradaMap(C c, V v) {
        clave = c; 
        valor = v; 
    }
   
    /** devuelve la clave de una Entrada de un Map Ordenado */
    public C getClave() { return clave; }
   
    /** devuelve el valor de una Entrada de un Map Ordenado */
    public V getValor() { return valor; }
   
    /** actualiza a nueva la clave de una Entrada de un Map Ordenado */
    public void setClave(C nueva) { clave = nueva; }
   
    /** actualiza a nuevo el valor de una Entrada de un Map Ordenado */
    public void setValor(V nuevo) { valor = nuevo; }
    
    /** comprueba si una Entrada es igual a otra, 
     *  i.e. si son iguales sus claves */
    @SuppressWarnings("unchecked")
    public boolean equals(Object otra) {
        return this.clave.equals(((EntradaMap<C,V>) otra).clave);
    }

    /** devuelve el resultado de la comparacion de una Entrada con otra, 
     *  i.e. de la comparacion de sus claves */
    public int compareTo(EntradaMap<C, V> otra) {
        return clave.compareTo(otra.clave);
    }
   
    /** devuelve un String que representa una Entrada de un Map Ordenado
     *  con un cierto formato, i.e. el del par formado por su clave y valor 
     */
    public String toString() { 
        return "(" + this.clave + ", " + this.valor + ")"; 
    }
}
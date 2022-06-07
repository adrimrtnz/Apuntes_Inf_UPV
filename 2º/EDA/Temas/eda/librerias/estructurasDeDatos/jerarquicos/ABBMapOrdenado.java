package librerias.estructurasDeDatos.jerarquicos; 

import  librerias.estructurasDeDatos.modelos.MapOrdenado; 
import  librerias.estructurasDeDatos.modelos.EntradaMap; 
import  librerias.estructurasDeDatos.modelos.ListaConPI;
import  librerias.estructurasDeDatos.lineales.LEGListaConPI;
 
/** Clase que implementa un MapOrdenado utilizando un ABB
  * @param <C>, la clase de las claves del MapOrdenado que implementa,
  *             y que debe ser Comparable
  * @param <V>, la clase de los valores del MapOrdenado que implementa             
  */
 
public class ABBMapOrdenado<C extends Comparable<C>, V> implements MapOrdenado<C, V> {
    
    // Un ABBMapOrdenado TIENE UN...
    protected ABB<EntradaMap<C, V>> abb;
    
    /** crea un Map Ordenado vacio, con talla 0 */
    public ABBMapOrdenado() { abb = new ABB<EntradaMap<C, V>>(); }
    
    /** Sobrescribe el metodo de Map: 
     *  comprueba si un Map esta vacio 
     */
    public boolean esVacio() { return abb.esVacio(); }
   
    /** Sobrescribe el metodo de Map: 
     *  devuelve la talla, o numero de Entradas, de un Map 
     */
    public int talla() { return abb.talla(); }
    
    /** Sobrescribe el metodo de Map:
     *  devuelve el valor asociado a la clave c en un Map,
     *  null si no existe una Entrada con dicha clave
     */
    public V recuperar(C c) { 
        EntradaMap<C, V> e = abb.recuperar(new EntradaMap<C, V>(c, null)); 
        if (e == null) { return null; }
        return e.getValor();
    }
   
    /** Sobrescribe el metodo de Map:
     *  inserta la Entrada (c, v) en un Map y devuelve null; si ya
     *  existe una Entrada de Clave c en el Map, devuelve su valor 
     *  asociado y lo substituye por v (o actualiza la Entrada)
     */
    public V insertar(C c, V v) {
        EntradaMap<C, V> e = abb.recuperar(new EntradaMap<C, V>(c, null));
        abb.insertar(new EntradaMap<C, V>(c, v));
        if (e == null) { return null; }
        return e.getValor();
    } 
   
    /** Sobrescribe el metodo de Map:
     *  elimina la Entrada con Clave c de un Map y devuelve su 
     *  valor asociado, null si no existe una Entrada con tal clave
     */
    public V eliminar(C c) {
        EntradaMap<C, V> e = abb.recuperar(new EntradaMap<C, V>(c, null));
        abb.eliminar(new EntradaMap<C, V>(c, null));
        if (e == null) { return null; }
        return e.getValor();
    } 
   
    /** Sobrescribe el metodo de Map:
     * devuelve una ListaConPI con las talla() Claves de un Map 
     */
    public ListaConPI<C> claves() {
        ListaConPI<EntradaMap<C, V>> lpi = abb.toListaConPI();
        ListaConPI<C> res = new LEGListaConPI<C>();
        for (lpi.inicio(); !lpi.esFin(); lpi.siguiente()) {
            res.insertar(lpi.recuperar().getClave()); 
        }
        return res;
    } 
    
    // METODOS PROPIOS, POR EFICIENTES, DE UN MAP ORDENADO ****
   
    /** SII !esVacio(): recupera la Entrada de Clave minima de un Map */
    public EntradaMap<C, V> recuperarEntradaMin() {
        return abb.recuperarMin();
    }   

    /** SII !esVacio(): recupera la Clave minima de un Map */
    public C recuperarMin() {
        return abb.recuperarMin().getClave();
    }
   
    /** SII !esVacio(): recupera la Entrada de Clave maxima de un Map */
    public EntradaMap<C, V> recuperarEntradaMax() {
        return abb.recuperarMax();
    }   

    /** SII !esVacio(): recupera la Clave maxima de un Map */
    public C recuperarMax() {
        return abb.recuperarMax().getClave();
    }
    
    /** SII !esVacio(): recupera la Entrada siguiente a c
     *  segun el orden establecido entre claves, null si no existe */
    public EntradaMap<C, V> sucesorEntrada(C c) {
        return abb.sucesor(new EntradaMap<C, V>(c, null));
    }
    
    /** SII !esVacio(): recupera la Clave siguiente a c
     *  segun el orden establecido entre claves, null si no existe */
    public C sucesor(C c) {
        EntradaMap<C, V> eSuc = abb.sucesor(new EntradaMap<C, V>(c, null));
        if (eSuc == null) { return null; }
        return eSuc.getClave();
    }
    
    /** SII !esVacio(): recupera la Entrada anterior a c
     *  segun el orden establecido entre claves, null si no existe */
    public EntradaMap<C, V> predecesorEntrada(C c) {
        return abb.predecesor(new EntradaMap<C, V>(c, null));
    }
    
    /** SII !esVacio(): recupera la clave anterior a c
     *  segun el orden establecido entre claves, null si no existe */
    public C predecesor(C c) {
        EntradaMap<C, V> ePred = abb.predecesor(new EntradaMap<C, V>(c, null));
        if (ePred == null) { return null; }
        return ePred.getClave();
    }
   
    /** SII !esVacio(): 
     *  elimina y devuelve la Entrada de Clave minima de un Map Ordenado */
    public EntradaMap<C, V> eliminarEntradaMin() {
        return abb.eliminarMin();
    }
   
    /** SII !esVacio(): 
     *  elimina y devuelve la Clave minima de un Map Ordenado */
    public C eliminarMin() {
        return abb.eliminarMin().getClave();
    }
    
    /** devuelve el String con las Entradas de un Map ordenadas por clave */
    public String toString() { 
        return abb.toStringInOrden(); 
    }
}
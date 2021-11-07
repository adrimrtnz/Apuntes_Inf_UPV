
/**
 * interface Coleccion
 * 
 * @author LTP 
 * @version 2021-22
 */

public interface Coleccion<T> {
    void add(T e);                  /** Inserta un elemento en la coleccion */
    T remove();                     /** Devuelve y borra un elemento de la coleccion */
    int size();                     /** Devuelve el numero de elementos de la coleccion */
    boolean isEmpty();              /** Comprueba si la coleccion esta vacia */
    boolean isGreater(Coleccion c); /** Comprueba si la coleccion tiene mas elementos que c */
    String aCadena();               /** Convierte la coleccion a cadena de texto */
    boolean pertenece(T e);
}
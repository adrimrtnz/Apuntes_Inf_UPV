
/**
 * interface Vector
 * 
 * @author LTP
 * @version 2021-22
 */

public interface Vector<T> extends Coleccion<T> {
    void addPos(int i, T e); /** Inserta un elemento en una posicion */
    T removePos(int i);      /** Devuelve y borra el elemento en una posicion */
    T getPos(int i);         /** Devuelve el elemento en una posicion */
}
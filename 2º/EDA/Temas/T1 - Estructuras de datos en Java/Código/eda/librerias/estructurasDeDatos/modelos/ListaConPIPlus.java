package librerias.estructurasDeDatos.modelos;

public interface ListaConPIPlus<E> extends ListaConPI<E> {
    
    /** comprueba si el Elemento e esta en una Lista Con PI **/
    boolean contiene(E e);    
    
    /** elimina la primera aparicion del Elemento e en una Lista Con PI 
     *  y devuelve true, o devuelve false si e no esta en la Lista
     */
    boolean eliminarPrimero(E e);
    
    /** si el Elemento e esta en una Lista Con PI elimina su ultima aparicion
     *  y devuelve true, o devuelve false si e no esta en la Lista 
     */
    boolean eliminarUltimo(E e);
    
    /** si el Elemento e esta en una Lista Con PI elimina todas sus apariciones,
     *  y devuelve true, o devuelve false si e no esta en la Lista 
     */
    boolean eliminarTodos(E e);
    
    /** elimina todos los Elementos de una Lista Con PI **/
    void vaciar();
    
    /** concatena una Lista Con PI con otra **/
    void concatenar(ListaConPI<E> otra);
    
    /** desplaza todos los elementos de la lista una posición hacia la derecha,
     *  de forma que el último elemento deberá pasar a ser el primero
     */
    void moverADerecha();

    /** desplaza todos los elementos de la lista una posición hacia la izquierda,
     *  de forma que el primer elemento deberá pasar a ser el último 
     */
    void moverAIzquierda();

    /** invierte in-situ una Lista a partir de su PI **/
    void invertirDesdePI();
}
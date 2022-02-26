package librerias.estructurasDeDatos.modelos;

public interface Lista<E> {
// metodos Modificadores del estado de la Lista:
    /** SII 0<=i<=talla(): 
     * inserta el elemento e en la posicion i de una Lista 
     */
    void insertar(E e, int i);
    
    /** SII 0<=i<talla(): 
     * elimina el elemento que ocupa la posicion i de una Lista 
     */
    void eliminar(int i);
    
// metodos Consultores del estado de la Lista:
    /** SII 0<=i<talla(): 
     * devuelve el elemento que ocupa la posición ide una Lista 
     */
    E recuperar(int i);
    
    /** comprueba si una Lista esta vacia 
     */
    boolean esVacia();
    
    /** devuelve la talla de una Lista, o su numero de elementos 
     */
    int talla();
}
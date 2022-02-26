package librerias.estructurasDeDatos.modelos;

public interface ListaConPIPlusMap<E> extends ListaConPI<E> {
    /** elimina los elementos repetidos de una ListaConPI, 
     *  dejando únicamente su 1ª aparición */
    void eliminarRepetidos(); 
    
    /** elimina los elementos de una ListaConPI que están en otra **/
    void diferencia(ListaConPI<E> otra);
} 
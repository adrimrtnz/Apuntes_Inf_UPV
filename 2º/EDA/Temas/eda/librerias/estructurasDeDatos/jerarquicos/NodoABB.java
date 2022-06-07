package librerias.estructurasDeDatos.jerarquicos;

/** Clase friendly NodoABB<E>: representa un Nodo de un ABB, por lo que
 *  TIENE UN: 
 *  1.- E dato, que representa el Elemento que ocupa un Nodo de un ABB 
 *  2.- NodoABB<E> izq, un enlace al Hijo Izquierdo de un Nodo de un ABB
 *  3.- NodoABB<E> der, un enlace al Hijo Derecho de un Nodo de un ABB
 *  4.- talla, un entero que representa el tamanyo de un Nodo de un ABB
 *      Un ABB que tiene Nodos con este atributo se denomina ABB con Rango
 *      
 *  @param <E>, el tipo de los datos del ABB
 *  @version (Abril 2016)
 **/
 
class NodoABB<E> {
    // un Nodo de un ABB TIENE UN
    protected E dato; 
    protected NodoABB<E> izq, der;
    protected int talla;

    /** construye el Nodo Hoja e de un ABB, i.e. un Nodo con dato e, 
        tamanyo 1 y sin hijos **/
    NodoABB(E e) {
        dato = e; 
        izq = null;
        der = null;
        talla = 1;
    }
}

package librerias.estructurasDeDatos.lineales;

import librerias.estructurasDeDatos.modelos.*;

public class LEGLista<E> implements Lista<E> {

    protected NodoLEG<E> primero;
    protected int talla;
    
    /** construye una Lista vacia, de talla cero **/
    public LEGLista() {
        primero = null;
        talla = 0;
    }
    
    /** SII 0<=i<=talla(): 
     *  inserta el elemento e en la posicion i de una Lista 
     */
    public void insertar(E e, int i) {
        NodoLEG<E> nuevo = new NodoLEG<E>(e); 
        talla++;
        NodoLEG<E> aux = primero;
        NodoLEG<E> ant = null; 
        for (int j = 0; j < i; j++) {
            ant = aux; 
            aux = aux.siguiente;
        }   
        nuevo.siguiente = aux;
        if (ant == null) primero = nuevo;
        else ant.siguiente = nuevo;
    }
    
    /** SII talla()>0 AND 0<=i<talla(): 
     *  elimina el elemento que ocupa la posicion i de una Lista 
     */
    public void eliminar(int i) {
        talla--;
        NodoLEG<E> aux = primero;
        NodoLEG<E> ant = null;
        for (int j = 0; j < i; j++) {
            ant = aux; 
            aux = aux.siguiente;
        }   
        if (ant == null) primero = aux.siguiente;   
        else ant.siguiente = aux.siguiente;
    }
     
    /** SII talla()>0 AND 0<=i<talla(): 
     *  devuelve el elemento que ocupa la i-esima posicion de una Lista 
     */
    public E recuperar(int i) {
        NodoLEG<E> aux; 
        int j;
        for (aux = primero, j = 0; j < i; aux = aux.siguiente, j++); 
        return aux.dato;
    }
    
    /** comprueba si una Lista esta vacia **/
    public boolean esVacia() { 
        return primero == null; 
        //alternativamente: return talla == 0;
    }
    
    /** devuelve la talla de una Lista **/
    public int talla() { return this.talla; }
    
    /** devuelve el String con los elementos de una Lista en orden de insercion
     *  y con el formato que se usa en el estandar de Java
     *  Asi, por ejemplo, si se tiene una Lista con los Integer del 1 al 4, en 
     *  orden de inserción, toString devuelve [1, 2, 3, 4]; 
     *  si la Lista esta vacia, entonces devuelve [] 
     */
    public String toString() { 
        StringBuilder res = new StringBuilder();
        res.append("[");
        if (talla == 0) return res.append("]").toString();
        NodoLEG<E> aux = primero; 
        for (int i = 0, j = talla - 1; i < j; i++, aux = aux.siguiente)
            res.append(aux.dato.toString() + ", ");
        res.append(aux.dato.toString() + "]"); 
        return res.toString();
    }
}
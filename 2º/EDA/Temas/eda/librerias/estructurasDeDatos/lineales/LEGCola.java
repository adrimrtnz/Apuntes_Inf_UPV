package librerias.estructurasDeDatos.lineales;

import librerias.estructurasDeDatos.modelos.*;

/**
 * Write a description of class LEGCola here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class LEGCola<E> implements Cola<E>
{
    protected NodoLEG<E> primero;
    protected NodoLEG<E> ultimo;
    protected int talla;
    
    @SuppressWarnings("unchecked")
    public LEGCola() 
    {
        primero = null;
        ultimo = null;
        talla = 0;
    }
    
    public void encolar(E e) {
        NodoLEG<E> nuevo = new NodoLEG<E>(e); 
        
        if (talla++ == 0) {
            primero = ultimo = nuevo;
        }
        else {
            ultimo.siguiente = nuevo;
            ultimo = nuevo;
        }
    }
    
    /** SII !esVacia(): 
     *  obtiene y elimina de una Cola el Elemento que ocupa su principio **/ 
    // principio se incrementa circularmente 
    public E desencolar() {
        if (esVacia()) return (E) primero;
        
        talla--;
        NodoLEG<E> aux = primero; 
        primero = primero.siguiente;
        
        return (E) aux;
    }
    
    /** SII !esVacia(): 
     *  obtiene el Elemento que ocupa el principio de una Cola,  
     *  el primero en orden de insercion **/
    public E primero() { return (E) primero; }
    
    /** comprueba si una Cola esta vacia **/
    public boolean esVacia() { return talla == 0; }
    
   /** obtiene un String con los Elementos de una Cola en orden FIFO, 
    *  o de insercion, y con el formato que se usa en el estandar de Java. 
    *  Asi, por ejemplo, si se tiene una Cola con los Integer del 1 al 4, 
    *  en orden FIFO, toString devuelve [1, 2, 3, 4]; 
    *  si la Cola esta vacia, entonces devuelve [] 
    */
    // OJO: se contempla la circularidad de elArray no solo usando el metodo
    // incrementar, sino contando el numero de Elementos desde 0 hasta talla-1
    public String toString() {
        String res = "";
        
        NodoLEG<E> aux = primero; 
        if (aux != null) { res += aux.dato.toString(); }
        else return res;
        aux = aux.siguiente;
        
        while(aux != null) {
            res += ", "+ aux.dato.toString() ;
            aux = aux.siguiente;
        }        
        
        return res;
    }
}

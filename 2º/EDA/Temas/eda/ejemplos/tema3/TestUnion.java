package ejemplos.tema3;

import librerias.estructurasDeDatos.modelos.*; 
import librerias.estructurasDeDatos.lineales.*; 
import librerias.estructurasDeDatos.deDispersion.*; 

public class TestUnion {

    public static <E> String unionPar(ListaConPI<E> l1, ListaConPI<E> l2) {
        ListaConPI<Par> aux = new LEGListaConPI<Par>();
        for (l1.inicio(); !l1.esFin(); l1.siguiente()) {
            E e = l1.recuperar();
            for (aux.inicio(); 
                !aux.esFin() && !e.equals(aux.recuperar().dato); 
                aux.siguiente());
            if (aux.esFin()) { aux.insertar(new Par(e, 1)); } 
            else { aux.recuperar().frec++; }
        }
        for (l2.inicio(); !l2.esFin(); l2.siguiente()) {
            E e = l2.recuperar();
            for (aux.inicio(); 
                !aux.esFin() && !e.equals(aux.recuperar().dato); 
                aux.siguiente());
            if (aux.esFin()) { aux.insertar(new Par(e, 1)); }
            else { aux.recuperar().frec++; }
        }
        return aux.toString();
    }
    
    public static <E> String unionMap(ListaConPI<E> l1, ListaConPI<E> l2) {
        // COMPLETAR
    }
}
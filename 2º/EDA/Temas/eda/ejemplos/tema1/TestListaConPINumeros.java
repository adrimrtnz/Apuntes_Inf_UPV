package ejemplos.tema1;

import librerias.estructurasDeDatos.modelos.ListaConPI;
import librerias.estructurasDeDatos.lineales.LEGListaConPI;

public class TestListaConPINumeros {
    public static void main(String[] args){     
        ListaConPI<Integer> l = new LEGListaConPI<Integer>();        
        
        l.insertar(1);
        // l.siguiente(); // daría error
        l.insertar(new Integer(2));
        l.insertar(3);
        l.insertar(5);
        l.insertar(6);
        
        System.out.println(l.toString());
        System.out.println("Se va a eliminar el primer elemento.");
        l.inicio();
        l.eliminar();
        System.out.println(l.toString());
        System.out.println(l.esFin());
        
        System.out.println("Vamos a buscar el número 5 e insertamos el 4 antes.");
        
        for(l.inicio(); !l.esFin() && !l.recuperar().equals(5); l.siguiente());
        l.insertar(new Integer(4));
        
        System.out.println(l.toString());
    }
}

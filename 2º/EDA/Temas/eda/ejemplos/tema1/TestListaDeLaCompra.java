package ejemplos.tema1;

import librerias.estructurasDeDatos.modelos.Lista;
import librerias.estructurasDeDatos.lineales.LEGLista;

public class TestListaDeLaCompra {
    public static void main(String[] args) {     
        Lista<String> l = new LEGLista<String>();   
        l.insertar("patatas", l.talla());
        l.insertar("cerezas", l.talla());
        l.insertar("leche", l.talla());
        System.out.println("Mi lista de la compra es:\n" + l.toString());        
        System.out.println("He olvidado apuntar el perejil?");
        //Busqueda secuencial de "perejil" en la lista tal que 
        //si no esta se apunta al final de esta
        int i = 0;
        while (i < l.talla() && !l.recuperar(i).equals("perejil")) i++;
        if (i == l.talla()) l.insertar("perejil", l.talla());
        System.out.println("Apuntado perejil en " + i + "-esimo lugar");
    }
}
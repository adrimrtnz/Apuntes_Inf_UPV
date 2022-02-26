package ejemplos.tema1;

import librerias.estructurasDeDatos.modelos.ListaConPI;
import librerias.estructurasDeDatos.lineales.LEGListaConPI;

public class TestListaConPIDeLaCompra {
    public static void main(String[] args){     
        ListaConPI<String> l = new LEGListaConPI<String>();        
        /*l.inicio();*/
        l.insertar("patatas"/*, l.talla()*/);
        l.insertar("cerezas"/*, l.talla()*/);
        l.insertar("leche"/*, l.talla()*/);
        System.out.println("Mi lista de la compra es:\n" + l.toString());        
        System.out.println("He olvidado apuntar el perejil?");
        // Busqueda secuencial de "perejil" en la lista tal que 
        // si no esta se apunta al final de esta        
        l.inicio(); String e = "perejil";
        while (!l.esFin() && !l.recuperar().equals(e)) l.siguiente();
        if (l.esFin()) {
            // MODIFICACION 1: agnadir "perejil" 
            // al principio de la lista, en lugar de al final: 
            l.inicio(); 
            l.insertar(e/*, l.talla()*/);
            System.out.println("Pues si. "
                + "Lo apunto al principio de la lista y arreglado:\n" 
                + l.toString());
        }
        else System.out.println("Pues no ¡Ya esta en la lista!");
        // MODIFICACION 2: agnadir "perejil" antes de "cerezas"
        // Paso previo: eliminarlo de la lista, de la que es el primero
        l.inicio(); l.eliminar();
        System.out.println("Tacho perejil del principio:\n"+l.toString());
        // Ahora se agnade antes que "cerezas": 
        // desplazamos el PI hasta cerezas e insertamos 
        l.inicio(); 
        while(!l.esFin() && !l.recuperar().equals("cerezas")) l.siguiente();
        if (!l.esFin()) {
            l.insertar(e);
            System.out.println("Apunto el perejil antes que las cerezas:\n" 
                + l.toString());
        }
        else {
            l.insertar(e);
            System.out.println("No hay cerezas en la lista!" 
                + "Apunto perejil al final:\n" 
                + l.toString());
        }
    }
}
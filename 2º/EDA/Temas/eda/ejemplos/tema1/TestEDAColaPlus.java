package ejemplos.tema1;

import librerias.estructurasDeDatos.modelos.*; 
import librerias.estructurasDeDatos.lineales.*;

public class TestEDAColaPlus {
    public static void main(String[] args) {
        // modificacion: usar ColaPlus y ArrayColaPlus
        ColaPlus<Integer> q = new ArrayColaPlus<Integer>(); 
    
        // ahora la interfaz incluye el metodo talla, la clase lo implementa
        // y, por tanto, ya no se necesita la variable tallaQ
        
        // modificacion 1
        // int tallaQ = 0;
                                                // modificacion 2
        System.out.println("Creada una Cola con " + q.talla()/*tallaQ*/ 
            + " Integer, q = " + q.toString());
        q.encolar(new Integer(10)); // tallaQ++; // modificacion 3
        q.encolar(new Integer(20)); // tallaQ++; // modificacion 4
        q.encolar(new Integer(30)); // tallaQ++; // modificacion 5
        q.encolar(new Integer(40));
        q.encolar(new Integer(50));
        System.out.println("La Cola de Integer actual es q = " 
            + q.toString());
        System.out.println("Usando otros metodos para mostrar sus Datos el resultado es ... ");
        String datosQ = "";
        while (!q.esVacia()) {
            Integer primero = q.primero(); 
            if (primero.equals(q.desencolar())) datosQ += primero + " "; 
            else datosQ += "ERROR ";
            // tallaQ--; // modificacion 6
        }
        System.out.println(" el mismo, " + datosQ 
            + ", PERO q se vacia, q = " + q.toString());
    }
}
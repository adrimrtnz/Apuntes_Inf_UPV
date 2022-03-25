package ejemplos.tema1;

// modificacion: incluir imports
import librerias.estructurasDeDatos.modelos.*; 
import librerias.estructurasDeDatos.lineales.*;

public class TestEDACola {
    public static void main(String[] args) {
        // modificacion: instanciar cola de enteros
        Cola<Integer> q = new ArrayCola<Integer>(); 
    
        // modificaciones relativas a la talla
        // declarar una variable local, tallaQ, con la misma funcionalidad
        // dado que, en este ejercicio, 
        // no se permiten cambios en Cola ni en ArrayCola
        
        // modificacion 1
        int tallaQ = 0;
                                                // modificacion 2
        System.out.println("Creada una Cola con " + /*q.talla()*/tallaQ 
            + " Integer, q = " + q.toString());
        q.encolar(new Integer(10)); 
        tallaQ++; // modificacion 3
        q.encolar(new Integer(20)); 
        tallaQ++; // modificacion 4
        q.encolar(new Integer(30)); 
        tallaQ++; // modificacion 5
        
        System.out.println("La Cola de Integer actual es q = " + q.toString());
        System.out.println("Usando otros metodos para mostrar sus Datos el resultado es ...");
        String datosQ = "";
        
        while (!q.esVacia()) {
            Integer primero = q.primero(); 
            if (primero.equals(q.desencolar())) datosQ += primero + " "; 
            else datosQ += "ERROR ";
            tallaQ--; // modificacion 6
        }
        System.out.println(" el mismo, " + datosQ 
            + ", PERO q se vacia, q = " + q.toString());
    }
}
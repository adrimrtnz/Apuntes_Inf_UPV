package ejemplos.tema1;

// modificacion: import
import java.util.*;

public class TestEDAColaVDeque {
    public static void main(String[] args) {
        // modificacion: usar Deque y ArrayDeque
        Deque<Integer> q = new ArrayDeque<Integer>();
        System.out.println("Creada una Cola con " 
            + q.size() + " Integer, q = " + q.toString());
        // modificacion: addLast, en lugar de encolar  
        q.addLast(new Integer(10)); 
        q.addLast(new Integer(20)); 
        q.addLast(new Integer(30));
        System.out.println("La Cola de Integer actual es q = " 
            + q.toString());
        System.out.println("Usando otros metodos para mostrar sus Datos el resultado es ...");
        String datosQ = "";
        // modificacion: guarda bucle while, usando size
        while (q.size() != 0) {
            // modificacion: peek, en lugar de primero
            Integer primero = q.peek();
            // modificacion: poll, en lugar de desencolar
            if (primero.equals(q.poll())) datosQ += primero + " "; 
            else datosQ += "ERROR ";
        }
        System.out.println(" el mismo, " + datosQ 
            + ", PERO q se vacía, q = " + q.toString());
    }
}
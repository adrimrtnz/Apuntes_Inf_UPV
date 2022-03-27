package ejemplos.tema4;

import java.util.Scanner; 
import librerias.estructurasDeDatos.modelos.ColaPrioridad;
import librerias.estructurasDeDatos.jerarquicos.MonticuloBinario;

/**
 * class TopKTest.
 * 
 * @author FTG
 * @version 1.0
 */

public class TopKTest {    
    private static Integer[] crearArrayAleatorio(int t) {
        Integer[] a = new Integer[t];
        for (int i = 0; i < a.length; i++) 
            a[i] = (int) Math.floor(Math.random() * a.length); 
        return a;
    }
    
    public static <E extends Comparable<E>> ColaPrioridad<E> cPTopK(
        E[] datos, int k, boolean verbose) 
    {
        ColaPrioridad<E> cP = new MonticuloBinario<E>(k + 2);
        for (int i = 0; i < datos.length; i++) {
            cP.insertar(datos[i]);
            if (verbose) System.out.println(i + "(a): " + cP);
            if (i >= k) { cP.eliminarMin(); }
            if (verbose) System.out.println(i + "(b): " + cP);
        }
        return cP;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in); 
        System.out.println("Escriba el valor de N:");
        int n = Integer.parseInt(in.nextLine());
        System.out.println("Escriba el valor de K:");
        int k = Integer.parseInt(in.nextLine());  
        System.out.println("Escriba el valor de verbose (true / false):");
        String s = in.nextLine();
        boolean verbose = s.equals("t") || s.equals("true");
        System.out.println("...................");
        Integer[] a = crearArrayAleatorio(n);        
        for (int i = 0; i < a.length; i++) {
            System.out.print(a[i] + ", ");
            if ((i + 1) % 20 == 0) System.out.println();
        }
        System.out.println("\n...................");
        ColaPrioridad<Integer> cP = cPTopK(a, k, verbose);
        System.out.println("cP = " + cP);
        System.out.println("...................");
    }
}
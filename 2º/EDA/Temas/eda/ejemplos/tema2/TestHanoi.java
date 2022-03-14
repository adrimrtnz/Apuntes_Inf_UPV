package ejemplos.tema2;

import java.util.Scanner;

/**
 * Write a description of class TestHanoi here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class TestHanoi extends Hanoi
{
    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
        System.out.println("Introduzca el número de discos en la torre origen: ");
        int N = teclado.nextInt();
        
        if (N > 0) {
            hanoi(N, "origen", "auxiliar", "destino");
        }
        else {
            System.out.println("El número de discos debe ser mayor que cero.");
        }
    }

    
}

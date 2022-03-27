package ejemplos.tema2;


/**
 * Write a description of class Hanoi here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Hanoi
{
    // El coste de hanoi es 2^n-1
    static void hanoi(int n, String origen, String auxiliar, String destino) {
        if (n == 1) {
            moverDisco(origen, destino);
        }
        else {
            hanoi(n-1, origen, destino, auxiliar);
            moverDisco(origen, destino);
            hanoi(n-1, auxiliar, origen, destino);
        }
    }
    
    static void moverDisco(String desde, String hasta) {
        System.out.println("Moviendo disco desde torre " + desde +
            " a torre " + hasta + ".");
    }
}

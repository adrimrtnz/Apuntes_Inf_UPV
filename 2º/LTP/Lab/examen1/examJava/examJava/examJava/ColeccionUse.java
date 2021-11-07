
/**
 * class ColeccionUse
 * 
 * @author LTP
 * @version 2021-22
 */

public class ColeccionUse {
    public static void main(String[] args) {
        Coleccion<Integer> vL = new VectorList<Integer>(); 
        Coleccion<Double> pL = new PilaList<Double>();    
        Coleccion<Figure> pF = new FiguresPila<Figure>(); 
        for (int i = 8; i > 0; i--) {
            vL.add(i);
            pL.add(i + 12.0);
        }
        int x = 99;
        double y = (double) x;
        System.out.println("VectorList vL : " + vL.aCadena());
        System.out.print("Pertenecen al Vector? ");
        System.out.print("(8 : " + vL.pertenece(8) + ") " ); 
        System.out.println("(" + x + " : " + vL.pertenece(x) + ")"); 
        pL.remove();
        pL.remove();
        pL.add(y);
        System.out.println("PilaList pL : " + pL.aCadena());
        System.out.print("Pertenecen a la Pila? ");
        System.out.print("(16.0 : " + pL.pertenece(16.0) + ") " ); 
        System.out.println("(" + y + " : " + pL.pertenece(y) + ")"); 
        Pila<Double> pL1 = (Pila<Double>) pL;
        System.out.println("cima : " + pL1.cima());
        System.out.println("desapilar : " + pL1.desapilar());
        System.out.println("cima : " + pL1.cima());
        System.out.println("PilaList pL : " + pL.aCadena());
        System.out.print("Pertenecen a la Pila? ");
        System.out.print("(16.0 : " + pL.pertenece(16.0) + ") " ); 
        System.out.println("(" + y + " : " + pL.pertenece(y) + ")"); 
        pF.add(new Figure(4.0, 6.5));
        pF.add(new Figure(3.5, 8.2));
        System.out.println("FiguresPila pF : " + pF.aCadena());
        FiguresPila pF1 = (FiguresPila) pF;
        System.out.println("x de la cima de pF: " + pF1.getXcima());
   }
}


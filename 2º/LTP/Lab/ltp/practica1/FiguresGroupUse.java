package practica1;


/**
 * class FiguresGroupUse.
 * 
 * @author LTP 
 * @version 2020-21
 */
public class FiguresGroupUse {
    public static void main(String[] args) {
        FiguresGroup g = new FiguresGroup();
        g.add(new Circle(10, 5, 3.5));
        g.add(new Triangle(10, 5, 6.5, 32));
        g.add(new Rectangle(10, 5, 5, 10));
        System.out.println(g);
        
        System.out.printf("Area total figuras: %.2fu\n", g.area());
        System.out.println("La figura más grande es: " +
                            g.greatestFigure());
        
        // FiguresGroup.equals() test
        FiguresGroup g2 = g;
        FiguresGroup g3 = new FiguresGroup();
        System.out.println(g.equals(g2));
        System.out.println(g.equals(g3));
    }
}
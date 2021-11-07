package practica1;


/**
 * class Circle.
 * 
 * @author LTP 
 * @version 2020-21
 */

public class Circle extends Figure {
    private double radius;

    public Circle(double x, double y, double r) {
        // Si se invoca el constructor de la clase base
        // tiene que ser la primera instrucción del cuerpo
        // del constructor de la subclase
        super(x, y);
        radius = r;
    }
    
    public double perimeter() {
        return 2 * Math.PI * radius;
    }
    
    public double area() {
        return Math.PI * radius * radius;
    }
    
    public boolean equals(Object o) {
        if (!(o instanceof Circle)) { return false; }
        
        Circle c = (Circle) o;
        return super.equals(c) &&
            radius == c.radius;
    }
    
    public String toString() {
        return "Circle:\n\t" +
            super.toString() +
            "\n\tRadius: " + radius;
    }
}
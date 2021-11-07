package practica3;

import java.lang.Math.*;

/**
 * Write a description of class Rectangle here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Rectangle extends Figure implements ComparableRange<Figure>
{
    private double base; 
    private double height;

    public Rectangle(double x, double y, double b, double h) {
        super(x, y);
        base = b;
        height = h;
    }
    
    public double area() {
        return base * height;
    }
    
    public boolean equals(Object o) {
        if (!(o instanceof Rectangle)) { return false; }
        
        Rectangle r = (Rectangle) o;
        return super.equals(r) &&
            base == r.base && height == r.height;
    }
    
    public String toString() {
        return "Rectangle:\n\t" +
            super.toString() +
            "\n\tBase: " + base +
            "\n\tHeight: " + height;
    }
    
    public int compareToRange(Figure o) {
        double suma = this.area() + o.area();
        double dif = this.area() - o.area();
       
        
        if (Math.abs(dif /suma) <= 0.10  ) { return 0; }
        
        return this.compareTo(o);
    }
    
    public void print(char c) {
        int b = (int) base;
        int h = (int) height;
        
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < b; j++) {
                System.out.print(c);
            }
            
            System.out.println();
        }
        System.out.println();
    }
}

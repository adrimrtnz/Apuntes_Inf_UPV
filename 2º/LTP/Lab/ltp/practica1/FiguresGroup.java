package practica1;


/**
 * class FiguresGroup.
 * 
 * @author LTP 
 * @version 2020-21
 */

public class FiguresGroup {
    private static final int NUM_FIGURES = 10;
    private Figure[] figuresList = new Figure[NUM_FIGURES];
    private int numF = 0;
    
    public void add(Figure f) { 
        // para crear grupo conjuntos
        // if (figuresList.found(f)) { return; }
        figuresList[numF++] = f; 
    }
    
    public double area() {
        double sum = 0;
        for (int i = 0; i < numF; i++) {
            sum += figuresList[i].area();
        }
        return sum;
    }
    
    public Figure greatestFigure() {
        int index = 0;
        double max = 0;
        for (int i = 0; i < (numF - 1); i++) {
            if (figuresList[i].area() > max) {
                max = figuresList[i].area();
                index = i;
            }
        }
        return figuresList[index];
    }
    
    public String toString() {
        String s = "";
        for (int i = 0; i < numF; i++) {
            s += "\n" + figuresList[i];
        }
        return s;
    }

    private boolean found(Figure f) {
        for (int i = 0; i < numF; i++) {
            if (figuresList[i].equals(f)) return true;
        }
        return false;
    }

    private boolean included(FiguresGroup g) {
        for (int i = 0; i < g.numF; i++) {
            if (!found(g.figuresList[i])) return false;
        }
        return true;
    }
    
    public boolean equals(Object o) {
        if (!(o instanceof FiguresGroup)) { return false; }
        
        FiguresGroup g = (FiguresGroup) o;
        return this.included(g) && g.included(this);
    }
}
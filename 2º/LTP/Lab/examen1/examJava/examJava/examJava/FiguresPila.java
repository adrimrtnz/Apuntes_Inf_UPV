
/**
 * Write a description of class FiguresPila here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class FiguresPila<T> extends PilaList<Figure>
{
    double getXcima() {
        Figure f = (Figure) this.cima();
        return f.x;
    }
}

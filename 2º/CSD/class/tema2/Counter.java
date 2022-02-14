package tema2;


/**
 * Write a description of class Counter here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Counter
{
    private int c = 0;
    
    public synchronized void increment() {
        c++;
    }
    
    public synchronized void decrement() {
        c--;
    }
    
    public synchronized int value() {
        return c;
    }
}

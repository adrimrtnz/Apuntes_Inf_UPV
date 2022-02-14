package tema2;


/**
 * Write a description of class RaceCondition here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class RaceCondition
{
    public static void main(String... args) throws InterruptedException
    {
        Counter c = new Counter();
        final int LOOPS = 1000;
        
        System.out.println("Loops: " + LOOPS);
        
        Incrementer inc1 = new Incrementer(c, 1, LOOPS);
        Incrementer inc2 = new Incrementer(c, 2, LOOPS);
        
        Decrementer dec1 = new Decrementer(c, 1, LOOPS);
        Decrementer dec2 = new Decrementer(c, 2, LOOPS);
        
        inc1.start();
        inc2.start();
        dec1.start();
        dec2.start();
        
        inc1.join();
        inc2.join();
        dec1.join();
        dec2.join();
        
        System.out.println("Final result: " + c.value() );
    }
}

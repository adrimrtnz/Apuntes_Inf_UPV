package tema2;


/**
 * Write a description of class Incrementer here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Incrementer extends Thread
{
    // instance variables - replace the example below with your own
    private Counter c;
    private int myname;
    private int cycles;

    public Incrementer(Counter count, int name, int quantity)
    {
        c = count;
        myname = name;
        cycles = quantity;
    }
    
    public void run()
    {
        for (int i = 0; i < cycles; i++) {
            c.increment();
            
            try {
                sleep( (int) (Math.random() * 1) );
            } catch(InterruptedException e) {}
        }
        
        System.out.println("Incrementer #" + myname + " has done " 
                            + cycles + " increments.");
    }
}

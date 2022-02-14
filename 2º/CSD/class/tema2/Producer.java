package tema2;


/**
 * Write a description of class Producer here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Producer extends Thread
{
    private final int N = 10;
    private Box box;
    private int prodname;
    
    public Producer(Box c, int name) 
    {
        box = c;
        prodname = name;
    }
    
    public void run()
    {
        for (int i = 1; i <= N; i++) {            
            try {
                while(box.isFull()) { Thread.sleep(5); }
                box.put(i);
                System.out.println("Producer #" + prodname + " puts: " + i);
                Thread.sleep( (int) (Math.random() * 100) );
            } catch (InterruptedException e) { }
        }
    }
}

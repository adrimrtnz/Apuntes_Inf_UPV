package tema2;


/**
 * Write a description of class Consumer here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Consumer extends Thread
{
    private final int N = 10;
    private Box box;
    private int cname;
    
    public Consumer(Box c, int name)
    {
        box = c;
        cname = name;
    }
    
    public void run()
    {
        for (int i = 1; i <= N; i++) {
            try {
                while(!box.isFull()) { Thread.sleep(5); }
                int value = box.get();
                System.out.println("Consumer #" + cname + " gets: " + value);
                Thread.sleep( (int) (Math.random() * 100) );
            } catch (InterruptedException e) { }
        } 
    }
}

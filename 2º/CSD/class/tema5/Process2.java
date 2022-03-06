package tema5;

import java.util.concurrent.Semaphore;

/**
 * Write a description of class Process2 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Process2 extends Thread
{
    private int id;
    private Semaphore sem;
    
    public Process2(int i, Semaphore s)
    {
        id = i;
        sem = s;
    }
    
    private void busy()
    {
        try
        {
            sleep(new java.util.Random().nextInt(500));
        } catch (InterruptedException e) {}
    }
    
    private void msg(String s)
    {
        System.out.println("Thread " + id + s);
    }
    
    private void noncritical()
    {
        msg(" is NON critical");
        busy();
    }
    
    private void critical()
    {
        msg(" entering CS");
        busy();
        msg(" leaving CS");
    }
    
    public void run()
    {
        for(int i = 0; i < 2; ++i) 
        {
            noncritical();
            
            try
            {
                sem.acquire();
            } catch(InterruptedException e) {}
            
            critical();
            sem.release();
        }
    }
    
    public static void main(String... args) 
    {
        Semaphore sem = new Semaphore(1, true);
        
        for (int i = 0; i < 4; i++)
        {
            new Process2(i, sem).start();
        }
    }
}

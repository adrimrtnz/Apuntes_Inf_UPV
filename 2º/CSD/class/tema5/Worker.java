package tema5;
import java.util.concurrent.CountDownLatch;


/**
 * Write a description of class Worker here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Worker implements Runnable
{
    private final CountDownLatch startSignal;
    private final CountDownLatch doneSignal;
    
    Worker(CountDownLatch start, CountDownLatch done)
    {
        startSignal = start;
        doneSignal = done;
    }
    
    public void run()
    {
        try 
        {
            startSignal.await();
            doWork();
            doneSignal.countDown();
        } catch(InterruptedException e) { return; }
    }
    
    public void doWork()
    {
        System.out.println("Doing Work.");
    }
}

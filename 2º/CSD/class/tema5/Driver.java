package tema5;
import java.util.concurrent.CountDownLatch;


/**
 * Write a description of class Driver here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Driver
{
    private int N = 10;
    
    void main() throws InterruptedException {
        CountDownLatch startSignal = new CountDownLatch(1);
        CountDownLatch doneSignal = new CountDownLatch(N);
        
        for (int i = 0; i < N; ++i)
        {
            new Thread(new Worker(startSignal, doneSignal)).start();
        }
        
        doSomethingElse();
        startSignal.countDown();
        doSomethingElse();
        doneSignal.await(); // Driver espera a que todos los Worker finalicen su trabajo
    }
    
    void doSomethingElse()
    {
        System.out.println("Doing Something Else.");      
    }
}

package tema2;


/**
 * Write a description of class ProducerConsumer here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ProducerConsumer
{
    public static void main(String... args)
    {
        Box c = new Box();
        Consumer c1 = new Consumer(c, 1);
        Producer p1 = new Producer(c, 1);
        
        c1.start();
        p1.start();
        
        try {
            c1.join();
            p1.join();
        } catch (InterruptedException e) {}
    }
}

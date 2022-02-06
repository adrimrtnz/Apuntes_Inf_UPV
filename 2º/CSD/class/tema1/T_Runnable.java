package tema1;


/**
 * Write a description of class T_Runnable here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class T_Runnable implements Runnable {
    protected int n;
    
    private final int N_ITERATIONS = 10;
    private static final int N_THREADS = 6;
    
    public T_Runnable (int n) {
        this.n = n;
    }
    
    public void delay (int ms) {
    // suspends execution for ms milliseconds
        try {
            Thread.sleep(ms);
        } catch (InterruptedException ie) {
            ie.printStackTrace();
        }
    }
    
    public void run () {
        for (int i = 0; i < N_ITERATIONS; i++) {
            System.out.println("Thread " + n + ", iteration " + i);
            delay((n+1) * 1000);
        }
        
        System.out.println("End of thread " + n);
    }
    
    public static void main (String... argv) {
        System.out.println("--- Begin of execution ---");
        
        for (int i = 0; i < N_THREADS; i++) {
            new Thread(new T_Runnable(i)).start();
        }
        
        System.out.println("--- End of execution ---");
    }
}

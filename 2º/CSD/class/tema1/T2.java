package tema1;


/**
 * Write a description of class T2 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class T2 extends Thread {
    
    private static final int N_THREADS = 3;
    protected int level;
    
    public T2 (int n) {
        this.level = n;
    }
    
    public void createThread(int i) {
        T2 h = new T2(i);
        System.out.println("Thread of level " + i + " created.");

        if (i >= 1) { 
            h.start(); 
            System.out.println("SUBTHREAD of level " + i + " STARTED.");
        }

        
    }
    
    public void run() {
       if (level > 0) {
           System.out.println("Thread of level " + level + " created.");
           createThread(level-1);
       }

       System.out.println("--- End of thread. Level: " + level + " ---");
    }
    
    public static void main(String... argv) {
       for (int i = 1; i < N_THREADS; i++) {
           new T2(2).start();
       }
    }
}

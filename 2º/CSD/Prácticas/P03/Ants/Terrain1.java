
import java.util.concurrent.locks.*;

/**
 * Native monitor based Terrain
 * 
 * @author CSD Juansa Sendra
 * @version 2021
 */
public class Terrain1 implements Terrain {
    Viewer v;
    Lock mutex;
    Condition c;
    
    public  Terrain1 (int t, int ants, int movs, String msg) {
        v = new Viewer(t,ants,movs,msg);
        mutex = new ReentrantLock();
        c = mutex.newCondition();
    }
    
    public void     hi      (int a) {
        try {
            mutex.lock();
            v.hi(a);    
        }
        finally {
            mutex.unlock();
        }
    }
    
    public void     bye     (int a) {
        try {
            mutex.lock();
            c.signalAll();
            v.bye(a); 
        }
        finally {
            mutex.unlock();
        }
    }
    
    public void     move    (int a) throws InterruptedException {
        
        try {
            mutex.lock();
            v.turn(a); 
            Pos dest=v.dest(a); 
            
            while (v.occupied(dest)) {
                try {
                    c.await(); 
                    v.retry(a);
                } catch (InterruptedException e) {}
            }
            
            v.go(a); 
            c.signalAll();
        }
        finally {
            mutex.unlock();
        }
    }
}

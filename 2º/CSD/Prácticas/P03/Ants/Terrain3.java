
import java.util.concurrent.locks.*;
import java.util.concurrent.TimeUnit;

/**
 * Native monitor based Terrain
 * 
 * @author CSD Juansa Sendra
 * @version 2021
 */
public class Terrain3 implements Terrain {
    Viewer v;
    Lock mutex;
    Condition c[][];
    
    public  Terrain3 (int t, int ants, int movs, String msg) {
        v = new Viewer(t,ants,movs,msg);
        mutex = new ReentrantLock();
        c = new Condition[t][t];
        
        for (int i = 0; i < t; i++) {
            for (int j = 0; j < t; j++) {
                c[i][j] = mutex.newCondition();
            }
        }
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
            Pos p = v.getPos(a);
            c[p.x][p.y].signal();
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
            Pos p = v.getPos(a);
            
            while (v.occupied(dest)) {
                if (!c[dest.x][dest.y].await(300, TimeUnit.MILLISECONDS)) {
                    v.chgDir(a);
                    dest = v.dest(a);
                }
                v.retry(a);
            }
            
            v.go(a); 
            c[p.x][p.y].signal();
        }
        finally {
            mutex.unlock();
        }
    }
}

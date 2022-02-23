// CSD feb 2015 Juansa Sendra

public class Pool1 extends Pool {   //no kids alone
    
    public void init(int ki, int cap) { 
        this.nk = 0;
        this.ni = 0;
    }
    
    public synchronized void kidSwims() throws InterruptedException {
        
        while(ni== 0) {
            log.waitingToSwim();
            wait();
        }
        
        nk++;
        log.swimming();
    }
    
    public synchronized void kidRests()      {
        log.resting(); 
        nk--;
        notifyAll();
    }
    
    public synchronized void instructorSwims()   {
        log.swimming();
        ni++;
        notifyAll();
    }
    
    public synchronized void instructorRests() throws InterruptedException {
        
        while(nk != 0 && ni == 1) {
            log.waitingToRest();
            wait();
        }
        
        ni--;
        log.resting(); 
    }
}

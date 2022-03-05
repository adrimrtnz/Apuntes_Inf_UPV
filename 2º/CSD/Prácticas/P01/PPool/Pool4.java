// CSD feb 2013 Juansa Sendra

public class Pool4 extends Pool { //kids cannot enter if there are instructors waiting to exit
    
    private int instructorWaiting;
    
    public void init(int ki, int cap) {
        this.nk = 0;
        this.ni = 0;
        this.ki = ki;
        this.cap = cap;
        instructorWaiting = 0;
    }
    
    public synchronized void kidSwims() throws InterruptedException {
        
        while(ni == 0 || (ni*ki) <= nk || (nk+ni+1) > this.cap || instructorWaiting > 0) {
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
    
    public synchronized void instructorSwims() throws InterruptedException {
        
        while((nk+ni+1) > this.cap) {
            log.waitingToSwim();
            wait();
        }
        
                
        log.swimming();
        ni++;
        notifyAll();
    }
    
    public synchronized void instructorRests() throws InterruptedException {
        
        instructorWaiting++;
        
        while(nk != 0 && ((ni-1)*ki) < nk) {
            log.waitingToRest();
            wait();
        }
        
        instructorWaiting--;
        ni--;
        log.resting(); 
        notifyAll();
    }
}

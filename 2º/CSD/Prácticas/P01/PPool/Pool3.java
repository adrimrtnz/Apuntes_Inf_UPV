// 2022 Adrián Martínez

public class Pool3 extends Pool{ 
    //max capacity
    
      
    public void init(int ki, int cap) {
        this.nk = 0;
        this.ni = 0;
        this.ki = ki;
        this.cap = cap;
    }
    
    public synchronized void kidSwims() throws InterruptedException {
        
        while(ni == 0 || (ni*ki) <= nk || (nk+ni+1) > this.cap) {
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
        
        while(nk != 0 && ((ni-1)*ki) < nk) {
            log.waitingToRest();
            wait();
        }
        
        ni--;
        notifyAll();
        log.resting(); 
    }
}

// CSD feb 2015 Juansa Sendra

public class Pool2 extends Pool{ //max kids/instructor
    public void init(int ki, int cap) {
        this.nk = 0;
        this.ni = 0;
        this.ki = ki;
    }
    
    public synchronized void kidSwims() throws InterruptedException {
        
        while(ni == 0 || (ni*ki) <= nk) {
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
        
        while(nk != 0 && ((ni-1)*ki) < nk) {
            log.waitingToRest();
            wait();
        }
        
        ni--;
        log.resting(); 
    }
}

// CSD Mar 2013 Juansa Sendra

public class LimitedTable extends RegularTable { //max 4 in dinning-room
    
    private final int MAXCAP = 4;
    private int counter = 0;
    
    public LimitedTable(StateManager state) {super(state);}
    
    public synchronized void enter(int id) throws InterruptedException {
        while (counter == MAXCAP)
        {
            state.wenter(id);
            wait();
        }
        state.enter(id);
        counter++;
        // al soltar los palillos se está haciendo el notifyAll() al dejar los palillos.
    }
    
    public synchronized void exit(int id)  {
        counter--;
        notifyAll();    // para no reducir la concurrencia
    }
}

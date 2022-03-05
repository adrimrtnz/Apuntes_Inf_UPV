import java.util.concurrent.Semaphore;

public class MyCondition {
	private MyMonitor mon;
	private Semaphore cond = new Semaphore (0);
	private int nwait = 0;

	public MyCondition (MyMonitor mon) {
		this.mon = mon;
	}

	public void await () throws InterruptedException {
		mon.checkOwner();
		nwait++;
		mon.exitMonitor();
		cond.acquire(); // Can throw InterruptedException
		mon.enterMonitor();
	}

	public void signalAll () {
		mon.checkOwner();
		if (nwait > 0) cond.release (nwait);				
		nwait=0;
	}
}
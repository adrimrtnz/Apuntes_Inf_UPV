import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicReference;
public class MyMonitor {

	private Semaphore mtx = new Semaphore (1);
	private AtomicReference owner = new AtomicReference (null); // reference to Thread.

	public final MyCondition newCondition () {
		return new MyCondition (this);
	}

	void checkOwner () {
		if (!Thread.currentThread().equals (owner.get())) 
			throw new IllegalMonitorStateException();
	}
	void checkNotOwner () {
		if (Thread.currentThread().equals (owner.get())) 
			throw new IllegalMonitorStateException();
	}

	protected void enterMonitor () { 
		checkNotOwner(); 
		mtx.acquireUninterruptibly (); 
		owner.set(Thread.currentThread()); 
	}	
	protected void exitMonitor () { checkOwner(); owner.set(null); mtx.release (); }

	protected void runMonitor ( Runnable r ) {
		enterMonitor ();
		try {
			r.run();
		} finally {
			exitMonitor();
		}
	}

}

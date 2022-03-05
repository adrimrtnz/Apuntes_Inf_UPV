public class Test {
	private static void randomSleep () { // Sleep between 0 to 5 milliseconds.
		try {Thread.sleep (Math.round (Math.random()*5));}catch (InterruptedException e) {}
	}
	public static void main (String [] args) throws InterruptedException {
		Caja caja = new Caja (3);
		Thread p = new Thread ( () -> {
			for (int i=0; i<10; i++) {
				randomSleep();
				caja.put (i);
			}
		});
		Thread c = new Thread ( () -> {
			for (int i=0; i<10; i++) {
				randomSleep();
				System.out.println ("get: " + caja.get () );
			}
		});
		p.start (); c.start();
		p.join(); c.join();
		System.out.println ("bye");
	}
}
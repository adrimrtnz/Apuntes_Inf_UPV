public class Test2 {
	private static void randomSleep () {
		try {Thread.sleep (Math.round (Math.random()*5));}catch (InterruptedException e) {}
	}

	private static void produce (Caja caja, int a, int b) {
		for (int i=a; i<=b; i++) {
			randomSleep();
			caja.put (i);
		}		
	}

	private static void consume (Caja caja, String name, int n) {
		for (int i=0; i<n; i++) {
			randomSleep();
			System.out.println ("get (" + name + "): " + caja.get () );
		}
	}

	public static void main (String [] args) {
		Caja caja = new Caja (3);
		new Thread ( () -> produce (caja, 1,10) ).start();
		new Thread ( () -> produce (caja, 11,20) ).start();
		new Thread ( () -> consume (caja, "A", 10) ).start();
		new Thread ( () -> consume (caja, "B", 10) ).start();
		System.out.println ("bye");		
	}
}
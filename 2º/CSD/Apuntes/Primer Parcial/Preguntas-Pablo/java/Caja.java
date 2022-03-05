public class Caja extends MyMonitor{

	private int elems=0, cabeza=0, cola=0;
 	private int[] datos;
 	private MyCondition cond;

	public Caja (int size) { 
		datos = new int [size]; 
		cond = newCondition ();
	}

	public int get () {
		enterMonitor();

		while (elems==0) {
			System.out.println("consumidor esperando");
			try {cond.await();} catch(InterruptedException e) {}
 		}
		int x=datos[cabeza]; cabeza=(cabeza+1) % datos.length; elems--;

 		cond.signalAll();		
		exitMonitor();
		return x;
	}

	public void put (int x) {
		runMonitor ( () -> {
			while (elems==datos.length) {
				System.out.println("productor esperando");
				try {cond.await();} catch(InterruptedException e) {}
			 }
			 datos[cola]=x; cola=(cola+1)%datos.length; elems++;
			 cond.signalAll();			
		});
	}
}

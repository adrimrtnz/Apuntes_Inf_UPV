package ejemplos.tema3;

public class Par<E> {
    E dato; 
    int frec;
    public Par(E d, int f) { 
        dato = d; frec = f; 
    }
    public String toString() { 
        return (dato.toString() + "-" + frec + " "); 
    }
}
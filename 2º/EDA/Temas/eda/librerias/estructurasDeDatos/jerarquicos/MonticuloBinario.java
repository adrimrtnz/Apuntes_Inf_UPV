package librerias.estructurasDeDatos.jerarquicos; 
import  librerias.estructurasDeDatos.modelos.*; 

public class MonticuloBinario<E extends Comparable<E>> 
    implements ColaPrioridad<E> {
        
    protected static final int C_P_D = 11; 
    protected E[] elArray; 
    protected int talla;
  
    /** crea un Heap vacio */
    public MonticuloBinario() { this(C_P_D); }
    
    /** crea una Cola de Prioridad (CP) vacia con capacidad inicial n */
    @SuppressWarnings("unchecked")
    public MonticuloBinario(int n) { 
        elArray = (E[]) new Comparable[n];
        talla = 0;
    }
  
    /** comprueba si un Heap es vacio en Theta(1) */
    public boolean esVacia() { return talla == 0; }
      
    /** devuelve el minimo de un Heap en Theta(1) */
    public E recuperarMin() { return elArray[1]; }

    /** inserta e en un Heap */
    public void insertar(E e) {
        if (talla == elArray.length - 1) duplicarArray();
        // PASO 1. Buscar la posicion de insercion ordenada de e
        // (a) Preservar la Propiedad Estructural
        int posIns = ++talla; 
        
        // (b) Preservar la Propiedad de Orden: reflotar 
        posIns = reflotar(e, posIns); 
        /*
        while (posIns > 1 && e.compareTo(elArray[posIns / 2]) < 0) { 
            elArray[posIns] = elArray[posIns / 2]; 
            posIns = posIns / 2;
        }
        */
        // PASO 2. Insertar e en su posicion de insercion ordenada
        elArray[posIns] = e;
    }
	
	protected int reflotar(E e, int posIns) {
        while (posIns > 1 && e.compareTo(elArray[posIns / 2]) < 0) { 
            elArray[posIns] = elArray[posIns / 2]; 
            posIns = posIns / 2;
        }
        return posIns;
    }

    @SuppressWarnings("unchecked")
    protected void duplicarArray() {
        E[] nuevo = (E[]) new Comparable[elArray.length * 2];
        System.arraycopy(elArray, 1, nuevo, 1, talla);
        elArray = nuevo;
    }  
  
    /** recupera y elimina el minimo de un Heap */
    public E eliminarMin() {
        E elMinimo = elArray[1];
        // PASO 1. Borrar el minimo del Heap
        // (a) Preservar la Propiedad Estructural: 
        //     borrar Por Niveles el minimo
        elArray[1] = elArray[talla--];
        // (b) Preservar la Propiedad de Orden:
        //     buscar la posicion de insercion ordenada de elArray[1] 
        // PASO 2. Insertar elArray[1] en su posicion ordenada
        hundir(1); 
        return elMinimo;
    }
  
    protected void hundir(int pos) {
        int posActual = pos; 
        E aHundir = elArray[posActual]; 
        int hijo = posActual * 2; 
        boolean esHeap = false; 
        while (hijo <= talla && !esHeap) {
            if (hijo < talla && 
                elArray[hijo + 1].compareTo(elArray[hijo]) < 0) {
                hijo++;
            }
            if (elArray[hijo].compareTo(aHundir) < 0) {
                elArray[posActual] = elArray[hijo];
                posActual = hijo;  
                hijo = posActual * 2; 
            } 
            else { esHeap = true; }
        }
        elArray[posActual] = aHundir;
    }

    /** obtiene un String con los datos de una CP ordenados Por Niveles 
     *  y con el formato que se usa en el estandar de Java (entre corchetes
     *  cuadrados y separando cada elemento del anterior mediante una coma 
     *  seguida de un espacio en blanco); si la CP esta vacia el String 
     *  resultado es []
     */
    public String toString() { 
      // NOTA: se usa la clase StringBuilder, en lugar de String, 
      // por motivos de eficiencia
        StringBuilder res = new StringBuilder();
        if (talla == 0) return res.append("[]").toString();
        int i = 1;
        res.append("[");
        while (i < talla) res.append(elArray[i++] + ", ");
        res.append(elArray[i].toString() + "]"); 
        return res.toString();
    }
    
    /** devuelve el numero de hojas de un Heap en Theta(1) */
    public int contarHojas() { 
        return talla - (talla / 2);
    }
    
    /** devuelve el maximo de un Heap tras talla/2 compareTo */
    public E recuperarMax() { 
        int pos = talla / 2 + 1;
        E max = elArray[pos];
        while (pos <= talla) {
            if (elArray[pos].compareTo(max) > 0) {
                max = elArray[pos];
            } 
            pos++;
        }
        return max;
    }
    
    public void introducir(E e) {
        if (talla == elArray.length - 1) { duplicarArray(); }
        elArray[++talla] = e;
    }
    
    public void arreglar() { arreglar(1); }
    
    protected void arreglar(int i) {
        if  (i <= talla / 2) { //si no es una Hoja
            if (2 * i <= talla) { arreglar(2 * i); }
            if (2 * i + 1 <= talla) { arreglar(2 * i + 1); } 
            hundir(i); 
        }
    }
    
    /*  Restablece la propiedad de orden de un Heap */ 
    //  hunde Por-Niveles y Descendente los nodos Internos 
    //  de elArray, pues las Hojas ya son Heaps
    public void arreglarIterativo() {
        for (int i = talla / 2; i > 0; i--) {
            hundir(i);
        }
    } 

}
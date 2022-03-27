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
    
    
    /**
     * Ejercicio 5: Implementar un método de instancia, hayMenoresQue que,
     * en tiempo constante, compruebe si existen elementos menores que e
     * en el montículo.
     */
    
    public boolean hayMenoresQue(E e) {
        if (talla == 0) { return false; }
        return elArray[1].compareTo(e) < 0; 
    }
    
    /**
     * Ejercicio 6: Implementar un método de instancia hayMayoresQue, que
     * comprueba si existen elementos mayores que e en el montículo.
     */
    public boolean hayMayoresQue(E e) {
        int pos1aHoja = talla / 2 + 1;
        
        for (int i = pos1aHoja; i <= talla; i++) {
            if (elArray[i].compareTo(e) > 0) { return true; }
        }
        
        return false;
    }
    
    /**
     * Ejercicio 7: Implementar un método de instancia, estaEn que compruebe
     * si el elemento e está en el montículo
     */
    public boolean estaEn(E e) {
        // NOTA: importante recordar que en el montículo
        // la pos 0 NO se gasta
        return estaEn(e, 1);
    }
    
    private boolean estaEn(E e, int i) {
        if ( i > talla || elArray[i].compareTo(e) > 0) { 
            return false; 
        }
        if (elArray[i].compareTo(e) == 0) {
            return true;
        }
        
        return estaEn(e, i*2) || estaEn(e, i*2 + 1);
    }
    
    /**
     * Ejercicio 8: Implementar un método de instancia, borrarHojasEnRango
     * que borre hojas del montículo que están dentro del rango genérico
     * y no vacío.
     */
    public void borrarHojasEnRango(E x, E y) {
        // PASO 1: Recorrer SOLO las hojas del Heap,
        // borrar por niveles las que están en [x, y]
        int n = talla;
        for (int i = n; i > n/2; i--) {
            if (elArray[i].compareTo(x) >= 0 && elArray[i].compareTo(y) <= 0) {
                if (i < talla) { elArray[i] = elArray[talla]; }
                talla--;
            }
        }
        
        // PASO 2: ¿Es Heap tras borrar las hojas en [x,y]?
        // Si no lo es, "arreglar" el Array
        arreglar();
    }
    
    
    /**
     * Ejercicio 9:
     */
    public E eliminar(int k) {
        E aux = elArray[k];
        elArray[k] = elArray[talla--];
        
        /* OPCIÓN MENOS EFICIENTE
        arreglar();
        */
       
        int pos = k;
        E compK = elArray[k];
        pos = reflotar(compK, pos);
        elArray[pos] = compK;
        
        if (pos == k) { hundir(pos); }
        return aux;
    }
    
    /**
     * Ejercicio 10:
     */
    public int igualesAlMinimo() {
        return igualesAlMinimo(1);
    }
    
    private int igualesAlMinimo(int i) {
        if (i > talla || elArray[i].compareTo(elArray[1]) > 0) { return 0; }
        else if (elArray[i].compareTo(elArray[1]) == 0) { 
            return 1 + igualesAlMinimo(i*2) + igualesAlMinimo(i*2 + 1); 
        }
        return 0 + igualesAlMinimo(i*2) + igualesAlMinimo(i*2 + 1);
    }
    
    
    /**
     * Ejercicio 11: Diseñar un método (estático) esHeap que con el menor coste
     * posible, compruebe si un array v es un Heap
     */
    public static <E extends Comparable<E>> boolean esHeap(E[] v) {
        
        // Empieza a comprobar por las hojas, no por las raíz
        int n = v.length - 1;
        for(int i = n; i > 1; i--) {
            if (v[i/2].compareTo(v[i]) > 0) { return false; }
        }
        
        return true;
    }
    
    /**
     * Ejercicio 12:
     */
    public int menoresQue(E e) {
        return menoresQue(e, 1);
    }
    
    private int menoresQue(E e, int i) {
        if (i > talla || elArray[i].compareTo(e) >= 0) { return 0; }
        
        return 1 + 
            menoresQue(e, i*2) + 
            menoresQue(e, i*2 + 1);
    }
    
    /**
     * Ejercicio 13:
     */
    public E eliminar1aHoja() {
        int primeraHoja = talla / 2 + 1;
        return eliminar(primeraHoja);
    }
    
    /**
     * Ejercicio 14: Diseñar un método estático, genérico e 
     * iterativo heapSort que ordene ascendentemente un array v
     * usando un montículo (diferente a cPSort()
     */
    public static <E extends Comparable<E>> void heapSort(E[] v) {
        /* // Esto es cPSort
        ColaPrioridad<E> aux = new MonticuloBinario<>(v.length + 1);
        
        for (int i = 0; i < v.length; i++) {
            aux.insertar(v[i]);
        }
        
        for (int i = 0; i < v.length; i++) {
            v[i] = aux.eliminarMin();
        }
        */
       
       for (int i = v.length / 2; i >= 0; i--) {
           hundirMax(v, i, v.length);
       }
    }
}
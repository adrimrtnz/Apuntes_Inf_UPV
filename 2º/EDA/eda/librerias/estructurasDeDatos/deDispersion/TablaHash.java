package librerias.estructurasDeDatos.deDispersion;

import librerias.estructurasDeDatos.modelos.Map;
import librerias.estructurasDeDatos.modelos.ListaConPI; 
import librerias.estructurasDeDatos.lineales.LEGListaConPI;

/**
 * TablaHash: implementacion de una Tabla Hash Enlazada 
 * en la que sus cubetas, o listas de colisiones, se
 * representan tallasnte Listas con PI de EntradaHash<C, V>
 * 
 * @param <C>  tipo de las Claves del Map que implementa
 * @param <V>  tipo de Valores del Map que implementa
 * 
 * @author (EDA-QA) 
 * @version (Curso 2021-2022)
 */

public class TablaHash<C, V> implements Map<C, V> {
    
    // Una Tabla Hash TIENE:
    
    // UNA CTE JAVA que representa...
    /** El valor (float) del factor de carga estandar (por defecto) de una  
     *  Tabla Hash, el mismo que se usa en la clase java.util.HashMap) */
    public static final double FACTOR_DE_CARGA = 0.75;
    
    // UNA CTE JAVA que representa...
    /** El valor (boolean) que indica si una Tabla Hash realiza 
     *  Rehashing cuando su factor de carga supera FC_ESTANDAR
     */
    public static final boolean REHASHING = false; // en Parte 1 vale false;
    
    // UN array de Listas Con PI de EntradaHash<C, V> elArray:
    // - elArray[h] representa una cubeta, o lista de    
    //   colisiones asociadas al indice Hash h
    // - elArray[h] contiene la referencia a la Lista     
    //   Con PI donde se encuentran todas las Entradas  
    //   cuya Clave tiene un indice Hash h 
    protected ListaConPI<EntradaHash<C, V>>[] elArray;
    
    // UNA talla que representa el numero de Entradas  
    // almacenadas en una Tabla Hash o, equivalentemente, 
    // en sus cubetas
    protected int talla; 
    
    // UN numero de operaciones de Rehashing (int) efectuadas
    // para mejorar el tiempo promedio que tardan en localizarse
    // las claves de sus talla Entradas
    private int numRH;
    
    
    // UN metodo indiceHash que representa la funcion de 
    // Dispersion de la Tabla
    //**SIN ESTE METODO NO SE TIENE UNA TABLA HASH, SOLO UN ARRAY**
    // Devuelve el indice Hash de la Clave c de una Entrada, 
    // i.e. la posicion de la cubeta en la que la que se ubica  
    // la Entrada de Clave c
    protected int indiceHash(C c) {
        int indiceHash = c.hashCode() % elArray.length;
        if (indiceHash < 0) { indiceHash += elArray.length; }
        return indiceHash;
    }
    
    /** Crea una Tabla Hash vacia, con tallaMaximaEstimada  
     *  Entradas y factor de carga 0.75 */
    @SuppressWarnings("unchecked") 
    public TablaHash(int tallaMaximaEstimada) {
        int n = (int) (tallaMaximaEstimada / FACTOR_DE_CARGA);
        int capacidad = siguientePrimo(n);
        elArray = new LEGListaConPI[capacidad];
        for (int i = 0; i < elArray.length; i++) {
            elArray[i] = new LEGListaConPI<EntradaHash<C, V>>();
        }
        talla = 0;
        numRH = 0;
    }
    // Devuelve un numero primo MAYOR o IGUAL a n, 
    // i.e. el primo que sigue a n
    public static final int siguientePrimo(int n) {
        if (n % 2 == 0) n++;
        for (; !esPrimo(n); n += 2); 
        return n;
    } 
    // Comprueba si n es un numero primo
    protected static final boolean esPrimo(int n) {
        for (int i = 3; i * i <= n; i += 2) 
            if (n % i == 0) return false; // n NO es primo
        return true; // n SI es primo
    }    
    
    /** Comprueba si una Tabla Hash esta vacia,  
     *  i.e. si tiene 0 Entradas */
    public boolean esVacio() { return talla == 0; }
    
    /** Devuelve la talla, o numero de Entradas, 
      * de una Tabla Hash */
    public int talla() { return talla; } 
    
    /** Devuelve el numero de operaciones de Rehashing que, 
      *  en su caso, se hayan efectuado para crear una 
      *  Tabla Hash */
    public int numeroDeRH() { return numRH; } 

    
    private ListaConPI<EntradaHash<C, V>> localizar(C c) {
        int pos = indiceHash(c);
        ListaConPI<EntradaHash<C, V>> cubeta = elArray[pos];
        for (cubeta.inicio(); 
             !cubeta.esFin() && !cubeta.recuperar().clave.equals(c); 
             cubeta.siguiente());
        return cubeta;
    }
        
    /** Devuelve el valor de la Entrada con Clave c de una 
     *  Tabla Hash, o null si tal entrada no esta en la Tabla */
    public V recuperar(C c) {
        V valor = null;
        // Busqueda en cubeta de la Entrada de clave c cuyo valor se quiere recuperar 
        ListaConPI<EntradaHash<C, V>> cubeta = localizar(c);
        // Resolucion de la Busqueda: SII esta la Entrada se recupera su valor
        if (!cubeta.esFin()) { valor = cubeta.recuperar().valor; }
        return valor;
    }
    
    /** Elimina la Entrada con Clave c de una Tabla Hash y 
     *  devuelve su valor asociado, o null si tal entrada 
     *  no esta en la Tabla */
    public V eliminar(C c) {
        V valor = null;
        // Busqueda en cubeta de la Entrada de clave c a eliminar
        ListaConPI<EntradaHash<C, V>> cubeta = localizar(c);
        // Resolucion de la Busqueda: 
        // SII esta la Entrada se elimina, tras recuperar su valor
        if (!cubeta.esFin()) {
            valor = cubeta.recuperar().valor;
            cubeta.eliminar();
            talla--;
        }
        return valor;
    }
        
    /** Inserta la Entrada (c, v) en una Tabla Hash y   
     *  devuelve el antiguo valor asociado a c, o null 
     *  si tal entrada no esta en la Tabla */
    // Invoca al metodo rehashing() SII
    // - El valor de la constante REHASHING es true
    // AND
    // - TRAS insertar una nueva Entrada en su  
    //   correspondiente cubeta e incrementar la 
    //   talla de la Tabla, factorCarga() > FACTOR_DE_CARGA
    public V insertar(C c, V v) {
        V antiguoValor = null;
        // Busqueda en cubeta de la Entrada de clave c 
        ListaConPI<EntradaHash<C, V>> cubeta = localizar(c);
        // Resolucion de la busqueda: 
        // si la Entrada (c, v) ya existe se actualiza su valor, y sino se inserta
        if (cubeta.esFin()) { 
            // si no esta, insercion efectiva de la Entrada (c, v)
            cubeta.insertar(new EntradaHash<C, V>(c, v));
            talla++;
                       
            if (factorCarga() > FACTOR_DE_CARGA && REHASHING) { 
                numRH++;
                rehashing(); 
            }            
        }
        else { 
            // si ya esta, actualizar (el valor de la) Entrada y retornar el antiguo
            antiguoValor = cubeta.recuperar().valor;
            cubeta.recuperar().valor = v; 
        }
        return antiguoValor;
    }
    
    // Metodo que implementa el Rehashing. Por motivos obvios, NO se 
    // debe re-inicializar el atributo numRH
    // PERO... OJO!! Para tener en cuenta el coste de las operaciones de 
    // rehashing en el tiempo que, en promedio, tarda en localizarse
    // una de las talla Entradas de una Tabla, el atributo numColisiones
    // TAMPOCO se debe re-inicializar en este metodo
    //
    @SuppressWarnings("unchecked")
    protected final void rehashing() {
        int nextCapacity = 0;
        ListaConPI<EntradaHash<C, V>>[] aux = elArray;
        elArray = new LEGListaConPI[siguientePrimo(elArray.length * 2)];
        
        for (int i = 0; i < elArray.length; i++) {
            elArray[i] = new LEGListaConPI<>();
        }
        
        for (ListaConPI<EntradaHash<C,V>> lista : aux) {
            for(lista.inicio(); !lista.esFin(); lista.siguiente()) {
                EntradaHash<C,V> elemento = lista.recuperar();
                elArray[indiceHash(elemento.clave)].insertar(
                    new EntradaHash<C,V>(elemento.clave, elemento.valor)
                    );
            }
        }
    }
    
    /** Devuelve una ListaConPI con las talla() claves  
     *  de una Tabla Hash */
    public ListaConPI<C> claves() {
        ListaConPI<C> l = new LEGListaConPI<C>();
        for (int i = 0; i < elArray.length; i++) 
            for (elArray[i].inicio(); !elArray[i].esFin(); elArray[i].siguiente()) 
                 l.insertar( elArray[i].recuperar().clave); 
        return l;
    }
    
    /** Devuelve el factor de carga (real) de una Tabla Hash,   
     *  lo que equivale a la longitud tallas de sus cubetas en  
     *  una implemetacion Enlazada de la Tabla */
    public final double factorCarga() { 
        return (double) talla / elArray.length; 
    }
    
    /** Devuelve un String con las Entradas de una Tabla Hash
     *  en un formato texto dado (ver toString de EntradaHash)
     */
    // RECUERDA: usa la clase StringBuilder por eficiencia
    public final String toString() {
        StringBuilder res = new StringBuilder();
        for (ListaConPI<EntradaHash<C, V>> cubeta : elArray) 
            for (cubeta.inicio(); !cubeta.esFin(); cubeta.siguiente()) 
                res.append(cubeta.recuperar() + "\n"); 
        return res.toString(); 
    }
    
    // Metodos para el analisis de la eficiencia de una 
    // Tabla Hash Enlazada, NO de un Map!!
    
    /** Devuelve la desviacion tipica de las longitudes de las 
     *  cubetas de una Tabla Hash Enlazada */
    public final double desviacionTipica() {
        double[] tallas = new double [elArray.length];
        double m = .0;
        double sum = .0;
    
        for (int i = 0; i < elArray.length; i++) {
            tallas[i] = elArray[i].talla();
            m += tallas[i];
        }
        
        m = m / elArray.length;
        
        for (int i = 0; i < elArray.length; i++) {
            sum += Math.pow(tallas[i] - m, 2);
        }

        return Math.sqrt(sum / elArray.length);
        
    }
    
    /** Devuelve el coste promedio de localizar
     *  una clave de una Tabla Hash Enlazada, 
     *  calculado a partir del numero de 
     *  colisiones que se producen al localizar 
     *  sus this.talla claves
     */
    public final double costeMLocalizar() {
        
        double out = .0;
        
        for(ListaConPI<EntradaHash<C,V>> cubeta : elArray) {
            out += (cubeta.talla() * (cubeta.talla() - 1)) / 2;
        }
        
        return out / talla;
        
    }

    /** Devuelve un String con el histograma de ocupacion 
     *  de una Tabla Hash Enlazada en formato texto. Asi, 
     *  en cada una de sus lineas deben aparecer dos valores 
     *  enteros separados por un tabulador: una longitud de 
     *  cubeta (valor int en el intervalo [0, 9]) y un numero 
     *  de cubetas. 
     *  MUY IMPORTANTE: el numero de cubetas que aparece en
     *  la linea i, ES: 
     ** (a) Si i en [0, 8], el numero de cubetas de la Tabla  
     **     que tienen una longitud i
     ** (b) Si i = 9 (ultima linea), el numero de cubetas de 
     **     la Tabla que tienen una longitud 9 o MAYOR
     */      
    public String histograma() {
        String res = "";
        int[] histo = new int[10];
        for (int i = 0; i < elArray.length; i++) {
            int longCubeta = elArray[i].talla();
            if (longCubeta < 9) { histo[longCubeta]++; }
            else { histo[9]++; }
        }
        for (int i = 0; i < histo.length; i++) {
            res += i + "\t" + histo[i] + "\n";
        }        
        return res;        
    }
    
    /**
     * Ejercicio Examen Lab1
     */
    public ListaConPI<C> clavesColisionadas() {
        ListaConPI<C> c = claves();
        ListaConPI<C> res = new LEGListaConPI();
        
        for(ListaConPI<EntradaHash<C, V>> cubeta: elArray){
            //Si la talla de la cubeta>1 se ha producido colision
            if (cubeta.talla()>1){
                for (cubeta.inicio(), cubeta.siguiente();!cubeta.esFin();cubeta.siguiente()){
                    res.insertar(cubeta.recuperar().clave);
                }
            }
        }
        return res;
    }
    
    public static void main(String[] args) {
        TablaHash<Integer,Integer> tabla = new TablaHash(8);
        for(int i=0;i<20;i++){
            tabla.insertar(i,i);
        }
        ListaConPI<Integer> colisionadas = tabla.clavesColisionadas();
        StringBuilder str = new StringBuilder();
        for (colisionadas.inicio(); !colisionadas.esFin(); colisionadas.siguiente())
            str.append(colisionadas.recuperar()+" ");
        System.out.println("Claves colisionadas: "+str.toString());
    }

}
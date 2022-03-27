package ejemplos.tema4;

import librerias.estructurasDeDatos.modelos.ColaPrioridad;
import librerias.estructurasDeDatos.jerarquicos.MonticuloBinario;
import librerias.estructurasDeDatos.modelos.ListaConPI;
import librerias.estructurasDeDatos.lineales.LEGListaConPI;

/**
 * class UsosColaPrioridad.
 * 
 * @author FTG 
 * @version 1.0
 */

public class UsosColaPrioridad {
    
    /** Problema 1: 
     *  Disenyar un metodo estatico e iterativo cPSort 
     *  que, con la ayuda de una Cola de Prioridad, 
     *  ordene un array v de elementos Comparable. 
     */
    public static <E extends Comparable<E>> void cPSort(E[] v) {
        
        // NOTA: En esta implementación la pos 0 del Montículo no se gasta
        ColaPrioridad<E> cP = new MonticuloBinario<>(v.length + 1); 
        
        for (int i = 0; i < v.length; i++) {
            cP.insertar(v[i]);
        }
        
        for (int i = 0; i < v.length; i++) {
            v[i] = cP.eliminarMin();
        }
    }
    
    /** Problema 2:
     *  Disenyar un metodo estatico, generico e iterativo cPFusionar 
     *  que devuelva una ListaConPI con los datos de 2 Colas de Prioridad dadas, 
     *  cP1 y cP2, ordenados ascendentemente. 
     *  El metodo no puede usar ninguna EDA auxiliar para calcular su resultado 
     *  y, ademas, cP1 y cP2 deben quedar vacias al concluir su ejecucion.
     */
    public static <E extends Comparable<E>> ListaConPI<E> cPFusionar(
        ColaPrioridad<E> cP1, ColaPrioridad<E> cP2) 
    {
        ListaConPI<E> res = new LEGListaConPI<>();
        
        while (!cP1.esVacia() && !cP1.esVacia()) {
            if (cP1.recuperarMin().compareTo(cP1.recuperarMin()) < 0) {
                res.insertar(cP1.eliminarMin());
            }
            else {
                res.insertar(cP2.eliminarMin());
            }
        }
        
        while(!cP1.esVacia()) { res.insertar(cP1.eliminarMin()); }
        while(!cP2.esVacia()) { res.insertar(cP2.eliminarMin()); }
        
        return res;
    }
    
    /** Problema 3:
     *  Disenyar un metodo estatico e iterativo cPEsLineal 
     *  que determine si un conjunto de valores reales se ajusta (aprox.) 
     *  a una funcion lineal creciente usando el siguiente algoritmo: 
     *  comprobar si la diferencia entre todo par de valores consecutivos, 
     *  en orden ascendente, esta acotada por un epsilon dado. 
     */
    public static boolean cPEsLineal(ColaPrioridad<Double> cP, double epsilon) {
        
        double a = cP.eliminarMin();
        
        while (!cP.esVacia()) {
            double b = cP.eliminarMin();
            if (b - a > epsilon) { return false; }
            a = b;
        }
        
        return true;
    }
    
    /** Problema 4:
     *  Disenyar un metodo estatico, generico e iterativo cPTopK 
     *  que, dado un array de datos v y un entero k, 
     *  devuelva una Cola de Prioridad con los k mejores (Top K) datos de v. 
     *  El metodo debe tener un coste O(X log k), siendo X la longitud de v.
     */
    public static <E extends Comparable<E>> ColaPrioridad<E> cPTopK(
        E[] v, int k) 
    {
        // la pos 0 no se gasta y una se va a poner y eliminar
        ColaPrioridad<E> cP = new MonticuloBinario<E>(k + 2);
        
        for (int i = 0; i < v.length; i++) {
            cP.insertar(v[i]);
            if (i >= k) { cP.eliminarMin(); }
        }
        return cP;
    }
    
}
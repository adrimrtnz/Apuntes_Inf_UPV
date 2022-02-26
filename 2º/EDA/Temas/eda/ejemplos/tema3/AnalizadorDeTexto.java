package ejemplos.tema3;

import librerias.estructurasDeDatos.modelos.*; 
import librerias.estructurasDeDatos.deDispersion.*; 

public class AnalizadorDeTexto {

    protected Map<String, Integer> m;
    
    /** construye un Analizador del Texto t, considerando que   
     *  el separador de sus palabras es el espacio en blanco
     */
    public AnalizadorDeTexto(String t) {
        String[] palabras = t.split(" +");
        m = new TablaHash<String, Integer>(palabras.length);
        for (int i = 0; i < palabras.length; i++) { 
            String pal = palabras[i].toLowerCase();
            Integer frec = m.recuperar(pal); 
            if (frec != null) {
               frec++;
               m.insertar(pal, frec); 
            }
            else { m.insertar(pal, 1); }
        }
    }
    
    /** devuelve el nº de palabras con frecuencia de aparición mayor   
     *  que n que aparecen en el texto tratado por un Analizador.   
     *  Así, por ejemplo, si n=0 devuelve el número de palabras distintas  
     *  que aparecen en el texto; si n=1 devuelve el número de palabras  
     *  repetidas que tiene el texto, etc.
     */
    public int frecuenciaMayorQue(int n) {
        // COMPLETAR 
    }  
}
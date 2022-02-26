package ejemplos.tema3;

import librerias.estructurasDeDatos.modelos.Map;
import librerias.estructurasDeDatos.deDispersion.TablaHash;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

/**
 * Traduccion Bilingue, Palabra a Palabra, de un texto.
 * Dos metodos:
 *  1.- cargarDiccionario: 
 *      del fichero de texto "diccioSpaEng.txt" ubicado en el proyecto eda
 *  2.- traducir: 
 *      traduce la frase textoE palabra a palabra consultando el diccionario d. 
 *      Cuando el diccionario d no contenga 
 *      la traduccion para una palabra de textoE, 
 *      el String resultado de traducir debe contener el literal "<error>"  
 *      en lugar de su traduccion
 */

public class Test5Map {
    
    public static Map<String, String> cargarDiccionario() {
        String nombreDic = "diccioSpaEng.txt";
        Map<String, String> m = new TablaHash<String, String>(100);
        try { 
            Scanner ft = new Scanner(new File(nombreDic), "ISO-8859-1");
            while (ft.hasNextLine()) {
                String linea = ft.nextLine();
                String[] a = linea.split("\t");
                m.insertar(a[0], a[1]);
            }
            ft.close();
            return m;
        } 
        catch (FileNotFoundException e) {
            System.out.println("** Error: No se encuentra el fichero " 
                + nombreDic);
            return null;
        }
    }
    
    public static String traducir(String textoE, Map<String, String> d) {
        //COMPLETAR
    }          
}
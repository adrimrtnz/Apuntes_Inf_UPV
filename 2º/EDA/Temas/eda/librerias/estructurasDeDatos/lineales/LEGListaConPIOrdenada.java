package librerias.estructurasDeDatos.lineales;

/**
 * Write a description of class LEGListaConPIOrdenada here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class LEGListaConPIOrdenada<E extends Comparable<E>> extends LEGListaConPI<E>
{
    @Override
    public void insertar(E e) {
        inicio();
        while(!esFin() && e.compareTo(recuperar()) > 0) {
            siguiente();
        }
        super.insertar(e);
    }
}
